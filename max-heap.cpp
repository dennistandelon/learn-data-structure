#include<stdio.h>

// Max heap = All node below parent always being smaller than the parent

int heap[100];
int size = 0;

int parent(int pos){
	return pos/2;
}

void swap(int a, int b){
	int temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

void insert(int key){
	size += 1;
	heap[size] = key;
	
	int pos = size;
	while(pos!=1){
		if(heap[pos] > heap[parent(pos)]){
			swap(pos,parent(pos));
		}
		pos=parent(pos);
	}
	
}

void print(){
	for(int i = 1; i <= size; i++){
		printf("%d\n", heap[i]);
	}
}

int getMax(){
	return heap[1];
}

int leftChild(int pos){
	return pos*2;
}

int rightChild(int pos){
	return pos*2+1;
}

void maxHeapify(int pos){
	if(!(pos>=size/2 && pos<=size)){
		int leftChildVal = heap[leftChild(pos)];
		int rightChildVal = heap[rightChild(pos)];
		
		
		if(leftChildVal > heap[pos] || rightChildVal > heap[pos]){
			if(leftChildVal > heap[pos]){
				swap(pos,leftChild(pos));
				maxHeapify(leftChild(pos));
			} else{
				swap(pos,rightChild(pos));
				maxHeapify(rightChild(pos));
			}
		}
		
	}
}

int extractMax(){
	int max = heap[1];
	
	heap[1] = heap[size];
	size--;
	
	maxHeapify(1);
	return max;
}

int main(){
	insert(5);
	insert(7);
	insert(8);
	insert(3);
	insert(12);
	print();
	printf("Maximum : %d\n", getMax());
	puts("After Extract: ");
	printf("Max value = %d\n", extractMax());
	print();
	
	return 0;
}
