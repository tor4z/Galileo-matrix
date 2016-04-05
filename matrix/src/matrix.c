#include "matrix.h"
#include "common.h"
#include <stdlib.h>

Matrix *matrix_new() {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    if(matrix == NULL)
        return NULL;
    
    matrix->max_col  = INI_MATRIX_COL;
    matrix->max_row  = INI_MATRIX_ROW;
    matrix->max_len  = matrix->max_col * matrix->max_row;
    matrix->curr_col = 0;
    matrix->curr_row = 0;
    matrix->curr_len = 0;
    matrix->data     = (Blucket**)malloc(matrix->max_len * sizeof(Blucket*));
    if(matrix->data == NULL) {
        safe_free(matrix);
        return NULL;
    }
    
    return matrix;
}

Status matrix_init(Matrix *matrix) {
    matrix->max_col  = INI_MATRIX_COL;
    matrix->max_row  = INI_MATRIX_ROW;
    matrix->max_len  = matrix->max_col * matrix->max_row;
    matrix->curr_col = 0;
    matrix->curr_row = 0;
    matrix->curr_len = 0;
    
    if(matrix->data != NULL)
        safe_free(matrix->data);
    matrix->data = (Blucket**)malloc(matrix->max_len * sizeof(Blucket*));
    if(matrix->data == NULL)
        return STAT_INIT_MATRIX_ERR;
    else
        return STAT_SUCCESS;
}

Status matrix_add(Matrix *matrix, Element *element) {
    unsigned index = hash_generator(element, matrix);
    if(index >= matrix->len) {
        Status res = matrix_realloc(matrix);
        if(res != STAT_SUCCESS)
            return res;
    }
    
    Blucket *blucket;
    if(matrix->data[index] == NULL) {
        blucket = blucket_new();
        if(blucket == NULL)
            return STAT_NEW_BLU_ERR;
        else
            matrix->data[index] = blucket;
    } else {
        blucket = matrix->data[index];
    }
    
    return blucket_add(blucket, element, False);
}

Status matrix_update(Matrix *matrix, Element *element) {
    unsigned index = hash_generator(element, matrix);
    return blucket_add(matrix->data[index], element, True);
}

Status matrix_clear(Matrix* matrix) {
    unsigned i;
    Blucket blucket;
    Status status;
    
    for(i=0; i < matrix->max_len; i++) {
        blucket = matrix->data[i];
        if(blucket == NULL) {
            continue;
        } else {
            status = blucket_free(blucket);
            if(status != STAT_SUCCESS)
                return status;
            else
                continue;
        }
    }
    
    return matrix_init(matrix);
}

Element *matrix_find_by_pos(Matrix *matrix, unsigned row, unsigned col) {
    unsigned index = hash_generator(element, matrix);
    return element_seek_by_pos(matrix->data[index], row, col);
}

Element *matrix_find_by_val(Matrix *matrix, int value) {
    unsigned index = hash_generator(element, matrix);
    return element_seek_by_pos(matrix->data[index], value);
}