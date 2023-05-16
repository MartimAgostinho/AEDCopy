#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arqueologo.h"

#define NDIM 2 //numero de dimensoes na posicao

void strToLower(char * str);

struct _arqueologo{
    int merito;
    char* nomeArqueologo;
    int penalizacoesCount;   //se penalizacoesCount < 0, o arqueologo esta desclassificado
    int pos[NDIM];          //[0] = x,[1] = y 
};                         //.h tem macros "COLUNA"->x e "LINHA"->y

arqueologo criaArqueologo(char* nomeArqueologo){//cria um arqueologo atribuindo-lhe um nome passado por parametro
    
    arqueologo arq=(arqueologo) malloc(sizeof(struct _arqueologo));
    if(arq == NULL){ return NULL; }

    arq->nomeArqueologo = (char *)malloc( sizeof(char) * (strlen(nomeArqueologo) + 1 ) );
    if(arq->nomeArqueologo == NULL){ 
        free(arq);
        return NULL;
    }
    strcpy(arq->nomeArqueologo,nomeArqueologo);

    arq->penalizacoesCount  = 0;
    arq->pos[LINHA]         = 0;
    arq->pos[COLUNA]        = 0;
    arq->merito             = 0;
    
    return arq;
}

void destroi_arq(arqueologo arq){
    free(arq->nomeArqueologo);
    free(arq);
}

void destroi_arqgen(void * arq){
    destroi_arq((arqueologo) arq);
}

void addMeritoArqueologo(arqueologo arq, int pontos){//modifica o valor do merito do arqueologo selecionado
    arq->merito += pontos;
}

void incrPenalizacoesArqueologo(arqueologo arq){//incrementa a quantidade de penalizacoes do arqueologo
    arq->penalizacoesCount++;
}

void moverArqueologo(arqueologo arq, int x, int y){//muda a posicao do arqueologo
    arq->pos[COLUNA] += x;
    arq->pos[LINHA]  += y;
}

void desclassificaArqueologo(arqueologo arq){//desclassifica o arqueologo
    //se penalizacoesCount for negativo, o arqueologo foi desclassificado
    arq->penalizacoesCount = -100;
}

int getMeritoArqueologo(arqueologo arq){//retorna o merito do arqueologo
    return arq->merito;
}

char* getNomeArqueologo(arqueologo arq){//retorna o nome do arqueologo
    return arq->nomeArqueologo;
}

int getPenalizacoesArqueologo(arqueologo arq){//retorna a quantidade de penalizacoes do arqueologo
    return arq->penalizacoesCount;
}

int *getPosicaoArqueologo(arqueologo arq){//retorna a posicao do arqueologo
    return arq->pos;
}

arqueologo comparar_estrela(arqueologo arq1,arqueologo arq2){
    
    if( arq2 == NULL ){ return arq1; }
    
    if( arq1 == NULL ){ return arq2; }

    if(arq1->merito == arq2->merito){
        
        if(arq1->penalizacoesCount==arq2->penalizacoesCount){
            
            char str1[40],str2[40];
            //Copia para nao mudar o nome do arqueologo
            strcpy(str1,arq1->nomeArqueologo);
            strcpy(str2,arq2->nomeArqueologo);
            //strToLower para podere usar o strcmp como meios de comparar a ordem alfabetica
            strToLower(str1);
            strToLower(str2);
            return strcmp(str1,str2)>0 ? arq2 : arq1;   
        }
        else{
            return arq1->penalizacoesCount>arq2->penalizacoesCount ?  arq2 :  arq1;
        }
    }
    else{
        return arq1->merito>arq2->merito ? arq1 : arq2;
    }
}

void strToLower(char * str){
    for(int i=0;i<strlen(str);i++){
        if(str[i]>'A' && str[i]<'Z'){
            str[i]+='a'-'A';
        }
    }
}

