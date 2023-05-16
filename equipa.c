#include <stdlib.h>
#include <string.h>

#include "arqueologo.h"
#include "equipa.h"
#include "noSimples.h"
#include "dicionario.h"

#define CAP 10

struct _equipa{
    noSimples cabeca;           //o ultimo arquelogo aponta para o primeiro
    noSimples cauda;
    arqueologo estrela;
    iteraeq arqueologocorrente;   // substituir por cabeça 
    int meritoeq;                //merito da equipa
    char desqualificada;        //1 se desqualificada e 0 se qualificada
    char * nome;
    unsigned int ndesqualificados;
    dicionario arqdesq;
};

equipa cria_equipa(char * nome){

    equipa e = (equipa)malloc(sizeof( struct _equipa ));
    
    if (e == NULL) { return NULL; }
    
    e->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1) ); // allocar espaco para copiar nome 
    
    if (e->nome == NULL) { 
        free(e);
        return NULL;
    }
    e->arqdesq = criaDicionario(CAP, 1);
    if (e->arqdesq == NULL) { 
        free(e->nome);
        free(e);
        return NULL;
    }
    strcpy(e->nome,nome);
    e->meritoeq         = 0;
    e->desqualificada   = 0;
    e->ndesqualificados = 0;
    e->estrela          = NULL;
    e->cauda            = NULL;
    e->cabeca           = NULL;
    return e;
}

//devolve 0 se nao existe ou 1 se existe
int existe_arqueologo(equipa eq,char *nome_arq){
    
    iteraeq it = eq->cabeca;

    do{
                    //nome do arqueologo no noosimples
        if( !strcmp( getNomeArqueologo( elemNoSimples(it) ) , nome_arq ) ){ 
            return 1;
        }
        it = segNoSimples(it);
    }while( it != eq->cabeca);//nao comeca com a cabeca 
    
    return 0;
}

//Pre condicao nao equipa tem de ter mais de um elemento
char * rm_elemeq(equipa eq,char * nome_arq){

    ++eq->ndesqualificados;
    if( eq->cabeca == eq->cauda ){

        arqueologo arqtmp = elemNoSimples(eq->cabeca);
        char * nome = (char *)malloc(sizeof(char) * (strlen( getNomeArqueologo( arqtmp ) ) + 1 )); //Nao me esquecer de dar free aos nomes
        strcpy(nome, getNomeArqueologo(arqtmp));
        destroiElemENoSimples(eq->cabeca, destroi_arqgen );
        eq->arqueologocorrente  = NULL;
        eq->estrela             = NULL;
        eq->meritoeq            = 0;
        eq->desqualificada      = 1;
        return nome;
    }

    iteraeq aux = eq->cabeca,tmp;

    do{
        tmp = aux;
        aux = segNoSimples(aux);
    }while( strcmp( getNomeArqueologo( elemNoSimples( aux ) ) , nome_arq ) ) ;
    
    arqueologo arqtmp = elemNoSimples( aux );
    char * nome = (char *)malloc(sizeof(char) * (strlen( getNomeArqueologo( arqtmp ) ) + 1 )); //Nao me esquecer de dar free aos nomes
    strcpy(nome, getNomeArqueologo(arqtmp));

    atribuiSegNoSimples(tmp, segNoSimples(aux) );
    
    if( aux == eq->cabeca ){ eq->cabeca = segNoSimples(aux); }

    else if ( aux == eq->cauda ) { eq->cauda = tmp; }

    destroiElemENoSimples(aux, destroi_arqgen);
    return nome;
}

void add_desq_eq(equipa eq,char * nome){

    adicionaElemDicionario(eq->arqdesq, nome , (void*) 1 );//Fita cola preta ptr nao importa mas tem de ser != NULL
}

int count_arq(equipa e){
    
    if(e->desqualificada){ return 0; }
    
    iteraeq aux = e->cabeca;
    int n = 0;

    do {

        aux = segNoSimples(aux);
        ++n;
    }while( aux != e->cabeca );
    return n;
}

unsigned int get_ndesqualificados(equipa eq){ return eq->ndesqualificados; }

void add_elemeq(equipa eq,arqueologo arq){

    if(eq->cabeca == NULL){ 
        eq->cabeca  = criaNoSimples(arq,NULL);
        atribuiSegNoSimples(eq->cabeca, eq->cabeca); 
        eq->cauda   = eq->cabeca;
        eq->arqueologocorrente = eq->cabeca;
        eq->estrela = arq;    
        return;
    }
    
    noSimples aux = criaNoSimples(arq, eq->cabeca);

    if( segNoSimples(eq->cabeca) == eq->cabeca){ atribuiSegNoSimples(eq->cabeca, aux); }

    atribuiSegNoSimples(eq->cauda, aux);
    eq->cauda = aux;
    eq->estrela = comparar_estrela(eq->estrela, arq);
}

char arq_desq_eq(equipa eq,char * nome){

    return existeElemDicionario(eq->arqdesq, nome);
}

void muda_estrela(equipa e, arqueologo arq){ e->estrela = arq; }

char * get_equipa_nome(equipa eq){ return eq->nome; }

int get_equipa_clacificacao(equipa eq){ return eq->meritoeq; }

char equipa_desqualificada(equipa e){ return e->desqualificada; }

void add_meritoeq(equipa eq,int merito){ eq->meritoeq += merito; }

arqueologo get_equipa_estrela(equipa eq){ return eq->estrela; }

iteraeq prox_arq(equipa e){//devolve o arqueologo corrente e incrementa o arqueologo
    iteraeq it = e->arqueologocorrente;
    e->arqueologocorrente = segNoSimples(it);
    return it;
}

arqueologo getit_arq(iteraeq it){ return (arqueologo)elemNoSimples(it); }

void destroi_equipaElems(equipa e){
    
    if( e->desqualificada ){ goto norm; }
    
    //iterar a equipa e destroir os arquelogos

    noSimples aux = e->cabeca,tmp;
    atribuiSegNoSimples(e->cauda, NULL);

    do{
        //ate chegar ao ultimo elemento da equipa        
        tmp = segNoSimples(aux);
        destroiElemENoSimples(aux, destroi_arqgen );
        aux = tmp;
    }while( aux != NULL );
    norm:
    destroiDicionario(e->arqdesq);
    free(e->nome);
    free(e);   
}

void destroi_equipagen(void * e){ destroi_equipaElems( (equipa) e); }

void load_estrela(equipa eq){
    if( eq->desqualificada ){ 
        eq->estrela = NULL;
        return;
    }
    arqueologo arq;
    noSimples no = eq->cabeca;

    eq->estrela = elemNoSimples(no);//1o arq
    while(no != eq->cauda){
        no  = segNoSimples(no);
        arq = elemNoSimples(no);
        eq->estrela = comparar_estrela(eq->estrela,arq);
    }
}

equipa compara_equipas(equipa eq1, equipa eq2){
    
    if(eq2 == NULL){ return eq1; }
    if(eq1 == NULL ){ return eq2; }
    
    if(eq1->meritoeq==eq2->meritoeq){

        if(eq1->ndesqualificados==eq2->ndesqualificados){
            int numArqs1 = count_arq(eq1);
            int numArqs2 = count_arq(eq2);
            if(numArqs1==numArqs2){
                char str1[40],str2[40];
                //Copia para nao mudar o nome do arqueologo
                strcpy(str1,eq1->nome);//como nao usamos o strtolower isto nao ]e necessario
                strcpy(str2,eq2->nome);//
                //strToLower para podere usar o strcmp como meios de comparar a ordem alfabetica
                //strToLower(str1);
                //strToLower(str2);
                return strcmp(str1,str2)>0 ? eq2 : eq1; 
            }
            else{
                return numArqs1>numArqs2 ? eq2 : eq1;
            }
        }else{
            return eq1->ndesqualificados<eq2->ndesqualificados ? eq1 : eq2;
        }
    }else{
        return eq1->meritoeq>eq2->meritoeq ? eq1 : eq2;
    }
}
