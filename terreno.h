#ifndef _TERRENO_H_
#define _TERRENO_H_

typedef struct _terreno * terreno;

/***********************************************
cria_terreno - Cria e devolve um terreno.
Parametros:
	dim_x - numero de colunas, posicoes no eixo x
	dim_y - numero de linhas, posicoes no eixo y
Retorno: terreno
Pre-condicoes:  x,y > 0
***********************************************/
terreno cria_terreno(unsigned int dim_x,unsigned int dim_y);

/***********************************************
destroi_terreno - Liberta toda a memoria associada a um terreno talhoes inclusive.
Parametros:
	t - terreno para destruir
Retorno: 
Pre-condicoes:  t != NULL 
***********************************************/
void destroi_terreno(terreno t );

/***********************************************
get_talhao - Devolve o talhao da posicao x,y do terreno t.
Parametros:
	t - terreno com o talhao
	x - coordenadas eixo x(coluna)
    y - coordenadas eixo y(linha)
Retorno: talhao
Pre-condicoes:  t != NULL && x,y > 0
***********************************************/
int gett_val(terreno t,int x,int y);//TODO: ATUALIZAR

/***********************************************
gett_dimx - Devolve o numero de colunas, posicoes do eixo x.
Parametros:
	t - terreno com x colunas
Retorno: numero de colunas 
Pre-condicoes:  t != NULL 
***********************************************/
unsigned int gett_dimx(terreno t);

/***********************************************
gett_dimy - Devolve o numero de linhas, posicoes do eixo y.
Parametros:
	t - terreno com y colunas
Retorno: numero de linhas 
Pre-condicoes:  t != NULL 
***********************************************/
unsigned int gett_dimy(terreno t);

/***********************************************
get_riqueza - Devolve a riqueza do terreno
Parametros:
	t - terreno 
Retorno: riqueza do terreno
Pre-condicoes:  t != NULL 
***********************************************/
unsigned int get_riqueza(terreno t);

/***********************************************
load_riqueza - Atualiza o valor da riqueza do terreno
Parametros:
	t - terreno 
Retorno: 
Pre-condicoes:  t != NULL 
***********************************************/
void load_riqueza(terreno t);

/***********************************************
preencher_terreno - preenche o terreno com os valores na matriz mat
Parametros:
	t 	- terreno 
	l 	- linhas da matriz
	c 	- colunas da matriz
	mat - matriz com os valores
Retorno:
Pre-condicoes:  t != NULL, l,c = dim de mat 
***********************************************/
void preencher_terreno(terreno t,int l,int c,int ** mat);

/***********************************************
escavar - escava na posicao l,c
Parametros:
	t 	- terreno 
	l 	- linhas da matriz
	c 	- colunas da matriz
Retorno:
Pre-condicoes:  t != NULL, l,c <= dim de mat 
***********************************************/
int escavar(terreno t, int c , int l);

/***********************************************
inc_riqueza - pincrementa a riqueza do terreno
Parametros:
	t 	- terreno 
	n	- valor para incrementar
Retorno:
Pre-condicoes:  t != NULL
***********************************************/
void inc_riqueza(terreno t,int n);
#endif
