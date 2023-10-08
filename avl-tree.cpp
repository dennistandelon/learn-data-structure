#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// AVL: Adelson-Velsky-Landis 

struct PERSON{
	char name[32];
	int age;
	
	int height;
	
	PERSON* left;
	PERSON* right;
}*root;


PERSON* createPerson(char _name[], int _age){
	PERSON* newPerson = (PERSON*)malloc(sizeof(PERSON));
	
	strcpy(newPerson->name,_name);
	newPerson->age = _age;
	newPerson->height = 1;
	
	newPerson->left = newPerson->right = NULL;
	
	return newPerson;	
}

int getHeight(PERSON* person){
	if(person==NULL){
		return 0;
	}
	return person->height;
}

int getBalance(PERSON* person){
	int leftHeight = getHeight(person->left);
	int rightHeight = getHeight(person->right);
	
	return leftHeight - rightHeight;
}

int max(int a, int b){
	if(a>b)return a;
	return b;
}

void updateHeight(PERSON* person){
	int leftHeight = getHeight(person->left);
	int rightHeight = getHeight(person->right);
	
	person->height = max(leftHeight,rightHeight) + 1;
}

// clock-wise rotation
PERSON* cw(PERSON* subroot){
	PERSON* newSubroot = subroot->left;
	PERSON* child = newSubroot->right;
	
	subroot->left = child;
	newSubroot->right = subroot;
	
	updateHeight(subroot);
	return newSubroot;
}

// counter clock-wise rotation
PERSON* ccw(PERSON* subroot){
	PERSON* newSubroot = subroot->right;
	PERSON* child = newSubroot->left;
	
	subroot->right = child;
	newSubroot->left = subroot;
	
	updateHeight(subroot);
	return newSubroot;
}

// avl
PERSON* avl(PERSON* person){
	if(person!=NULL){
		int balance = getBalance(person);	
		if(balance > 1){ // left imbalance
			balance = getBalance(person->left);
			if(balance<0){
				person->left = ccw(person->left);
			}
			person = cw(person);
		} else if(balance<-1){ // right Imbalance
			balance = getBalance(person->right);
			if(balance>0){
				person->right = cw(person->right);
			}
			person = ccw(person);
		}
		updateHeight(person);
	}
	return person;
}


PERSON* push(PERSON* cursor, PERSON* newPerson){
	if(cursor==NULL){
		cursor =  newPerson;	
	} else if(newPerson->age < cursor->age){
		cursor->left = push(cursor->left,newPerson);
	} else{
		cursor->right = push(cursor->right,newPerson);		
	}
	return avl(cursor);
}

PERSON* pop(PERSON* cursor, int _age){
	if(cursor!=NULL){
		if(_age < cursor->age){
			cursor->left = pop(cursor->left,_age);
		} else if(_age > cursor->age){
			cursor->right = pop(cursor->right,_age);			
		} else{
			if(cursor->left==NULL){
				PERSON* deleted = cursor;
				cursor = cursor->right;
				free(deleted);
			} else if(cursor->right==NULL){
				PERSON* deleted = cursor;
				cursor = cursor->left;
				free(deleted);
			} else{
				PERSON* pred = cursor->left;
				while(pred->right!=NULL){
					pred = pred->right;
				}
				strcpy(cursor->name,pred->name);
				cursor->age = pred->age;
				
				pop(cursor->left,pred->age);
			}
		}
	}
	return avl(cursor);
}

void postOrder(PERSON* cursor){
	if(cursor){
		postOrder(cursor->left);
		postOrder(cursor->right);
		printf("%s [%d] [h:%d]\n", cursor->name, cursor->age,cursor->height);
	}
}

int main(){
	
	root = push(root,createPerson("Aishia",28));
	root = push(root,createPerson("Rio",16));
	root = push(root,createPerson("Celia",21));
	root = push(root,createPerson("Latifa",30));
	root = push(root,createPerson("Christina",43));
	root = push(root,createPerson("Flora",49));
	
//	pop(root,18);
	postOrder(root);
	
	return 0;
}
