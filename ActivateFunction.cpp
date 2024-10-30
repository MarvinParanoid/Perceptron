#include "ActivateFunction.h"
#include <cmath>

void ActivateFunction::Use(Vector &v) {
    for (auto &i: v) {
        i = 1 / (1 + exp(-i));
    }
}

void ActivateFunction::UseDer(Vector &v) {
    for (auto &i: v) {
        i = i * (1 - i);
    }
}

double ActivateFunction::UseDer(double value) {
    return value * (1 - value);
}
