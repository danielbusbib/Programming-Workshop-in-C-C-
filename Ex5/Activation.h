//Activation.h

#include "Matrix.h"
#include <cmath>
#ifndef ACTIVATION_H
#define ACTIVATION_H

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType {
    RELU,
    SOFTMAX
};

class Activation {
  ActivationType activation_type;

 public:
  Activation (ActivationType activation_type);
  ActivationType get_activation_type () const;
  Matrix operator() (const Matrix &) const;

 private:
  static Matrix relu_func (const Matrix &);
  static Matrix soft_max_func (const Matrix &matrix);
};

#endif //ACTIVATION_H
