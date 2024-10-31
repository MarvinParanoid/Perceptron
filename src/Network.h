#ifndef PERCEPTRON_NETWORK_H
#define PERCEPTRON_NETWORK_H

#include "ActivateFunction.h"
#include "Matrix.h"
#include <vector>

// todo: optimize it with MT

class Network {
    using Vector2D = std::vector<std::vector<double>>;
    using Layers = std::vector<uint32_t>;
    Layers mLayers;
    uint32_t mL;
    std::vector<Matrix> mWeights;
    Vector2D mNeuronsVal;
    Vector2D mNeuronsErr;
    Vector2D mBios;
    ActivateFunction mActFunc;

    uint32_t SearchMaxIndex(const std::vector<double> &values);

public:
    void Init(Layers layers);
    std::vector<double> &GetInput() { return mNeuronsVal[0]; }
    uint32_t ForwardFeed();
    void BackPropagation(double expect);
    void WeightsUpdater(double lr);

    // todo
    void StoreWeights();
    void LoadWeights();
};


#endif//PERCEPTRON_NETWORK_H
