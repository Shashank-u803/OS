#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int state[5]; // 0: Thinking, 1: Hungry, 2: Eating
int fork[5] = {1,1,1,1,1}; // 1 means fork available

void take_forks(int p){
	if(fork[p] && fork[(p+1)%5]){
		fork[p] = fork[(p+1)%5] = 0;
		state[p] = 2;
		printf("Philosopher %d is Eating\n", p);
	}else{
		printf("Philosopher %d is Hungry but forks not available\n", p);
		state[p] = 1;
	}
}

void put_forks(int p){
	if(state[p] == 2){
		fork[p] = fork[(p+1)%5] = 1;
		state[p] = 0;
		printf("Philosopher %d puts down forks and starts Thinking\n", p);
	}else{
		printf("Philosopher %d was not Eating\n", p);
	}
}

int main(){
	int choice, p;
	while(1){
		printf("\n1. Eat\n2. Put Forks\n3. Exit\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				printf("Enter philosopher number (0–4): ");
				scanf("%d", &p);
				if(p>=0 && p<5) take_forks(p);
				else printf("Invalid philosopher\n");
				break;
			case 2:
				printf("Enter philosopher number (0–4): ");
				scanf("%d", &p);
				if(p>=0 && p<5) put_forks(p);
				else printf("Invalid philosopher\n");
				break;
			case 3: exit(0);
			default: printf("Invalid choice\n");
		}
	}
	return 0;
}
