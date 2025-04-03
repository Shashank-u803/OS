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


/*Non-preemptive algo is basically:
1)Sort by AT,(PID if ATs are same)
2)Do these steps until all processes are completed:
    ~ Scan through the process to find out which aren't  completed and which have arrived 
     ~ among them find the process having least burst time (store its index,min_bt)
     ~ if any such process is found at that point of time, add the CT till now, store CT,mark it true,increment the counter of completed process
     ~ if not found just increment completion time by 1 and move to next second iteration
*/

void find_ct_non_premptive(int ct[],int at[],int bt[],int n){
    int c=0,completed_count=0,BT,min_index;
    bool completed[n];
    for(int i=0;i<n;i++){
        completed[i]=false;
    }
    while(completed_count<n){
        BT=__INT_MAX__, min_index=-1;
        for(int i=0;i<n;i++){
            if(!completed[i] && at[i]<=c && bt[i]<BT){
                BT=bt[i];
                min_index=i;
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

void find_ct_premptive(int ct[],int at[],int bt[],int n){
    int c=0,completed_count=0,min_bt,min_index;
    bool completed[n];
    int rem_bt[n];
    for(int i=0;i<n;i++){
        rem_bt[i]=bt[i];
        completed[i]=false;
    }
    while(completed_count<n){
        min_bt=__INT_MAX__, min_index=-1;
        for(int i=0;i<n;i++){
            if(!completed[i] && at[i]<=c && rem_bt[i]<min_bt){
                min_bt=rem_bt[i];
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
    int at[n],bt[n],tat[n],ct[n],wt[n],pid[n];
    for(int i=0;i<n;i++){
        printf("Enter details for process %d (PID,AT,BT):\n",i+1);
        scanf("%d%d%d",&pid[i],&at[i],&bt[i]);
    }
    sort(pid,at,bt,n);
    find_ct_non_premptive(ct,at,bt,n);
    find_tat(ct,at,tat,n);
    find_wt(wt,tat,bt,n);
    printf("SJF scheduling:(Non-premptive)\n");
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
    printf("-----------------------------------------------------------------\n");
    find_ct_premptive(ct,at,bt,n);
    find_tat(ct,at,tat,n);
    find_wt(wt,tat,bt,n);
    printf("SJF scheduling:(Premptive)\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],ct[i],tat[i],wt[i]);
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
