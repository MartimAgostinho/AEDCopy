#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arqueologo.h"
#include "sequencia.h"
#include "terreno.h"
#include "dicionario.h"
#include "equipa.h"
#include "iterador.h"
#include "noSimples.h"
#include "concurso.h"

#define MULT 10     //multiplicador de penalizacoes
#define CAP 100   //Capacidade incial da sequencia

equipa* organizaEquipas(concurso c);

/*typedef struct _trino * trino;

struct _trino{

    trino antes;
    trino esq;
    trino dir;
    void *elem;

};*/

struct _concurso{
    sequencia equipasFicheiro;
    //dicionario arqsDescl;
    dicionario equipas;
    terreno campo;
    equipa* organizadas;  
};

//recebe numero de equipas e dimensoes do terreno
concurso cria_concurso(int nequipas,unsigned int dimx,unsigned int dimy){

    concurso c = (concurso)malloc(sizeof(struct _concurso));

    if(c == NULL){ return NULL; }
    
    //nequipas + 1 para nao ter de aumentar a capacidade do dicionario 
    c->equipas = criaDicionario(nequipas + 1, 1);

    if(c->equipas == NULL){ 
        free(c);
        return NULL;
    }
    c->equipasFicheiro = criaSequencia(CAP);
    
    if(c->equipasFicheiro == NULL){ 
        destroiDicionario(c->equipas);
        free(c);
        return NULL;
    }

    c->campo = cria_terreno(dimx, dimy);  
    
    if(c->campo == NULL){ 
        destroiDicionario(c->equipas);
        destroiSequencia(c->equipasFicheiro);
        free(c);
        return NULL;
    }
   
    /*
    c->arqsDescl = criaDicionario(nequipas,1 );
    if(c->arqsDescl == NULL){ 
        destroi_terreno(c->campo);
        destroiDicionario(c->equipas);
        destroiSequencia(c->equipasFicheiro);
        free(c);
        return NULL;
    }*/
    return c;
}

//Precondicao c.equipasFicheiro != NULL
char presair(concurso c){

    iterador it = iteradorDicionario(c->equipas);
    int n = get_riqueza(c->campo);

    while (temSeguinteIterador(it)){
        if(!equipa_desqualificada((equipa)seguinteIterador(it))){
            
            return n;
        }
        
    }
    
    return -1;
    }

int get_nequipas(concurso c){ return tamanhoDicionario(c->equipas); }

void destroi_concurso(concurso c){

    destroi_terreno(c->campo);
    destroiDicionario(c->equipas);
    destroiSeqElems(c->equipasFicheiro, destroi_equipagen);
    //destroiDicEElems(c->arqsDescl, free);
    free(c);
}

void add_equipa(concurso c,int n){

    equipa aux = elementoPosSequencia(c->equipasFicheiro,n);
    
    adicionaElemDicionario(c->equipas, get_equipa_nome( aux ),aux);
}

equipa get_equipa(concurso c,char *nome_equipa){ 
    return elementoDicionario(c->equipas, nome_equipa);
}

char load_equipas(concurso c ,char * filename){
	
    int j,numarq;
    char line[MAXLINESIZE];
    equipa  eq;
    arqueologo arq;
    FILE *teams;
    
    teams = fopen(filename, "r");
    if(teams == NULL){
        return 0;
    }
    
    while( (fscanf(teams, " %d", &numarq) ) != EOF ){
        fscanf(teams, " %[^\n]",line);//nao devia ser gets
        eq = cria_equipa(line);
        
        for( j = 0;j < numarq;++j){
            fscanf(teams, " %[^\n]",line);
            arq = criaArqueologo(line);
            add_elemeq(eq, arq);
        }
        adicionaPosSequencia(c->equipasFicheiro, eq, tamanhoSequencia(c->equipasFicheiro) + 1);
    }
    fclose(teams);
    return 1;
}

unsigned int mostrarRiqueza(concurso c){
    return (get_riqueza(c->campo));
}

char* get_nome_estrela(concurso c, char*nomeEquipa){
    
    arqueologo arq = get_equipa_estrela(get_equipa(c,nomeEquipa));

    if(arq == NULL){ return 0; }

    return getNomeArqueologo( arq );
}

int existe_equipa(concurso c, char*nomeEquipa){
    
    if(!existeElemDicionario(c->equipas,nomeEquipa))
        return 0;
    
    if(equipa_desqualificada(elementoDicionario( c->equipas,nomeEquipa ))){
        return 0;
    }
    return 1;
}

//retorna 0 se a nao encontrar nada
//retorna o nome da equipa "chave" se encontrar
char *find_arqueologo_concurso(concurso c,char *nome_arq){//Devolve nome da equipa
    
    iterador it = iteradorDicionario(c->equipas);
    equipa aux;

    while(temSeguinteIterador(it)){
        
        aux = (equipa) seguinteIterador(it);
        if( existe_arqueologo( aux , nome_arq ) ){
            destroiIterador(it);
            return get_equipa_nome( aux );
        }
    } 
    destroiIterador(it);
    return 0;

}

int comandoReforcoConcurso(concurso c,char* nomeEquipa, char*nomeArq){

    if(!existeElemDicionario(c->equipas,nomeEquipa)){
        return 1;
    }

    equipa eq=elementoDicionario(c->equipas,nomeEquipa);

    if( existe_arqueologo(eq,nomeArq) || arq_desq_eq(eq,nomeArq) ){
        return 2;
    }

    arqueologo arq = criaArqueologo(nomeArq);

    add_elemeq(eq,arq);
    
    muda_estrela(eq, comparar_estrela(arq, get_equipa_estrela(eq) ));

    //load_estrela(eq);//O novo arqueologo pode ser estrela se todos tiverem merito < 0
    
    return 0;
}

//0 se escavou -1 se salto = 0,0 -2 se equipa nao existe -3  se desqualificado e n se talhao escavado 
int executar_escavacao(concurso c,int x,int y,char* nomeEquipa){
    
    if( !x && !y){ return -1; }//o salto nao é nulo 

    if( !existeElemDicionario(c->equipas, nomeEquipa) ){ return -2; }
    
    equipa eq = elementoDicionario(c->equipas, nomeEquipa);

    if( equipa_desqualificada(eq) ){ return -3; }

    arqueologo arq = getit_arq( prox_arq(eq) );
    int *pos = getPosicaoArqueologo(arq);
    int i = x + pos[COLUNA],j = y + pos[LINHA];//i,j sao as posicoes absolutas
    
    //ver se as dim se encontram dentro do terreno
    if( i <= 0 || j <= 0 || i > gett_dimx(c->campo) || j > gett_dimy(c->campo) ){

        desclassificaArqueologo(arq);
        add_meritoeq(eq, - getMeritoArqueologo(arq) );
        add_desq_eq(eq, rm_elemeq(eq, getNomeArqueologo(arq)));
        //retorna 1 se for desqualificada
        load_estrela(eq);
        if(equipa_desqualificada(eq)){ return -5; }
        return -4;
    }
    //aqui sabemos que todas as condicoes se encontram para escavar
    moverArqueologo(arq, x, y);

    int n = escavar(c->campo, i , j );

    if( n < 0 ){
        incrPenalizacoesArqueologo(arq);
        n *= MULT;
    }
    addMeritoArqueologo(arq, n);
    add_meritoeq(eq, n);
    
    n < 0 ? load_estrela(eq) : muda_estrela(eq, comparar_estrela(arq, get_equipa_estrela(eq) ));//compara a estrela com o arquelo que escavou agora e mudar a estrela da equipa 
    
    return 0;
}

void load_campo(concurso cq, int l,int c,int **mat){
    preencher_terreno(cq->campo, l, c, mat);
}

equipa criaEquipaConcurso(char * nome){
    return cria_equipa(nome);
}

equipa criaArqueologoConcurso(equipa e,char * nome){
    arqueologo a;
    a=criaArqueologo(nome);
    add_elemeq(e,a);
    return e;
}

//PRE c,l > 0
char mostrar_talhao(concurso con,int c,int l){ 
    
    if(c > gett_dimx(con->campo) || l > gett_dimy(con->campo)  ){ 
        return 0;
    }

    return gett_val(con->campo, c, l)  > 0 ? '*' : '-';
}

void adicionaSequenciaConcurso(concurso c,equipa e,int eqCount){
    adicionaPosSequencia(c->equipasFicheiro,e,eqCount);
}

int comandoEquipa(concurso c, int numEquipa){
    
    equipa e;

    int aux = tamanhoSequencia(c->equipasFicheiro);
    
    if (numEquipa > aux || numEquipa<0){
        return -2;
    }
    e = elementoPosSequencia(c->equipasFicheiro,numEquipa);
    if(existeElemDicionario(c->equipas,get_equipa_nome(e))){
        return -1;
    }
    add_equipa(c,numEquipa);
    return 0;
}

/*trino criatrino(){return (trino)malloc(sizeof(struct _trino));}
//Falta de tempo para acabar :v
void sort_equipas(concurso c){

    iterador it = iteradorDicionario(c->equipas);
    int i,n = tamanhoDicionario(c->equipas);
    c->organizadas = (equipa *)malloc(sizeof(equipa) * n);
    equipa aux = seguinteIterador(it),aux2;
    trino t,top = criatrino(),taux;
    top->antes = NULL;
    top->dir   = NULL;
    top->esq   = NULL;
    top->elem  = aux;

    for(i = 0;temSeguinteIterador(it);++i){
        aux  = seguinteIterador(it);
        aux2 = top->elem; 
        taux = top;
        
        if( aux2 == compara_equipas(aux, aux2) ){
            top:
            if(taux->esq != NULL && aux != compara_equipas(aux, (taux->esq)->elem) ){
                taux = taux->esq;
                goto top;
            }
            else if( taux->dir != NULL && aux != compara_equipas(aux, (taux->dir)->elem )  )   {
                taux = taux->dir;
                goto top;
            }
            else {
                t = criatrino();
                top->antes = taux;
                top->dir   = NULL;
                top->esq   = taux->dir;
                top->elem  = aux;
            }    
        }
        else{
            t = criatrino();
            top->antes = NULL;
            top->dir   = NULL;
            top->esq   = taux;
            top->elem  = aux;
            top = t;
        }
    }

    taux = top;
    i = 0;

    top1:
    while( taux != NULL && taux->esq != NULL){ 
        taux = taux->esq;
         }

    while( taux != top->esq ){ 
        c->organizadas[i++] = taux->elem;
        if(taux->antes == NULL){ break; }
        taux = taux->antes;
        //free(taux->dir);
        if( taux->dir != NULL ){ 
            taux = taux->dir;
            goto top1;
        }
    }
    for(i = 0;i < n;++i){ printf("EQ:%s\n",get_equipa_nome(c->organizadas[i]) ); }   

}*/

void sort_equipas(concurso c){
    //bubble sort num vetor de equipas
    int dimDic=tamanhoDicionario(c->equipas);
    iterador it= iteradorDicionario(c->equipas);
    int elemNum;
    c->organizadas=(equipa*)malloc(sizeof(equipa)*dimDic);
    for(elemNum=0;temSeguinteIterador(it);elemNum++){
        //Enche o vetor com as equipas desordenadas
        c->organizadas[elemNum]=seguinteIterador(it);
    }
    for (int loop = 0; loop < dimDic-1; ++loop) {
        //O loop vai contar a quantidade de equipas que já estão em ordem, ou seja, a quantidade de vezes que o vetor já foi corrido
        for (elemNum = 0; elemNum < dimDic - loop-1; ++elemNum) {
            //Compara a equipa atual à próxima
            if (compara_equipas(c->organizadas[elemNum], c->organizadas[elemNum+1]) != c->organizadas[elemNum]) {
                //As equipas estão na ordem errada. é preciso trocar
                equipa aux = c->organizadas[elemNum];
                c->organizadas[elemNum] = c->organizadas[elemNum+1];
                c->organizadas[elemNum+1] = aux;
            }
        }
    }
}

void returnEquipa(concurso c,int numEquipa,char* nomeEquipa,int* pontos, int* numDescl, int* numLic){
    equipa eq=c->organizadas[numEquipa];
    strcpy(nomeEquipa,get_equipa_nome(eq));
    *pontos = get_equipa_clacificacao(eq);
    *numDescl = get_ndesqualificados(eq);
    *numLic = count_arq(eq);
}
