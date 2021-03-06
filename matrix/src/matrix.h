#include "common.h"
#include "element.h"

#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

typedef struct matrix_s {
    unsigned max_col;
    unsigned max_row;
    unsigned max_len;
    unsigned curr_col;
    unsigned curr_row;
    unsigned curr_len;
    Blucket  **data;
} Matrix;

typedef struct config_s {
    unsigned max_col;
    unsigned max_row;
} Config;

//functions of matrix
Config *config_new(unsigned, unsigned);

Matrix  *matrix_new(Config*);
Status  matrix_add(Matrix*, Element*);
Status  matrix_update(Matrix*, Element*);
Status  matrix_clear(Matrix*);
Element *matrix_find_by_pos(Matrix*, unsigned, unsigned);
Element *matrix_find_by_val(Matrix*, int);
Status  matrix_expand(Matrix*);
Status  matrix_print(Matrix*);

unsigned hash_generator( unsigned, unsigned, Matrix*);
Matrix   *array_to_matrix(int*, unsigned, unsigned);

#endif //MATRIX_MATRIX_H_
