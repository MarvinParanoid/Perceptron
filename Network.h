#ifndef PERCEPTRON_NETWORK_H
#define PERCEPTRON_NETWORK_H

#include "ActivateFunction.h"
#include "Matrix.h"
#include <vector>

class Network {
    using Vector2D = std::vector<std::vector<double>>;
    using Layers = std::vector<int>;
    Layers mLayers;
    uint32_t mL;
    std::vector<Matrix> mWeights;
    Vector2D mNeuronsVal;
    Vector2D mNeuronsErr;
    Vector2D mBios;
    ActivateFunction mActFunc;

    int SearchMaxIndex(const std::vector<double> &values);

public:
    void Init(Layers layers);
    void SetInput(std::vector<double> values);
    double ForwardFeed();
    void BackPropagation(double expect);
    void WeightsUpdater(double lr);
};


#endif//PERCEPTRON_NETWORK_H
