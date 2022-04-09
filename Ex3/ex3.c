#include "ex3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRINT_ERROR_MSG_WITH_RETURN(s) {fprintf(stderr, "ERROR: %s \n", s); return NULL;}
#define PRINT_ERROR_MSG(s) fprintf(stderr, "ERROR: %s \n", s)
#define SLICE_CHECK_ARGS(mat, rs, re, cs, ce) \
if (!mat || rs > re || cs > ce || rs >= mat->n_rows || cs >= mat->n_columns) \
return m;
#define SET_MATRIX_VALUES(m, mat, n_rows, n_columns) m->data = mat;\
m->n_rows = n_rows;\
m->n_columns = n_columns;
#define UPDATE()  if (row_end > mat->n_rows)\
{\
row_end = mat->n_rows;\
}\
n_rows = row_end - row_start;\
if (col_end > mat->n_columns)\
{\
col_end = mat->n_columns;\
}\
n_columns = col_end - col_start;
#define CHECK_ERROR(e) if(e==1) {return NULL;}

/**
 * This function free allocation of double mat
 * @param data
 * @param n_row
 */
void free_mat_pointers (double **data, size_t n_row)
{
  if (!data)
  {
    return;
  }
  for (size_t i = 0; i < n_row; ++i)
  {
    if (data[i])
    {
      free (*(data + i));
      *(data + i) = NULL;
    }
  }
  free (data);
  data = NULL;
}
/**
 * function to initialize matrix with safe c allocation
 * @param mat matrix
 * @param error size_t
 */
void initialize_matrix (matrix **mat, size_t *error)
{
  matrix *m = calloc (1, sizeof (matrix));
  if (!m)
  {
    PRINT_ERROR_MSG(ALLOC_FAIL);
    *error = 1;
  }
  else
  {
    *mat = m;
  }
}
/**
 * function initialize data (double 2D array)
 * @param data double **
 * @param n_rows size_t
 * @param n_columns size_t
 * @param error size_t
 */
void initialize_data (double ***data, size_t n_rows, size_t n_columns, size_t *error)
{
  double **mat = malloc (sizeof (double *) * n_rows);
  if (!mat)
  {
    PRINT_ERROR_MSG(ALLOC_FAIL);
    *error = 1;
    return;
  }
  for (size_t i = 0; i < n_rows; i++)
  {
    double *tmp_row = calloc (n_columns, sizeof (double));
    if (!tmp_row)
    {
      free_mat_pointers (mat, i);
      PRINT_ERROR_MSG(ALLOC_FAIL);
      *error = 1;
      return;
    }
    mat[i] = tmp_row;
  }
  *data = mat;
}
/**
 * update data of m_data from matrix mat data
 * @param mat
 * @param m_data
 * @param mrow
 * @param mcol
 * @param row_start
 * @param col_start
 */
void change_data (matrix *mat, double **m_data, size_t mrow, size_t mcol, size_t row_start, size_t col_start)
{
  for (size_t i = 0; i < mrow; ++i)
  {
    for (size_t j = 0; j < mcol; ++j)
    {
      m_data[i][j] = mat->data[row_start + i][col_start + j];
    }

  }
}

/**
 * create a new matrix_s on the heap.
 * @param n_rows number of rows in the new matrix_s.
 * @param n_columns number of columns in the new matrix_s.
 * @return A pointer to the new matrix_s struct.
 */
matrix *create_matrix (size_t n_rows, size_t n_columns)
{
  size_t error = ZERO;
  if (!n_rows || !n_columns)
  {
    matrix *m;
    initialize_matrix (&m, &error);
    CHECK_ERROR(error);
    return m;
  }
  double **mat;
  initialize_data (&mat, n_rows, n_columns, &error);
  CHECK_ERROR(error);
  matrix *m = calloc (1, sizeof (matrix));
  if (!m)
  {
    //free
    free_mat_pointers (mat, n_rows);
    PRINT_ERROR_MSG_WITH_RETURN(ALLOC_FAIL);
  }
  SET_MATRIX_VALUES(m, mat, n_rows, n_columns);
  return m;

}

/**
 * Get value based on index.
 * @param matrix
 * @param row_index
 * @param col_index
 * @return matrix_s[row_index, col_index],
 * NULL if the index is out of range.
 */
double *get_by_index (matrix *mat, size_t row_index, size_t col_index)
{
  if (!mat)
  {
    PRINT_ERROR_MSG_WITH_RETURN(NULL_ERROR);
  }
  if (row_index >= mat->n_rows)
  {
    PRINT_ERROR_MSG_WITH_RETURN(ROW_INDEX_ERROR);
  }
  if (col_index >= mat->n_columns)
  {
    PRINT_ERROR_MSG_WITH_RETURN(COL_INDEX_ERROR);
  }

  return (*(mat->data + row_index) + col_index);
}

/**
 * slice the matrix data and return new matrix
 * @param matrix
 * @param row_range
 * @param col_range
 * @return
 */
matrix *slice (matrix *mat, size_t row_start,
               size_t row_end, size_t col_start, size_t col_end)
               {
  matrix *m;
  size_t error = ZERO;
  initialize_matrix (&m, &error);
  CHECK_ERROR(error);
  SLICE_CHECK_ARGS(mat, row_start, row_end, col_start, col_end);
  size_t n_columns = ZERO, n_rows = ZERO;
  UPDATE();
  if (n_rows == ZERO || n_columns == ZERO)
  {
    return m;
  }
  double **m_data;
  initialize_data (&m_data, n_rows, n_columns, &error);
  CHECK_ERROR(error);
  change_data (mat, m_data, n_rows, n_columns, row_start, col_start);
  SET_MATRIX_VALUES(m, m_data, n_rows, n_columns);
  return m;

}
/**
* This function concatenate 2 matrix data -> top & bottom
 * and return new data after concatenate
* @param top
* @param bottom
* @param n_rows
* @param n_cols
* @return double**
*/
double **concatenate_data (double **top, double **bottom, size_t new_rows,
                          size_t n_cols, size_t top_rows)
                          {
 double **m_data;
 size_t error = ZERO;
 initialize_data (&m_data, new_rows, n_cols, &error);
 CHECK_ERROR(error);

 for (size_t i = 0; i < new_rows; ++i)
 {
   for (size_t j = 0; j < n_cols; ++j)
   {
     if (i < top_rows)
     {
       m_data[i][j] = top[i][j];
     }
     else
     {
       m_data[i][j] = bottom[i - (top_rows)][j];
     }

   }
 }
 return m_data;
}
/**
 *This function concatenate vertically 2 matrix -> top
 * & bottom, and return new matrix after concatenate.
 * @param top matrix
 * @param bottom matrix
 * @return matrix
 */
matrix *concatenate_vertically (matrix *top, matrix *bottom)
{
  if (!top || !bottom)
  {
    PRINT_ERROR_MSG_WITH_RETURN(NULL_ERROR);
  }
  if (top->n_columns != bottom->n_columns)
  {
    PRINT_ERROR_MSG_WITH_RETURN(CONCATENATE_VERTICALLY_ERROR);
  }
  size_t n_rows = top->n_rows + bottom->n_rows;
  double **mat;
  if (!n_rows)
  {
    mat = NULL;
  }
  else
  {
    mat = concatenate_data (top->data, bottom->data,
                            n_rows, top->n_columns, top->n_rows);
    if (!mat && n_rows > ZERO)
    {
      return NULL;
    }
  }
  size_t error = ZERO, n_columns = top->n_columns;
  matrix *m;
  initialize_matrix (&m, &error);
  CHECK_ERROR(error);
  SET_MATRIX_VALUES(m, mat,  n_rows, n_columns  );
  return m;
}
/**
 * helper function -> transpose m (double **)
 * @param m double**
 * @param col size_t
 * @param row size_t
 * @return double**
 */
double **transpose_helper (double **m, size_t col, size_t row)
{
  if (m == NULL || !row || !col)
  {
    return NULL;
  }
  double **n;
  size_t error = ZERO;
  initialize_data (&n, row, col, &error);
  CHECK_ERROR(error);
  for (size_t i = 0; i < row; i++)
  {

    for (size_t j = 0; j < col; j++)
    {
      n[i][j] = m[j][i];
    }
  }
  return n;

}
/**
 * helper function to concatenate_horizontally -> initialize
 * and concatenate the left and right matrix data
 * @param left
 * @param right
 * @param new_cols
 * @param n_rows
 * @param left_rows
 * @return double**
 */
double **concatenate_data_cols (double **left, double **right, size_t new_cols, size_t n_rows, size_t left_rows)
{
  double **m_data;
  size_t error = ZERO;
  initialize_data (&m_data, n_rows, new_cols, &error);
  CHECK_ERROR(error);
  for (size_t i = 0; i < n_rows; ++i)
  {
    for (size_t j = 0; j < new_cols; ++j)
    {
      if (j < left_rows)
      {
        m_data[i][j] = left[i][j];
      }
      else
      {
        m_data[i][j] = right[i][j - (left_rows)];
      }

    }
  }
  return m_data;
}
/**
 * concatenate horizontally function
 * @param left matrix
 * @param right matrix
 * @return matrix after concatenate horizontally left & right
 */
matrix *concatenate_horizontally (matrix *left, matrix *right)
{
  if (!left || !right)
  {
    PRINT_ERROR_MSG_WITH_RETURN(NULL_ERROR);
  }
  if (left->n_rows != right->n_rows)
  {
    PRINT_ERROR_MSG_WITH_RETURN(CONCATENATE_VERTICALLY_ERROR);
  }
  size_t n_columns = left->n_columns + right->n_columns;
  double **mat;
  if (!n_columns)
  {
    mat = NULL;
  }
  else
  {
    mat = concatenate_data_cols (left->data, right->data, n_columns, left->n_rows, left->n_columns);
    if (!mat && n_columns > ZERO)
    {
      return NULL;
    }
  }
  matrix *m;
  size_t error = ZERO, n_rows = left->n_rows;
  initialize_matrix (&m, &error);
  CHECK_ERROR(error);
  SET_MATRIX_VALUES(m, mat, n_rows, n_columns );
  return m;
}
/**
 * Transpose matrix function
 * @param matrix
 * @return matrix
 */
matrix *transpose (matrix *mat)
{
  matrix *m = calloc (1, sizeof (matrix));
  if (!m)
  {
    PRINT_ERROR_MSG_WITH_RETURN(ALLOC_FAIL);
  }
  m->data = transpose_helper (mat->data, mat->n_rows, mat->n_columns);
  m->n_columns = mat->n_rows;
  m->n_rows = mat->n_columns;
  return m;
}

/**
 * ravel function --> get all matrix data into one D array
 * @param matrix
 * @return double*
 */
double *ravel (matrix *mat)
{

  size_t len = (mat->n_rows) * (mat->n_columns), ind = ZERO;
  double *ravel_arr = malloc (len * sizeof (double));
  if (!ravel_arr)
  {
    PRINT_ERROR_MSG_WITH_RETURN(ALLOC_FAIL);
  }
  for (size_t i = 0; i < mat->n_rows; ++i)
  {
    for (size_t j = 0; j < mat->n_columns; ++j)
    {
      ravel_arr[ind] = mat->data[i][j];
      ind++;
    }
  }
  return ravel_arr;
}
/**
 * This function free all allocation of matrix
 * @param matrix
 */
void free_matrix (matrix *mat)
{
  if (!mat)
  {
    return;
  }
  free_mat_pointers (mat->data, mat->n_rows);
  free (mat);
  mat = NULL;
}