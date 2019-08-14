
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

    void sp_matrix_show(const struct sp_matrix* amigo){

        if(!amigo){
        printf("SP_SHOW() ERROR 1");
        exit(EXIT_FAILURE);
        }
        struct line *temp_l=NULL;
        struct elem *temp_e=NULL;

        if(!amigo->lines){
            printf("\nMatrice nulle \n");

        }
        else{
            printf("\nMATRICE %dX%d mis à l'adresse : %p\n\t",amigo->nlines,amigo->ncols,amigo);

            temp_l=amigo->lines;
            while(temp_l!=NULL){
            temp_e=temp_l->elems;
            printf("\t");
            printf("Ligne %d |\n\t",temp_l->i);
                while(temp_e!=NULL){
                    printf("Colonnes %d : Value : %f\n\t", temp_e->j,temp_e->value);
                    if(temp_e->next){

                        temp_e=temp_e->next;
                    }
                    else{
                        temp_e=NULL;
                    }
                }
                if(temp_l->next){
                temp_l=temp_l->next;
                }
                else{
                    temp_l=NULL;
                }
            }
            printf("\n");


        }
    }

        // POUR CHECK-UP
    void matrix_show(const struct matrix *matrix){
    if(matrix==NULL){
        printf("SHOW() ERROR 1\n");
        exit(EXIT_FAILURE);
    }

    else{
        int i,j;
        int lines=matrix->nlines;
        int cols=matrix->ncols;
        printf("    =====================================================\n");
        printf("            MATRICE de l'adresse = %p\n\n", matrix);
        for (i = 0; i < lines; i++) {
            printf("       ");
            for (j = 0; j < cols; j++){
                printf(" %f ", *(*((matrix->elems)+i)+j));
            }
            printf("\n");
        }
        printf("    =====================================================\n");
    }
    }

    //POUR REMPLIR MATRICE
    void matrix_fill(struct matrix *matrix){
        if(matrix==NULL){
            printf("FILL() ERROR 1\n");
             exit(EXIT_FAILURE);
        }
        else{
            int i,j;
            int lines=matrix->nlines;
            int cols=matrix->ncols;
            double count=1;
            for (i = 0; i < lines; i++) {
                for (j = 0; j < cols; j++){
                    (matrix->elems)[i][j]=count;
                    count++;

                }
            }
        }
    }
int main()
{



    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++ DEBUT DU PROG++++++++++++++++++++++++++++


    //double op = 9.5;
    //struct matrix *maMatrice= matrix_init(5,6);
    struct sp_matrix *miMatrice=NULL;
    miMatrice=sp_matrix_init(1,6,6);
    //struct sp_matrix *moMatrice=NULL;
    //moMatrice=sp_matrix_init(1,4,3);
    //struct sp_matrix *muMatrice=NULL;
    //muMatrice=sp_matrix_init(1,4,4);
    //struct matrix *addMatrice= matrix_init(2,2);
    //matrix_fill(maMatrice);
    //matrix_fill(addMatrice);
    sp_matrix_set(miMatrice,2,1,1);
    sp_matrix_set(miMatrice,0,0,1);
    sp_matrix_set(miMatrice,0,1,2);
    sp_matrix_set(miMatrice,0,2,3);
    sp_matrix_set(miMatrice,4,2,6);
    sp_matrix_set(miMatrice,5,1,5);
    sp_matrix_set(miMatrice,2,3,1);
    sp_matrix_set(miMatrice,1,0,4);
    //sp_matrix_set(moMatrice,2,1,1);
    //sp_matrix_set(moMatrice,3,3,43);
    //sp_matrix_set(moMatrice,0,0,1);
    //sp_matrix_set(moMatrice,0,1,2);
    //sp_matrix_set(moMatrice,0,2,3);
    //sp_matrix_set(moMatrice,1,2,6);
    //sp_matrix_set(moMatrice,1,1,5);

    //sp_matrix_set(moMatrice,1,0,4);

    //sp_matrix_set(miMatrice,99,78,593.65);
    //sp_matrix_show(miMatrice);
    struct matrix *result=NULL;
    result=sp_matrix_to_matrix(miMatrice);
    matrix_show(result);





    //matrix_set(maMatrice,0,1,9.5456);
    //matrix_show(maMatrice);

    //matrix_show(matrix_add(maMatrice,addMatrice));

    //matrix_show(matrix_transpose(maMatrice));
    //matrix_show(matrix_mult(maMatrice,addMatrice));
    //FREE TIME
    sp_matrix_save(miMatrice,"TEST");
    //sp_matrix_show(sp_matrix_load("TEST"));


    printf("MATRICE: %u X %u : Ligne :%u  Colonne :%u Valeur:%f\n",miMatrice->nlines,miMatrice->ncols,miMatrice->lines->i,miMatrice->lines->elems->j,
    miMatrice->lines->elems->value);
    printf("MATRICE: %u X %u : Ligne :%u  Colonne :%u Valeur:%f\n",miMatrice->nlines,miMatrice->ncols,miMatrice->lines->next->i,miMatrice->lines->next->elems->j,
    miMatrice->lines->next->elems->value);
    printf("MATRICE: %u X %u : Ligne :%u  Colonne :%u Valeur:%f\n",miMatrice->nlines,miMatrice->ncols,miMatrice->lines->next->i,miMatrice->lines->next->elems->next->j,
    miMatrice->lines->next->elems->next->value);
    printf("MATRICE: %u X %u : Ligne :%u  Colonne :%u Valeur:%f\n",miMatrice->nlines,miMatrice->ncols,miMatrice->lines->next->next->i,miMatrice->lines->next->next->elems->j,
    miMatrice->lines->next->next->elems->value);

    //matrix_free(maMatrice);
    //sp_matrix_free(muMatrice);
    sp_matrix_free(miMatrice);
    //sp_matrix_free(moMatrice);
    matrix_free(result);
    //matrix_free(addMatrice);
    return 0;
}

