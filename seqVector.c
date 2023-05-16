#include <stdlib.h>
#include "iterador.h"
#include "sequencia.h"

/* Estrutura de dados: sequencia implementada em vector */
struct _sequencia{
	void * * elems; // apontador para vector de enderecos de elementos
	int numElems;   // posicao do ultimo elemento do vetor ocupado
	int capacidade; // capacidade corrente do vector
};

void incSequencia (sequencia d);

sequencia criaSequencia(int cap){ 
	
	sequencia s = (sequencia)malloc(sizeof(struct _sequencia));

	if( s == NULL ){ return NULL; }

	if( cap < 1 ){ cap = 1; }

	s->elems = (void *)malloc(sizeof(void *) * cap);

	if( s->elems == NULL ){ 
		free(s);	
		return NULL;
	}
	
	s->capacidade = cap;
	s->numElems = 0;
	return s;
}

//destroi a sequencia
void destroiSequencia (sequencia s ){ 
	free(s->elems);
	free(s);
}

//destroi sequencia e elementos da sequencia
void destroiSeqElems(sequencia s, void (*destroi)(void *) ){
	
	int i;

	for(i = 0;i < s->numElems;i++){ destroi( s->elems[i] ); }

	destroiSequencia(s);
}

//1 se estiver vazia e 0 se nao
int vaziaSequencia(sequencia s){
	if( s->numElems > 0 ){ return 0; }
	return 1;
}

//quantas posicoes estao ocupadas
int tamanhoSequencia(sequencia s){ return s->numElems; }


void * elementoPosSequencia(sequencia s, int i){ return s->elems[i - 1]; }


void adicionaPosSequencia(sequencia s, void * elem, int pos){
	if(pos==s->capacidade)
		incSequencia(s);
	for(int n=s->numElems;n>=pos-1;n--)
	{
		s->elems[n+1]=s->elems[n];
	}
	s->numElems++;
	s->elems[pos-1]=elem;
}


void * removePosSequencia(sequencia s, int i){

	int j;

	void * el = s->elems[i - 1];

	for( j = i;j < s->numElems;j++){ s->elems[j - 1] = s->elems[j]; }
	s->numElems--;

	return el;
}


iterador iteradorSequencia(sequencia s){
	
    int i,nel = s->numElems;
	void ** tmps = (void **)malloc(sizeof(void *) * s->numElems);

    if( tmps == NULL ){ return NULL; }
	for(i = 0;i < s->numElems;++i){ tmps[i] = s->elems[i]; }

	iterador it = criaIterador(tmps, nel);

    return it;
}

void incSequencia (sequencia d){

	d->capacidade = (d->capacidade + 1) * 2;

	void** aux = (void**)malloc(sizeof(void*) * d->capacidade); // duplica
	
	for (int i = 0; i < d->numElems; i++)
		aux[i] = d->elems[i];
	free(d->elems);
	d->elems = aux;
	
}
