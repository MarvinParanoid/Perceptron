#include "ActivateFunction.h"
#include <cmath>

void ActivateFunction::Use(Vector &v) {
    for (auto &i: v) {
        i = 1 / (1 + exp(-i));
    }
}

double ActivateFunction::UseDer(double value) {
    return value * (1 - value);
}
