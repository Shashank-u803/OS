/* 
Write a C program to simulate Real-Time CPU Scheduling
algorithms: 
a) Rate- Monotonic
b) Earliest-deadline First
c) Proportional scheduling
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int id;
	int execution_time;
	int period; // also deadline
	int remaining_time;
	int deadline;
	int weight; // for proportional scheduling
} Task;

void input_tasks(Task *tasks, int n){
	for(int i=0;i<n;i++){
		printf("Enter Execution time and Period for Task %d: ", i);
		scanf("%d%d", &tasks[i].execution_time, &tasks[i].period);
		tasks[i].id = i;
		tasks[i].remaining_time = tasks[i].execution_time;
		tasks[i].deadline = tasks[i].period;
	}
}

void rate_monotonic(Task *tasks, int n, int time_limit){
	printf("\n--- Rate Monotonic Scheduling ---\n");
	for(int t=0; t<time_limit; t++){
		int min_period = 9999, sel = -1;
		for(int i=0;i<n;i++){
			if(t % tasks[i].period == 0){
				tasks[i].remaining_time = tasks[i].execution_time;
			}
			if(tasks[i].remaining_time > 0 && tasks[i].period < min_period){
				min_period = tasks[i].period;
				sel = i;
			}
		}
		if(sel != -1){
			printf("Time %d: Running Task %d\n", t, sel);
			tasks[sel].remaining_time--;
		}else{
			printf("Time %d: Idle\n", t);
		}
	}
}

void earliest_deadline_first(Task *tasks, int n, int time_limit){
	printf("\n--- Earliest Deadline First ---\n");
	for(int i=0;i<n;i++){
		tasks[i].deadline = tasks[i].period;
	}
	for(int t=0;t<time_limit;t++){
		int min_deadline = 9999, sel = -1;
		for(int i=0;i<n;i++){
			if(t % tasks[i].period == 0){
				tasks[i].remaining_time = tasks[i].execution_time;
				tasks[i].deadline = t + tasks[i].period;
			}
			if(tasks[i].remaining_time > 0 && tasks[i].deadline < min_deadline){
				min_deadline = tasks[i].deadline;
				sel = i;
			}
		}
		if(sel != -1){
			printf("Time %d: Running Task %d\n", t, sel);
			tasks[sel].remaining_time--;
		}else{
			printf("Time %d: Idle\n", t);
		}
	}
}

void proportional_scheduling(Task *tasks, int n, int time_limit){
	printf("\n--- Proportional Scheduling ---\n");
	int total_weight = 0;
	for(int i=0;i<n;i++){
		printf("Enter weight for Task %d: ", i);
		scanf("%d", &tasks[i].weight);
		total_weight += tasks[i].weight;
		tasks[i].remaining_time = 0;
	}
	int allocated[100] = {0};
	for(int t=0;t<time_limit;t++){
		int sel = -1;
		int max_ratio = -1;
		for(int i=0;i<n;i++){
			if(tasks[i].execution_time > 0){
				int expected = (tasks[i].weight * (t+1)) / total_weight;
				if(allocated[i] < expected && expected - allocated[i] > max_ratio){
					max_ratio = expected - allocated[i];
					sel = i;
				}
			}
		}
		if(sel != -1){
			printf("Time %d: Running Task %d\n", t, sel);
			allocated[sel]++;
			tasks[sel].execution_time--;
		}else{
			printf("Time %d: Idle\n", t);
		}
	}
}

int main(){
	int n, time_limit;
	printf("Enter number of tasks: ");
	scanf("%d", &n);
	Task tasks[10], tasks_copy[10];

	input_tasks(tasks, n);

	printf("Enter total time to simulate: ");
	scanf("%d", &time_limit);

	// RMS
	for(int i=0;i<n;i++) tasks_copy[i] = tasks[i];
	rate_monotonic(tasks_copy, n, time_limit);

	// EDF
	for(int i=0;i<n;i++) tasks_copy[i] = tasks[i];
	earliest_deadline_first(tasks_copy, n, time_limit);

	// Proportional
	for(int i=0;i<n;i++) tasks_copy[i] = tasks[i];
	proportional_scheduling(tasks_copy, n, time_limit);

	return 0;
}
