#pragma once

#include "Matrix.h"

class ActivateFunction {
public:
    void Use(Vector &v);

    double UseDer(double value);
};
