#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

/*

    1 2 3 4 5 6 7

a	0 0 0 0 0 0 0
b	0 0 0 0 0 0 0
c	0 0 0 0 0 0 0
d	0 0 0 0 0 0 0
e	0 0 0 0 0 0 0
f	0 0 0 0 0 0 0

*/

/*
Svuota la matrice, ovvero la riempie con tutti 0
*/
void svuotaMatrice();

/*
Stampa a video la matrice
*/
void stampaMatrice();

/*
Verifica se la stringa che indica la posizione è nel formato corretto
Esempio di stringhe corretta: c4, d1, e5
Esempio di stringhe non corrette: c11, c0, 8d, a11
Ritorna 1 in caso positivo, 0 altrimenti
*/
int stringaCorretta();

/*
Verifica se la posizione indicata è liberata.
Ritorna 1 in caso positivo, 0 altrimenti
*/
int posizioneLibera();

/*
Modifica la matrice inserendo nella posizione indicata il token relativo all'utente
Si presuppone che la stringa sia ben formattata e che la posizione non sia occupata
*/
void scriviInPosizione();

/*
Verifica se c'è stata la vittoria di uno dei due giocatori dopo ogni mossa
Ritorna un valore maggiore a 1 in caso positivo, 0 altrimenti
*/
int verificaVittoria();

/*
Verifica se ci sono 4 token uguali orizzontalmente
Ritorna 1 in caso positivo, 0 altrimenti
*/
int allineamentoOrizzontale();

/*
Verifica se ci sono 4 token uguali verticalmente
Ritorna 1 in caso positivo, 0 altrimenti
*/
int allineamentoVerticale();

/*
Verifica se ci sono 4 token uguali diagonalmente
Ritorna 1 in caso positivo, 0 altrimenti
*/
int allineamentoDiagonale();

/*
Genera una mossa del computer modificando la stringa passata per parametro.
La generazione della mossa è random.
*/
void generaMossaComputer();

/*
Genera una mossa del computer modificando la stringa passata per parametro.
La generazione della mossa è intelligente.
*/
void generaMossaComputerIntelligente();

int main(){
	int **matrice;
	int i=0;

	matrice = malloc(6 * sizeof(int));
  	for (i=0; i<6; i++){
    	matrice[i] = malloc(7 * sizeof(int));
  	}
	int eTerminata=0;
	char tmp_player[30];

	char *player;

	svuotaMatrice(matrice);
	
	printf("Benvenuto nella versione digitale del gioco Forza 4!\n");
	printf("Inserisci il tuo nome giocatore: ");
	scanf("%s",tmp_player);
	player=malloc(strlen(tmp_player) * sizeof(char));
	strcpy(player,tmp_player);
	free(tmp_player);

	printf("Le caselle con . rappresentano posizioni libere.\n");
	printf("Le caselle con X rappresentano posizioni occupate da %s\n",player);
	printf("Le caselle con 0 rappresentano posizioni occupate dal computer\n");
	printf("Per indicare la casella dovrai utilizzare la seguente sintassi: colonna\n");
	printf("Se vuoi inserire un token nella colonna '4' dovrai scrivere semplicemente '4'\n");
	printf("Che dire %s, buona fortuna!\n",player);
	printf("Ecco la scacchiera di partenza.\n");
	stampaMatrice(matrice);


	while(!eTerminata){

		/*Turno Player1*/
		char stringa[1];

		printf("%s: ",player);
		scanf("%s",stringa);

		while(!stringaCorretta(stringa) || !posizioneLibera(stringa, matrice)){
			printf("Posizione non corretta o occupata\n");
			printf("Ricorda: Se vuoi inserire un token nella colonna 4 dovrai scrivere semplicemente '4'\n");
			printf("%s: ",player);
			scanf("%s",stringa);
		}

		scriviInPosizione(stringa, matrice,80);
		printf("Ecco la scacchiera\n");
		stampaMatrice(matrice);
		if(verificaVittoria(matrice, 80)>0){
			printf("Vittoria di %s\n", player);
			return 1;
		}

		/*Turno Computer*/
		generaMossaComputer(stringa);

		printf("Computer: ");
		printf("%s\n",stringa);
		scriviInPosizione(stringa, matrice,67);
		printf("Ecco la scacchiera\n");
		stampaMatrice(matrice);
		if(verificaVittoria(matrice, 67)>0){
			printf("Vittoria del computer!\n");
		}
	}
	return 0;
}


void scriviInPosizione(char* stringa, int** matrice,int valore){
	int numero = stringa[0];

	int posizione_colonna = numero - '0'-1;

	int i=0;;
	for(i=5;i>=0;i--)
			if(matrice[i][posizione_colonna]==0){
				matrice[i][posizione_colonna]=valore;
				break;
			}
}

int posizioneLibera(char* stringa, int** matrice){
	int numero = stringa[0];
	int posizione_colonna = numero - '0'-1;

	return matrice[0][posizione_colonna]==0;
}

int stringaCorretta(char* stringa){
	if(strlen(stringa)!=1)
		return 0;
	int numero = stringa[0];
	return (numero>48 && numero <56);
}

void svuotaMatrice(int** matrice){
	int i=0;
	int j=0;
	for(i=0;i<6;i++)
		for(j=0;j<7;j++)
			matrice[i][j]=0;
}

void stampaMatrice(int** matrice){
	int i=0;
	int j=0;
	printf("  1 2 3 4 5 6 7\n");
	char x = 'a';
	for(i=0;i<6;i++){
		printf("%c ", x);
		for(j=0;j<7;j++)
			switch (matrice[i][j]){
				case 0: 
				printf(". ");
				break;
				case 67: 
				printf("0 ");
				break;
				case 80: 
				printf("X ");
				break;
			}
		printf("\n");
		x++;
	}
	printf("\n");

}

int verificaVittoria(int** matrice, int player){
	return allineamentoOrizzontale(matrice,player) + allineamentoVerticale(matrice,player) + allineamentoDiagonale(matrice,player);
}

int allineamentoOrizzontale(int** matrice, int player){
	int i=0;
	int j=0;
	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			if(matrice[i][j] == player && matrice[i][j]==matrice[i][j+1] && matrice[i][j]==matrice[i][j+2] && matrice[i][j]==matrice[i][j+3])
				return 1;
		}
	}
	return 0;
}

int allineamentoVerticale(int** matrice, int player){
	int i=0;
	int j=0;
	for(j=0;j<7;j++){
		for(i=0;i<3;i++){
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j] && matrice[i][j]==matrice[i+2][j] && matrice[i][j]==matrice[i+3][j])
				return 1;
		}
	}
	return 0;
}

int allineamentoDiagonale(int** matrice, int player){
	int i=0;
	int j=0;
	
/*
    1 2 3 4 5 6 7

a	L * K Y 0 0 0
b	I L * K Y 0 0
c	X I L * K Y 0
d	0 X I L * K Y
e	0 0 X I L * K
f	0 0 0 X I L *
*/

	//L
	for(i=0,j=0;i<3;i++,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j+1] && matrice[i][j]==matrice[i+2][j+2] && matrice[i][j]==matrice[i+3][j+3])
				return 1;
	//*
	for(i=0,j=1;i<3;i++,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j+1] && matrice[i][j]==matrice[i+2][j+2] && matrice[i][j]==matrice[i+3][j+3])
				return 1;
	//I
	for(i=1,j=0;i<2;i++,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j+1] && matrice[i][j]==matrice[i+2][j+2] && matrice[i][j]==matrice[i+3][j+3])
				return 1;
	//K
	for(i=0,j=2;i<2;i++,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j+1] && matrice[i][j]==matrice[i+2][j+2] && matrice[i][j]==matrice[i+3][j+3])
				return 1;
	//X
	for(i=2,j=0;i<3;i++,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j+1] && matrice[i][j]==matrice[i+2][j+2] && matrice[i][j]==matrice[i+3][j+3])
				return 1;

	//Y
	for(i=0,j=3;i<1;i++,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i+1][j+1] && matrice[i][j]==matrice[i+2][j+2] && matrice[i][j]==matrice[i+3][j+3])
				return 1;


/*
    1 2 3 4 5 6 7

a	0 0 0 X I L *
b	0 0 X I L * K
c	0 X I L * K Y
d	X I L * K Y 0
e	I L * K Y 0 0
f	L * K Y 0 0 0
*/

	//L
	for(i=5,j=1;i>2;i--,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i-1][j+1] && matrice[i][j]==matrice[i-2][j+2] && matrice[i][j]==matrice[i-3][j+3])
				return 1;

	//*
	for(i=5,j=1;i>2;i--,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i-1][j+1] && matrice[i][j]==matrice[i-2][j+2] && matrice[i][j]==matrice[i-3][j+3])
				return 1;

	//I
	for(i=4,j=0;i>2;i--,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i-1][j+1] && matrice[i][j]==matrice[i-2][j+2] && matrice[i][j]==matrice[i-3][j+3])
				return 1;
	
	//K
	for(i=5,j=2;i>3;i--,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i-1][j+1] && matrice[i][j]==matrice[i-2][j+2] && matrice[i][j]==matrice[i-3][j+3])
				return 1;

	//X
	for(i=3,j=0;i>2;i--,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i-1][j+1] && matrice[i][j]==matrice[i-2][j+2] && matrice[i][j]==matrice[i-3][j+3])
				return 1;

	//Y
	for(i=5,j=3;i>4;i--,j++)
			if(matrice[i][j] == player && matrice[i][j]==matrice[i-1][j+1] && matrice[i][j]==matrice[i-2][j+2] && matrice[i][j]==matrice[i-3][j+3])
				return 1;

	return 0;
}

void generaMossaComputer(char* stringa){
	int x = 49 + rand()%7;
	char *tmp;	

	switch (x){
				case 49: 
					tmp="1";
					break;
				case 50: 
					tmp="2";
					break;
				case 51: 
					tmp="3";
					break;
				case 52: 
					tmp="4";
					break;
				case 53: 
					tmp="5";
					break;
				case 54: 
					tmp="6";
					break;
				case 55: 
					tmp="7";
					break;
			}	
  	strcpy(stringa,tmp);
  	free(tmp);
}