#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct PERSON{
	char name[30];
	int age;
	
	PERSON* next;
	PERSON* prev;
}*head[100],*tail[100];  // array of heads and tails

int HASH_SIZE = 100;

PERSON* createPerson(char _name[], int _age){
	PERSON* newPerson = (PERSON*)malloc(sizeof(PERSON));
	
	strcpy(newPerson->name,_name);
	newPerson->age = _age;
	
	newPerson->next = NULL;
	newPerson->prev = NULL;
	
	return newPerson;
}

// To get the index for hash data
// Hash Function depend on the programmer,
// Programmer may use other algorithm for hashing
int hashFunction(char _name[]){
	int total = 0;
	int len = strlen(_name);
	for(int i=0; i < len; i++){
		total = total + (_name[i]-'A');
	}
	
	return total % HASH_SIZE;
}

void pushTail(PERSON* newPerson){
	int index = hashFunction(newPerson->name);
	if(head[index]==NULL){
		head[index] = newPerson;
		tail[index] = newPerson;
	} else{
		tail[index]->next = newPerson;
		newPerson->prev = tail[index];
		tail[index] = newPerson;
	}
}


PERSON* search(char _name[]){
	int index = hashFunction(_name);
	PERSON* cursor = head[index];
	while(cursor!=NULL && strcmp(cursor->name,_name)!=0){
		cursor = cursor->next;
	}
	
	return cursor;
}

void popHead(int index){
	if(head[index]==NULL){
		printf("No Data!\n");
	} else if( head[index] == tail[index]){
		free(head[index]);
		head[index] = NULL;
		tail[index] = NULL;
	} else{
		head[index] = head[index]->next;
		free(head[index]->prev);
		head[index]->prev = NULL;
	}
}

void popTail(int index){
	if(head[index]==NULL || head[index]==tail[index]){
		popHead(index);
	} else{
		tail[index] = tail[index]->prev;
		free(tail[index]->next);
		tail[index]->next = NULL;
	}
}

void popMidbyName(char _name[]){
	PERSON* personToDelete = search(_name);
	int index = hashFunction(_name);
	if(personToDelete == NULL){
		printf("[!] Not Found\n");
	} else if(personToDelete == head[index]){
		popHead(index);
	} else if(personToDelete == tail[index]){
		popTail(index);
	}else{
		personToDelete->next->prev = personToDelete->prev;
		personToDelete->prev->next = personToDelete->next;
		free(personToDelete);
	}
}

void printAll(){
	for(int i=0; i<HASH_SIZE; i++){
		PERSON* cursor = head[i];
		while(cursor!=NULL){
			printf("[%d] %s (%d)\n", i, cursor->name, cursor->age);
			cursor = cursor->next;
		}
	}
}


int main(){

	pushTail(createPerson("Rio",12));
	pushTail(createPerson("Celia",17));
	pushTail(createPerson("Christina",13));
	pushTail(createPerson("Flora",11));
//	pushTail(createPerson("Latifa",8));
//	pushTail(createPerson("Latifad",14));
//	pushTail(createPerson("Latifadd",19));	
//	printAll();

	popMidbyName("Latifad");
	printAll();
	
	PERSON* searchPerson = search("Celia");
	if(searchPerson == NULL){
		printf("[!] Not Found\n");
	} else{
		printf("%s (%d)\n", searchPerson->name, searchPerson->age);		
	}
	
	return 0;
}
