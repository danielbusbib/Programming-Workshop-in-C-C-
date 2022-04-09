#include "MlpNetwork.h"
#define DIG_NUMBERS 10
#define PRINT_ERROR_AND_EXIT(msg) \
{std::cerr << "Error: " << msg << std::endl; \
exit(EXIT_FAILURE); \
}
#define INCORRECT_WEIGHT "INCORRECT WEIGHT MATRIX INPUT"
#define INCORRECT_BIAS "INCORRECT BIAS MATRIX INPUT"
#define INCORRECT_IMAGE "INCORRECT IMAGE MATRIX IN () OP"


/**
 * Constructor
 * @param weights pointer to array of 4 Matrix
 * @param biases pointer to array of 4 Matrix
 */
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases) : weights (weights), biases (biases)
{
  for (size_t i = 0; i < 4; ++i)
  {
    if (weights_dims[i].rows != weights[i].get_rows () ||
    weights_dims[i].cols != weights[i].get_cols ())
    {
      PRINT_ERROR_AND_EXIT(INCORRECT_WEIGHT);
    }
    if (bias_dims[i].rows != biases[i].get_rows () ||
    bias_dims[i].cols != biases[i].get_cols ())
    {
        PRINT_ERROR_AND_EXIT(INCORRECT_BIAS);
    }
  }
}

/**
 * operator () -
 * get an image and return the digit with
 * the highest pr that in that image
 * @param image Matrix
 * @return digit
 */
digit MlpNetwork::operator() (const Matrix &image)
{
  if (image.get_rows () != (img_dims.rows * img_dims.cols)
  || image.get_cols () != 1)
  {
      PRINT_ERROR_AND_EXIT(INCORRECT_IMAGE);
  }

  Dense r1 (weights[0], biases[0], RELU);
  Matrix in1 = r1 (image);
  Dense r2 (weights[1], biases[1], RELU);
  Matrix in2 = r2 (in1);
  Dense r3 (weights[2], biases[2], RELU);
  Matrix in3 = r3 (in2);
  Dense r4 (weights[3], biases[3], SOFTMAX);
  Matrix out = r4 (in3);
  // check digit:
  digit max = {0, 0};
  for (int i = 0; i < DIG_NUMBERS; ++i)
  {
    if (out[i] > max.probability)
    {
      max.probability = out[i];
      max.value = i;
    }
  }
  return max;
}

