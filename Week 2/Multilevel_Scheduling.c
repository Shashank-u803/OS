#include<stdio.h>
#define MAX_PROCESSES 100

typedef struct Process{
	int pid,at,bt,priority;
}Process;

void FCFS(Process queue[],int n,const char* queue_name){
	int wt=0,tat=0;
	printf("\n%s Queue Execution order: \n",queue_name);
	printf("PID\tAT\tBT\tWT\tTAT\n");
	for(int i=0;i<n;i++){
		if(i==0){
			wt=0;
		}else{
			wt+=queue[i-1].bt;
		}
	  tat = wt + queue[i].bt;
	  printf("%d\t%d\t%d\t%d\t%d\n",queue[i].pid,queue[i].at,queue[i].bt,wt,tat);
	}
}

int main(){
	int n;
	Process processes[MAX_PROCESSES],systemQueue[MAX_PROCESSES],userQueue[MAX_PROCESSES];
	int sysCount=0,userCount=0;
	printf("Enter no.of process:");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		printf("Enter PID,AT,BT,Priority(0=system,1=user):");
		scanf("%d%d%d%d",&processes[i].pid,&processes[i].at,&processes[i].bt,&processes[i].priority);

		if(processes[i].priority==0){
			systemQueue[sysCount++]=processes[i];
		}else{
			userQueue[userCount++]=processes[i];
		}
	}

	if(sysCount>0){
		FCFS(systemQueue,sysCount,"System");
	}
	if(userCount>0){
		FCFS(userQueue,userCount,"User");
	}
	return 0;
}

	
