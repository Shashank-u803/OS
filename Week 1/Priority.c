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
            if(at[j]>at[j+1] || (at[j]==at[j+1] && pid[j]>pid[j+1])){
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

void find_ct_non_premptive(int ct[],int at[],int bt[],int priority[],int n){
    int c=0,completed_count=0,min_priority,min_index;
    bool completed[n];
    for(int i=0;i<n;i++){
        completed[i]=false;
    }
    while(completed_count<n){
        min_priority=__INT_MAX__, min_index=-1;
        for(int i=0;i<n;i++){
            if(!completed[i] && at[i]<=c){
                if(priority[i]<min_priority || (priority[i]==min_priority && at[i]<at[min_index])){
                    min_priority=priority[i];
                    min_index=i;
                }
            }
        }
        if(min_index==-1){
            c++;
            continue;
        }
        c+=bt[min_index];
        ct[min_index]=c;
        completed[min_index]=true;
        completed_count++;
    }
}

void find_ct_premptive(int ct[],int at[],int bt[],int priority[],int n){
    int c=0,completed_count=0,min_priority,min_index;
    bool completed[n];
    int rem_bt[n];
    for(int i=0;i<n;i++){
        rem_bt[i]=bt[i];
        completed[i]=false;
    }
    while(completed_count<n){
        min_priority=__INT_MAX__, min_index=-1;
        for(int i=0;i<n;i++){
            if(!completed[i] && at[i]<=c && priority[i]<min_priority){
                min_priority=priority[i];
                min_index=i;
            }
        }
        if(min_index!=-1){
            rem_bt[min_index]--;

            if(rem_bt[min_index]==0){
                completed_count++;
                completed[min_index]=true;
                ct[min_index]=c+1;
            }
        }
        c++;
    }
}



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
    int at[n],bt[n],tat[n],ct[n],wt[n],pid[n],prior[n];
    for(int i=0;i<n;i++){
        printf("Enter details for process %d (PID,AT,BT,Priority):\n",i+1);
        scanf("%d%d%d%d",&pid[i],&at[i],&bt[i],&prior[i]);
    }
    sort(pid,at,bt,n);
    find_ct_non_premptive(ct,at,bt,prior,n);
    find_tat(ct,at,tat,n);
    find_wt(wt,tat,bt,n);
    printf("Priority scheduling:(Non-premptive)\n");
    printf("PID\tAT\tBT\tPRN\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],prior[i],ct[i],tat[i],wt[i]);
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
    printf("-----------------------------------------------------------------\n");
    find_ct_premptive(ct,at,bt,prior,n);
    find_tat(ct,at,tat,n);
    find_wt(wt,tat,bt,n);
    printf("Priotity scheduling:(Premptive)\n");
    printf("PID\tAT\tBT\tPRN\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],prior[i],ct[i],tat[i],wt[i]);
    }
    ttat=0,twt=0;
    for(int i=0;i<n;i++){
        ttat+=tat[i];
        twt+=wt[i];
    }
    avg_tat=ttat/(double)n;
    avg_wt=twt/(double)n;
    printf("Average Turn-around time:%lf\n",avg_tat);
    printf("Average Waiting time:%lf\n",avg_wt);

    return 0;
}
