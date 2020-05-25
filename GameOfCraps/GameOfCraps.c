//Steve Tran G01187141
//CS 262, Lab Section 204
//Project 1
#include <stdio.h>
#include <stdlib.h>

/*Function prototype*/
int rollDice();
void playGame(int *bankRollPlayingGame);
void playAgain(int *bankRollAddress);
int makeBet(int *bankRollPlayingGame);
int passLine(int *bankRollPayingGame, int bet);
int rollPointPL(int rolled,int bet, int*bankRollPlayingGame);
int doubleBetAmount(int *currentBankRoll,int betAmount);
int dontPassLine(int *bankRollPlayingGame,int bet);
int letItRide(int *bankRollPlayingGame, int bet, int gameMode);
int rollPointDPL(int rolled,int bet, int *bankRollPlayingGame );

/**
 * Main function will prompt a welcome message and then will prompt the user for the number of seed.
 * @return 0
 */
int main() {
    int bankRoll=100;
    char seed, inBuff[20];
    printf("Welcome to Game of Craps\n");
    //want to input in seed for debug purposes
    printf("Please enter a random number of seed: \n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff," %c",&seed);
    srand(seed);
    playAgain(&bankRoll);
    return 0;
}

/**
 * This function will roll 2 dice and get it result
 * @return result of rolling two dice
 */
int rollDice(){
    int d1, d2,sum ,validCheck=1;
    char inBuff[20];
    char rolling;
    while(validCheck){
        printf("Press 'R' or 'r' to roll the dice\n");
        fgets(inBuff,20,stdin);
        sscanf(inBuff,"%c",&rolling);
        if(rolling == 'R' || rolling == 'r'){
            d1 = rand() % 6 + 1; // this will generate a number between 0-5 , since the dice ranged from 1-6 so we have to +1 to the solution.
            d2 = rand() % 6 + 1;
            sum=d1+d2;
            printf("You rolled %d & %d \n", d1,d2);
            validCheck=0;

        } else{
            printf("Invalid option , choose again\n");
        }
    }
    return sum;
}
/**
 * This function will prompt the user if they wanted to play the game again
 * @param bankRollAddress is being pass into playgame() to update through out the game
 */
void playAgain(int *bankRollAddress){

    int play=1, bankRollPlayingGame;
    char option,inBuff[20];
    bankRollPlayingGame = * bankRollAddress;
    playGame(&bankRollPlayingGame);
    do{
        printf("Current Bankroll: $%d\n",bankRollPlayingGame);
        //check if user can play again or not
        if(bankRollPlayingGame <5){break;}
        //checking to see if the user have at least $5 to bet
            printf("Press [P|p] to Play Again  or [E|e] to Exit\n");
            fgets(inBuff,20,stdin);
            sscanf(inBuff," %c",&option);
            if(option == 'E' || option == 'e')
            {
                play=0;
            }
            else{
                if(option == 'P' || option == 'p'){
                    playGame(&bankRollPlayingGame);
                } else{
                    printf("Invalid option , choose again\n");
                }
            }

    }
    while (play==1);
    *bankRollAddress=bankRollPlayingGame;
}

/**
 * This function will run the game
 * @param bankRollPlayingGame is the bankroll amount using while playing the game
 */
void playGame( int *bankRollPlayingGame){
    int bet=0,betGotFromGame,validCheck=1;
    char choice,inBuff[20];
    bet=makeBet(bankRollPlayingGame);
    *bankRollPlayingGame= *bankRollPlayingGame-bet;
    while(validCheck==1){
        printf("Press [P|p] to play Pass Line, [D|d] for Don't Pass Line. \n");
        fgets(inBuff,20,stdin);
        sscanf(inBuff,"%c",&choice);
        if(choice == 'P' || choice=='p'){
            betGotFromGame=passLine(bankRollPlayingGame,bet);
            validCheck=0;
        }
        else
        {
            if(choice== 'D' || choice == 'd'){
                betGotFromGame=dontPassLine(bankRollPlayingGame,bet);
                validCheck=0;
            }
            else
            {
                printf("Invalid input try again.\n");
            }
        }
    }
    *bankRollPlayingGame=*bankRollPlayingGame+betGotFromGame;
}

/**
 * This is function will play the pass line rules of the game
 * @param bankRollPlayingGame amount of current bank roll
 * @param bet is the current bet amount
 * @return winning amount
 */
int passLine(int *bankRollPlayingGame,int bet) {
    printf("You are playing Pass Line\n");
    int firstRolled, winAmount,gameMode=1,wlResult=0;
    firstRolled=rollDice();

    if(firstRolled== 7 || firstRolled == 11 ){
        printf("You Win! You rolled 7 or 11 as  the first roll.\n");
        winAmount=bet*2;
        wlResult=bet;
        printf("YOU WON: $%d\n",wlResult);
    }
    else if(firstRolled== 2 || firstRolled == 3 || firstRolled == 12 ){
        printf("You Lose! You rolled 2 3 12 as the first roll.\n");
       winAmount=0;
        wlResult=bet;
        printf("YOU LOST: $%d\n",wlResult);
    }
    else{
        winAmount=rollPointPL(firstRolled,bet,bankRollPlayingGame);
    }
   // printf("winning amount %d\n",bet);
    if(winAmount>0){
        winAmount=letItRide(bankRollPlayingGame,winAmount,gameMode);
    }
return winAmount;
}

/**
 * This is function will play the dont pass line rules of the game
 * @param bankRollPlayingGame amount of current bank roll
 * @param bet is the current bet amount
 * @return winning amount
 */
int dontPassLine(int *bankRollPlayingGame,int bet) {
    printf("You are playing Don't Pass Line\n");
    int firstRolled, winAmount,gameMode=2,wlResult=0;
    firstRolled=rollDice();

    if(firstRolled== 7 || firstRolled == 11 ){
        printf("You Lose! You rolled 7 or 11 as  the first roll.\n");
        winAmount=0;
        wlResult=bet;
        printf("YOU LOST: $%d\n",wlResult);
    }
    else if(firstRolled== 2 || firstRolled == 3 || firstRolled == 12 ){
        printf("You Win! You rolled 2 3 12 as the first roll.\n");
        winAmount=bet*2;
        wlResult=bet;
        printf("YOU WON: $%d\n",wlResult);
    }
    else{
         winAmount=rollPointDPL(firstRolled,bet,bankRollPlayingGame);
    }
    //check to see if user can Let it Ride
    if(winAmount>0){
        winAmount=letItRide(bankRollPlayingGame,winAmount,gameMode);
    }
    return winAmount;
}


/**
 * This function will playing the game again with the winning bet money.
 * @param bankRollPlayingGame the current bankroll money, this is use for when the user want to do "press"
 * @param bet the winning bet amount from previous game
 * @param gameMode what game mode should the function play again. 1 for Pass line 2 for Dont pass line
 * @return the win/lose amount after let it ride completed
 */
int letItRide(int *bankRollPlayingGame, int bet,int gameMode) {
    int currentAmount=*bankRollPlayingGame;
    int validCheck =1;
    char inBuff[20],option;
    while(validCheck==1) {
        printf("Press [Y|y] to Let It Ride  or [N|n] to not\n");
        fgets(inBuff,3,stdin);
        sscanf(inBuff," %c",&option);
        if(option == 'N' || option == 'n'){validCheck=0;}
        else  if(option == 'Y' || option == 'y'){
            if(gameMode==1){
                printf("THIS IS LET IT RIDE PASS LINE\n");
                bet=passLine(&currentAmount,bet);
                *bankRollPlayingGame=currentAmount;
                validCheck=0;

            } else if(gameMode==2){
                printf("THIS IS LET IT RIDE DONT PASS LINE\n");
                bet=dontPassLine(&currentAmount,bet);
                *bankRollPlayingGame=currentAmount;
                validCheck=0;
            }
        }
    }
    return bet;
}
/**
 *This function will roll until reached 7 or "point" value, this Roll function is for Dont Pass Line, follow Dont Pass Line rules
 * @param rolled is the value of the rolldice() if first roll did not decide the game
 * @param bet is the bet amount
 * @param bankRollPlayingGame use for "press" if user wanted to
 * @return win amount
 */
int rollPointDPL(int rolled,int bet, int *bankRollPlayingGame ) {
    int currentBankRoll = *bankRollPlayingGame,wlResult=0, pointValue,true=1,roll,winAmount;
    pointValue=rolled;
    printf("Your \"Point\" is: %d. You must roll 7 before you roll this number to win the game \n ", pointValue);
    if(currentBankRoll>=bet){
    bet=doubleBetAmount(&currentBankRoll,bet);
    *bankRollPlayingGame=currentBankRoll;}
    while(true){
        roll=rollDice();
        printf("The total value of dice: %d\n",roll);
        if(pointValue == roll){
            printf("You Lose! You rolled your \"point\" value before rolling a 7.\n");
             winAmount=0;
            wlResult=bet;
            printf("YOU LOST: $%d\n",wlResult);
            true=0;
        }
        else {
            if (roll == 7){
                printf("Sevening Out! You Win!!\n");
                winAmount=bet*2;
                wlResult=bet;
                printf("YOU WON: $%d\n",wlResult);
                true=0;
            }
        }
    }
    return winAmount;
}
/**
 *This function will roll until reached 7 or "point" value, this Roll function is for  Pass Line, follow Pass line rules.
 * @param rolled is the value of the rolldice() if first roll did not decide the game
 * @param bet is the bet amount
 * @param bankRollPlayingGame use for "press" if user wanted to
 * @return win amount
 */
int rollPointPL(int rolled,int bet, int *bankRollPlayingGame ) {
    int currentBankRoll = *bankRollPlayingGame,wlResult=0,pointValue, true = 1, roll, winAmount;
    pointValue = rolled;
    printf("Your \"Point\" is: %d. You must roll this number before you roll a 7 to win the game \n ", pointValue);
    if (currentBankRoll >= bet) {
    bet = doubleBetAmount(&currentBankRoll, bet);
    *bankRollPlayingGame = currentBankRoll;
    }
    while(true){
        roll=rollDice();
        printf("The total value of dice: %d\n",roll);
        if(pointValue == roll){
            printf("You win! You rolled your \"point\" value before rolling a 7.\n");
      winAmount=bet*2;
            wlResult=bet;
            printf("YOU WON: $%d\n",wlResult);
            true=0;
        }
        else {
            if (roll == 7){
                printf("Sevening Out! You Lose.\n");
                winAmount=0;
                wlResult=bet;
                printf("YOU LOST: $%d\n",wlResult);
                true=0;
            }
        }
    }
    return winAmount;
}


/**
 * This function will double the user bet amount if they choose to do it
 * @param currentBankRoll Update the bankRoll amount when the user chose to double their bet
 * @param betAmount Bet amount will be double if the user want to double, else keep the same
 * @return current bet amount
 */
int doubleBetAmount(int *currentBankRoll,int betAmount){
    char doubleBet, inBuff[20];
    int validCheck=1;
    while (validCheck) {
        printf("Press [Y|y] if you want to \"Press\" your bet or [N|n] if you don't want to\n");
        fgets(inBuff, 20, stdin);
        sscanf(inBuff, "%c", &doubleBet);
        // Double the amount and subtract another same bet from bankRoll
        if (doubleBet == 'Y' || doubleBet == 'y') {
            *currentBankRoll=*currentBankRoll-betAmount;
            betAmount=betAmount*2;
            validCheck = 0;
            printf("BANKROLL AFTER PRESS: $%d\n",*currentBankRoll);
            printf("BET AFTER PRESS: $%d\n",betAmount);
        } else {
            if (doubleBet == 'N' || doubleBet == 'n') {
                printf("You chose not to double\n");
                validCheck = 0;
            } else {
                printf("Please enter a valid respond\n");
            }
        }
    }

    return betAmount;
}
/**
 * This function will let the user make their bet
 * @param bankRollPlayingGame subtracted the current bankroll with current bet
 * @return bet amount
 */
int makeBet(int *bankRollPlayingGame) {
    int validCheck =1,bet;
    char inBuff[20];
    while(validCheck) {
        printf("Please place your bet here: \n");
        fgets(inBuff, 20, stdin);
        sscanf(inBuff, "%d", &bet);
        if (bet >= 5 && bet <= *bankRollPlayingGame) {
            validCheck = 0;
        } else {
            if (bet > *bankRollPlayingGame) {
                printf("You cannot bet more than what you current have. \n");
            } else {
                printf("Please place a valid bet\n");
            }
        }
    }
    return bet;
}

