// Matrix.h
#include <cmath>
#include <iostream>
#include <cstring>
#ifndef MATRIX_H
#define MATRIX_H

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and in main.cpp.
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
  int rows, cols;
  float *mat;
 public:
  Matrix ();
  Matrix (int, int);
  Matrix (const Matrix &);
  ~Matrix ();
  int get_rows () const;
  int get_cols () const;
  Matrix &transpose ();
  Matrix &vectorize ();
  void plain_print () const;
  Matrix dot (const Matrix &m) const;
  float norm () const;
  Matrix operator+ (const Matrix &b) const;
  Matrix &operator= (const Matrix &other);
  Matrix operator* (const Matrix &b) const;
  Matrix operator* (float c) const;
  friend Matrix operator* (float c, const Matrix &m) ;
  Matrix &operator+= (const Matrix &b);
  float operator() (int i, int j) const;
  float &operator() (int i, int j);
  float operator[] (int i) const;
  float &operator[] (int i);
  friend std::ostream &operator<< (std::ostream &os, const Matrix &matrix);
  friend std::istream &operator>> (std::istream &input, const Matrix &matrix);

 private:
  friend float get_mul (const Matrix &matrix,
                        const float *mat_b,
                        int index_row,
                        int index_col,
                        int b_cols);
  friend float *get_mat (const Matrix &matrix);
};

#endif //MATRIX_H
