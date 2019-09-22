/** Grupo: Francis Vargas, Mario Alves e Renan Scherer. **/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 8
#define COLUNAS 8
#define TAM 8 /* TAManho da matriz - 8x8 */

struct drone {
	int ali,troc;
	int capSacos;
	int capSS,capSO;
	struct pontoRecolhimento *lxP;
	struct drone *prox;
	
};

struct pontoRecolhimento {
	int cap;
	int tipo;
	struct pontoRecolhimento *prox;
	
};

//Configurando ambiente 
int **configuraAmbiente(){
	int **p;
	int i;
	
	p=(int **)malloc(sizeof(int *)*TAM);
	if(p==NULL){
		return(NULL);
	}
	for(i=0;i<TAM;i++){
		p[i] = (int *)malloc(sizeof(int)*TAM);
		if(p[i] == NULL){
			return(NULL);
		}
	}
	return (p);
}

//Criar os pontos de recolhimento


//Criar os agentes Drones


// Preenchendo matriz 
int preencheAmbiente (int **amb, struct drone **iniD,struct PRecolhim **iniPR){
	int i, j, valorX, valorY, addok=0;
	int qtdObstaculos = 12, qtdDrones = 4, qtdPRecolhi = 2; // cap=3; Capacidade do drone( Avaliar se precisa ter )
	
	/**	Resetando matriz **/
	for(i = 0;i < TAM; i++){
		for(j = 0;j < TAM; j++){
			amb[i][j]=0;
		}
	}
	
	/** Inicia contador de obstáculos **/
	qtdObstaculos *= (TAM / 8);
	for(i=0;i<qtdOsbtaculos;i++){
		valorX=rand()%TAM;
		valorY=rand()%TAM;
		if(amb[valorX][valorY] == 0){
			if((i%2)==0){
				amb[valorX][valorY]=4;	
			}else{
				amb[valorX][valorY]=3;
			}			
		}else{
			i--;
		}
	}
	
	/** Inicia contador de pontos de recolhimento **/
	qtdPRecolhi *= (TAM / 8);
	for(i = 0; i < qtdPRecolhi; i ++){
		addok=0;
		valorX = rand() % TAM;
		valorY = rand() % TAM;	
		if(amb[valorX][valorY] == 0){
			if(valorX == 0){
				if(valorY == 0){
					if(amb[valorX+1][valorY]==0||amb[valorX][valorY+1]==0){
						addok=1;
					}
				}else if(valorY==(TAM - 1)){
					if(amb[valorX+1][valorY]==0||amb[valorX][valorY-1]==0){
						addok=1;
					}
				}else{
					if(amb[valorX+1][valorY]==0||amb[valorX][valorY-1]==0||amb[valorX][valorY+1]==0){
						addok=1;
					}
				}
			}else if(valorX==(TAM - 1)){
				if(valorY==0){
					if(amb[valorX-1][valorY]==0||amb[valorX][valorY+1]==0){
						addok=1;
					}
				}else if(valorY==(TAM - 1)){
					if(amb[valorX-1][valorY]==0||amb[valorX][valorY-1]==0){
						addok=1;
					}
				}else{
					if(amb[valorX-1][valorY]==0||amb[valorX][valorY-1]==0||amb[valorX][valorY+1]==0){
						addok=1;
					}
				}
			}else if(valorY==0){
				if(amb[valorX+1][valorY]==0||amb[valorX-1][valorY]==0||amb[valorX][valorY+1]==0){
					addok=1;
				}
			}else if(valorY==(TAM-1)){
				if(amb[valorX+1][valorY]==0||amb[valorX-1][valorY]==0||amb[valorX][valorY-1]==0){
					addok=1;
				}
			}else{
				if(amb[valorX+1][valorY]==0||amb[valorX-1][valorY]==0||amb[valorX][valorY-1]==0||amb[valorX][valorY+1]==0){
					addok=1;
				}				
			}
			if(addok==1){
				if((i%2)==0){
					criaPRecolhimento(iniL,valorY,valorX,2,6);
					amb[valorX][valorY]=2;
				}else{
					criaPRecolhimento(iniL,valorY,valorX,1,6);
					amb[valorX][valorY]=1;
				}
			}else{
				i--;
			}
		}else{
			i--;
		}
	}
	
	/* Inicia contador de drones */
	qtdDrone *= (TAM/8);
	for(i = 0; i < qtdDrone; i++){
		valorX = rand() % TAM;
		valorY = rand() % TAM;
		if(amb[valorX][valorY] == 0){
			criaDrone(iniA,valorX,valorY,cap,cap,cap);
			amb[valorX][valorY] = 5;		
		}else{
			i--;
		}
	}
	return(qtdObstaculos);
	
}


main(){
	struct agente *ptriD = NULL;
	struct lixeira *ptriPR = NULL;
	int *qtdObstaculos = malloc(sizeof(int));
	int **amb;
	int TAM = -5, velocidade = -5;
	
	printf("Trabalho de IA - Ferrovia Inteligente\n\n");
	srand(time(NULL));

	if(qtdObstaculos==NULL){
		printf("\n IMPOSSIVEL ALOCAR QUANTIDADE DE OBSTACULOS \n");
		system("pause");
		return(0);
	}
	
	printf("\n\n Escolha o tipo de ciclo: [1] MANUAL; [2] AUTOMATICO); ");
	while(velocidade<=0||velocidade>3){
		if(scanf("%d",&velocidade)==0){
			printf("ERRO ENTRADA\n");
			while(fgetc(stdin)!='\n');
			continue;
		}
		if(velocidade<=0||velocidade>3){
			printf("ERRO. VELOCIDADE INVALIDA\n");
		}
	}
	system("cls");
	
	/* Cria ambiente da ferrovia */
	amb = configuraAmbiente();
	if(amb==NULL){
		printf("\nIMPOSSIVEL ALOCAR AMBIENTE\n");
		system("pause");
		return(0);
	}
	
	/* Inicia ambiente ferrovia */
//	*qtdObstaculos = droneNoAmbiente(amb, TAM, &ptriD, &ptriPR);
	
	printf("\n \n");
    system("pause");
}


