#include<stdio.h>
#include<stdbool.h>
// i/p  ->pids,bt,at,ct,tat,wt
// sort the arrays based on AT,if they are same then based on  pid
// compute ct,tat,wat
// compute average wt,tat
//print the data

void swap(int* a,int* b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void sort(int pid[],int at[],int bt[],int n){
    bool swapped;
    for(int i=1;i<n;i++){
        swapped=false;
        for(int j=0;j<n-i;j++){
            if(at[j]>at[j+1]){
                swap(&at[j],&at[j+1]);
                swap(&bt[j],&bt[j+1]);
                swap(&pid[j],&pid[j+1]);
                swapped=true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

//CT = BT + AT
void find_ct(int ct[],int at[],int bt[],int n){
    int c=0;
    for(int i=0;i<n;i++){
        if(c>=at[i]){
            c = c + bt[i];
        }else{
            c = c + bt[i] + (at[i] - ct[i-1]);
            // brackets denotes extra time to arrive 
        }
        ct[i]=c;
    }
}

//Turnaround Time measures the entire time spent by
//  a process in the system, including 
// its execution time and the waiting time in the queue.
//TAT = CT - AT
void find_tat(int ct[],int at[],int tat[],int n){
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
    }
}

//WT = TAT - BT
void find_wt(int wt[],int tat[],int bt[],int n){
    for(int i=0;i<n;i++){
        wt[i]=tat[i]-bt[i];
    }
}

int main(){
    int n;
    printf("Enter no. of process:");
    scanf("%d",&n);
    int at[n],bt[n],tat[n],ct[n],wt[n],pid[n];
    for(int i=0;i<n;i++){
        printf("Enter details for process %d (PID,AT,BT):\n",i+1);
        scanf("%d%d%d",&pid[i],&at[i],&bt[i]);
    }
    sort(pid,at,bt,n);
    find_ct(ct,at,bt,n);
    find_tat(ct,at,tat,n);
    find_wt(wt,tat,bt,n);
    printf("FCFS scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    int ttat=0,twt=0;
    for(int i=0;i<n;i++){
        ttat+=tat[i];
        twt+=wt[i];
    }
    double avg_tat=ttat/(double)n;
    double avg_wt=twt/(double)n;
    printf("Average Turn-around time:%lf\n",avg_tat);
    printf("Average Waiting time:%lf\n",avg_wt);
    return 0;
}
