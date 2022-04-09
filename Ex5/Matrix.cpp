#include "Matrix.h"
// g++ -Wextra -Werror -Wall -Wvla Activation.cpp
// Dense.cpp MlpNetwork.cpp Matrix.cpp main.cpp -o ex5
#include <fstream>
#include <ostream>
#define PRINT_ERROR_AND_EXIT(msg) \
{std::cerr << "Error: " << msg << std::endl; \
exit(EXIT_FAILURE); \
}
#define CHECK_INDEX(m, i)  i >= (m.rows * m.cols)
#define CHECK_ROW(m, i)  i >= (m.rows) || i < 0
#define CHECK_COL(m, j)  j >= (m.cols)  || j < 0
#define DOT_ERROR_MSG "INVALID MATRIX PARAMETERS - CAN NOT DOT"
#define PLUS_ERROR_MSG "INVALID MATRIX FOR + OPERATOR"
#define MULT_ERROR_MSG "INVALID MATRIX FOR * OPERATOR"
#define INDEX_ERROR "INVALID INDEX OF MATRIX"
#define NUM_B 0.1
#define ALLOC_ERROR "INVALID ALLOCATION OF MATRIX"
#define INV_PARAM "INVALID PARAM OF MATRIX"

/**
 * default Matrix constructor
 */
Matrix::Matrix ()
{
  rows = 1;
  cols = 1;
  mat = new float[rows * cols] ();
  if (!mat)
  {
    PRINT_ERROR_AND_EXIT(ALLOC_ERROR);
  }
}
/**
 * Matrix constructor with given rows,cols
 * @param rows
 * @param cols
 */
Matrix::Matrix (int rows, int cols) : rows (rows), cols (cols)
{
  if (rows <= 0 || cols <= 0)
  {
      PRINT_ERROR_AND_EXIT(INV_PARAM);
  }
  mat = new float[rows * cols] ();
  if (!mat)
  {
      PRINT_ERROR_AND_EXIT(ALLOC_ERROR);
  }
}
/**
 * Matrix Constructor from another Matrix
 * @param matrix
 */
Matrix::Matrix (const Matrix &matrix)
{
  rows = matrix.rows;
  cols = matrix.cols;
  mat = new float[rows * cols];
  //check error
  for (int i = 0; i < matrix.rows; ++i)
  {
    for (int j = 0; j < matrix.cols; ++j)
    {
      mat[i * matrix.cols + j] = matrix.mat[i * matrix.cols + j];
    }
  }
}

/**
 * Matrix destructor
 * delete allocated memory of matrix
 */
Matrix::~Matrix ()
{
  delete[] mat;
}

/**
 * Getter - get rows of matrix
 * @return number of rows
 */
int Matrix::get_rows () const
{
  return rows;
}

/**
 * Getter - get cols of matrix
 * @return number of cols
 */
int Matrix::get_cols () const
{
  return cols;
}

/**
 * function that transpose the matrix.
 * @return Transposed Matrix
 */
Matrix &Matrix::transpose ()
{
  float *tmp_mat = new float[rows * cols];
  for (int i = 0; i < rows * cols; ++i)
  {
    tmp_mat[i] = mat[i];
  }
  int tmp = rows;

  rows = cols;
  cols = tmp;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      (*this) (i, j) = tmp_mat[j * rows + i];
    }
  }
  delete[] tmp_mat;
  return *this;
}
/**
 * Vectorize the matrix.
 * @return matrix after vectorized
 */
Matrix &Matrix::vectorize ()
{
  rows = rows * cols;
  cols = 1;
  return *this;
}
/**
 * function to print matrix numbers format
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      std::cout << (*this) (i, j) << " ";
    }
    std::cout << std::endl;
  }
}
/**
 * Function dot on matrix
 * @param m
 * @return
 */
Matrix Matrix::dot (const Matrix &m) const
{
  if (rows != m.rows || cols != m.cols)
  {
    PRINT_ERROR_AND_EXIT(DOT_ERROR_MSG);
  }
  Matrix d(rows,cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      d[i * cols + j] = (mat[i * cols + j] * m.mat[i * cols + j]);
    }
  }
  return d;
}
/**
 * function that return the norm of the
 * current matrix.
 * @return float - norm
 */
float Matrix::norm () const
{
  float sum = 0;
  for (int i = 0; i < rows * cols; ++i)
  {
    sum += ((mat[i]) * (mat[i]));
  }
  return std::sqrt (sum);
}

/**
 * operator +
 * @param b
 * @return Matrix
 */
Matrix Matrix::operator+ (const Matrix &b) const
{
  if (rows != b.rows || cols != b.cols)
  {
    PRINT_ERROR_AND_EXIT(PLUS_ERROR_MSG);
  }
  Matrix k (b);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      k (i, j) = ((*this) (i, j) + b (i, j));
    }
  }
  return k;
}
/**
 * assignment operator
 * @param other
 * @return instance matrix
 */
Matrix &Matrix::operator= (const Matrix &other)
    {
  if (this != &other)
  {
    this->rows = other.rows;
    this->cols = other.cols;
    delete[] this->mat;
    this->mat = new float[this->rows * this->cols];
    for (int i = 0; i < (this->rows * this->cols); ++i)
    {
      this->mat[i] = other.mat[i];
    }
  }
  return *this;
}
/**
 * operator of multiply -
 * multiply two matrix
 * @param b
 * @return matrix
 */
Matrix Matrix::operator* (const Matrix &b) const
{
  if (this->cols != b.rows)
  {
    PRINT_ERROR_AND_EXIT(MULT_ERROR_MSG);
  }
  Matrix m(rows, b.cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < b.cols; ++j)
    {
      m[i * b.cols + j] = get_mul ((*this), b.mat, i, j, b.cols);
    }
  }
  return m;
}
/**
 *
 * @param c
 * @return
 */
Matrix Matrix::operator* (float c) const
{
  Matrix m(rows,cols);
  for (int i = 0; i < rows * cols; ++i)
  {
    m[i] = mat[i] * c;
  }
  return m;
}
/**
 *
 * @param c
 * @param m
 * @return
 */
Matrix operator* (float c, const Matrix &m)
{
  return m * c;
}
/**
 *
 * @param b
 * @return
 */
Matrix &Matrix::operator+= (const Matrix &b)
{
  if (rows != b.rows || cols != b.cols)
  {
    PRINT_ERROR_AND_EXIT(PLUS_ERROR_MSG);
  }
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      this->mat[i * cols + j] = (this->mat[i * cols + j] + b.mat[i * cols + j]);
    }
  }
  return *this;
}
/**
 * operator () -
 * (i,j) -> return mat[i][j]
 * @param i row
 * @param j col
 * @return number in place i,j - float
 */
float Matrix::operator() (int i, int j) const
{
  if (CHECK_ROW((*this), i) || CHECK_COL((*this), j))
  {
    PRINT_ERROR_AND_EXIT(INDEX_ERROR);
  }
return mat[i * cols + j];
}

/**
 *
 * @param i
 * @param j
 * @return
 */
float &Matrix::operator() (int i, int j)
{
  if (CHECK_ROW((*this), i) || CHECK_COL((*this), j))
  {
    PRINT_ERROR_AND_EXIT(INDEX_ERROR);
  }
  return (float &) (mat[i * cols + j]);
}

/**
 * operator [] of Matrix-
 * get Matrix element in index i
 * @param i index
 * @return element in place i,
 * if i is invalid index exit with error
 */
float Matrix::operator[] (int i) const
{
  if (CHECK_INDEX((*this), i))
  {
    PRINT_ERROR_AND_EXIT(INDEX_ERROR);
  }
  return mat[i];
}

/**
 * operator [] of Matrix-
 * get Matrix element in index i
 * @param i index
 * @return reference to element in place i,
 * if i is invalid index exit with error
 */
float &Matrix::operator[] (int i)
{
  if (CHECK_INDEX((*this), i))
  {
    PRINT_ERROR_AND_EXIT(INDEX_ERROR);
  }
  return (float &) (mat[i]);
}

/**
 * output stream operator
 * @param os std::ostream
 * @param matrix Matrix
 * @return os
 */
std::ostream &operator<< (std::ostream &os, const Matrix &matrix)
{
  for (int i = 0; i < matrix.rows; ++i)
  {
    for (int j = 0; j < matrix.cols; ++j)
    {
      os << (matrix (i, j) > NUM_B ? "**" : "  ");
    }
    os << std::endl;
  }
  return os;
}
/**
 *  input operator
 * @param input std::istream
 * @param matrix Matrix
 * @return input stream
 */
std::istream &operator>> (std::istream &input, const Matrix &matrix)
{

  float f;
  int i = 0;
  while (i < matrix.rows * matrix.cols)
  {
    if (input.read (reinterpret_cast<char *>(&f), sizeof (float)).fail ())
    {
      PRINT_ERROR_AND_EXIT("ERROR INPUT");
    }
    matrix.mat[i] = f;
    i++;
  }
  if (i != matrix.rows * matrix.cols)
  {
    PRINT_ERROR_AND_EXIT("ERROR INPUT FILE");
  }

  return input;
}
/*
 * Private function:
 */
/**
 *
 * @param matrix
 * @return
 */
float *get_mat (const Matrix &matrix)
{
  return matrix.mat;
}
float get_mul (const Matrix &matrix, const float *mat_b,
               int index_row, int index_col, int b_cols)
{
  float sum = 0;
  for (int i = 0; i < matrix.cols; ++i)
  {
    sum += ((matrix (index_row, i)) * (mat_b[i * b_cols + index_col]));
  }
  return sum;
}
