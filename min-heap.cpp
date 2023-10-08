#include<stdio.h>

// Min heap = all child below the parent is bigger than the parent

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
		if(heap[pos] < heap[parent(pos)]){
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

int getMin(){
	return heap[1];
}

int leftChild(int pos){
	return pos*2;
}

int rightChild(int pos){
	return pos*2+1;
}

void minHeapify(int pos){
	if(!(pos>=size/2 && pos<=size)){
		int leftChildVal = heap[leftChild(pos)];
		int rightChildVal = heap[rightChild(pos)];
		
		
		if(leftChildVal < heap[pos] || rightChildVal < heap[pos]){
			if(leftChildVal < heap[pos]){
				swap(pos,leftChild(pos));
				minHeapify(leftChild(pos));
			} else{
				swap(pos,rightChild(pos));
				minHeapify(rightChild(pos));
			}
		}
		
	}
}

int extractMin(){
	int min = heap[1];
	
	heap[1] = heap[size];
	size--;
	
	minHeapify(1);
	return min;
}

int main(){
	insert(15);
	insert(7);
	insert(4);
	insert(3);
	insert(12);
	print();
	printf("Minimum : %d\n", getMin());
	puts("After Extract: ");
	printf("Min value = %d\n", extractMin());
	print();
	
	return 0;
}
