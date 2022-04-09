//
// Created by yuval on 01-Oct-21.
//
#include "Activation.h"

#ifndef DENSE_H
#define DENSE_H

// Insert Dense class here...
class Dense {
  Matrix weights, bias;
  Activation activation;
 public:
  /**
   * Constructor
   * @param weights
   * @param bias
   * @param activation_type
   */
  Dense (const Matrix &weights,
         const Matrix &bias, ActivationType activation_type);
  /**
   * Getter - get weights
   * @return Matrix weights
   */
  const Matrix &get_weights () const;
  /**
  * Getter - get weights
  * @return Matrix bias
  */
  const Matrix &get_bias () const;
  /**
  * Getter - get activation
  * @return Activation
  */
  const Activation &get_activation () const;
  /**
   * operator () -->
   * get Matrix and return Matrix calculation
   * of Dense
   * @return Matrix
   */
  Matrix  operator() (const Matrix &) const;
};

#endif //DENSE_H
