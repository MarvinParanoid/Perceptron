#pragma once

#include <cstdint>
#include <vector>

using Vector = std::vector<double>;

class Matrix {
    std::vector<Vector> mMatrix;

    uint32_t Row() const { return mMatrix.size(); }
    uint32_t Col() const { return mMatrix[0].size(); }

public:
    void Init(uint32_t row, uint32_t col);

    void Rand();

    static void Multi(const Matrix &matrix, const Vector &neuron, Vector &res);

    static void MultiT(const Matrix &matrix, const Vector &neuron, Vector &res);

    static void SumVector(Vector &a, Vector &b);

    const std::vector<Vector> &data() const { return mMatrix; }
    std::vector<Vector> &data() { return mMatrix; }
    double &operator()(uint32_t i, uint32_t j) { return mMatrix[i][j]; }
};
