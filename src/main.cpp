#include "DatasetReader.h"
#include "Network.h"
#include <cmath>
#include <iostream>

int main() {
    DatasetReader dr("../mnist/train-images.idx3-ubyte", "../mnist/train-labels.idx1-ubyte");
    Network net;
    net.Init({DatasetReader::IMG_SIZE, 128, 10});
    auto &data = net.GetInput();
    uint32_t expected, predicted;
    for (uint32_t i = 0; i < 1000; i++) {
        uint32_t ra = 0;
        for (uint32_t epoch = 0; epoch < 20; epoch++) {
            dr.ReadNext(data, expected);
            predicted = net.ForwardFeed();
            if (predicted != expected) {
                net.BackPropagation(expected);
                net.WeightsUpdater(0.15 * exp(-epoch / 20.));
            } else {
                ra++;
            }
        }
        std::cout << ra << "\n";
    }

    return 0;
}
