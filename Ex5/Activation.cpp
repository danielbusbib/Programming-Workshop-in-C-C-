#include "Activation.h"
#define PRINT_ERROR_AND_EXIT(msg) \
{std::cerr << "Error: " << msg << std::endl; \
exit(EXIT_FAILURE); \
}
#define INVALID_ACTIVATION_TYPE "INVALID ACTIVATION TYPE"
/**
 * Activation Constructor
 * @param activation_type ActivationType
 */
Activation::Activation (ActivationType activation_type)
{
  if (activation_type != RELU && activation_type != SOFTMAX)
  {
    PRINT_ERROR_AND_EXIT(INVALID_ACTIVATION_TYPE);
  }

  this->activation_type = activation_type;
}

/**
 * Getter - activation type
 * @return ActivationType
 */
ActivationType Activation::get_activation_type () const
{
  return activation_type;
}

/**
 * operator () - implement func on matrix given
 * @param vector
 * @return Matrix
 */
Matrix Activation::operator() (const Matrix &vector) const
{
  return activation_type == RELU ? relu_func(vector) : soft_max_func(vector);
}

/**
 * Relu Func
 * @param matrix
 * @return output Matrix of Relu func
 */
Matrix Activation::relu_func (const Matrix &matrix)
{
  Matrix m (matrix.get_rows (), matrix.get_cols ());
  for (int i = 0; i < matrix.get_rows () * matrix.get_cols(); ++i)
  {
    m[i] = matrix[i] >= 0 ? matrix[i] : 0;
  }
  return m;
}

/**
 * SoftMax function
 * @param matrix
 * @return output Matrix
 */
Matrix Activation::soft_max_func (const Matrix &matrix)
{
  Matrix m (matrix.get_rows (), matrix.get_cols ());
  float sum_exp = 0;
  for (int i = 0; i < matrix.get_rows () * matrix.get_cols(); ++i)
  {
    m[i] = std::exp (matrix[i]);
    sum_exp += std::exp (matrix[i]);
  }
  sum_exp = (1 / sum_exp);
  return sum_exp * m;
}