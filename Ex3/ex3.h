
#ifndef _MATRIX_H_
#define _MATRIX_H_

#define ALLOC_FAIL "ERROR: ALLOCATION FAILED\n"
#define ROW_INDEX_ERROR "ERROR: INDEX OF ROW OUT OF MATRIX DATA RANGE\n"
#define COL_INDEX_ERROR "ERROR: INDEX OF ROW OUT OF COLUMN DATA RANGE\n"
#define NULL_ERROR "ERROR: NULL POINTER ERROR\n"
#define CONCATENATE_VERTICALLY_ERROR "ERROR: CAN NOT CONCATENATE VERTICALLY ->"\
" NUM OF TOP COLS NOT THE SAME OF BOTTOM\n"
#define ZERO 0
#include <math.h>
#include <stddef.h>

typedef struct matrix {
    double **data;
    size_t n_rows;
    size_t n_columns;
} matrix;

/**
 * create a new matrix_s on the heap.
 * @param n_rows number of rows in the new matrix_s.
 * @param n_columns number of columns in the new matrix_s.
 * @return A pointer to the new matrix_s struct.
 */
matrix *create_matrix (size_t n_rows, size_t n_columns);

/**
 * Get value based on index.
 * @param matrix
 * @param row_index
 * @param col_index
 * @return matrix_s[row_index, col_index],
 * NULL if the index is out of range.
 */
double *get_by_index (matrix *mat, size_t row_index, size_t col_index);

/**
 *
 * @param matrix
 * @param row_range
 * @param col_range
 * @return
 */
matrix *slice (matrix *mat, size_t row_start,
               size_t row_end, size_t col_start, size_t col_end);

/**
 *
 * @param top
 * @param bottom
 * @return
 */
matrix *concatenate_vertically (matrix *top, matrix *bottom);

/**
 *
 * @param left
 * @param right
 * @return
 */
matrix *concatenate_horizontally (matrix *left, matrix *right);

/**
 *
 * @param matrix
 * @return
 */
matrix *transpose (matrix *mat);

/**
 *
 * @param matrix
 * @return
 */
double *ravel (matrix *mat);

/**
 *
 * @param matrix
 * @return
 */
void free_matrix (matrix *mat);

#endif //_MATRIX_H_
