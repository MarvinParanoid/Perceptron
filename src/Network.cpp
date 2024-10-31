#include "Network.h"
#include <cstdlib>
#include <ctime>
#include <utility>

void Network::Init(Network::Layers layers) {
    srand(std::time(nullptr));
    mLayers = std::move(layers);
    mL = mLayers.size();

    mNeuronsVal.resize(mL);
    mNeuronsErr.resize(mL);
    for (uint32_t i = 0; i < mL; i++) {
        mNeuronsVal[i].resize(mLayers[i]);
        mNeuronsErr[i].resize(mLayers[i]);
    }

    mWeights.resize(mL - 1);
    mBios.resize(mL - 1);
    for (int i = 0; i < mL - 1; i++) {
        mWeights[i].Init(mLayers[i + 1], mLayers[i]);
        mBios[i].resize(mLayers[i + 1]);
        mWeights[i].Rand();
        for (int j = 0; j < mLayers[i + 1]; j++) {
            mBios[i][j] = ((rand() % 50)) * 0.06 / (mLayers[i] + 15);
        }
    }
}

std::pair<uint32_t, const std::vector<double> *> Network::ForwardFeed() {
    for (int k = 1; k < mL; k++) {
        Matrix::Multi(mWeights[k - 1], mNeuronsVal[k - 1], mNeuronsVal[k]);
        Matrix::SumVector(mNeuronsVal[k], mBios[k - 1]);
        mActFunc.Use(mNeuronsVal[k]);
    }
    return {SearchMaxIndex(mNeuronsVal[mL - 1]), &mNeuronsVal[mL - 1]};
}

uint32_t Network::SearchMaxIndex(const std::vector<double> &values) {
    double max = values[0];
    int prediction = 0;
    for (int j = 1; j < mLayers[mL - 1]; j++) {
        if (values[j] > max) {
            prediction = j;
            max = values[j];
        }
    }
    return prediction;
}

void Network::BackPropagation(double expect) {
    for (uint32_t i = 0; i < mLayers[mL - 1]; i++) {
        if (i != static_cast<int>(expect)) {
            mNeuronsErr[mL - 1][i] = -mNeuronsVal[mL - 1][i] * mActFunc.UseDer(mNeuronsVal[mL - 1][i]);
        } else {
            mNeuronsErr[mL - 1][i] = (1.0 - mNeuronsVal[mL - 1][i]) * mActFunc.UseDer(mNeuronsVal[mL - 1][i]);
        }
    }
    for (uint32_t i = mL - 2; i > 0; i--) {
        Matrix::MultiT(mWeights[i], mNeuronsErr[i + 1], mNeuronsErr[i]);
        for (uint32_t j = 0; j < mLayers[i]; j++) {
            mNeuronsErr[i][j] *= mActFunc.UseDer(mNeuronsVal[i][j]);
        }
    }
}

void Network::WeightsUpdater(double lr) {
    for (uint32_t i = 0; i < mL - 1; i++) {
        for (uint32_t j = 0; j < mLayers[i + 1]; j++) {
            for (uint32_t k = 0; k < mLayers[i]; k++) {
                mWeights[i](j, k) += mNeuronsVal[i][k] * mNeuronsErr[i + 1][j] * lr;
            }
        }
    }
    for (uint32_t i = 0; i < mL - 1; i++) {
        for (uint32_t k = 0; k < mLayers[i + 1]; k++) {
            mBios[i][k] += mNeuronsErr[i + 1][k] * lr;
        }
    }
}