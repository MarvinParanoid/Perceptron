#include "DatasetReader.h"
#include "Network.h"
#include "Render.h"
#include <cmath>

int main() {
    DatasetReader dr("../mnist/train-images.idx3-ubyte", "../mnist/train-labels.idx1-ubyte");
    Render render;
    sf::Event event{};
    bool paused = false;
    while (render.window().isOpen()) {
        while (render.window().pollEvent(event) || paused) {
            if (event.type == sf::Event::Closed) {
                render.window().close();
            } else if (event.type == sf::Event::KeyPressed) {
                paused = true;
            } else if (event.type == sf::Event::KeyReleased) {
                paused = false;
            }
        }
        std::vector<double> image(784);
        Data data{&image};
        uint32_t expected;
        dr.ReadNext(image, expected);
        render.updateData(&data);
        render.render();
    }

    //    DatasetReader dr("../mnist/train-images.idx3-ubyte", "../mnist/train-labels.idx1-ubyte");
    //    Network net;
    //    net.Init({DatasetReader::IMG_SIZE, 128, 10});
    //    auto &data = net.GetInput();
    //    uint32_t expected, predicted;
    //    for (uint32_t i = 0; i < 1000; i++) {
    //        uint32_t ra = 0;
    //        for (uint32_t epoch = 0; epoch < 20; epoch++) {
    //            dr.ReadNext(data, expected);
    //            predicted = net.ForwardFeed();
    //            if (predicted != expected) {
    //                net.BackPropagation(expected);
    //                net.WeightsUpdater(0.15 * exp(-epoch / 20.));
    //            } else {
    //                ra++;
    //            }
    //        }
    //        std::cout << ra << "\n";
    //    }

    return 0;
}
