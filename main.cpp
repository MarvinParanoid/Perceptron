#include <iostream>

#include "DatasetReader.h"
#include "Network.h"

int main() {
    DatasetReader dr("../mnist/train-images.idx3-ubyte", "../mnist/train-labels.idx1-ubyte");
    Network net;
    net.Init({DatasetReader::IMG_SIZE, 128, 10});
    std::vector<double> data(DatasetReader::IMG_SIZE);
    uint32_t expected;
    for (uint32_t i = 0; i < 1000; i++) {
        dr.ReadNext(data, expected);
        net.SetInput(data);
        net.ForwardFeed();
        net.BackPropagation(expected);
        net.WeightsUpdater(0.8);
    }

    return 0;
}
