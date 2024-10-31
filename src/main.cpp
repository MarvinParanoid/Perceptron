#include "DatasetReader.h"
#include "Network.h"
#include "Render.h"
#include <cmath>

int main() {
    DatasetReader dr("../mnist/train-images.idx3-ubyte", "../mnist/train-labels.idx1-ubyte");
    Network net;
    net.Init({DatasetReader::IMG_SIZE, 128, 10});

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
        std::vector<double> res(10);
        Data data{&image, &res};
        dr.ReadNext(image, data.expected);

        for (uint32_t epoch = 0; epoch < 20; epoch++) {
            auto p = net.ForwardFeed();
            data.predicted = p.first;
            data.res = p.second;
            if (data.predicted != data.expected) {
                net.BackPropagation(data.expected);
                //net.WeightsUpdater(0.15 * exp(-epoch / 20.));
                net.WeightsUpdater(0.5);
            }
            render.updateData(&data);
            render.render();
        }
    }

    return 0;
}
