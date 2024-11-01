#include "DatasetReader.h"
#include "Network.h"
#include "Render.h"
#include <cmath>
#include <iostream>

constexpr uint32_t epoch = 10;
constexpr uint32_t learning_samples = 60000;
constexpr uint32_t training_samples = 10000;
constexpr uint32_t lfirst = DatasetReader::IMG_SIZE;
constexpr uint32_t llast = 10;
constexpr uint32_t hidden = 128;

void learning() {
    DatasetReader dr("../mnist/train-images.idx3-ubyte", "../mnist/train-labels.idx1-ubyte");
    Network net({lfirst, hidden, llast});

    sf::Event event{};
    Data data{&net.GetFirstLayer(), &net.GetLastLayer()};
    Render render(&data);
    bool paused = false;
    for (uint32_t i = 0; i < learning_samples && render.window().isOpen(); i++) {
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

        for (uint32_t j = 0; j < epoch; j++) {
            data.predicted = net.ForwardFeed();
            if (data.predicted != data.expected) {
                net.BackPropagation(data.expected);
                //net.WeightsUpdater(0.15 * exp(-j / 20.));
                net.WeightsUpdater(0.5);
            }
            render.render();
        }
    }

    net.StoreWeights();
}

void testing() {
    DatasetReader dr("../mnist/t10k-images.idx3-ubyte", "../mnist/t10k-labels.idx1-ubyte");
    Network net;
    net.LoadWeights();

    sf::Event event{};
    Data data{&net.GetFirstLayer(), &net.GetLastLayer()};
    Render render(&data);
    bool paused = false;
    uint32_t ra = 0;
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
            ra++;
        }
        render.render();
    }
    std::cout << "Accuracy rate: " << (static_cast<double>(ra) / training_samples) * 100.0 << "\n";
}

int main() {
    learning();
    // testing();
    return 0;
}
