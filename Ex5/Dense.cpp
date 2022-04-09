#include "Dense.h"
#include "Activation.h"
#define INVALID_DENSE_PARAM "Error: Invalid Dense Matrix params given"
Dense::Dense (const Matrix &weights,
       const Matrix &bias, ActivationType activation_type)
       : weights (weights), bias (bias),
       activation (Activation (activation_type))
{
  if (weights.get_rows() != bias.get_rows()){
    std::cerr << INVALID_DENSE_PARAM << std::endl;
    exit(EXIT_FAILURE);
  }
}
const Matrix &Dense::get_weights () const
{
  return weights;
}
const Matrix &Dense::get_bias () const
{
  return bias;
}
const Activation &Dense::get_activation () const
{
  return activation;
}
Matrix Dense::operator() (const Matrix &input) const
{
  return activation ((weights * input) + bias);
}


