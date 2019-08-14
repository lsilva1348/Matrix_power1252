#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

//TEST SUR MATRICE
void matrix_init_test(void);
void matrix_set_test(void);
void matrix_get_test(void);
void matrix_add_test(void);
void matrix_transpose_test(void);
void matrix_mult_test(void);
void matrix_save_test(void);
void matrix_load_test(void);
//TEST SUR SP_MATRICE
void sp_matrix_init_test(void);
void sp_matrix_set_test(void);
void sp_matrix_get_test(void);
void sp_matrix_add_test(void);
void sp_matrix_transpose_test(void);
void sp_matrix_mult_test(void);
void sp_matrix_save_test(void);
void sp_matrix_load_test(void);
//TEST CONVERSION
void sp_matrix_to_matrix_test(void);
void matrix_to_sp_matrix_test(void);
void matrix_init_test(){
    //TEST MATRICE NULLE -> DOIT RENVOYER NULL
    struct matrix *test=NULL;
    test=matrix_init(0,0);
    //CU_ASSERT(test==NULL);
    matrix_free(test);
    test=NULL;

    //TEST LIGNE PUIS COLONNE NULLE -> RENVOI NULL
    test=matrix_init(0,1);
    //CU_ASSERT(test==NULL);
    matrix_free(test);
    test=NULL;

    test=matrix_init(1,0);
    //CU_ASSERT(test==NULL);
    matrix_free(test);
    test=NULL;

    //TEST SI MARCHE
    test=matrix_init(4,8);


}
