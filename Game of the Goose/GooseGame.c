/*
 * Steve Tran G01187141
 * CS 262, Lab Section 212
 * Project 1
 */


#include <stdio.h>
#include <stdlib.h>


#define BOARD_SIZE 24
#define NUM_GOOSE_SPACES 3
#define NUM_BRIDGE_SPACES 1
#define NUM_MAZE_SPACES 2
#define NUM_SKULL_SPACES 1

const int gooseSpaces[NUM_GOOSE_SPACES]={7 ,11, 15};
const int bridgeSpaces[NUM_BRIDGE_SPACES]={6};
const int mazeSpaces[NUM_MAZE_SPACES]={13,20};
const int skullSpaces[NUM_SKULL_SPACES]={23};

/**Prototypes*/
void setSeed();
int roll();
void menu();
int options(char userInput);
void gamePlayControl();
int goFirstCheck();
void printBoard(int hPos, int cPos);
void locator(int hPos, int cPos,int i);
void symbols(int position);
void gooseSymbols(int pos);
void bridgeSymbols(int pos);
void mazeSymbols(int pos);
void skullSymbols(int pos);
void hFirst();
void cFirst();
int winnerCheck(int hPos, int cPos);
int isGoose(int *pos,int distance);
int isBridge(int *pos);
int isMaze(int *pos,int prev);
int isSkull(int *pos);
void trapsCheck(int * pos,int dist, int prev);
void positionCheck(int *pos);
int hTurn(int *hPos,int cPos);
int cTurn(int hPos,int *cPos);
void goToMenu();
void playerLocator(int player,int cLocation);
void isOver(int * pos);
/**
 * Main function.
 */
int main(){
	setSeed();
	menu();
	return 0;
}

/**
 * Get and Set the seed from user input for rand() to use through out the program.
 */
void setSeed(){
	int seed;
	char inBuf[20];
	printf("Please enter an integer number that will be used as seed for the generation of random numbers when rolling the dice: \n");
	fgets(inBuf,20,stdin);
	sscanf(inBuf,"%d",&seed);
	srand(seed);
}

/**
 * Roll() function uses to roll 2 dices and return the sum of them.
 */
int roll(){
	char enterKey, inBuf[20];
	int total=0,valid=0,firstDice=0,secondDice=0;
	while(valid == 0){
		printf("Press <enter> to roll the dice");
		fgets(inBuf,20,stdin);
		sscanf(inBuf,"%c",&enterKey);
		if(enterKey== '\n'){
			firstDice=random()%6+1;
			secondDice=random()%6+1;
			total = firstDice + secondDice;
			printf("%d and %d for a %d\n",firstDice,secondDice,total);
			valid =1;
		}else{
			printf("\nInvalid input please try again \n");
		}
	}
	return total;
}
/**
 * Main menu of the game.
 */
void menu(){
	int valid =0;
	char userInput,inBuf[20];
	printf("\nWelcome to the game of goose, please select an option: \n");
	while(valid ==0){
		printf("\nPress 'P' or 'p' to play \n");
		printf("\nPress 'Q' or 'q' to quit \n");
		fgets(inBuf,20,stdin);
		sscanf(inBuf,"%c",&userInput);
		valid =options(userInput);
	}
}
/**
 * Options from main menu for user to choose.
 */
int options(char userInput){
	int valid =0;
	if(userInput == 'P' || userInput == 'p'){
		gamePlayControl();
		valid =1;
	}
	else if(userInput == 'Q' || userInput == 'q'){
		printf("Good bye. \n");
		exit(1);
	}
	else{
		printf("\nInvalid input please try again \n");

	}
	return valid;
}
/**
 * Check to see which player is going first.
 *
 */
int goFirstCheck(){
	int humanRoll,compRoll,valid=0,goFirst=0;
	while(valid == 0){
		printf("\nHUMAN PLAYER, ");
		humanRoll=roll();
		printf("\nCOMPUTER PLAYER, ");
		compRoll=roll();
		if(humanRoll>compRoll){
			printf("\nHUMAN PLAYER goes first\n");
			valid =1;
		}
		else if(compRoll>humanRoll){
			printf("\nCOMPUTER PLAYER goes first\n");
			valid =1;
			goFirst=1;
		}else{
			printf("\nBoth the Human and Computer rolled the same value. Roll Again. \n");

		}
	}
	return goFirst;
}

/**
 * Control the flow of the game.
 */
void gamePlayControl(){
	int turn;
	turn=goFirstCheck();
	if(turn == 0){
		hFirst();
	}else{
		cFirst();
	}
}
/**
 * This function will display the board.
 */
void printBoard(int hPos, int cPos){
	int i;
	for(i=1; i<=BOARD_SIZE; i++){
		symbols(i);
		locator(hPos,cPos,i);
		if(i== BOARD_SIZE/2){
			printf("\n");
		}
	}
	printf("\n");
}
/**
 * This function will locate where is human/computer player is on the board.
 */
void locator(int hPos, int cPos,int i){
	char h='$',c='%';
	if(hPos == i && cPos == i){
		printf("[%c%c]\t",h,c);
	}
	else if(hPos == i){
		playerLocator(h,i);
	}
	else if(cPos ==i){
		playerLocator(c,i);
	}
	else if(i == BOARD_SIZE){
		printf("<%d>\t",i);

	}
	else {
		printf("[%d]\t",i);
	}
}
/**
 * Put the player/computer at the location.
 */
void playerLocator(int player,int cLocation){
	if(cLocation == BOARD_SIZE){
		printf("<%c>\t",player);
	}else{
		printf("[%c]\t",player);

	}
}
/**
 * Display all the symbol for traps on the board.
 */
void symbols(int position){
	gooseSymbols(position);
	bridgeSymbols(position);
	mazeSymbols(position);
	skullSymbols(position);
}

/**
 * Display goose symbol.
 */
void gooseSymbols(int position){
	int i;
	for(i=0; i<NUM_GOOSE_SPACES; i++){
		if(gooseSpaces[i] == position){
			printf("+");
		}
	}
}
/**
 * Display bridge symbol.
 */
void bridgeSymbols(int position){
	int i;
	for(i=0; i<NUM_BRIDGE_SPACES; i++){
		if(bridgeSpaces[i] == position){
			printf("*");
		}
	}
}
/**
 * Display maze symbol.
 */
void mazeSymbols(int position){
	int i;
	for(i=0; i<NUM_MAZE_SPACES; i++){
		if(mazeSpaces[i] == position){
			printf("-");
		}
	}
}
/**
 * Display skull symbol.
 */
void skullSymbols(int position){
	int i;
	for(i=0; i<NUM_SKULL_SPACES; i++){
		if(skullSpaces[i] == position){
			printf("!");
		}
	}
}
/**
 * Checking for winner.
 */
int winnerCheck(int hPos, int cPos){
	int winner=0;
	if(hPos == BOARD_SIZE){
		printf("\nGame over!  Human Won!\n");
		winner=1;
	}
	else if(cPos == BOARD_SIZE){
		printf("\nGame over!  Computer Won!\n");
		winner =1;
	}
	return winner;

}

/**
 * Human Player go first.
 */
void hFirst(){
	int hPos=1,cPos=1,valid=0;
	printBoard(hPos,cPos);
	while(valid == 0) {
		if(hTurn(&hPos,cPos)){
			valid =1;
		}
		else if(cTurn(hPos,&cPos)){
			valid =1;
		}
	}
	goToMenu();
}
/**
 * Computer Player go first.
 */
void cFirst(){
	int hPos=1,cPos=1,valid=0;
	printBoard(hPos,cPos);
	while(valid == 0) {
		if(cTurn(hPos,&cPos)){
			valid =1;
		}
		else if(hTurn(&hPos,cPos)){
			valid =1;
		}
	}
	goToMenu();
}


/**
 * Check if the player landed of any of the traps.
 */
void trapsCheck(int *pos,int dist,int prev){
	int valid =0;
	positionCheck(pos);
	while(valid == 0){
		if(!isGoose(pos, dist) && !isBridge(pos)  && !isMaze(pos,prev) && !isSkull(pos) ){
			valid =1;
		}
	}
	printf("\n\n");
}

/**
 * Use to check when the player hit he goose space to see if the player will go over the BOARD_SIZE after that or not.
 */
void isOver(int *pos) {
	int nOver =0;
	if (*pos > BOARD_SIZE) {
		nOver = *pos - BOARD_SIZE;
		*pos = BOARD_SIZE - nOver;
	}
}

/**
 * Check if player landed on a goose space.
 */
int isGoose(int *pos,int distance){
	int i,goose=0;
	for( i= 0; i<NUM_GOOSE_SPACES; i++){
		if(gooseSpaces[i] == *pos){
			*pos += distance;
			isOver(pos);
			printf(", go to space %d", *pos);
			goose =1;
			break;
		}
	}
	return goose;
}
/**
 * Check if player landed on a bridge space.
 */
int isBridge(int *pos){
	int i,bridge =0;
	for( i= 0; i<NUM_BRIDGE_SPACES; i++){
		if(bridgeSpaces[i] == *pos){
			*pos = 12;
			printf(", go to space %d", *pos);
			bridge= 1;
		}
	}
	return bridge;
}
/**
 * Check if player landed on a maze space.
 */
int isMaze(int *pos , int prev){
	int i,maze =0;
	for( i= 0; i<NUM_MAZE_SPACES; i++){
		if(mazeSpaces[i] == *pos){
			*pos = prev;
			printf(", come back to space %d", *pos);

			maze= 1;
		}
	}
	return maze;
}
/**
 * Check if player landed on a skull space.
 */
int isSkull(int *pos){
	int i,skull=0;
	for( i= 0; i<NUM_SKULL_SPACES; i++){
		if(skullSpaces[i] == *pos){
			*pos=1;
			printf(", return to start %d", *pos);
			skull= 1;
		}
	}
	return skull;
}
/**
 * Check position of player after each roll().
 */
void positionCheck(int *pos){
    int nOver=0;
    if(*pos > BOARD_SIZE){
        nOver=*pos-BOARD_SIZE;
        *pos = BOARD_SIZE - nOver;
    }
    printf("go to space %d",*pos);
}
/**
 * Human turn to roll.
 */
int hTurn(int *hPos,int cPos){
	int dist=0,prev=0;
	printf("HUMAN PLAYER'S TURN, [%d]... ", *hPos);
	dist=roll();
	prev=*hPos;
	*hPos += dist;
	trapsCheck(hPos,dist,prev);
	printBoard(*hPos, cPos);
	return winnerCheck(*hPos,cPos);
}
/**
 * Computer turn to roll.
 */
int cTurn(int hPos, int *cPos){
	int dist=0,prev=0;
	printf("COMPUTER PLAYER'S TURN, [%d]... ", *cPos);
	dist=roll();
	prev=*cPos;
	*cPos += dist;
	trapsCheck(cPos,dist,prev);
	printBoard(hPos, *cPos);
	return winnerCheck(hPos,*cPos);
}


/**
 * Go back to main menu.
 */
void goToMenu() {
	char inBuf[20], enterKey;
	int valid = 0;
	while (valid == 0) {
		printf("Press <enter> to return to the main menu");
		fgets(inBuf,20,stdin);
		sscanf(inBuf,"%c",&enterKey);
		if(enterKey == '\n'){
			valid =1;
			menu();
		}
		else{
			printf("\nInvalid input please try again \n");
		}
	}
}
