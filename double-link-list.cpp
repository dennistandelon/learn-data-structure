#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NODE{
	char code[10];
	int number;
	
	struct NODE *next;
	struct NODE *prev;
}*head = NULL ,*tail = NULL;

struct NODE* createNewNode(char _code[], int _number){
	struct NODE* newNode = (NODE*)malloc(sizeof(NODE));
	
	strcpy(newNode->code,_code);
	newNode->number = _number;
	
	newNode->next = newNode->prev = NULL;
	return newNode;
}

void pushHead(struct NODE* dataNode){
	if(head==NULL){
		head = tail = dataNode;
	} else{
		dataNode->next = head;
		head->prev = dataNode;
		head = dataNode;
	}
}

void pushTail(struct NODE* dataNode){
	if(head==NULL){
		pushHead(dataNode);
	} else{
		dataNode->prev = tail;
		tail->next = dataNode;
		tail = dataNode;
	}
}

void pushMid(struct NODE* dataNode){
	if(head == NULL){
		pushHead(dataNode);
	} else if(strcmp(head->code,dataNode->code) > 0){
		pushHead(dataNode);
	} else if(strcmp(tail->code,dataNode->code) < 0){
		pushTail(dataNode);
	} else{
		NODE* curr = head;
		while(curr->next != NULL && strcmp(curr->next->code,dataNode->code) < 0){
			curr = curr->next;
		}
		dataNode->next = curr->next;
		dataNode->prev = curr;
		curr->next->prev = dataNode;
		curr->next = dataNode;	
	}
}

void popHead(){
	if(head==NULL){
		printf("[!] No data stored in the Link List\n");
	} else if (head==tail){
		free(head);
		head = tail = NULL;
	} else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

void popTail(){
	if(head==NULL || head==tail){
		popHead();
	} else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}
}

// Pop Mid
void popNodebyCode(char _nodeCode[]){
	if(head==NULL){
		popHead();
	} else{
		struct NODE* curr = head;
		while(curr!=NULL && strcmp(curr->code,_nodeCode)!=0){
			curr = curr->next;
		}
		if(curr == NULL){
			printf("Data Not Found!\n");
		} else if(curr==head){
			popHead();
		} else if(curr==tail){
			popTail();
		} else{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			free(curr);
		}
	}
}

void displayAllData(){
	struct NODE* curr = head;
	while(curr!=NULL){
		printf("( %s , %d )-> ", curr->code, curr->number);
		curr = curr->next;
	}
	printf("\n\n");
}

int main(){
	
//	pushHead(createNewNode("S02",49));
//	pushHead(createNewNode("P10",14));
//	pushHead(createNewNode("D00",14));
//	pushHead(createNewNode("D09",14));
	
	pushMid(createNewNode("S02",49));
	pushMid(createNewNode("P10",14));
	pushMid(createNewNode("D00",14));
	pushMid(createNewNode("D09",14));
	displayAllData();
	
	// Add data to the beginning = push head
	pushHead(createNewNode("N03",20));
	printf("After add new Data in the beginning:\n");
	displayAllData();
	
	// Add data to the end = push tail
	pushTail(createNewNode("B08",30));
	printf("After add new Data in the end:\n");
	displayAllData();
	
	// Remove node at beginning = pop head
	popHead();
	printf("After remove Data in the beginning:\n");
	displayAllData();
	
	// Remove node at end = pop tail
	popTail();
	printf("After remove Data in the end:\n");
	displayAllData();
	
	// Remove node in the middle = pop Mid
	popNodebyCode("P10");
	printf("After remove Data in the middle (remove data by its code):\n");
	displayAllData();
	
	return 0;
}
