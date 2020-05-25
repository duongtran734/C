/**
 * Steve Tran G01187141
 * CS262, Lab Section 204
 * Project 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

/**
 * Song Structure
 */
typedef struct _songnode
{
	char title[35];
	char artist[35];
	char album[35];
	double duration;
	struct _songnode *next;
} SongNode;
/**Prototypes for read and store input file*/
void readInputFileControl(char *fileName, SongNode **head);
void checkValidFile(FILE **filePtr , char fileName[]);
int readInputFile(FILE **filePtr, SongNode **head);
/**Prototypes for getters ,setters, and prompts*/
void libraryMenuPrompt();
int getUseChoice();
void getTitleSong(char* title);
int getNodePosition(SongNode *head, char *search);
void strUpper(char * str);
int getPosition();
int checkValidPosition(char *position);
int checkEmptyString(const char *str);
int checkDuration(char *duration);
int isDuration(char *dur);
void checkValidNewFile(FILE **filePtr);
/**Prototypes for linked list*/
SongNode *createEmptyList();
SongNode *createSongNode(char *title, char *artist, char *album, double duration);
void addAlphabeticalOrder(SongNode **head, SongNode *newNode);
void printSongInfo(SongNode *song);
void printList(SongNode *head);
void deleteList(SongNode **head);
int compareTitle (SongNode *node1 , SongNode *node2);
SongNode *searchByTitle(SongNode *head, char *search);
SongNode *removeSong(SongNode **head, SongNode *remNode);
int deleteSong(SongNode **head, SongNode *delNode);
void appendSong(SongNode **head, SongNode *newNode);
void insertBeginning(SongNode **head, SongNode *newNode);
int insertSong(SongNode **head, SongNode *newNode, int position);
int getListSize(SongNode *head);
double computeDuration(SongNode *head);
int contain(SongNode *musicLibraryHead,SongNode *nodeToAdd);
void deleteSongList(SongNode **head);
/**Prototypes for controls*/
void searchSongTitleControl(SongNode **musicLibraryHead);
void addSongToPlaylistControl(SongNode **musicLibraryHead,SongNode **playListHead);
void addSongMenuControl(SongNode *nodeToAdd,SongNode **playListHead,SongNode **musicLibraryHead);
void musicLibraryControl(SongNode **musicLibraryHead,SongNode **playListHead);
void playListMenuControl(SongNode **musicLibraryHead,SongNode **headPlayList);
void moveSongUp(SongNode **headPlayList);
void moveSongDown(SongNode **headPlayList);
void removeSongFromList(SongNode **musicLibraryHead,SongNode **headList);
/**
 * Main function
 * @param argc command line argument
 * @param argv command line argument
 * @return 0
 */
int main(int argc, char *argv[]) {
	SongNode *headMusicLibrary=createEmptyList();
	SongNode *headPlaylist=createEmptyList();
	readInputFileControl(argv[1], &headMusicLibrary);
	playListMenuControl(&headMusicLibrary,&headPlaylist);
	return 0;
}
/**
 * Prompt for the library menu
 */
void libraryMenuPrompt(){
	printf("\n\t\t\tLibrary Menu\n");
	printf("1- View all songs\n");
	printf("2- Search by title\n");
	printf("3- Add a song to playlist\n");
	printf("4- Back to playlist\n");
}
/**
 * Prompt for add song to playlist menu
 */
void addSongMenuPrompt(){
	printf("\n\t\t\tAdd Song Menu\n");
	printf("1- Add song to the end\n");
	printf("2- Add song at the beginning\n");
	printf("3- Insert song at a specific position\n");
}
/**
 * Prompt for playlist menu
 */
void playListMenuPrompt(){
	printf("\n\t\t\tPlaylist Menu\n");
	printf("1 - Print playlist\n");
	printf("2 - Show duration\n");
	printf("3 - Search by title\n");
	printf("4 - Move a song up\n");
	printf("5 - Move a song down\n");
	printf("6 - Remove a song\n");
	printf("7 - Go to Music Library\n");
	printf("8 - Quit\n");
}
/**
 * Get the user choice for menu choices
 * @return the user choice
 */
int getUseChoice(){
	int userChoice=0;
	char inBuf[20];;
	printf("\nEnter your choice here \n");
	fgets(inBuf,20,stdin);
	sscanf(inBuf,"%d",&userChoice);
	return userChoice;
}
/**
 * Get the title of the song from user
 * @param title is the title
 */
void getTitleSong(char* title){
	char inBuf[35];
	printf("\nEnter the title of the song here: \n");
	fgets(inBuf,35,stdin);
	sscanf(inBuf,"%[^\n]",title);
	strUpper(title);
}
/**
 * Convert the string to uppercase
 * @param str is the string to convert
 */
void strUpper(char * str){
	while (*str) {
		*str = toupper((unsigned char) *str);
		str++;
	}
}
/**
 * Get the position from the user
 * @return the position
 */
int getPosition(){
	char inBuf[25],position[25];
	int valid=0,index;
	do {
		printf("Enter the position in the playlist you want the song into \n");
		fgets(inBuf, 25, stdin);
		sscanf(inBuf, "%s", position);
		index=checkValidPosition(position);
		if(index>=0){
			valid =1;
		}
	}while(valid == 0);
	return index;
}
/**
 * Check if the enterted position is valid
 * @param position is the position to check for
 * @return the position
 */
int checkValidPosition(char *position){
	int length=0,count =0,i=0,index=0;
	length = strlen(position);
	count = 0;
	for (i = 0; i < length; i++) {
		if (!isdigit(position[i])) {
			printf("Invalid input try again\n");
			count++;
			return -1;
		}
	}
	if (count == 0) {
		printf("%s\n", position);
		index = atoi(position);
	}
	return index;
}
/**
 * This function check to see if the string is empty.
 * @param str is the string to check for
 */
int checkEmptyString(const char * str){
	if (str[0] == 0){
		printf("Error-empty string\n");
		return -1;
	}
	else {
		return 0;
	}
}
/**-----------------------------------------Read and store from text file-----------------------------------------*/
/**
 * Check to see if the input file is valid.
 * @param filePtr is the file pointer
 * @fileName is the file to check for
 */
void checkValidFile(FILE **filePtr , char fileName[]){
	int valid =0;
	char inBuff[50], *inputFileName=fileName ;
	do{
		if(( *filePtr = fopen(inputFileName, "r")) == NULL){
			printf("\nInvalid Input File.\nEnter your input file name again.\n");
			fgets(inBuff,50,stdin);
			sscanf(inBuff,"%s",inputFileName);
		}
		else{
			printf("Valid Input File.\n");
			valid=1;
		}
	}while(valid==0);
}
/**
 * Check to see if the new entered file is valid.
 * @param filePtr is the file pointer
 */
void checkValidNewFile(FILE **filePtr){
	int valid =0;
	char inBuff[50],inputFileName[35];
	printf("Enter Differrent File Name\n");
	fgets(inBuff,50,stdin);
	sscanf(inBuff,"%s",inputFileName);
	do{
		if(( *filePtr = fopen(inputFileName, "r")) == NULL){
			printf("\nInvalid Input File.\nEnter your input file name again.\n");
			fgets(inBuff,50,stdin);
			sscanf(inBuff,"%s",inputFileName);
		}
		else{
			printf("Valid Input File.\n");
			valid=1;
		}
	}while(valid==0);
}
/**
 * Check is see if the duration is valid
 * @param dur is the duration to check for
 */
int isDuration(char *dur){
	char c;
	int dot=0;
	if(dur == NULL){
		return -1;
	}
	while(*dur) {
		c = *dur;
		if(c == '.'){
			if (++dot > 1) {
				printf("Invalid duration \n");
				return -1;
			}
		}
		else{
			if (c < '0' || c > '9') {
				printf("Invalid duration \n");
				return -1;
			}
		}
		dur++;
	}
	return 0;
}

/**
 * This function will read the input data from the file and store it in the linked list
 * @param filePtr is the filePtr to the input file
 * @param head is the head of the linked list
 */
int readInputFile(FILE **filePtr, SongNode **head){
	int count=0;
	char title[35],album[35],artist[35],inBuff[100],durationStr[35];
	double duration=0;
	SongNode *newNode;
	title[0]=0,album[0]=0,artist[0]=0;
	while (fgets(inBuff, 100, *filePtr) != NULL) {
		if (count == 0) {
			sscanf(inBuff, "%[^\n]", title);
			if(checkEmptyString(title)<0){
				return -1;
			}
			count++;
		} else if (count == 1) {
			sscanf(inBuff, "%[^\n]", artist);
			if(checkEmptyString(artist)<0){
				return -1;
			}
			count++;
		} else if (count == 2) {
			sscanf(inBuff, "%[^\n]", album);
			if(checkEmptyString(album)<0){
				return -1;
			}
			count++;
		} else if (count == 3) {
			sscanf(inBuff, "%[^\n]", durationStr);
			if(isDuration(durationStr)<0){
				return -1;
			}
			sscanf(durationStr,"%lf",&duration);
			newNode = createSongNode(title, artist, album, duration);
			addAlphabeticalOrder(head, newNode);
			count = 0;
		}
	}
	return 0;
}
/**
 * Read data from input file
 * @param fileName is the file to read from
 * @param head is the list that will be store into
 */
void readInputFileControl(char *fileName, SongNode **head){
	FILE *filePtr;
	int valid=0;
	checkValidFile(&filePtr, fileName);

	do{
		valid=readInputFile(&filePtr, head);
		if(valid <0){
			fclose(filePtr);
			deleteSongList(head);
			checkValidNewFile(&filePtr);
		}
	}while(valid !=0);
	fclose(filePtr);
}
/**
 * Insert a song into the list in  alphabetical order.
 * @param head is the list to be insert into
 * @param newNode is the node to insert
 */
void addAlphabeticalOrder(SongNode **head, SongNode *newNode){

	if (*head == NULL || compareTitle(newNode, *head) < 0) {
		newNode->next = *head;
		*head=newNode;
	} else {
		SongNode *current = *head;

		while (current->next != NULL && compareTitle(newNode, current->next) >= 0) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}
/**-----------------------------------------Linked List Methods------------------------------------------*/
/**
 * Create an empty list
 * @return the head of the new list
 */
SongNode *createEmptyList(){
	SongNode *head =NULL;
	return head;
}
/**
 * Compare to 2 song titles for alphabetical use
 * @param node1 is song 1
 * @param node2 is song 2
 * @return 0 if they are equal, 1 if song1>song2,-1 if song1<song2
 */
int compareTitle (SongNode *node1 , SongNode *node2)
{
	return strcmp(node1->title, node2->title);
}
/**
 * Create a new song node.
 * @param title is the title of the new song
 * @param artist is the artist name of the new song
 * @param album is the album name of the new song
 * @param duration is the duration of the new song
 * @return the song that just created
 */
SongNode *createSongNode(char *title, char *artist, char *album, double duration){
	SongNode *song = malloc(sizeof(SongNode));
	strUpper(title);
	strcpy((char *) &song->title, title);
	strcpy((char *) &song->artist, artist);
	strcpy((char *) &song->album, album);
	song->duration=duration;

	song->next=NULL;
	return song;
}
/**
 * Display the content of a song.
 * @param song is the song to display
 */
void printSongInfo(SongNode *song){
	printf("\nTitle: %20s  |",song->title);
	printf("Artist: %18s  |",song->artist);
	printf("Album: %28s  |",song->album);
	printf("Duration: %8.2f\n",song->duration);

}
/**
 * Display the contents of a list.
 * @param head is the list to display
 */
void printList(SongNode *head){
	SongNode *current = head;
	while(current != NULL){
		printSongInfo(current);
		current=current->next;
	}
	printf("\n");
}
/**
 * Remove a song from the list.
 * @param head is the list to remove from
 * @param remNode is the node to remove
 * @return the removed node
 */
SongNode *removeSong(SongNode **head, SongNode *remNode) {
	SongNode *current = *head,*previous = NULL;
	if(current==NULL){
		printf("Cannot delete empty list\n");
		return NULL;
	}

	if(*head != remNode){
		while (current != NULL)
		{
			if(current==remNode){
				previous->next = current->next;
				current->next=NULL;
				return current;
			}
			previous = current;
			current = current->next;
		}
		return NULL;
	}
	else{
		*head=current->next;
		current->next=NULL;
		return current;
	}

}
/**
 * Comepletely delete a song from the list.
 * @param head the list to delete rom
 * @param delNode is the node to delete
 * @return 0 for successfully deleted else return -1
 */
int deleteSong(SongNode **head, SongNode *delNode){
	SongNode* rem=removeSong(head,delNode);
	if(rem != NULL)
	{
		free(rem);
		return 0;
	}
	else{
		return -1;
	}
}
/**
 * Insert the song tp the end of a list
 * @param head is the list to insert into
 * @param newNode is the node to insert
 */
void appendSong(SongNode **head, SongNode *newNode){
	SongNode *current = *head;
	if(*head==NULL){
		newNode->next=*head;
		*head=newNode;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
		newNode->next = NULL;
	}
}
/**
 * Insert a song into a given position.
 * @param head is the list that will insert the new song into
 * @param newNode is the node that will be insert
 * @param position is where to insert the new node
 * @return 0
 */
int insertSong(SongNode **head, SongNode *newNode, int position){
	int i,size=getListSize(*head);
	if(*head == NULL){
		*head=newNode;
		return 0;
	}
	else if(position == 0){
		newNode ->next=*head;
		*head=newNode;
		return 0;
	}
	else if(position >= size){
		appendSong(head,newNode);
		return 0;
	}
	else {
		SongNode *current = *head;
		for(i=0;i<position-1;i++){
			current=current->next;
		}
		newNode->next=current->next;
		current->next=newNode;
	}
	return 0;
}
/**
 * Get the current size of the list.
 * @param head is the list
 * @return the size of the list
 */
int getListSize(SongNode *head){
	int size=0;
	SongNode *current = head;
	while(current != NULL){
		size++;
		current= current->next;
	}
	return size;
}
/**
 * Insert a song in beginning of the list.
 * @param head is the list to insert into
 * @param newNode is the node in insert
 */
void insertBeginning(SongNode **head, SongNode *newNode){
	if(*head == NULL){
		*head=newNode;
	}
	else{
		newNode->next=*head;
		*head=newNode;
	}

}
/**
 * Search for a song based on the title of the song.
 * @param head is the list to search for
 * @param search is the name of the song to search for
 * @return the song if found else return null
 */
SongNode *searchByTitle(SongNode *head, char *search) {
	SongNode *current = head;
	while(current != NULL){
		if(strcmp(current->title,search)==0){
			return current;
		}
		current=current->next;
	}
	return NULL;
}
/**
 *Control the flow of searching for a song option.
 * @param musicLibraryHead is the library
 */
void searchSongTitleControl(SongNode **musicLibraryHead){
	char title[35];
	SongNode *titleNode;
	getTitleSong(title);
	titleNode=searchByTitle(*musicLibraryHead,title);
	if(titleNode!=NULL){
		printSongInfo(titleNode);}
	else{
		printf("Cannot find the song \"%s\" \n",title);
	}
}
/**
 * Calculate the total duration of all the songs
 * @param head is the list that will be calculate
 * @return the total duration
 */
double computeDuration(SongNode *head){
	double sumDurations=0;
	SongNode *current = head;
	while(current != NULL){
		sumDurations+=current->duration;
		current=current->next;
	}
	return sumDurations;
}
/**
 * Check to see if the node is contain in the list.
 * @param musicLibraryHead is the list to search for
 * @param nodeToAdd is the node to search for
 * @return 0 if found else return -1
 */
int contain(SongNode *musicLibraryHead,SongNode *nodeToAdd){
	SongNode *current = musicLibraryHead;
	while(current != NULL){
		if(current == nodeToAdd){
			return 0;
		}
		current = current->next;
	}
	return -1;

}
/**
 * Remove everything from the list.
 * @param head is the list to remove from
 */
void deleteSongList(SongNode **head){
	SongNode *current=*head, *temp=NULL;
	while(current !=NULL){
		temp=current->next;
		deleteSong(head,current);
		current=temp;
	}
	*head=NULL;
}
/**-------------------------------------------------Controls-------------------------------------------*/
/**
 * Control the flow of playlist menu
 * @param musicLibraryHead is the library
 * @param headPlayList  is the playlist
 */
void playListMenuControl(SongNode **musicLibraryHead,SongNode **headPlayList){
	int  userChoice=0,valid=0;
	double duration=0;
	do{
		playListMenuPrompt();
		userChoice=getUseChoice();
		switch(userChoice){
			case 1:
				printf("Print playlist");
				printList(*headPlayList);
				break;
			case 2:
				duration=computeDuration(*headPlayList);
				printf("Durations : %.2f",duration);
				break;
			case 3:
				searchSongTitleControl(headPlayList);
				break;
			case 4:
				moveSongUp(headPlayList);
				break;
			case 5:
				moveSongDown(headPlayList);
				break;
			case 6:
				removeSongFromList(musicLibraryHead,headPlayList);
				break;
			case 7:
				printf("Choice 7:\n");
				musicLibraryControl(musicLibraryHead,headPlayList);
				break;
			case 8:
				printf("Quit:\n");
				deleteSongList(musicLibraryHead);
				deleteSongList(headPlayList);
				valid=1;
			default:
				printf("Please Enter a valid input\n");
		}
	}
	while(valid==0);
}

/**
 * Control the flow of music library menu.
 * @param musicLibraryHead is the library
 * @param playListHead  is the playlist
 */
void musicLibraryControl(SongNode **musicLibraryHead,SongNode **playListHead){
	int  userChoice=0,valid=0;
	do{
		libraryMenuPrompt();
		userChoice=getUseChoice();
		switch(userChoice){
			case 1:
				printf("View All Songs:\n");
				printList(*musicLibraryHead);
				break;
			case 2:
				printf("Search by title\n");
				searchSongTitleControl(musicLibraryHead);
				break;
			case 3:
				printf("Add Song To Playlist\n");
				addSongToPlaylistControl(musicLibraryHead,playListHead);
				break;
			case 4:
				printf("Back to Playlist\n");
				valid =1;
				break;
			default:
				printf("Please Enter a valid input\n");
		}
	}while(valid==0);

}

/**
 * Control the flow of adding a song from library to playlist
 * @param playListHead is the playlist
 * @param musicLibraryHead is the library
 */
void addSongToPlaylistControl(SongNode **musicLibraryHead,SongNode **playListHead){
	char title[35];
	SongNode *nodeToAdd;
	getTitleSong(title);
	nodeToAdd=searchByTitle(*musicLibraryHead,title);
	if (contain(*musicLibraryHead, nodeToAdd) == 0) {
		addSongMenuControl(nodeToAdd, playListHead, musicLibraryHead);
	}
	else{
		printf("\nCannot find the song \"%s\" from library to add to play list\n",title);
	}

}
/**
 * Menu control for the add song function.
 * @param nodeToAdd is the node what will be added in
 * @param playListHead is the playlist
 * @param musicLibraryHead is the library
 */
void addSongMenuControl(SongNode *nodeToAdd,SongNode **playListHead,SongNode **musicLibraryHead){
	int  userChoice=0,valid=0,position=0;
	do{
		addSongMenuPrompt();
		userChoice=getUseChoice();
		switch(userChoice){
			case 1:
				removeSong(musicLibraryHead,nodeToAdd);
				appendSong(playListHead,nodeToAdd);
				printf("Song added to the end of the playlist:\n");
				valid=1;
				break;
			case 2:
				removeSong(musicLibraryHead,nodeToAdd);
				insertBeginning(playListHead,nodeToAdd);
				printf("Song is added to beginning of the playlist: \n");
				valid=1;
				break;
			case 3:
				position = getPosition();
				removeSong(musicLibraryHead,nodeToAdd);
				insertSong(playListHead,nodeToAdd,position);
				printf("Song is added in to the playlist\n");
				valid=1;
				break;
			default:
				printf("Please Enter a valid input\n");
		}
	}while(valid==0);
}
/**
 * Get the position of a node.
 * @param head is the list where to search for
 * @param search is the name of the node to search for
 * @return the position
 */
int getNodePosition(SongNode *head, char *search){
	SongNode *current = head;
	int position=0;
	while(current != NULL){
		if(strcmp(current->title,search)==0 ){
			return position;
		}
		position++;
		current = current->next;
	}
	return -1;

}
/**
 * Move a song up 1 position.
 * @param headPlayList is the list where the song is located in
 */
void moveSongUp(SongNode **headPlayList){
	char title[35];
	int position;
	SongNode *temp;
	getTitleSong(title);
	position=getNodePosition(*headPlayList,title)-1;
	temp=searchByTitle(*headPlayList,title);
	if(contain(*headPlayList,temp)==0){
		if(position<0){
			printf("\nThe song \"%s\" is already at the top of the playlist \n",title);
		}else{
			removeSong(headPlayList,temp);
			insertSong(headPlayList,temp,position);
			 printf("Successfully moved the song up \n");
		}
	}else{
		printf("Cannot find the song \"%s\" to remove",title);
	}
}
/**
 * Move a song down 1 position.
 * @param headPlayList is the list where the song is located in
 */
void moveSongDown(SongNode **headPlayList){
	char title[35];
	int position;
	SongNode *temp;
	getTitleSong(title);
	temp=searchByTitle(*headPlayList,title);
	position=getNodePosition(*headPlayList,title)+1;
	if(contain(*headPlayList,temp)==0){
		removeSong(headPlayList,temp);
		insertSong(headPlayList,temp,position);
		printf("Successfully moved the song down \n");
	}
	else{
		printf("Cannot find the song \"%s\" to remove",title);
	}

}
/**
 * Remove the Song from playing.
 * @param musicLibraryHead is the head of music library list that the removed node will be added to.
 * @param headList is the list where the song will be remove from
 */
void removeSongFromList(SongNode **musicLibraryHead,SongNode **headList) {
	char title[35];
	SongNode *temp;
	getTitleSong(title);
	temp = searchByTitle(*headList, title);
	if (contain(*headList, temp) == 0) {
		printf("The song  \"%s\" is removed from playlist",title);
		addAlphabeticalOrder(musicLibraryHead,removeSong(headList,temp));
	}else{
		printf("Cannot find the song \"%s\" to remove",title);
	}
}




