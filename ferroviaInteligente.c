//Grupo: Francis Vargas, Mario Alves e Renan Scherer. 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 8  //Tamanho da matriz - 8x8

struct drone {
	int x, y;
	int ali, troc;
	int capOE, capOV;
	int capBateria;
	struct pontoRecolhimento *lxP;
	struct drone *prox;
	
};

struct pontoRecolhimento {
	int x, y;
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
int criaPRecolhimento(struct pontoRecolhimento **inicio, int posX, int posY, int tipo, int cap){
	
	struct pontoRecolhimento *novo=NULL;
	
	novo=(struct pontoRecolhimento *)malloc(sizeof(struct pontoRecolhimento));
	
	if(novo==NULL){
		printf("\nNAO FOI POSSIVEL CRIAR PONTO DE RECOLHIMENTO.\n");
	}else{
		novo->x=posY;
		novo->y=posX;
		novo->cap=cap;
		novo->tipo=tipo;
		novo->prox=*inicio;
		*inicio=novo;
	}
}

//Criar os agentes Drones
int criaDrone(struct drone **inicio, int posX, int posY, int capOE, int capOV, int capBateria){
	
	struct drone *novo=NULL,*aux=*inicio;
	
	novo=(struct drone *)malloc(sizeof(struct drone));
	
	if(novo==NULL){
		printf("\nNAO FOI POSSIVEL CRIAR O DRONE.\n");
	}else{
		novo->x=posX;
		novo->y=posY;
		novo->ali=1;
		novo->troc=1;
		novo->capBateria = capBateria;
		novo->lxP=NULL;
		novo->prox=*inicio;
		*inicio=novo;
	}
}

// Preenchendo matriz 
int preencheAmbiente(int **amb, struct drone **iniD, struct pontoRecolhimento **iniPR){
	int i, j, valorX, valorY, addok=0;
	int qtdObstaculos = 11, qtdDrones = 2, qtdPRecolhi = 2, cap = 5;
	
	/**	Resetando matriz **/
	for(i = 0;i < TAM; i++){
		for(j = 0;j < TAM; j++){
			amb[i][j]=0;
		}
	}
	
	/** Inicia contador de obstaculos **/
	for(i=0; i < qtdObstaculos; i++){
		valorX = rand() % TAM;
		valorY = rand() % TAM;
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
	for(i = 0; i < qtdPRecolhi; i ++){
		addok = 0;
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
					criaPRecolhimento(iniPR, valorY, valorX, 2, 6);
					amb[valorX][valorY]=2;
				}else{
					criaPRecolhimento(iniPR,valorY,valorX,1,6);
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
	for(i = 0; i < qtdDrones; i++){
		valorX = rand() % TAM;
		valorY = rand() % TAM;
		if(amb[valorX][valorY] == 0){
			criaDrone(iniD, valorX, valorY, cap, cap, cap);
			amb[valorX][valorY] = 5;		
		}else{
			i--;
		}
	}
	return(qtdObstaculos);
}

int direcoes(int **amb, int dX, int dY){
	
	int dir = 0,c = 0,b = 0,d=0,e=0;
	while(c==0||b==0||d==0||e==0){
		dir=rand()%4;
		if(dir==0){
			if(dY-1>=0){
				if(amb[dY-1][dX]==0){
					return(-30);
				}
				c=1;	
			}else{
				c=1;
			}
		}else if(dir==1){
			if(dY+1<TAM){
				if(amb[dY+1][dX]==0){
					return(30);
				}
				b=1;	
			}else{
				b=1;
			}
		}else if(dir==2){
			if(dX-1>=0){
				if(amb[dY][dX-1]==0){
					return(-3);
				}
				e=1;	
			}else{
				e=1;
			}
		}else if(dir==3){
			if(dX+1<TAM){
				if(amb[dY][dX+1]==0){
					return(3);
				}
				d=1;	
			}else{
				d=1;
			}
		}	
	}
	return(0);	
}

/* Procura ponto de recolhimento mais proximo */
int procuraPontoRecolhimento(int **amb, struct pontoRecolhimento **iniPR, struct drone *a, struct pontoRecolhimento *atual){
	
	struct pontoRecolhimento *aux=*iniPR;
	int dA,dV;
	
	if(atual!=NULL){
		a->lxP=NULL;
	}
	while(aux!=NULL){
		if(atual!=aux){
			if(a->capOE==0&&aux->tipo==1){
				if(a->lxP==NULL){
					a->lxP=aux;
				}else{
					dV=(a->y)>(aux->y)?(a->y)-(aux->y):(aux->y)-(a->y);
					dV+=(a->x)>(aux->x)?(a->x)-(aux->x):(aux->x)-(a->x);
					dA=(a->y)>(a->lxP->y)?(a->y)-(a->lxP->y):(a->lxP->y)-(a->y);
					dA+=(a->x)>(a->lxP->x)?(a->x)-(a->lxP->x):(a->lxP->x)-(a->x);
					dA--;
					dV--;
					if(dA>dV){
						a->lxP=aux;
					}
				}
			}else if(a->capOV==0 && aux->tipo==2){
				if(a->lxP==NULL){
					a->lxP=aux;
				}else{
					dV=(a->y)>(aux->y)?(a->y)-(aux->y):(aux->y)-(a->y);
					dV+=(a->x)>(aux->x)?(a->x)-(aux->x):(aux->x)-(a->x);
					dA=(a->y)>(a->lxP->y)?(a->y)-(a->lxP->y):(a->lxP->y)-(a->y);
					dA+=(a->x)>(a->lxP->x)?(a->x)-(a->lxP->x):(a->lxP->x)-(a->x);
					dA--;
					dV--;
					if(dA>dV){
						a->lxP=aux;
					}
				}
			}
		}
		aux=aux->prox;
	}
	a->ali=1;
}

/* Se achou, larga o obstaculo ali */
int vaiAoPonto (int **amb,struct drone *a){
	struct pontoRecolhimento *aux = a->lxP;
	if((a->x+1==a->lxP->x && a->y==a->lxP->y)||(a->x-1==a->lxP->x && a->y==a->lxP->y)||(a->y+1==a->lxP->y && a->x==a->lxP->x)||(a->y-1==a->lxP->y && a->x==a->lxP->x)){
		if(a->lxP->cap>0){
			return(200);
		}else{
			return(100);
		}
	}else if(a->ali==1){
		if(a->x-1>=0 && amb[a->x-1][a->y]==0 && (a->x)>(a->lxP->x)){ // Para cima
			return(-20);
		}else if(a->x+1<TAM && amb[a->x+1][a->y]==0 && (a->x)<(a->lxP->x)){ // Para baixo
			return(20);
		}else if(a->x!=a->lxP->x){
		    if(a->y+1>TAM && amb[a->x][a->y+1]>0){
		    	a->troc=1;
			}else if(a->troc==1&&a->y-1>=0&&amb[a->x][a->y-1]==0){ // Para esquerda
				return(-2);
			}else if(a->y+1<TAM && amb[a->x][a->y+1]==0){ // Para direita
				a->troc=0;
				return(2);
		    }else if(a->x-1>=0 && amb[a->x-1][a->y]==0){ // Para cima	
				a->ali=0;
				return(-20);
			}else if(a->x+1<TAM && amb[a->x+1][a->y]==0){ // Para baixo
				a->ali=0;
				return(20);
			}
		}
		if(a->x==a->lxP->x){
			a->ali=0;
		}
	}else{
		if(a->y-1>=0 && amb[a->x][a->y-1]==0 && (a->y)>(a->lxP->y)){ //Para esquerda
			return(-2);
		}else if(a->y+1<TAM && amb[a->x][a->y+1]==0 && (a->y)<(a->lxP->y)){ // Para direita
			return(2);
		}else if (a->y!=a->lxP->y){ 
			if(a->x+1>TAM && amb[a->x+1][a->y]>0){
		    	a->troc=1;
			}else if(a->troc==1 && a->x-1>=0 && amb[a->x-1][a->y]==0){ //Para cima
				return(-20);
			}else if(a->x+1<TAM && amb[a->x+1][a->y]==0){ // Para baixo
				a->troc=0;
				return(20);
			}else if(a->y-1>=0 && amb[a->x][a->y-1]==0){ // Para esquerda
				a->ali=1;
				return(-2);
			}else if(a->y+1<TAM && amb[a->x][a->y+1]==0){ // Para direita
				a->ali=1;
				return(2);
		    }
		}
		if(a->y==a->lxP->y){
			a->ali=1;
		}
	}
	return(0);
}

int droneVerifica(struct drone *a, int **amb, struct pontoRecolhimento **iniPR){
	int i=1, lp=3, cap;
	
	if(a->capOE>0 && a->capOV>0){
		/* Verifica por perto */
		while(i<3){
			cap=lp==3?a->capOE:a->capOV;
			if(a->x-i>=0 && amb[a->x-i][a->y]==lp && cap>0){
				if(i==2 && amb[a->x-1][a->y]==0){
					return(-i*10);	
				}else if(i==1){
					return(-i*10);
				}
			}
			if(a->x+i<TAM && amb[a->x+i][a->y]==lp && cap>0){
				if(i==2 && amb[a->x+1][a->y]==0){
					return(i*10);	
				}else if(i==1){
					return(i*10);	
				}
			} 
			if(a->y-i>=0&&amb[a->x][a->y-i]==lp&&cap>0){
				if(i==2&&amb[a->x][a->y-1]==0){
					return(-i);	
				}else if(i==1){
					return(-i);	
				}
			}
			if(a->y+i<TAM&&amb[a->x][a->y+i]==lp&&cap>0){
				if(i==2&&amb[a->x][a->y+1]==0){
					return(i);	
				}else if(i==1){
					return(i);
				}
			}
			if(lp==4){
				lp=3;
				i++;
			}else{
				lp=4;	
			}
		}
		// Se não tem ponto por perto
		return(direcoes(amb, a->y, a->x));		
	}else{	// Procura o mais perto
		if(a->lxP == NULL){
			return(procuraPontoRecolhimento(amb, iniPR, a, a->lxP));
		}else{
			if(vaiAoPonto(amb,a) == 100){
				return(procuraPontoRecolhimento(amb, iniPR, a, a->lxP));
			}else{
				return(vaiAoPonto(amb, a));
			}
		}
	}
	return(0);
}

/* Função para capturar obstaculo e baixar a bateria do drone em 1 */
int capturaObstaculo(struct drone *a, int *qtdObstaculo){
	a->capBateria--;
	*qtdObstaculo -= 1;
}

int depositaObstaculo(struct drone *a, int **amb){
	
	if(a->capOE==0){
		a->capOE=a->capBateria;
	}else if(a->capOV==0){
		a->capOV=a->capBateria;
	}
	a->lxP->cap-=a->capBateria;
	a->lxP=NULL;		
}

int droneAcao(struct drone *a, int acao, int **amb, int *qtdObstaculo){
	
	if(acao>=1&&acao<=3){
		amb[a->x][a->y]=0;
		a->y++;
		if(acao==1){
			capturaObstaculo(a, qtdObstaculo);
		}
		amb[a->x][a->y] = 5;
	}else if(acao >= -3 && acao <= -1){
		amb[a->x][a->y] = 0;
		a->y--;
		if(acao == -1){
			capturaObstaculo(a, qtdObstaculo);
		}
		amb[a->x][a->y]=5;
	}else if(acao >= 10 && acao <= 30){
		amb[a->x][a->y] = 0;
		a->x++;
		if(acao == 10){
			capturaObstaculo(a, qtdObstaculo);
		}
		amb[a->x][a->y]=5;
	}else if(acao >= -30 && acao <= -10){
		amb[a->x][a->y]=0;
		a->x--;
		if(acao == -10){
			capturaObstaculo(a, qtdObstaculo);
		}
		amb[a->x][a->y]=5;
	}else if(acao == 200){
		depositaObstaculo(a, amb);
	}
}

/* Imprime ambiente da matriz */
int imprimeAmbiente(int **amb){
	int i, j;
	
	for(i = 0; i <= TAM; i++){
		printf("%2d|", i);	
	}
	
	printf("\n");
	for(i = 0; i <= TAM; i++){
		printf("---");	
	}
	
	printf("\n");
	for(i=0;i<TAM;i++){
		printf("%2d", i+1);
		for(j=0;j<TAM;j++){
			printf("|");
			if(amb[i][j]==0){
				printf("%2c",' ');
			}else if(amb[i][j]==1){
				printf("%c%c",'P','R');
			}else if(amb[i][j]==2){
				printf("%c%c",'P','R');
			}else if(amb[i][j]==3){
				printf("%2c",'E');
			}else if(amb[i][j]==4){
				printf("%2c",'V');
			}else if(amb[i][j]==5){
				printf("%2c",'D');
			}
		}
		printf("|");
		printf("\n");
	}
	for(i=0; i <= TAM; i++){
		printf("---");	
	}
	printf("\n");	
}

int imprimeDrones(struct drone **iniD){
	struct drone *aux=*iniD;
	int i=1;
	
	while(aux != NULL){
		printf("\nDRONE %2d: x =%2d y =%2d BATERIA =%2d ", i, aux->x+1, aux->y+1, aux->capBateria);
		if(aux->lxP!=NULL){
			printf("\nPONTO DE RECOLHIMENTO PROXIMA DRONE %2d: X =%3d Y =%3d", i, aux->lxP->x+1, aux->lxP->y+1);
		}
		aux = aux->prox;
		i++;
	}	
	
}

int imprimePRecolhimentos(struct pontoRecolhimento **iniPR){
	struct pontoRecolhimento *aux=*iniPR;
	int i = 1;
	while(aux!=NULL){
		printf("\nPONTO DE RECOLHIMENTO %2d: X =%3d Y =%3d CAP =%2d TIPO:%2d",i,aux->x+1,aux->y+1,aux->cap,aux->tipo);
		i++;
		aux = aux->prox;
	}
}

int droneNoAmbiente(int **amb, struct drone **iniD, struct pontoRecolhimento **iniPR, int *qtdObstaculos, int velocidade){
	struct drone *aux=*iniD;
	int acao=0, i=0, tempo, pausa=0;
	
	while(aux!=NULL){
		while(*qtdObstaculos >= 0 && pausa == 0){
			if(*qtdObstaculos == 0){
				return(0);	
			}else{
				acao = droneVerifica(aux, amb, iniPR);
				if(acao==3||acao==-3||acao==30||acao==-30){
					i++;
				}
				droneAcao(aux, acao, amb, qtdObstaculos);
				pausa = 0;
			}
			system("cls");
			imprimePRecolhimentos(iniPR);
			printf("\n");
			imprimeDrones(iniD);
			printf("\n\n");
			if(TAM <= 18){
				imprimeAmbiente(amb);
			}		
			printf("Obstaculos restantes: %d",*qtdObstaculos);
			if(i == 3){
				i = 0;
				aux = aux->prox;
				pausa=1;
			}
			if(velocidade==1){
				getchar();	
			}else if(velocidade==2){
				tempo=clock();
				while(clock()-tempo<500);
			}
		}
		pausa=0;
	}	
}

int main(){
	struct drone *ptriD = NULL;
	struct pontoRecolhimento *ptriPR = NULL;
	int *qtdObstaculos = malloc(sizeof(int));
	int **amb;
	int tam=-5, velocidade=-5;
	
	printf("Trabalho de IA - Ferrovia Inteligente\n\n");
	srand(time(NULL));

	if(qtdObstaculos == NULL){
		printf("\n IMPOSSIVEL ALOCAR QUANTIDADE DE OBSTACULOS \n");
		system("pause");
		return(0);
	}
	
	printf("\nEscolha o tipo de ciclo: [1] PASSO A PASSO; [2] PADRAO(AUTOMATICO) ");
	while(velocidade<=0||velocidade > 3){
		if(scanf("%d", &velocidade) == 0){
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
	*qtdObstaculos = preencheAmbiente(amb, &ptriD, &ptriPR);
	
	/* Drone no ambiente */
	while(*qtdObstaculos > 0){
		droneNoAmbiente(amb, &ptriD, &ptriPR, qtdObstaculos, velocidade);
	}
	
	printf("\n---OPERACAO FINALIZADA\n");
    system("pause");
}
