#include "terreno.h"

#include <stdio.h>
#include <stdlib.h>
struct _terreno{        
    int ** terr;
    unsigned int dim_x;  //sempre positivo 
    unsigned int dim_y; //sempre positivo
    unsigned int riqueza;
};

terreno cria_terreno(unsigned int dim_x,unsigned int dim_y){
 
    terreno t = (terreno)malloc(sizeof(struct _terreno));
    int i,j;

    if (t == NULL) { return NULL; }
    
    t->terr = (int **)malloc(sizeof(int *) * dim_y);

    if (t->terr == NULL) { 
        free(t);
        return NULL;
    }

    for(j = 0;j < dim_y;j++){ 
        
        t->terr[j] = (int *)malloc(sizeof(int) * dim_x);
        
        if (t->terr[j] == NULL) { 
            for (i = 0; i < j; i++) {
                free(t->terr[i]);
            }
            free(t->terr);
            free(t);
            return NULL;
        }
    }

    for(i = 0;i < dim_y;i++){ //preenche com talhoes a 0
        for(j = 0;j < dim_x;j++){
            t->terr[i][j] = 0;
        }
    }
    
    t->dim_x = dim_x;
    t->dim_y = dim_y;
    return t;
}

//Prerequisito l = t.linhas c = t.colunas
void preencher_terreno(terreno t,int l,int c,int ** mat){
    
    int i,j;

    for(i = 0;i < l;i++){
        for(j = 0;j < c;j++){
            t->terr[i][j] = mat[i][j];
            t->riqueza   +=  mat[i][j];
        }
    }
}

void destroi_terreno(terreno t ){

    int j = get_riqueza(t);

    for(j = t->dim_y - 1;j >= 0;j--){
        free(t->terr[j]);
    }
    free(t->terr);
    free(t);
}

int escavar(terreno t, int c , int l){
    
    --c;--l;
    int val = t->terr[l][c];
    
    if(val >= 0){
        t->riqueza -= val;
        t->terr[l][c] = -1;
        return val;
    }
    return t->terr[l][c]--;
}

int gett_val(terreno t,int x,int y){ return t->terr[y-1][x-1]; }

unsigned int gett_dimx(terreno t){ return t->dim_x;}

unsigned int gett_dimy(terreno t){ return t->dim_y; }

unsigned get_riqueza(terreno t){ return t->riqueza; }

/*
void load_riqueza(terreno t){
    
    int i,j;
    t->riqueza = 0;
    for (i=0;i<t->dim_y;i++){

        for(j=0;j<t->dim_x;j++){
           
            if( t->terr[i][j] < 0 ){ continue; }
            t->riqueza += t->terr[i][j];
        }
    }
}*/
