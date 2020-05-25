/*
 * Steve Tran G01187141
 * CS262, Lab Section 212
 * Project 2
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"GMUsms.h"


#define msgSize 160
#define pSize 120

/*Prototypes*/
void menu();
void menuPrompt();

void initArr(char *arr);
void initUnsignedArr1(unsigned char *arr);
void initUnsignedArr2(unsigned char *arr);

void getFileName(char *fname);
void getMsg(char *msgASCII);
void remNewLine(char *msg);

void pOption();
void convertToSMS(char *msgASCII, unsigned char *msgGMUSCII);
void pack(unsigned char *pArr, unsigned char *msgGMUSCII);

void uOption();
void unpack(unsigned char *pArr, unsigned char *msgGMUSCII);
void convertToChar(char *msgASCII, unsigned char *msgGMUSCII);


/*
 * Main function.
 */
int main(int argc, char *argv[]){
	menu();
	return 0;
}


/*
 * Menu prompt.
 */
void menuPrompt(){
	printf("\n\n[P]ack and save a line of text  (options are 'P' or 'p')\n");
	printf("[U]npack and print a line of text (options are 'U' or 'u')\n");
	printf("[Q]uit  (options are 'Q' or 'q')\n\n");

}



/*
 * Menu control.
 */
void menu(){
	int valid =0;
	char inBuff[20],choice;
	while(valid == 0){
		menuPrompt();
		fgets(inBuff,20,stdin);
		sscanf(inBuff,"%c",&choice);
		switch(choice){
			case 'p':
			case 'P':
				pOption();
				break;
			case 'U':
			case 'u':
				uOption();
				break;
			case 'Q':
			case 'q':
				valid =1;
				break;
			default:
				printf("\nInvalid input try again\n");
		}
	}
}





/*
 * Remove new line character at the end of a string.
 */
void remNewLine(char *msg){
	int i;
	for(i=0;i<strlen(msg);i++){
		if(msg[i] == '\n'){
			msg[i] = '\0';
		}
	}
}





/*
 * Initialize all the elements of the char array with size 160 to 0.
 */
void initArr(char *arr){
	int i;	
	for(i=0;i<msgSize;i++){
		arr[i] =0;

	}


}





/*
 * Initialize all the elements of the unsigned char array with size 160 to 0.
 */
void initUnsignedArr1(unsigned char *arr){
	int i;
	for(i=0;i<msgSize;i++){
		arr[i] =0;

	}
}




/*
 * Initialize all the elements of the unsigned char array with size 120 to 0.
 */
void initUnsignedArr2(unsigned char *arr){
	int i;
	for(i=0;i<pSize;i++){
		arr[i] =0;

	}
}




/*
 * Pack option control.
 */
void pOption(){
	FILE *outPtr;
	char msgASCII[msgSize],fileName[100];
	unsigned char msgGMUSCII[msgSize], pArr[pSize];
	initArr(fileName);
	initArr(msgASCII);
	initUnsignedArr1(msgGMUSCII);
	initUnsignedArr2(pArr);

	//prompted for a filename
	getFileName(fileName);	
	//prompt the user for a line of text
	getMsg(msgASCII);
	//If the file cannot be opened, an appropriate message is displayed to the user, and the program execution will return to the menu.
	if((outPtr = fopen(fileName, "wb")) == NULL){
		printf("\nCannot open the file returning to main menu\n");
	}else{
		convertToSMS(msgASCII,msgGMUSCII);
		pack(pArr, msgGMUSCII);
		fwrite(pArr, sizeof(unsigned char), sizeof(pArr), outPtr);
		fclose(outPtr);
	}	

}



/*
 * Get the file name from the user.
 */
void getFileName(char *fname){
	char inBuf[100];
	printf("Enter the name of your file:\n");
	fgets(inBuf,20,stdin);
	sscanf(inBuf,"%s",fname);
}




/*
 * Get a line of text of the user.
 */
void getMsg(char *msgASCII){
	int i,valid =0;
	while(valid == 0){
		printf("Enter a line of text:\n");
		fgets(msgASCII,msgSize,stdin);
		remNewLine(msgASCII);
		if(strlen(msgASCII) != 0){
			valid =1;
		}else{
			printf("\nInvalid input please try again.\n");
		}
	}
}




/*
 * Convert the ASCII value to GMUSCII value.
 */
void convertToSMS(char *msgASCII, unsigned char *msgGMUSCII){
	int i;
	for(i=0;i<strlen(msgASCII);i++){
		msgGMUSCII[i] = CharToSMS( (unsigned char)msgASCII[i]);
	}
}



/*
 * Pack the message.
 */
void pack(unsigned char *pArr, unsigned char *msgGMUSCII)
{
	//Pattern 	_ _ b b b b b b	
	//              _ _ _ _ b b b b		
	//              _ _ _ _ _ _ b b
	//		Repeat
	int i,j;
	unsigned char holder=0;
	for(i=0,j=0;j<msgSize;i=i+3,j=j+4){
		
		holder = (msgGMUSCII[j+1] & 3);
		pArr[i]   = (msgGMUSCII[j]) | (holder << 6);
		holder =0;

		holder = (msgGMUSCII[j+2] & 15);
		pArr[i+1] = (msgGMUSCII[j+1] >> 2) |  (holder << 4);
		holder =0;
		
		holder = (msgGMUSCII[j+3]  << 2);
		pArr[i+2] = (msgGMUSCII[j+2] >> 4) | (holder);
		holder = 0;
		//Repeat
	}
}




/*
 * Unpack option control.
 */
void uOption(){
	int i;
	FILE *inPtr;
	char msgASCII[msgSize],fileName[100];
	unsigned char msgGMUSCII[msgSize], pArr[pSize];
	initArr(fileName);
	initArr(msgASCII);
	initUnsignedArr1(msgGMUSCII);
	initUnsignedArr2(pArr);
	//prompted for a filename
	getFileName(fileName);
	//check if file is valid
	if((inPtr = fopen(fileName,"rb")) == NULL){
		printf("\nCannot open the file returning to main menu\n");	
	}else{
		//reading from binary format file
		fread(pArr,sizeof(unsigned char), sizeof(pArr), inPtr);
		unpack(pArr,msgGMUSCII);
		convertToChar(msgASCII,msgGMUSCII);
		printf("\nThe message is:\t%s\n",msgASCII);		
		fclose(inPtr);
	}
}


/*
 * Unpack the message.
 */
void unpack(unsigned char *pArr, unsigned char *msgGMUSCII){
	int i,j;
	unsigned char holder =0;
	for(i=0,j=0;i<pSize;i=i+3,j=j+4){
	
		msgGMUSCII[j]= (pArr[i] & 63);

		holder = (pArr[i+1] & 15);
		msgGMUSCII[j+1] = (pArr[i] >> 6) | (holder <<2);
		holder =0;

		holder = (pArr[i+2] & 3);
		msgGMUSCII[j+2] = (pArr[i+1] >> 4) | (holder << 4);

		msgGMUSCII[j+3] = (pArr[i+2] >> 2); 
		//Repeat
	}
}



/*
 * Convert the message from GMUSCII backto ASCII value.
 */
void convertToChar(char *msgASCII, unsigned char *msgGMUSCII){	
	int i;
	for(i=0;i<strlen(msgGMUSCII);i++){
		msgASCII[i] = SMSToChar( (char) msgGMUSCII[i]);
	}

}


