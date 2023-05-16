#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "concurso.h"

#define SaltoInv "Salto invalido\n"
#define	EqInv "Equipa invalida\n"
#define	EqInex "Equipa inexistente\n"
#define CmdInv "Comando invalido\n"
#define ArqInv "Arqueologo invalido\n"
#define ErroIn "Erro Inesperado\n"

    void rm_enter(char * str);

    int  instructionReader(char* op);
    void preencherTerrenoMain();
    void registarEquipasMain();
    void menu(concurso c);
    void riquezaFunc();
    void terrenoFunc();
    void estrelaFunc();
    void escavacaoFunc();
    void reforcoFunc();
    void equipaFunc();
    void classificacao();
    //equipa ler_equipa(int n,char * filename);
    char ** get_comandos(char str[MAXLINESIZE]);
    concurso cria_concurso_main(int * nequipas);


    int main() {

        int nequipas;//criei nequipas pq das scanf do numero ao criar o concurso e preciso desse numero da funcao registarEquipasMain

        concurso c;
        c = cria_concurso_main(&nequipas);
        if( !load_equipas(c,"teams.txt") ){ 
            printf("Ficheiro Invalido\n");
            return 1;
        }

        registarEquipasMain(c,nequipas);

        menu(c);
        switch(presair(c)){ 
            case  0: 	printf("Todos os tesouros foram descobertos!\n"); 
                        classificacao(c);
                        break;
            case -1:	printf("Todas as equipas foram expulsas.\n");     break;
            default:	printf("Ainda havia tesouros por descobrir...\n");
                        classificacao(c);
        }
        
        return 0;
    }

    void menu(concurso c){
        int op,n1,n2;
        char comando[MAXLINESIZE],input[MAXLINESIZE],str1[MAXLINESIZE],str2[MAXLINESIZE];
        fgets(input,MAXLINESIZE,stdin);//retira o \n
        while(1){

            fgets(input,MAXLINESIZE,stdin);
            
            sscanf(input," %s",comando);

            op = instructionReader(comando);


            switch(op){
                
                case 1://Comando-Riqueza FUNCIONA
                    riquezaFunc(c);
                    break;
                
                case 2://Comando-Terreno FUNCIONA
                    terrenoFunc(c);
                    break;
                
                case 3://Comando-Estrela FUNCIONA
                    sscanf(input," %s %[^\n]",comando,str1);
                    estrelaFunc(c,str1);
                    break;
                
                case 4://Comando-Escavacao FUNCIONA
                    sscanf(input," %s %d %d %[^\n]",comando,&n1,&n2,str1);
                    
                    switch(executar_escavacao(c,n2,n1,str1)){
                        case 0:  break;
                        case -1: printf(SaltoInv); break;
                        case -2: 
                        case -3: printf(EqInv); break;
                        case -4: break;
                        case -5: printf ("%s foi expulsa\n",str1);break;//remover equipa do dicionario?
                        default: printf(ErroIn);
                    }
                    break;			
                case 5://Comando-Reforco (2a fase)
				
				fgets(str1, MAXLINESIZE,stdin);
				rm_enter(str1);

				fgets(str2, MAXLINESIZE,stdin);
				
				rm_enter(str2);
				reforcoFunc(c,str1,str2);
				break;
			
			case 6://Comando-Equipa
				sscanf(input, " %s %d",comando,&n1 );
				
				switch(comandoEquipa(c,n1)){
					case 0:  break;
					case -1: printf(EqInv); break;
					case -2: printf(EqInex); break;
					default: printf(ErroIn);
				}
				break;

			case 7://Comando-Sair (2a fase)
				return;
			
			default://Comando Invalido
				printf(CmdInv);
		}
	}
}

concurso cria_concurso_main(int *nequipas){

	unsigned int c,l; //colunas e linhas

	scanf(" %u %u",&l,&c);
	int ** valores = (int **)malloc(sizeof(int *) * l);

	if( valores == NULL ){ return NULL; }
	
	int i;
	
	for(i = 0;i < l;i++){

		valores[i] = (int *)malloc(sizeof(int) * c);
		if( valores[i] == NULL ){
			
			for(i--;i > 0;i--){ free(valores[i]); }
			free(valores);
		}
	}

	preencherTerrenoMain(l,c,valores);

	scanf(" %d",nequipas);

	concurso conc = cria_concurso(*nequipas,c,l);
	
	if(conc == NULL){ 
		for(i = l;i >= 0;i--){ free(valores[i]); }
		free(valores);
		return NULL;
	}
	
	load_campo(conc,l,c,valores);
	for(i = l - 1; i >= 0;i--){ free(valores[i]); }
	free(valores);
	return conc;
}

int contarPalavras(char* str){
	int i,palavrasCount=1;
	for(i=0;i<strlen(str);i++){
		
		if (str[i]==' ')
			palavrasCount++;
	}
	return palavrasCount;
}

void destroir_matriz(char **mat){

	int j = (int)mat[0][0];

	for(int i = j;i > 0;i--){
		free(mat[i]);
	}
	free(mat);

}

int instructionReader(char* str){ //Devolve um int dependendo da instrução lida
	if(!strcmp(str,"riqueza")) return 1;
	if(!strcmp(str,"terreno")) return 2;
	if(!strcmp(str,"estrela")) return 3;
	if(!strcmp(str,"escavacao")) return 4;
	if(!strcmp(str,"reforco")) return 5;
	if(!strcmp(str,"equipa")) return 6;
	if(!strcmp(str,"sair")) return 7;
	return -1;
}   

void preencherTerrenoMain(int l,int c,int ** t){
	
	int i,j;
    
	for(i = 0;i < l ;i++){
        for(j = 0;j < c;j++){
            scanf(" %d",&t[i][j]);
        }
    }
}

void registarEquipasMain(concurso c,int nEquipas){
	
	int numeroDaEquipa,i;
	for (i=0;i<nEquipas;i++){
		scanf(" %d",&numeroDaEquipa);
		add_equipa(c,numeroDaEquipa);
	}
}

void riquezaFunc(concurso c){//FUNCIONA
	printf("Riqueza enterrada: %d\n",mostrarRiqueza(c));
}

void terrenoFunc(concurso c){

	int x = 1,y = 1;
	char val = mostrar_talhao(c, x, y);

	while( val ){
		while( val ){ 
			printf("%c",val);
			x++;
			val = mostrar_talhao(c, x, y);
		}
		x = 1;
		y++;
		val = mostrar_talhao(c, x, y);
		printf("\n");
	}
}

void estrelaFunc(concurso c, char* nomeEquipa){
	char *ch;

	if( existe_equipa(c,nomeEquipa) == 1){

		if( ( ch = get_nome_estrela(c,nomeEquipa) ) ){
			printf("Estrela de %s: %s\n",nomeEquipa,ch);
			return;
		}
	}
	printf(EqInv);
}

//TODO: POR TESTAR
void reforcoFunc(concurso c, char* nomeEq, char* nomeArq){
	switch(comandoReforcoConcurso(c,nomeEq,nomeArq)){
		case 0: break;
		case 1: printf(EqInv); break;
		case 2: printf(ArqInv); break;
		default: printf(ErroIn);
	}
}

void equipaFunc(concurso c,int numEquipa){
	
	int ctrl = comandoEquipa(c,numEquipa);
	if(ctrl == 2){
		printf(EqInex);
	}
	if( ctrl ){
		printf(EqInv);
	}
}

void classificacao(concurso c){
	char nomeEquipa[41];
	int pontos,numDescl,numLic,i;
	sort_equipas(c);
	printf("classificacao\n");
	for(i = 0;i < get_nequipas( c );i++){
		returnEquipa(c,i,nomeEquipa,&pontos,&numDescl,&numLic);
		if(!numLic)
			continue;
		printf("%s: %d pts; %d descl.; %d com lic.\n",nomeEquipa,pontos,numDescl,numLic);
    }
}

void rm_enter(char * str){ 
	if (str[strlen(str) - 1] == '\n') {str[strlen(str) - 1] = '\0';}
}


