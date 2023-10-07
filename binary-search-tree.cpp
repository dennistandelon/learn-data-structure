#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NODE{
	int key;
	char name[100];
	
	NODE* left;
	NODE* right;
}*root;


NODE* createNode(int _key, char _name[]){
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	strcpy(newNode->name,_name);
	newNode->key = _key;
	
	newNode->left = newNode->right = NULL;
	return newNode;
}


NODE* insertNode(NODE* curr, int key, char name[]){
	if(curr==NULL){
		return createNode(key,name);
	} else if(key < curr->key){
		curr->left = insertNode(curr->left,key,name);
	} else{
		curr->right = insertNode(curr->right,key,name);
	}
}

void preOrder(NODE* curr){
	// Traverse from parent -> left -> right
	if(curr!=NULL){
		printf("Key : %d  Name: %s\n", curr->key, curr->name);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(NODE* curr){
	// Traverse from left -> parent -> right
	if(curr!=NULL){
		inOrder(curr->left);
		printf("Key : %d  Name: %s\n", curr->key, curr->name);
		inOrder(curr->right);
	}
}

void postOrder(NODE* curr){
	// Traverse from left -> right -> parent
	if(curr!=NULL){
		postOrder(curr->left);
		postOrder(curr->right);
		printf("Key : %d  Name: %s\n", curr->key, curr->name);
	}
}

NODE* deleteAll(NODE* curr){
	if(curr!=NULL){
		curr->left = deleteAll(curr->left);
		curr->right = deleteAll(curr->right);
		free(curr);
		curr = NULL;
	}
	return curr;
}

NODE* searchByKey(NODE* curr, int key){
	if(curr==NULL){
		return curr;
	} else if(key < curr->key){
		return searchByKey(curr->left,key);
	} else if(key > curr->key){
		return searchByKey(curr->right,key);
	} else{
		return curr;
	}
}


NODE* deleteNode(NODE* curr, int deleteKey){
	if(curr==NULL){
		return curr;
	} else if(deleteKey < curr->key){
		curr->left = deleteNode(curr->left,deleteKey);
	} else if(deleteKey > curr->key){
		curr->right = deleteNode(curr->right,deleteKey);
	} else{
		if(curr->left==NULL && curr->right==NULL){
			free(curr);
			curr = NULL;
		} else if(curr->right==NULL){
			NODE* temp = curr;
			curr = curr->left;
			free(temp);
			temp = NULL;
		} else if(curr->left==NULL){
			NODE* temp = curr;
			curr = curr->right;
			free(temp);
			temp = NULL;
		} else{
			// predesuccessor = get highest value from left subset tree
			NODE* temp = curr->left;
			while(temp->right!=NULL){
				temp = temp->right;
			}
			curr->key = temp->key;
			strcpy(curr->name,temp->name);
			curr->left = deleteNode(curr->left,temp->key);
			
			// sucessesor = get lowest value from right subset tree
//			NODE* temp = curr->right;
//			while(temp->left!=NULL){
//				temp = temp->left;
//			}
//			curr->key = temp->key;
//			strcpy(curr->name,temp->name);
//			curr->right = deleteNode(curr->right,temp->key);
		}
		return curr;
	}
}

void Update(NODE* curr, int key, int newKey, char newName[]){
	NODE* search = searchByKey(curr,key);
	if(search!=NULL){
		deleteNode(curr,key);
		curr = insertNode(curr,newKey,newName);
		return;
	}
	printf("Key not Found!\n");
}

int main(){
	
	root = insertNode(root,8,"Aishia");
	root = insertNode(root,3,"Haruto");
	root = insertNode(root,15,"Liselotte");
	root = insertNode(root,1,"Miharu");
	root = insertNode(root,6,"Celia");
	root = insertNode(root,9,"Rio");
	root = insertNode(root,19,"Christina");
	root = insertNode(root,2,"Flora");
	root = insertNode(root,17,"Naruto");
	
	// Traversal
	puts("preorder");
	preOrder(root);
	puts("inorder");
	inOrder(root);
	puts("postorder");
	postOrder(root);
	
//	puts("Before Delete");
//	preOrder(root);
//
//	root = deleteNode(root,8);
//	
//	puts("After Delete");
//	preOrder(root);
	
	NODE* search = searchByKey(root,9);
	if(search==NULL){
		puts("Not Found");
	} else{
		puts("Found");
		printf("(%d) %s\n", search->key, search->name);
	}

//	puts("Before Update");
//	preOrder(root);
//	
//	Update(root,19,90,"Shido");
//	
//	puts("After Update");
//	preOrder(root);

//	puts("Before Delete All:");
//	preOrder(root);
//	
	root = deleteAll(root);
	
	puts("After Delete All:");
	preOrder(root);		
	
	
	return 0;
}
