#pragma once

#include "ActivateFunction.h"
#include "Matrix.h"
#include <vector>

// todo: optimize it with MT

class Network {
public:
    using Vector2D = std::vector<std::vector<double>>;
    using Layers = std::vector<uint32_t>;

private:
    Layers mLayers;
    uint32_t mL;
    std::vector<Matrix> mWeights;
    Vector2D mNeuronsVal;
    Vector2D mNeuronsErr;
    Vector2D mBios;
    ActivateFunction mActFunc;

    uint32_t SearchMaxIndex(const std::vector<double> &values);

public:
    explicit Network() = default;
    explicit Network(Layers layers);

    uint32_t ForwardFeed();
    void BackPropagation(double expect);
    void WeightsUpdater(double lr);

    std::vector<double> &GetFirstLayer() { return mNeuronsVal.front(); }
    std::vector<double> &GetLastLayer() { return mNeuronsVal.back(); }

    void StoreWeights();
    void LoadWeights();
};
