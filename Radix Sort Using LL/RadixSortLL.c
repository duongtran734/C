/*
 * Steve Tran G01187141
 * CS262, Lab Section 212
 * Project 3
 */


#include <stdio.h>
#include <stdlib.h>

#define bucketSize 10

typedef struct Node {
	int data;
	struct Node *next;
} ListNode;


/**Prototypes*/
void generateUnsortedList(int N, int lowVal, int highVal, ListNode **listHead,ListNode **listTail);
void printList(ListNode *head);
int length(ListNode *head);
ListNode *newList(void);
ListNode *newNode(int value);
ListNode *insertNode(ListNode **head,ListNode **tail, ListNode *node);
ListNode *removeFirst(ListNode **head);
ListNode *removeNode(ListNode **head, ListNode **tail);

void bucketsInitializer(ListNode **bucketHead);
void printBuckets(ListNode **bucketHead);
void insertBackToList(ListNode **listHead,ListNode **listTail, ListNode **bucketHead);


int getMSD(ListNode *head);
int getLargestNum(ListNode *head);
int getValueDigit(ListNode *node, int pos);
void radixSort(ListNode **listHead, ListNode **listTail);
void deleteList(ListNode **head,ListNode **tail);
void deleteBucketLists(ListNode **bucketHead,ListNode **bucketTail);


/**
 * Main fuction
 */
int main(int argc, char *argv[]){
	int S,N,lowVal,highVal;
	ListNode *listHead = newList(),*listTail = NULL;

	S = atoi(argv[1]);
	N = atoi(argv[2]);
	lowVal = atoi(argv[3]);
	highVal = atoi(argv[4]);
	srand(S);
	
	if(highVal < lowVal){
	printf("cannot generate the list because highVal < lowVal\n");
	exit(0);
	}
	generateUnsortedList(N,lowVal,highVal,&listHead,&listTail);

	printf("\n\nUnsorted List: ");
	printList(listHead);
	
	radixSort(&listHead,&listTail);
	printf("\n\nSorted List: ");
	printList(listHead);


	deleteList(&listHead,&listTail);
	
	return 0;
}



/*
 * Creating the unsorted list from user inputs.
 */
void generateUnsortedList(int N, int lowVal, int highVal, ListNode **listHead,ListNode **listTail){
	int i,range,x;
	ListNode *node;
	range= highVal - lowVal + 1;

	for(i = 0 ; i < N ; i++){
		x = rand() % range + lowVal;
		node = newNode(x);
		insertNode(listHead,listTail,node);
	}


}


/**
 * Displaying the element in the list.
 */
void printList(ListNode *head) {
	ListNode *current = head;
	while (current != NULL) {
		if(current->next == NULL){
			printf("%d", current->data);
		}else{
			printf("%d -> ", current->data);
		}
	current = current->next;
	}
	printf("\n");
}

/*
 * Gettung the length of a list.
 */
int length(ListNode *head) {
	ListNode *current = head;
	int result = 0;
	while (current != NULL) {
		result = result + 1;
		current = current->next;
	}
	return result;
}

/*
 * Function to make a new list.
 */
ListNode *newList(void) {
	ListNode *head = NULL;
	return head;
}
/*
 * Function to create a node.
 */
ListNode *newNode(int value) {
	struct Node *node = malloc(sizeof(ListNode));
	if(node == NULL){
	printf("Error allocating memory for node\n");
	exit(0);
	}
	node->data = value;
	node->next = NULL;
	return node;
}



/**
 *Function to insert a node at the end of a list.
 */
ListNode *insertNode(ListNode **head, ListNode **tail, ListNode *newNode) {
	if (*head == NULL) {
		*head = *tail = newNode;
	} else {
		(*tail)->next = newNode;
		*tail = newNode;
	}
	return newNode;
}
/*
 * Initialize all the head of the bucket to NULL.
 */
void bucketsInitializer(ListNode **bucketHead) {
	int i;
	for (i = 0; i < bucketSize; i++) {
		bucketHead[i] = NULL;
	}
}

/*
 * Displaing all the element in each bucket.
 */
void printBuckets(ListNode **bucketHead) {
	int i;
	printf("\n");
	for (i = 0; i < bucketSize; i++) {
		ListNode *current = bucketHead[i];
		if (current == NULL) {
			printf("Bucket %d -> NULL\n", i);
		} else {
			printf("Bucket %d ->", i);
			printList(current);
		}
	}
}


/*
 * Function the get the most significant digit from the list.
 */
int getMSD(ListNode *head) {

	int largestNum = getLargestNum(head), digit = 0, i;
	for (i = largestNum; i != 0; i = i / 10) {
		digit++;
	}
	return digit;
}
/*
 * Function to get the largest number in a list.
 */
int getLargestNum(ListNode *head) {
	int largestNum = 0;
	ListNode *current = head;
	while (current != NULL) {
		if (current->data > largestNum) {
			largestNum = current->data;
		}
		current = current->next;
	}
	return largestNum;
}
/*
 * Get the value of the given digit from a number.
 */
int getValueDigit(ListNode *node, int pos) {
	int value = 0, i, k = 1;
	for (i = 0; i < pos; i++) {
		value = (node->data) % (10 * k);
		value = value / k;
		k = k * 10;
	}
	return value;
}
/*
 * Function to insert all the element from each bucket back into the original list.
 */
void insertBackToList(ListNode **listHead,ListNode **listTail, ListNode **bucketHead) {
	int i, size, j;
	for (i = 0; i < bucketSize; i++) {
		ListNode *current = bucketHead[i], *temp = NULL;
		size = length(bucketHead[i]);
		for (j = 0; j < size; j++) {
			temp = removeFirst(&bucketHead[i]);
			insertNode(listHead,listTail, temp);
		}
	}
	printf("\n\nList obtained after stitching the sublists together:\n");
	printList(*listHead);
}

/*
 * Function to remove the first element in the list.
 */
ListNode *removeFirst(ListNode **head) {
	ListNode *temp = *head;
	if (*head == NULL) {
		return NULL;
	} else {
		*head = (*head)->next;
		temp->next = NULL;

	}
	return temp;

}

ListNode *removeNode(ListNode **head,ListNode **tail){

	ListNode *nodeRemoved,*prev=NULL,*current=*head;
	if(*head == *tail) {
		return removeFirst(head);
	}
	while(current->next != NULL){
		prev=current;
		current=current->next;
	}
	nodeRemoved=current;
	prev->next = NULL;
	*tail = prev;
	return nodeRemoved;

}

/*
 * Function for the radix sort.
 */
void radixSort(ListNode **listHead, ListNode **listTail) {
	int N = getMSD(*listHead), pos = 1, x, i, size = length(*listHead);
	ListNode *temp = NULL, *bucketHead[bucketSize],*bucketTail[bucketSize];
	bucketsInitializer(bucketHead);
	bucketsInitializer(bucketTail);
	printf("\n---------------------------------Starting out ---------------------------------");

	printBuckets(bucketHead);
	for (pos = 1; pos <= N; pos++) {
		printf("\n---------------------------------Pass %d---------------------------------", pos);
		for (i = 0; i < size; i++) {
			temp = removeFirst(listHead);
			x = getValueDigit(temp, pos);
			insertNode(&bucketHead[x],&bucketTail[x], temp);
		}
		printBuckets(bucketHead);
		insertBackToList(listHead, listTail , bucketHead);
	}
	deleteBucketLists(bucketHead,bucketTail);
}

/*
 * Function to free all the element in the list.
 */
void deleteList(ListNode **head,ListNode **tail){

	ListNode *current=*head, *temp=NULL;
	int i,n=length(*head);
	for(i=0;i<n;i++){
		temp=removeNode(head,tail);
		free(temp);

	}
	*head=NULL;
	*tail = NULL;

}
/*
 * Function to free all the elment in each bucket list.
 */
void deleteBucketLists(ListNode **bucketHead,ListNode **bucketTail){
	int i; 
	for(i = 0; i< bucketSize; i++){
		deleteList(&bucketHead[i],&bucketTail[i]);
	}
}
