/* Write a C program to simulate: 
a) Bankers’ algorithm for the purpose of deadlock
avoidance.
b) Deadlock Detection
*/
#include<stdio.h>
#include<stdbool.h>

int main(){
	int n, r;
	printf("Enter no. of processes: ");
	scanf("%d", &n);
	printf("Enter no. of resources: ");
	scanf("%d", &r);

	int alloc[n][r], max[n][r], need[n][r], avail[r];

	printf("Enter Allocation Matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<r;j++){
			printf("alloc[%d][%d]: ",i,j);
			scanf("%d", &alloc[i][j]);
		}
	}

	printf("Enter Max Matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<r;j++){
			printf("max[%d][%d]: ",i,j);
			scanf("%d", &max[i][j]);
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	printf("Enter Available Resources:\n");
	for(int i=0;i<r;i++){
		printf("avail[%d]: ", i);
		scanf("%d", &avail[i]);
	}

	bool finish[n];
	for(int i=0;i<n;i++) finish[i]=false;

	int safe[n], count=0;

	while(count < n){
		bool found = false;
		for(int i=0;i<n;i++){
			if(!finish[i]){
				bool can_allocate = true;
				for(int j=0;j<r;j++){
					if(need[i][j] > avail[j]){
						can_allocate = false;
						break;
					}
				}
				if(can_allocate){
					for(int j=0;j<r;j++){
						avail[j] += alloc[i][j];
					}
					safe[count++] = i;
					finish[i] = true;
					found = true;
				}
			}
		}
		if(!found){
			printf("System is not in a safe state\n");
			return 1;
		}
	}

	printf("System is in a safe state.\nSafe sequence: ");
	for(int i=0;i<n;i++){
		printf("P%d ", safe[i]);
	}
	printf("\n");
	return 0;
}
