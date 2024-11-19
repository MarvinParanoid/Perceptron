#include "DatasetReader.h"
#include "Network.h"
#include "Render.h"
#include <chrono>
#include <iostream>

constexpr uint32_t epoch = 20;
constexpr uint32_t learning_samples = 60000;
constexpr uint32_t training_samples = 10000;
constexpr uint32_t lfirst = DatasetReader::IMG_SIZE;
constexpr uint32_t llast = 10;

void learning() {
    const auto start{std::chrono::steady_clock::now()};
    Network net({lfirst, 128, llast});
    sf::Event event{};
    Data data{&net.GetFirstLayer(), &net.GetLastLayer()};
    Render render(&data);
    bool paused = false;

    for (uint32_t i = 0; i < epoch; i++) {
        uint32_t ar = 0;
        DatasetReader dr("../resources/mnist/train-images.idx3-ubyte", "../resources/mnist/train-labels.idx1-ubyte");
        for (uint32_t j = 0; j < learning_samples; j++) {
            while (render.window().pollEvent(event) || paused) {
                if (event.type == sf::Event::Closed) {
                    render.window().close();
                } else if (event.type == sf::Event::KeyPressed) {
                    paused = true;
                } else if (event.type == sf::Event::KeyReleased) {
                    paused = false;
                }
            }
            dr.ReadNext(net.GetFirstLayer(), data.expected);
            data.predicted = net.ForwardFeed();
            if (data.predicted != data.expected) {
                net.BackPropagation(data.expected);
                //net.WeightsUpdater(0.15 * exp(-j / 20.));
                net.WeightsUpdater(0.5);
            } else {
                ar++;
            }
            render.render();
        }
        std::cout << "Epoch: " << i << "; Accuracy rate: " << (static_cast<double>(ar) / learning_samples) * 100.0 <<
                "\n";
    }
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "Training time: " << elapsed_seconds << "\n";
    net.StoreWeights();
}

void testing() {
    const auto start{std::chrono::steady_clock::now()};
    DatasetReader dr("../resources/mnist/t10k-images.idx3-ubyte", "../resources/mnist/t10k-labels.idx1-ubyte");
    Network net;
    net.LoadWeights();
    sf::Event event{};
    Data data{&net.GetFirstLayer(), &net.GetLastLayer()};
    Render render(&data);
    bool paused = false;
    uint32_t ar = 0;
    for (uint32_t i = 0; i < training_samples && render.window().isOpen(); i++) {
        while (render.window().pollEvent(event) || paused) {
            if (event.type == sf::Event::Closed) {
                render.window().close();
            } else if (event.type == sf::Event::KeyPressed) {
                paused = true;
            } else if (event.type == sf::Event::KeyReleased) {
                paused = false;
            }
        }
        dr.ReadNext(net.GetFirstLayer(), data.expected);
        data.predicted = net.ForwardFeed();
        if (data.predicted == data.expected) {
            ar++;
        }
        render.render();
    }
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "Testing time: " << elapsed_seconds << "\n";
    std::cout << "Accuracy rate: " << (static_cast<double>(ar) / training_samples) * 100.0 << "\n";
}

int main() {
    learning();
    testing();
    return 0;
}
