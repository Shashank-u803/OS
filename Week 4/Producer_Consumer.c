/*
Write a C program to simulate:
a) Producer-Consumer problem using semaphores.
b) Dining-Philosopher’s problem
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int buffer[5], in = 0, out = 0;
int mutex = 1, full = 0, empty = 5;

int wait(int s){ return --s; }
int signal(int s){ return ++s; }

void producer(){
	if(empty == 0){
		printf("Buffer is Full. Producer waits...\n");
		return;
	}
	if(mutex == 1){
		mutex = wait(mutex);
		full = signal(full);
		empty = wait(empty);
		buffer[in] = rand()%100;
		printf("Produced: %d at %d\n", buffer[in], in);
		in = (in + 1) % 5;
		mutex = signal(mutex);
	}
}

void consumer(){
	if(full == 0){
		printf("Buffer is Empty. Consumer waits...\n");
		return;
	}
	if(mutex == 1){
		mutex = wait(mutex);
		full = wait(full);
		empty = signal(empty);
		printf("Consumed: %d from %d\n", buffer[out], out);
		out = (out + 1) % 5;
		mutex = signal(mutex);
	}
}

int main(){
	int choice;
	while(1){
		printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1: producer(); break;
			case 2: consumer(); break;
			case 3: exit(0);
			default: printf("Invalid choice\n");
		}
	}
	return 0;
}
