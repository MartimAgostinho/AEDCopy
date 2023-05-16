#ifndef ARQUEOLOGO_H_
#define ARQUEOLOGO_H_

#define COLUNA 0
#define LINHA 1

typedef struct _arqueologo *arqueologo;

/***********************************************
criaArqueologo - Cria uma nova instancia arqueologo.
Parametros:
	nomeArqueologo - Nome do arqueologo
Retorno: instancia arqueologo
Pre-condicoes:  e != NULL e arq existe em 'e'
***********************************************/
arqueologo criaArqueologo(char* nomeArqueologo);

/***********************************************
addMeritoArqueologo - adiciona pontos ao merito do arqueologo.
Parametros:
	arq     - Arqueologo para modificar os pontos
    pontos  - pontos addicionados ao arqueolog
Retorno: 
Pre-condicoes:  arq != NULL 
***********************************************/
void addMeritoArqueologo(arqueologo arq, int pontos);

/***********************************************
incrPenalizacoesArqueologo - adiciona +1 ao numero de penalizacoes do arqueologo
Parametros:
	arq - Arqueologo para incrementar o merito
Retorno: 
Pre-condicoes:  arq != NULL arq->merito > 0
***********************************************/
void incrPenalizacoesArqueologo(arqueologo arq);

/***********************************************
moverArqueologo - Muda a posicao atual do arqueologo
Parametros:
	arq - Arqueologo a mudar a posicao
Retorno: 
Pre-condicoes:  arq != NULL 
***********************************************/
void moverArqueologo(arqueologo arq, int x, int y);

/***********************************************
desclassificaArqueologo - Muda o numero de penalizacoes para -1 indicando que o arqueologo eesta desqualificado
Parametros:
	arq - Arqueologo desqualificado
Retorno: 
Pre-condicoes:  arq != NULL 
***********************************************/
void desclassificaArqueologo(arqueologo arq);

/***********************************************
getMeritoArqueologo - Devolve o merito da arqueologo arq
Parametros:
	arq - Arqueologo a ler merito
Retorno: Merito do arqueologo arq
Pre-condicoes:  arq != NULL 
***********************************************/
int getMeritoArqueologo(arqueologo arq);

/***********************************************
getNomeArqueologo - Devolve o nome do arqueologo
Parametros:
	arq - Arqueologo a aceder o nome 
Retorno: char * com o nome do arq
Pre-condicoes:  arq != NULL 
***********************************************/
char* getNomeArqueologo(arqueologo arq);

/***********************************************
getPenalizacoesArqueologo - Devolve o numero de penalizacoes do arq 
Parametros:
	arq - Arqueologo a aceder as penalizacoes
Retorno: int com numero de penalizacoes
Pre-condicoes:  arq != NULL 
***********************************************/
int getPenalizacoesArqueologo(arqueologo arq);

/***********************************************
getPosicaoArqueologo - Devolve a posicao do arq
Parametros:
	arq - Arqueologo a aceder o nome 
Retorno: posicao do arqueologo
Pre-condicoes:  arq != NULL 
***********************************************/
int * getPosicaoArqueologo(arqueologo arq);

/***********************************************
destroi_arq - liberta a memoria associada a instancia arqueologo
Parametros:
	arq - Arqueologo a destruir
Retorno: 
Pre-condicoes:  arq != NULL 
***********************************************/
void destroi_arq(arqueologo arq);

/***********************************************
destroi_arqgen - liberta a memoria associada a instancia arqueologo
Parametros:
	arq - Arqueologo a aceder o nome 
Retorno: 
Pre-condicoes:  arq != NULL 
***********************************************/
void destroi_arqgen(void * arq);

/***********************************************
comparar_estrela - Compara dois arqueologos e retorna qual dos dois é a estrela
Parametros:
	arq1 e arq2 - Arqueologos a compara ordem nao importa  
Retorno: arqueologo estrela
Pre-condicoes:  arq1,arq2 != NULL 
***********************************************/
arqueologo comparar_estrela(arqueologo arq1,arqueologo arq2);

void strToLower(char * str);//Esta função usa-se no equipa.c e é por isso que está no header do arqueologo
#endif
