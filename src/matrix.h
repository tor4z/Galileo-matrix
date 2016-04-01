#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

#include "common.h"
#include "element.h"

typedef struct matrix_s {
    unsigned max_col;
    unsigned max_raw;
    unsigned curr_col;
    unsigned curr_row;
    unsigned len;
    Blucket **data;
} Matrix;

//functions of matrix
Matrix *matrix_new();
int matrix_realloc(Matrix*);
int matrix_add(Matrix*, Element*);
int matrix_update(Matrix*, Element*);
int matrix_status(Matrix*);
int matrix_clear(Matrix*);
Element *matrix_find(Matrix*);

#endif //MATRIX_MATRIX_H_