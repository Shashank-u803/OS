#include<stdio.h>
#include<stdbool.h>

int main(){
	int n, r;
	printf("Enter no. of processes: ");
	scanf("%d", &n);
	printf("Enter no. of resources: ");
	scanf("%d", &r);

	int alloc[n][r], req[n][r], avail[r];

	printf("Enter Allocation Matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<r;j++){
			printf("alloc[%d][%d]: ", i, j);
			scanf("%d", &alloc[i][j]);
		}
	}

	printf("Enter Request Matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<r;j++){
			printf("req[%d][%d]: ", i, j);
			scanf("%d", &req[i][j]);
		}
	}

	printf("Enter Available Resources:\n");
	for(int i=0;i<r;i++){
		printf("avail[%d]: ", i);
		scanf("%d", &avail[i]);
	}

	bool finish[n];
	for(int i=0;i<n;i++) finish[i] = false;

	int deadlocked[n], count=0;

	for(int k=0;k<n;k++){
		bool allocated = false;
		for(int i=0;i<n;i++){
			if(!finish[i]){
				bool can_allocate = true;
				for(int j=0;j<r;j++){
					if(req[i][j] > avail[j]){
						can_allocate = false;
						break;
					}
				}
				if(can_allocate){
					for(int j=0;j<r;j++){
						avail[j] += alloc[i][j];
					}
					finish[i] = true;
					allocated = true;
				}
			}
		}
		if(!allocated) break;
	}

	printf("Deadlocked processes: ");
	bool deadlock = false;
	for(int i=0;i<n;i++){
		if(!finish[i]){
			printf("P%d ", i);
			deadlock = true;
		}
	}
	if(!deadlock) printf("None");
	printf("\n");
	return 0;
}
