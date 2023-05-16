#ifndef CONCURSO_H_
#define CONCURSO_H_

#define MAXLINESIZE 42

typedef struct _concurso *concurso;

/***********************************************
cria_concurso - Cria uma nova instancia concurso.
Parametros:
	nequipas - Numero de equipas em jogo
    dimx - Dimensao x do terreno
    dimy - Dimensao y do terreno
Retorno: instancia arqueologo
Pre-condicoes:
***********************************************/
concurso cria_concurso(int nequipas,unsigned int dimx,unsigned int dimy);

/***********************************************
destroi_concurso - Liberta a memoria ocupada pela instancia da estrutura associada ao concurso.
Parametros:
	c - concurso
Retorno: -1 se todas as equipas forem desqualificadas, num de tesouro restante caso contrario
Pre-condicoes: c != NULL && c->equipasFicheiro
***********************************************/
void destroi_concurso(concurso c);

char presair(concurso c);

/***********************************************
add_equipa - Adiciona uma equipa ao concurso
Parametros:
	c - concurso
    n - numero da equipa no ficheiro
Retorno: 
Pre-condicoes: c != NULL
***********************************************/
void add_equipa(concurso c,int n);

/***********************************************
load_equipas - Adiciona a uma sequencia todas as equipas que podem entrar no jogo
Parametros:
	c - concurso
    filename - nome do ficheiro das equipas
Retorno: 0 em caso de erro, 1 caso tudo corra bem
Pre-condicoes: c != NULL
***********************************************/
char load_equipas(concurso c ,char * filename);

/***********************************************
mostrarRiqueza - Retorna a riqueza associada ao terreno
Parametros:
	c - concurso
Retorno: Riqueza do terreno (soma de todos os tesouros dos talhoes)
Pre-condicoes: c != NULL
***********************************************/
unsigned int mostrarRiqueza(concurso c);

/***********************************************
get_nome_estrela - Retorna o nome da estrela de uma determinada equipa
Parametros:
	c - concurso
    nomeEquipa - nome da equipa a analisar
Retorno: o nome da estrela de uma determinada equipa
Pre-condicoes: c != NULL
***********************************************/
char* get_nome_estrela(concurso c, char*nomeEquipa);

/***********************************************
existe_equipa - Retorna 1 ou 0 dependendo se existe ou nao uma equipa com esse nome
Parametros:
	c - concurso
    nomeEquipa - nome da equipa a ser analisada
Retorno: 1 caso ja exista uma equipa com o mesmo nome, 0 caso contrario
Pre-condicoes: c != NULL
***********************************************/
int existe_equipa(concurso c, char*nomeEquipa);

/***********************************************
executar_escavacao - Funcao que executa o comando escavacao e retorna dependendo de erros
Parametros:
	c - concurso
    x - coordenada x de onde vai ser a escavacao
    y - coordenada y de onde vai ser a escavacao
    nomeEquipa - nome da equipa a escavacar
Retorno:    -1 caso salto invalida, -2 caso a equipa nao exista em hogo
            -3 caso a equipa esteja desqualificada, -4 caso seja desqualificada apos a escavacao
             0 se tudo correu bem.
Pre-condicoes: c != NULL
***********************************************/
int executar_escavacao(concurso c,int x,int y,char* nomeEquipa);

/***********************************************
comandoEquipa - Funcao que executa o comando equipa
Parametros:
	c - concurso
    numEquipa - numero da equipa a adicionar
Retorno: -2 Caso a equipa nao exista, -1 caso a equipa seja invalida, 0 se tudo correu bem
Pre-condicoes: c != NULL
***********************************************/
int comandoEquipa(concurso c, int numEquipa);

/***********************************************
load_campo - Cria o terreno para o inicio do concurso
Parametros:
	cq - concurso
    l - numero de linhas
    c - numero de colunas
    mat - matriz de tesouros
Retorno: 
Pre-condicoes: c != NULL
***********************************************/
void load_campo(concurso cq, int l,int c,int **mat);

/***********************************************
mostrar_talhao - Retorna os pontos de um talhao
Parametros:
	con - concurso
    c - numero da coluna
    l - numero da linha
Retorno: tesouro do talhao
Pre-condicoes: c != NULL c>0 l>0
***********************************************/
char mostrar_talhao(concurso con,int c,int l);

/***********************************************
comandoReforcoConcurso - Faz o reforco
Parametros:
	c       - concurso
    nomeEq  - Nome da equipa para onde o arqueologo vai
    nomeArq - Nome do arqueologo novo
Retorno: 1 se equipa invalida 2 se arqueologo invalido 0 se correu bem
Pre-condicoes: c != NULL
***********************************************/
int comandoReforcoConcurso(concurso c,char* nomeEq,char* nomeArq);

/***********************************************
returnEquipa - Devolve os parametros finais da equipa por ordem
Parametros:
	c       - concurso
    (...)   - apontadores para os parametros
Retorno: 
Pre-condicoes: c != NULL (...) != NULL
***********************************************/
void returnEquipa(concurso c,int numEquipa,char* nomeEquipa,int* pontos, int* numDescl, int* numLic);
/***********************************************
sort_equipas - preenche por ordem o vetor de equipas
Parametros:
	c       - concurso
Retorno: 
Pre-condicoes: c != NULL 
***********************************************/
void sort_equipas(concurso c);
/***********************************************
get_nequipas - Devolve o numero de equipas do concurso
Parametros:
	c       - concurso
Retorno: Devolve o numero de equipas
Pre-condicoes: c != NULL 
***********************************************/
int get_nequipas(concurso c);

#endif
