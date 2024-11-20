#include "Matrix.h"
#include <cstdlib>
#include <stdexcept>

void Matrix::Init(uint32_t row, uint32_t col) {
    mMatrix.resize(row);
    for (uint32_t i = 0; i < row; i++) {
        mMatrix[i].resize(col, 0);
    }
}

void Matrix::Rand() {
    for (uint32_t i = 0; i < mMatrix.size(); i++) {
        for (uint32_t j = 0; j < mMatrix[0].size(); j++) {
            mMatrix[i][j] = ((rand() % 100)) * 0.03 / (mMatrix.size() + 35);
        }
    }
}

// todo: slowest part, need to use intrinsics or math library
void Matrix::Multi(const Matrix &matrix, const Vector &neuron, Vector &res) {
    if (matrix.Col() != neuron.size() || matrix.Row() != res.size()) {
        throw std::runtime_error("Multi error");
    }
    auto col = matrix.Col();
    for (uint32_t i = 0; i < matrix.Row(); ++i) {
        double tmp = 0;
        auto neuronPtr = neuron.data();
        auto matrixRowPtr = matrix.mMatrix[i].data();
        for (uint32_t j = 0; j < col; ++j) {
            tmp += *matrixRowPtr++ * *neuronPtr++;
        }
        res[i] = tmp;
    }
}

void Matrix::MultiT(const Matrix &matrix, const Vector &neuron, Vector &res) {
    if (matrix.Row() != neuron.size() || matrix.Col() != res.size()) {
        throw std::runtime_error("Multi error");
    }
    auto row = matrix.Row();
    for (uint32_t i = 0; i < matrix.Col(); i++) {
        double tmp = 0;
        for (uint32_t j = 0; j < row; j++) {
            tmp += matrix.mMatrix[j][i] * neuron[j];
        }
        res[i] = tmp;
    }
}

void Matrix::SumVector(Vector &a, Vector &b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("Sum error");
    }
    for (uint32_t i = 0; i < a.size(); i++) {
        a[i] += b[i];
    }
}
