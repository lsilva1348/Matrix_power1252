#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


/* matrix_init
 * Créer une nouvelle matrice tableau.
 *
 * @nlines: nombre de lignes
 * @ncols: nombre de colonnes
 * @return: pointeur vers la matrice ou NULL si erreur
 *
 * Préconditions: @nlines > 0 && @ncols > 0
 * Postconditions: Les éléments de la nouvelle matrice sont initialisés à 0.
 *		   @m->nlines > 0 && @m->ncols > 0
 */
struct matrix *matrix_init(unsigned int nlines, unsigned int ncols){
        //Initialisation de la matrice
        struct matrix *init=NULL;
        init=(struct matrix *) malloc(sizeof(struct matrix));
        if(init==NULL){
            printf("INIT() ERROR 0 \n");
            return NULL;
        }
        if(nlines<=0 || ncols<=0){
            printf("MUST CHOOSE LINES AND COLS GREATER THAN ZERO");
            return NULL;
        }
        double *elemento=NULL;
        double len=0;
        int i,j;
        len=sizeof(double *)*nlines + sizeof(double)*nlines*ncols;
        init->elems=(double **)malloc(len);
        if (init->elems==NULL){
            printf("FAIL \n");
            return NULL;
        }

        //ptr is now pointing to the first  element
        elemento=(double *)((init->elems)+nlines);

        for(i =0;i<nlines;i++){
         (init->elems)[i]= (elemento+ncols*i);
        }
        for (i =0; i<nlines ;i++){
            for(j=0; j<ncols; j++){
            *(*((init->elems)+i)+j)=0;
            }
         }
        init->ncols=ncols;
        init->nlines=nlines;
   return init;
}



/* matrix_free
 * Libère la mémoire allouée à une matrice tableau.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void matrix_free(struct matrix* matrix){
    if(matrix==NULL){
        printf("PAS DE MATRICE A SUPPRIMER");
        exit(EXIT_FAILURE);

    }
    if(matrix->elems==NULL){
        free(matrix);
    }
    else{
    free(matrix->elems);
    free(matrix);
    }
    printf("Matrice a l'adresse : %p libérée\n",matrix);
}




/* matrix_get
 * Récupère la valeur d'un élément de la matrice tableau.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @return: valeur de l'élément (@i,@j) de la matrice
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: @matrix est inchangé.
 */




double matrix_get(const struct matrix *matrix, unsigned int i, unsigned int j){
    if(i>matrix->nlines || j>matrix->ncols || i<0 || j<0){
        printf("GET() SEGFAULT MORON");
        exit(EXIT_FAILURE);
        }
    return  *(*((matrix->elems)+i)+j);
}





/* matrix_set
 * Définit la valeur d'un élément de la matrice tableau.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @val: valeur à définir
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: L'élément (@i,@j) de la matrice @matrix vaut @val.
 */
int matrix_set(struct matrix *matrix, unsigned int i, unsigned int j, double val){
        if(i>=matrix->nlines || j>=matrix->ncols || i<0 || j<0){
        printf("SET() SEGFAULT MORON");
        return -1;
        }
    //printf("Valeur de matrix[%d][%d] = %f\n",i,j,*(*((matrix->elems)+i)+j));
    *(*((matrix->elems)+i)+j)=val;
    //printf("Valeur de matrix[%d][%d] after = %f\n",i,j,*(*((matrix->elems)+i)+j));
    return 0;

}




/* matrix_add
 * Additionne deux matrices tableau.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice tableau résultant de l'addition de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct matrix *matrix_add(const struct matrix *m1, const struct matrix *m2){
    //TEST NULL
    if(m1==NULL || m2==NULL){
        printf("ADD() ERROR 1");
        return NULL;
    }
    //TEST MEME TAILLE
    if(m1->nlines!=m2->nlines || m1->ncols!=m2->ncols){
        printf("ADD() ERROR 2\n");
        return NULL;
    }
    unsigned int lines=m1->nlines, cols=m1->ncols;
    int i,j;
    double tot=0;

    //CREATION NOUVELLE MATRICE RESULT
    struct matrix *result=NULL;
    result=matrix_init(lines,cols);
    //ADDITION DES DEUX DANS RESULT
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
            tot=((m1->elems)[i][j])+((m2->elems)[i][j]);
            (result->elems)[i][j]=tot;
        }
    }
    return result;
}





/* matrix_transpose
 * Calcule la transposée d'une matrice tableau.
 *
 * @matrix: opérande
 * @return: Matrice tableau étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */





struct matrix *matrix_transpose(const struct matrix *matrix){

    //TEST NULL
    if(matrix==NULL){
        printf("ADD() ERROR 1");
        return NULL;
    }
    int i,j;
    //INTERVERTIR LE NOMBRE DE LIGNE/COLONNES

    unsigned int cols=matrix->nlines, lines=matrix->ncols;
    double **momo=matrix->elems;
    struct matrix *transp=NULL;
    transp= matrix_init(lines,cols);
    double **res=transp->elems;
    //TRANSPOSITION
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
            res[i][j]=momo[j][i];
        }
    }
    return transp;
}






/* matrix_mult
 * Multiplie deux matrices tableau.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice tableau résultant de la multiplication de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct matrix *matrix_mult(const struct matrix *m1, const struct matrix *m2){
    //TEST NULL
    if(m1==NULL || m2==NULL){
        printf("MULT() ERROR 1");
        return NULL;
    }
    //TEST TAILLE CORRECT
    if(m1->ncols!=m2->nlines){
        printf("MULT ERROR 2\n");
        return NULL;
    }
    unsigned int lines=m1->nlines,cols=m2->ncols;
    //INITIATION MATRICE RESULT
    struct matrix *mult=NULL;
    mult=matrix_init(lines,cols);
    //INITIALISATION VAR
    double **momo=m1->elems,**mimi=m2->elems,**res=mult->elems;
    int i,j,k;
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
            for(k=0;k<m1->ncols;k++){
            res[i][j]+=momo[i][k]*mimi[k][j];
            }
        }
    }
    return mult;
}





/* matrix_save
 * Sauvegarde une matrice tableau dans un fichier
 *
 * @matrix: matrice tableau à sauvegarder
 * @path: chemin du fichier vers lequel sauvegarder la matrice
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: matrix != NULL
 * Postconditions: Le fichier @path contient la matrice tableau sauvegardée
 */
 /*MATRICE DE LA FORME :   @matrix->nlines @matrix->ncols
  *                         X X X
  *                         X X X
  *                         X X X
  *
  */
int matrix_save (const struct matrix *matrix, char *path){
    if(matrix==NULL || path==NULL){
        printf("SAVE() ERROR 1\n");
        return -1;
    }
    //OUVERTURE FICHIER
    FILE *outFile= fopen(path,"w+");
    if(outFile==NULL){
        printf("SAVE() Erreur ouverture\n");
        return -1;
    }

    //ECRITURE DANS FICHIER
    int lines=matrix->nlines,cols=matrix->ncols;
    fprintf(outFile,"%d %d\n",lines,cols);
    int i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
            fprintf(outFile,"%lf ",(matrix->elems)[i][j]);

        }
        fprintf(outFile,"\n");
    }
    fclose(outFile);
    return 0;
}






/* matrix_load
 * Charge une matrice tableau à partir d'un fichier
 *
 * @path: chemin du fichier à partir duquel charger la matrice
 * @return: matrice tableau contenue dans le fichier @path, NULL en cas d'erreur
 *
 * Préconditions: path != NULL
 * Postconditions: @path est inchangée
 */

struct matrix *matrix_load (char *path){
    if(path==NULL){
        return NULL;
    }
    //OUVERTURE FICHIER
    FILE * inFile = fopen(path,"r");
    if(inFile==NULL){
        printf("LOAD() Erreur ouverture\n");
        return NULL;
    }
    unsigned int lines,cols;
    fscanf(inFile,"%u",&lines);
    fscanf(inFile," %u",&cols);
    struct matrix *load=NULL;
    load=matrix_init(lines,cols);
    double number=0;
    int i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
        fscanf(inFile,"%lf",&number);
        matrix_set(load,i,j,number);
        }
    }


    //FERMETURE FICHIER
    fclose(inFile);
    return load;

}

//=================================================================================================================================================
//===========================================================SP_MATRIX=============================================================================
//=================================================================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++START INIT TIME+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* sp_matrix_init
 * Créer une nouvelle matrice creuse.
 *
 * @precision: précision des élements de la matrice
 * @nlines: nombre de lignes
 * @ncols: nombre de colonnes
 * @return: pointeur vers la matrice ou NULL si erreur
 *
 * Préconditions: @nlines > 0 && @ncols > 0
 * Postconditions: Les éléments de la nouvelle matrice sont initialisés à 0.
 *		   @m->nlines > 0 && @m->ncols > 0
 */
struct sp_matrix *sp_matrix_init(double precision, unsigned int nlines, unsigned int ncols){

    struct sp_matrix *init=NULL;
    init=(struct sp_matrix *)malloc(sizeof(struct sp_matrix));
    //CONDITIONS;
    if(init==NULL){
        printf("INIT_SP() ERROR 0 \n");
        return NULL;
    }
    if(nlines<=0 || ncols<=0){
            printf("MUST CHOOSE LINES AND COLS GREATER THAN ZERO\n");
            return NULL;
        }
    //INITIATION
    //initie lines à NULL car tous les elems de la matrice sont nuls
    init->lines=NULL;
    init->nlines=nlines;
    init->ncols=ncols;
    init->precision=precision;

    return init;
}

/*sp_matrix_init_lines
 *Crée une nouvelle ligne i
 *
 *@lignes: le numéro de la ligne
 *@elems: le premier element à rajouter;
 *@return: un pointeur vers ligne où on aura placé elems ou NULL si erreur
 *
 *Pré-Conditions= @lignes<= nombrede lignes max de la matrice ou elle sera introduite && @lignes ne doit pas déjà etre présente dans la matrice
 *                @elems!=NULL
 *Post-Conditions=@init->elems !=NULL;
 */
 struct line *sp_matrix_init_line(unsigned int lignes, struct elem *elems){
    struct line *init=NULL;
    init=(struct line *) malloc(sizeof(struct line));
    if(init==NULL){
    printf("INIT_LINE_SP() ERROR 0 \n");
    return NULL;
    }
    init->elems=elems;
    init->i=lignes;
    init->next=NULL;
    return init;
 }

 /*sp_matrix_init_cols
 *Crée un nouvel élément j et attribue la valeur NULL à son next;
 *
 *@cols: le numéro de la colonne
 *@value: valeur de l'élement ;
 *@return: un pointeur vers l'élément ou NULL si erreur
 *
 *Pré-Conditions= @cols<= nombre de cols max de la matrice ou elle sera introduite && @cols ne doit pas déjà etre présent dans la matrice
 *Post-Conditions= /
 */

 struct elem *sp_matrix_init_elem(unsigned int cols, double value){
    struct elem *init=NULL;
    init=(struct elem *) malloc(sizeof(struct elem));
    if(init==NULL){
    printf("INIT_LINE_SP() ERROR 0 \n");
    return NULL;
    }
    init->j=cols;
    init->value=value;
    init->next=NULL;
    return init;
 }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END INIT TIME+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++START FREE-TIME+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* sp_matrix_free
 * Libère la mémoire allouée à une matrice creuse.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void sp_matrix_free(struct sp_matrix *matrix){
    if(matrix==NULL){
        printf("PAS DE MATRICE A SUPPRIMER");
        exit(EXIT_FAILURE);

    }
    else{
        //ON CREE UNE STRUCT POUR RETENIR LE NOEUD A SUPPRIMER  LA MATRICE
        struct line * temp_l=NULL;
        struct elem * temp_e=NULL;

        while((temp_l=matrix->lines)!=NULL){ //ON ASSIGNE TEMP_L AU DEBUT ET ON S'ARRETE SI MATRIX EST VIDE
                while((temp_e=matrix->lines->elems)!=NULL){//ON ASSIGNE TEMP_E AU DEBUT DE LA LISTE ET ON S'ARRETE SI LIGNE EST VIDE
                matrix->lines->elems=matrix->lines->elems->next;//LE PREMIER ELEMENT DEVIENT LE PREMIER ELEMENT->NEXT
                free(temp_e);//ON LIBERE L'ANCIEN PREMIER ELEMENT
                temp_e=NULL;//ASSIGNER A NULL;
                }
            matrix->lines=matrix->lines->next;//SAME QUE POUR LES ELEMENTS
            free(temp_l);
            temp_l=NULL;

        }
        printf("Matrice à l'adresse : %p | libérée\n",matrix);
        free(matrix);
        matrix=NULL;
    }

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END FREE TIME+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*checkup
 *Renvoie si la ligne en question existe ou non.
 *@lines: la ligne à chercher
 *@i: le numéro de la ligne à vérifier
 *@return: 1 si trouver, 0 sinon;
 *
 */
int checkup_line(struct line * lines , unsigned int i){
    if(lines==NULL){
        return 0;
    }

    while(lines!=NULL){
        if(lines->i==i){
            printf("Ligne Trouvée \n ");
            return 1;
        }
        //printf("INTHATSHIT\n");
        lines=lines->next;
    }
      printf("Ligne PAS Trouvée \n ");
    return 0;

}
/*checkup_elems
 *Renvoie si l'element en question existe ou non.
 *@elems: la ligne à chercher
 *@j: le numéro de la colonne à vérifier
 *@return: 1 si trouver, 0 sinon;
 *
 */
int checkup_elems(struct elem *elems,unsigned int j){
    if(elems==NULL){
        return 0;
    }
    while(elems!=NULL){
        if(elems->j==j){
         printf("Elem Trouvé \n ");
            return 1;
        }
        elems=elems->next;
    }
    printf("Elem PAS Trouvé \n ");
    return 0;

}


/* sp_matrix_set
 * Définit la valeur d'un élément de la matrice creuse.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @val: valeur à définir
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: L'élément (@i,@j) de la matrice @matrix vaut @val.
 */
int sp_matrix_set(struct sp_matrix *matrix, unsigned int i, unsigned int j, double val){
    /* CAS POSSIBLE :
    *       -1: @matrix->lines=NULL si VAL<@matrix->precision alors -> on fait rien ; OK
    *       -2: val==0 :
    *           -2.1-> matrix[i][j] != existe : vérifie ligne puis elems; OK
    *           -2.2-> on doit suprrimer l'élément:
    *               -2.2.1->si autre element dans la ligne:
    *                                           -2.2.1.1: Si autre que premier; OK
    *                                           -2.2.1.2: Si premier; OK
    *               -2.2.2->si seul élement=!0 : free(elems j) -> free(ligne i):
    *                                                               -2.2.2.1: Premiere ligne + pas d'autre qui existe; OK
    *                                                               -2.2.2.2: Premiere ligne + autre ligne existante; OK
    *                                                               -2.2.2.3: Pas premiere + Autre ligne existante; OK
    *       -3: val!=0:
    *           -3.1: Ligne existe:
    *               -3.1.1: Elems existe déjà ->change la valeur; OK
    *               -3.1.2: ELems existe pas-> on rajoute un nouvel élément au bon endroit:
    *                       -3.1.2.1 -> Element devient tete de liste; OK
    *                       -3.1.2.2 -> Element autre part; OK
    *           -3.2: Ligne !existe->crée un nouvel elem puis on crée une nouvelle liste -> on place la liste:
    *               -3.2.1: Ligne devient tete de matrice;
    *               -3.2.2: Ligne autre part;
    */
    //--------------------Pre-conditions-----------------------
    if (!matrix){
        printf("SET() ERROR 1 Not existing");
        return -1;
    }
    if (i<0 || i>=matrix->nlines || j<0 || j>=matrix->ncols){
        printf("SET() ERROR 2 Not in the matrix\n");
        return -1;
    }
    printf("\n ============== \n");
    //VALEUR DE VAL MISE A ZERO SI |@val|<@matrix->precision
    if(fabs(val)<matrix->precision){
    val=0;
    printf("VAL==ZERO\n");
    }
    //-------------------CAS 1---------------------
    if(matrix->lines==NULL){
        if(val==0){
            return 0;
        }
        else{
            printf("SET CAS 1\n");
            struct elem *set_elem=NULL;
            set_elem=sp_matrix_init_elem(j,val);
            struct line *set_line=NULL;
            set_line=sp_matrix_init_line(i,set_elem);
            matrix->lines=set_line;
            return 0;
        }
    }
    else{


    //-------------------CAS 2---------------------------
        if(val==0){
            // CAS 2.1
            //ON CREE NOTRE RUNNER
            struct elem *temp_e=NULL;
            struct line *temp_l=NULL;
            temp_l=matrix->lines;
            //REGARDE SI LIGNE EXISTE
            if(checkup_line(temp_l,i)){
                //ON PLACE LE CURSEUR AU BONNE ENDROIT
                while(temp_l->i!=i){
                    temp_l=temp_l->next;
                }
                temp_e=temp_l->elems;
                //REGARDE SI L'ELEM EXISTE
                if(checkup_elems(temp_e,j)){
                //CAS 2.2

                    if(temp_e->next!=NULL){
                    //CAS 2.2.1

                        if(temp_l->elems->j!=j){
                            //CAS 2.2.1.1
                            printf("CAS 2.2.1.1\n");
                            struct elem * temp_e_bis=NULL;
                            temp_e_bis=temp_l->elems;

                            while(temp_e->j!=j){
                                temp_e=temp_e->next;
                            }
                            while(temp_e_bis->next!=temp_e){
                                temp_e_bis=temp_e_bis->next;
                            }
                            temp_e_bis->next=temp_e->next;
                            free(temp_e);
                            temp_e=NULL;
                            return 0;
                        }
                        else{

                            printf("CAS 2.2.1.2\n");
                            struct elem * temp_e_bis=NULL;
                            temp_e_bis=temp_l->elems;
                            temp_l->elems=temp_e_bis->next;
                            free(temp_e_bis);
                            temp_e_bis=NULL;
                            return 0;
                        }
                    }
                    //CAS 2.2.2
                    else{

                        free(temp_e);
                        struct line *temp_l_bis=NULL;
                        temp_l_bis=matrix->lines;

                        if(temp_l_bis==temp_l){
                            //CAS 2.2.2.1

                            if(temp_l_bis->next==NULL){
                                printf("CAS 2.2.2.1\n");
                                free(temp_l);
                                temp_l=NULL;
                                matrix->lines=NULL;
                                return 0;
                            }
                            //CAS 2.2.2.2

                            else{
                                printf("CAS 2.2.2.2\n");
                                matrix->lines=temp_l->next;
                                free(temp_l);
                                temp_l=NULL;
                                return 0;
                            }
                        }
                        else{

                            //CAS 2.2.2.3
                            printf("CAS 2.2.2.3\n");
                            while(temp_l_bis->next!=temp_l){
                                temp_l_bis=temp_l_bis->next;
                            }
                            temp_l_bis->next=temp_l->next;
                            free(temp_l);
                            temp_l=NULL;
                            return 0;
                        }
                    }
                }
                else{
                printf("SET CAS 2.1\n");
                    return 0;
                }

            }
            else{
            printf("SET CAS 2.1\n");
                return 0;
            }
        }
    //-----------------------------------------------CAS 3-------------------------------------------------------------
        else{
            //ON CREE NOTRE RUNNER
            struct elem *temp_e=NULL;
            struct line *temp_l=NULL;

            temp_l=matrix->lines;

            //SI LIGNE EXISTE
            if(checkup_line(temp_l,i)){
                //CAS 3.1
                //printf("3\n");
                while(temp_l->i!=i){
                    temp_l=temp_l->next;
                }
                temp_e=temp_l->elems;
                if(checkup_elems(temp_e,j)){
                    //CAS 3.1.1
                    printf("SET CAS 3.1.1\n");
                    while(temp_e->j!=j){
                        temp_e=temp_e->next;
                    }
                    temp_e->value=val;
                    return 0;
                }
                else{
                    //CAS 3.1.2

                    struct elem *nouveau=NULL;
                    nouveau=sp_matrix_init_elem(j,val);
                    if(temp_e->j>j){
                        //CAS 3.1.2.1
                        printf("SET CAS 3.1.2.1\n");
                        nouveau->next=temp_e;
                        temp_l->elems=nouveau;
                        return 0;
                    }
                    else{
                        //CAS 3.1.2.2
                        printf("SET CAS 3.1.2.2\n");
                        while(temp_e->next!=NULL && temp_e->next->j < j){
                            temp_e=temp_e->next;

                        }

                        nouveau->next=temp_e->next;
                        temp_e->next=nouveau;
                        return 0;

                    }
                }
            }

            else{
                //CAS 3.2
                //printf("DEBUT 3.2 \n");
                struct elem *set_elem=NULL;
                set_elem=sp_matrix_init_elem(j,val);
                struct line *set_ligne=NULL;
                set_ligne=sp_matrix_init_line(i,set_elem);

                if(temp_l->i>i){
                    //CAS 3.2.1
                    printf("SET CAS 3.2.1\n");
                    set_ligne->next=temp_l;
                    matrix->lines=set_ligne;
                    return 0;
                }
                else{
                    //CAS 3.2.2
                    printf("SET CAS 3.2.2\n");
                    while(temp_l->i<i && temp_l->next){

                        temp_l=temp_l->next;
                    }
                    //printf("OUTWHILE\n");
                    set_ligne->next=temp_l->next;
                    temp_l->next=set_ligne;
                    return 0;
                }
            }
        }
    }
    return -1;
}

/* sp_matrix_get
 * Récupère la valeur d'un élément de la matrice creuse.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @return: valeur de l'élément (@i,@j) de la matrice
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: @matrix est inchangé.
 */
double sp_matrix_get(const struct sp_matrix *matrix, unsigned int i, unsigned int j){
    if(matrix==NULL){
        printf("GET() ERROR 1");
        return 0;
    }
    if (i<0 || i>=matrix->nlines || j<0 || j>=matrix->ncols){
        printf("SET() ERROR 2 Not in the matrix\n");
        return 0;
    }
    else{
        struct elem *temp_e=NULL;
        struct line *temp_l=NULL;
        temp_l=matrix->lines;
        if(checkup_line(temp_l,i)){
            while(temp_l->i!=i){
                temp_l=temp_l->next;
            }
            temp_e=temp_l->elems;
            if(checkup_elems(temp_e,j)){
                while(temp_e->j!=j){
                    temp_e=temp_e->next;
                }
                return temp_e->value;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
}

/* sp_matrix_add
 * Additionne deux matrices creuses.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice creuse résultant de l'addition de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct sp_matrix *sp_matrix_add(const struct sp_matrix *m1, const struct sp_matrix *m2){
    //TEST NULL
    if(m1==NULL || m2==NULL){
        printf("SP_ADD() ERROR 1");
        return NULL;
    }
    //TEST MEME TAILLE
    if(m1->nlines!=m2->nlines || m1->ncols!=m2->ncols){
        printf("SP_ADD() ERROR 2\n");
        return NULL;
    }
    // ON PREND LA PRECISION LA PLUS HAUTE
    double min_preci;
    if(m1->precision<m2->precision){
        min_preci=m2->precision;
    }
    else{
        min_preci=m1->precision;
    }
    //CREATION DE LA NOUVELLE MATRICE
    struct sp_matrix *result=NULL;
    result=sp_matrix_init(min_preci,m1->nlines,m1->ncols);
    if(!result){
        return NULL;
    }

    unsigned int i,j;
    double k;

    for(i=0;i<result->nlines;i++){
        for(j=0;j<result->ncols;j++){
            k= sp_matrix_get(m1,i,j)+sp_matrix_get(m2,i,j);
            //ON TEST ET ON ASSIGNE EN MEME TEMPS;
            if(sp_matrix_set(result,i,j,k)){
                return NULL;
            }
        }
        printf("LIGNE %u DONE", i);
    }
    return result;

}

/* sp_matrix_transpose
 * Calcule la transposée d'une matrice creuse.
 *
 * @matrix: opérande
 * @return: Matrice creuse étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */
struct sp_matrix *sp_matrix_transpose(const struct sp_matrix *matrix){
    if(!matrix){
        printf("SP_TRANSPOSE() ERROR 1");
        return NULL;
    }
    struct sp_matrix *result=NULL;
    result=sp_matrix_init(matrix->precision,matrix->ncols,matrix->nlines);
    if(!result){
        return NULL;
    }
    unsigned int i,j;
    double k;
    for(i=0;i<matrix->nlines;i++){
        for(j=0;j<matrix->ncols;j++){
            k=sp_matrix_get(matrix,i,j);
            if(sp_matrix_set(result,j,i,k)){
                return NULL;
            }
        }
    }

    return result;
}


/* sp_matrix_mult
 * Multiplie deux matrices creuses.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice creuse résultant de la multiplication de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct sp_matrix *sp_matrix_mult(const struct sp_matrix *m1, const struct sp_matrix *m2){
    //TEST NULL
    if(m1==NULL || m2==NULL){
        printf("SP_MULT() ERROR 1");
        return NULL;
    }
    //TEST TAILLE CORRECT
    if(m1->ncols!=m2->nlines){
        printf("SP_MULT ERROR 2\n");
        return NULL;
    }
    // ON PREND LA PRECISION LA PLUS HAUTE
    double min_preci;
    if(m1->precision<m2->precision){
        min_preci=m2->precision;
    }
    struct sp_matrix *result=NULL;
    result=sp_matrix_init(min_preci,m1->nlines,m2->ncols);
    if(!result){
        return NULL;
    }
    unsigned int i,j,k;
    double l;
    for (i=0;i<result->nlines;i++){
        for(j=0;j<result->ncols;j++){
            for(k=0;k<m1->ncols;k++){
                l+=sp_matrix_get(m1,i,k)*sp_matrix_get(m2,k,j);

            }
            if(sp_matrix_set(result,i,j,l)){
                return NULL;
            }
            l=0;

        }
    }
    return result;
}

//===============================================CONVERSION TIME=============================================
/* matrix_to_sp_matrix
 * Transforme une matrice tableau en une matrice creuse.
 *
 * @matrix: matrice tableau à transformer
 * @precision: précision des éléments de la nouvelle matrice creuse
 * @return: matrice creuse correspondante à @matrix ou NULL si erreur
 *
 * Préconditions: matrix != NULL
 * Postconditions: matrix est inchangée && 0 < @precision
 */
struct sp_matrix *matrix_to_sp_matrix (const struct matrix *matrix, double precision){
    if(!matrix){
        printf("CONVERT() ERROR 1");
        return NULL;
    }
    struct sp_matrix *result=NULL;
    result=sp_matrix_init(precision,matrix->nlines,matrix->ncols);
    if(!result){
        return NULL;
    }
    unsigned int i,j;
    double k;
    for(i=0;i<result->nlines;i++){
        for(j=0;j<result->ncols;j++){
            k=matrix_get(matrix,i,j);
            if(sp_matrix_set(result,i,j,k)){
                return NULL;
            }

        }
    }
    return result;

}
/* sp_matrix_to_matrix
 * Transforme une matrice creuse en une matrice tableau.
 *
 * @matrix: matrice creuse à transformer
 * @return: matrice tableau correspondante à @matrix ou NULL si erreur
 *
 * Préconditions: matrix != NULL
 * Postconditions: matrix est inchangée
 */
struct matrix *sp_matrix_to_matrix (const struct sp_matrix *matrix){
    if(!matrix){
        return NULL;
    }
    struct matrix *result=NULL;
    result=matrix_init(matrix->nlines,matrix->ncols);
    if(!result){
        return NULL;
    }
    unsigned int i,j;
    double k;
    for(i=0;i<matrix->nlines;i++){
        for(j=0;j<matrix->ncols;j++){
            k=sp_matrix_get(matrix,i,j);
            if(matrix_set(result,i,j,k)){
                return NULL;
            }
        }
    }
    return result;
}
/* sp_matrix_save
 * Sauvegarde une matrice creuse dans un fichier
 *
 * @matrix: matrice creuse à sauvegarder
 * @path: chemin du fichier vers lequel sauvegarder la matrice
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: matrix != NULL
 * Postconditions: Le fichier @path contient la matrice creuse sauvegardée
 * Exemple 3x3
 *MATRICE DE LA FORME :   @matrix->nlines @matrix->ncols @matrix->precision
 *                         X X X
 *                         X X X
 *                         X X X
 *
 */
int sp_matrix_save (const struct sp_matrix *matrix, char *path){

    if(matrix==NULL || path==NULL){
        printf("SAVE() ERROR 1\n");
        return -1;
    }
    //OUVERTURE FICHIER
    FILE *outFile= fopen(path,"w+");
    if(outFile==NULL){
        printf("SAVE() Erreur ouverture\n");
        return -1;
    }

    //ECRITURE DANS FICHIER
    int lines=matrix->nlines,cols=matrix->ncols;
    fprintf(outFile,"%d %d %lf\n",lines,cols,matrix->precision);
    unsigned int i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
            fprintf(outFile,"%lf ",sp_matrix_get(matrix,i,j));
        }
        fprintf(outFile,"\n");
    }
    fclose(outFile);
    return 0;
}
/* sp_matrix_load
 * Charge une matrice creuse à partir d'un fichier
 *
 * @path: chemin du fichier à partir duquel charger la matrice
 * @return: matrice creuse contenue dans le fichier @path, NULL en cas d'erreur
 *
 * Préconditions: path != NULL
 * Postconditions: @path est inchangée
 */
struct sp_matrix *sp_matrix_load (char *path){
    if(path==NULL){
        return NULL;
    }
    //OUVERTURE FICHIER
    FILE * inFile = fopen(path,"r");
    if(inFile==NULL){
        printf("LOAD() Erreur ouverture\n");
        return NULL;
    }
    unsigned int lines,cols;
    double precision;
    fscanf(inFile,"%u",&lines);
    fscanf(inFile," %u",&cols);
    fscanf(inFile," %lf",&precision);
    struct sp_matrix *load=NULL;
    load=sp_matrix_init(precision,lines,cols);
    double number=0;
    int i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<cols;j++){
        fscanf(inFile,"%lf",&number);
        if(sp_matrix_set(load,i,j,number)){
            fclose(inFile);
            return NULL;
        }
        }
    }


    //FERMETURE FICHIER
    fclose(inFile);
    return load;

}


