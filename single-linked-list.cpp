#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct PERSON{
	char name[20];
	int age;
	double weight;
	PERSON* next;
};

PERSON* head = NULL;
PERSON* tail = NULL;

// Constructor to create new node
PERSON* generatePerson(char names[], int age, double weight){
	PERSON* newPerson = (PERSON*)malloc(sizeof(PERSON));

	strcpy(newPerson->name,names);
	newPerson->age = age;
	newPerson->weight = weight;
	
	newPerson->next = NULL;
	
	return newPerson;
}

// Push = insert data to link list

// Push head = insert data to the first index of list 
void pushHead(PERSON* Data){
	if(head==NULL){
		head = Data;
		tail = Data;
	} else{
		Data->next = head;
		head = Data;
	}
}

// Push tail = insert data to end index of list
void pushTail(PERSON* Data){
	if(head==NULL){
		head = Data;
		tail = Data;
	} else {
		tail->next = Data;
		tail = Data;
	}
}

// Push Mid = insert data into list ordered by a filter
void pushMid(PERSON* Data){
	if(head==NULL){
		pushHead(Data);
	} else if(strcmp(Data->name,head->name)>0){
		pushHead(Data);
	} else if(strcmp(Data->name,tail->name)<0){
		pushTail(Data); 
	} else{
		PERSON* cursor = head;
		while(cursor!=NULL){
			if(strcmp(Data->name,cursor->next->name)>0){
				PERSON* curr = cursor->next;
				cursor->next = curr->next;
				free(curr);
			}
		}
	}
}


// Pop = delete data from Linked List

// Pop Head = delete first entered data
void popHead(){
	if(head==NULL){
		printf("No Data!");
	} else if(head==tail){
		free(head);
		head = NULL;
		tail = NULL;	
	} else{
		PERSON* cursor = head;
		head = head->next;
		free(cursor);
	}
}

// Pop Tail delete latest data inserted
void popTail(){
	if(head==NULL){
		printf("No Data!");
	} else if(head==tail){
		free(head);
		head = NULL;
		tail = NULL;	
	} else{
		PERSON* cursor = head;
		while(cursor->next!=tail){
			cursor = cursor->next;
		}
		PERSON* temp = tail;
		tail = cursor;
		tail->next = NULL;
		free(temp);
	}
}

// Pop Mid = delete selected data
void popMid(char *str){
	if(head==NULL){
		printf("No Data Stored!");
	} else if(strcmp(head->name,str)==0){
		popHead();
	} else if(strcmp(tail->name,str)==0){
		popTail();
	} else{
		PERSON* cursor = head;
		while(cursor->next!=NULL){
			if(strcmp(cursor->next->name,str)==0){
				PERSON* temp = cursor->next;
				cursor->next = temp->next;
				free(temp);
				break;
			}
			cursor = cursor->next;
		}	
	}
}



// Display all data in Single Link List
void viewAll(){
	if(head==NULL){
		printf("No Data!");
	} else{
		PERSON* cursor = head;
		while(cursor!=NULL){
			printf("%s %d %.2lf\n", cursor->name, cursor->age, cursor->weight);
			cursor = cursor->next;
		}
	}
}

int main(){
	PERSON* miku = generatePerson("MIKU",36,51.0);
	PERSON* nino = generatePerson("NINO",14,52.0); 
	PERSON* itsuki = generatePerson("ITSUKI",17,52.2);
	PERSON* yotsuba = generatePerson("YOTSUBA",24,56.3);
	PERSON* ichika = generatePerson("ICHIKA",24,46.9);
//	pushHead(miku);
//	pushTail(nino);
	pushMid(miku);
	pushMid(nino);
	pushMid(itsuki);
	pushMid(ichika);
	viewAll();
	printf("\n=======================================\n");
//	popHead();
	popMid("ITSUKI");
//	popTail();
	viewAll();
	
	return 0;
}
