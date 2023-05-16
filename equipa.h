#ifndef EQUIPA_H_
#define EQUIPA_H_


#include "arqueologo.h"

typedef struct _equipa * equipa;

typedef struct _noSimples * iteraeq;

/***********************************************
cria_equipa - Devolve uma equipa sem elementos, com o nome recebido.
Parametros:
	nome - Nome da equipa
Retorno: Equipa sem elementos 
Pre-condicoes:  nome != NULL
***********************************************/
equipa cria_equipa(char * nome);

/***********************************************
add_elemq - Adiciona elemento a equipa.
Parametros:
	eq  - Equipa onde elemento é adicionado
    arq - Elemento novo da equipa
Retorno: 
Pre-condicoes:  eq,arq != NULL
***********************************************/
void add_elemeq(equipa eq,arqueologo arq);
/***********************************************
rm_elemeq - Remove um elemento da equipa.
Parametros:
	e  	 	 - Equipa para mudar a estrela
    nome_arq - Nome do arqueologo a ser removido
Retorno: 1 se equipa desqualificada 0 se nao
Pre-condicoes:  e != NULL e equipa tem de ter mais que um elemento
***********************************************/
char * rm_elemeq(equipa eq,char * nome_arq);

/***********************************************
muda_estrela - Adiciona elemento a equipa.
Parametros:
	e   - Equipa para mudar a estrela
    arq - Nova estrela da equipa
Retorno: 
Pre-condicoes:  e != NULL e arq existe em 'e'
***********************************************/
//Prerequisito: arq existe em e
void muda_estrela(equipa e, arqueologo arq);

/***********************************************
prox_arq - Devolve o proximo arqueologo.
Parametros:
	it - iterador
Retorno: 
Pre-condicoes:  e != NULL
***********************************************/
iteraeq prox_arq(equipa e);

/***********************************************
getit_arq - Devolve o arqueologo corrento no iterador.
Parametros:
	it - iterador
Retorno: 
Pre-condicoes:  it != NULL
***********************************************/
arqueologo getit_arq(iteraeq it);

/***********************************************
destroi_equipaElems - Liberta toda a memoria acossiada a equipa.
Parametros:
	e   - Equipa a ser destruida
Retorno: 
Pre-condicoes:  e != NULL
***********************************************/
void destroi_equipaElems(equipa e);

/***********************************************
get_equipa_nome(equipa eq) - Retorna o nome da equipa.
Parametros:
	e   - Equipa
Retorno: Nome da equipa
Pre-condicoes:  e != NULL
***********************************************/
char * get_equipa_nome(equipa eq);

/***********************************************
get_equipa_clacificacao - Retorna a clacificacao da equipa.
Parametros:
	eq  - Equipa
Retorno: Clacificacao da equipa 
Pre-condicoes:  e != NULL
***********************************************/
int get_equipa_clacificacao(equipa eq);

/***********************************************
get_equipa_estrela - Retorna a estrela da equipa.
Parametros:
	e   - Equipa
Retorno: Estrela da equipa
Pre-condicoes:  e != NULL
***********************************************/
arqueologo get_equipa_estrela(equipa eq);

/***********************************************
equipa_desqualificada - Retorna o estado da qualificacao da equipa.
Parametros:
	e   - Equipa
Retorno: 1 se desqualificada e 0 se qualificada
Pre-condicoes:  e != NULL
***********************************************/
char equipa_desqualificada(equipa e);

/***********************************************
destroi_equipagen - destroi a equipa.
Parametros:
	e   - Equipa
Retorno: 
Pre-condicoes:  e != NULL, e -> é um instancia equipa
***********************************************/
void destroi_equipagen(void * e);

/***********************************************
existe_arqueologo - Diz se o arqueologo com o nome "nome_arq".
Parametros:
	e        - Equipa
    nome_arq - Nome de arqueologo
Retorno: 1 se encontrou e 0 se nao
Pre-condicoes:  e != NULL, nome_arq != NULL
***********************************************/
int existe_arqueologo(equipa eq,char *nome_arq);

/***********************************************
load_meritoeq - Atualiza o merito da equipa.
Parametros:
	e   - Equipa
Retorno: 
Pre-condicoes:  e != NULL
***********************************************/
void load_meritoeq(equipa e);

/***********************************************
load_quaificacao - Atualiza a qualificacao da equipa.
Parametros:
	e   - Equipa
Retorno: 
Pre-condicoes:  e != NULL
***********************************************/
void load_quaificacao(equipa e);

/***********************************************
load_estrela - Atualiza a estrela da equipa.
Parametros:
	e   - Equipa
Retorno: 
Pre-condicoes:  e != NULL
***********************************************/
void load_estrela(equipa eq);
/***********************************************
get_ndesqualificados - Devolve o numero de arqueologos desqualificados.
Parametros:
	eq   - Equipa
Retorno:  numero de arqueologos desqualificados
Pre-condicoes:  e != NULL
***********************************************/
unsigned int get_ndesqualificados(equipa eq);

/***********************************************
count_arq - Conta numero de arqueoogos
Parametros:
	e   - Equipa
Retorno: numero de arqueoogos
Pre-condicoes:  e != NULL
***********************************************/
int count_arq(equipa e);

/***********************************************
add_meritoeq - Adiciona merito a uma equipa
Parametros:
	e   	-	Equipa
	merito	-	merito a ser adicionado
Retorno: 
Pre-condicoes:  e != NULL
***********************************************/
void add_meritoeq(equipa eq,int merito);

/***********************************************
compara_equipas - Compara duas equipas.
Parametros:
	eq1	- Equipa
	eq2	- Equipa
Retorno:equipa que ganha
Pre-condicoes:  e != NULL
***********************************************/
equipa compara_equipas(equipa eq1, equipa eq2);

/***********************************************
arq_desq_eq - Diz se foi desqualificado da equipa.
Parametros:
	eq   	- Equipa
	nome	- nome de arqueologo a desqualificar
Retorno: 1 se desqualificado 0 caso contrario
Pre-condicoes:  e != NULL
***********************************************/
char arq_desq_eq(equipa eq,char * nome);

/***********************************************
add_desq_eq - Adiciona nome de arqueologo ao dicionario de arqueologos desqualificados .
Parametros:
	e   	- Equipa
	nome	- nome do arqueologo
Retorno: 
Pre-condicoes:  e != NULL nome != NULL
***********************************************/
void add_desq_eq(equipa eq, char *nome);

#endif
