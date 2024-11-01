#ifndef PERCEPTRON_ACTIVATEFUNCTION_H
#define PERCEPTRON_ACTIVATEFUNCTION_H

#include "Matrix.h"

class ActivateFunction {
public:
    void Use(Vector &v);
    double UseDer(double value);
};


#endif//PERCEPTRON_ACTIVATEFUNCTION_H
