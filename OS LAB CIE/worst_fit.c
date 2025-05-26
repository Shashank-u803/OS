 /*
 * Name: Shashank U
 * USN: 1BM23CS314
 * Lab: Operating Systems Lab CIE
 * Program: Worst Fit Memory Allocation with Deallocation and fragmentation 
 */

#include<stdio.h>
#include<stdlib.h>

void display(int alloc[], int process[], int blocks[], int p, int b) {
    printf("----------Worst_FIT----------\n");
    printf("Allocation Table\n");
    printf("PID\t\t\tPsize\t\t\tBlock_id\t\t\tFragment size\n");
    for(int i = 0; i < p; i++) {
        printf("P%d\t\t\t%d\t\t\t", i + 1, process[i]);
        if(alloc[i] == -1) {
            printf("Not alloted\t\t\tNot alloted\n");
        } else {
            printf("B%d\t\t\t\t%d\n", alloc[i] + 1, blocks[alloc[i]]);
        }
    }
}

// CODE THAT HANDLES THE MODIFICATION ASKED IN THE QUESTION
void deallocate(int process[], int blocks[], int alloc[], int p, int b, int p_index) {
    //deallocate the block
    if(p_index < 0 || p_index >= p) {
        printf("Invalid process index\n");
        return;
    }
    if(alloc[p_index] != -1) {
        int block_id = alloc[p_index];
        printf("Before Deallocation of Process P%d\n", p_index + 1);
        printf("Block ID\t\tBlock Size\t\tProcess size\n");
        printf("B%d\t\t\t%d\t\t\t%d\n", block_id + 1, blocks[block_id], process[p_index]);
        blocks[block_id] += process[p_index];
        alloc[p_index] = -1;
        printf("After Deallocation of Process P%d\n", p_index + 1);
        printf("Block ID\t\tBlock Size\t\tProcess size\n");
        printf("B%d\t\t\t%d\t\t\t%d\n", block_id + 1, blocks[block_id], process[p_index]);
    } else {
        printf("Process P%d was not allocated to any block.\n", p_index + 1);
    }
}

//CODE THAT HANDLES THE MAIN QUESTION
void worst_fit(int process[], int blocks[], int p, int b) {
    int alloc[p], temp_blocks[b];
    for(int i = 0; i < p; i++) {
        alloc[i] = -1;
    }
    for(int i = 0; i < b; i++) {
        temp_blocks[i] = blocks[i];
    }

    for(int i = 0; i < p; i++) {
        int worst_idx = -1;
        for(int j = 0; j < b; j++) {
            if(temp_blocks[j] >= process[i]) {
                if(worst_idx == -1 || (temp_blocks[j] > temp_blocks[worst_idx])) {
                    worst_idx = j;
                }
            }
        }
        if(worst_idx != -1) {
            alloc[i] = worst_idx;
            temp_blocks[worst_idx] -= process[i];
            blocks[worst_idx] -= process[i];
        }
    }
    display(alloc, process, blocks, p, b);
    //Example
    deallocate(process, blocks, alloc, p, b, 2);
}

int main() {
    int p, b;
    printf("Enter no.of process and blocks:");
    scanf("%d%d", &p, &b);
    int process[p], blocks[b];
    printf("Enter the process memory requirements\n");
    for(int i = 0; i < p; i++) {
        printf("P%d:", i + 1);
        scanf("%d", &process[i]);
    }
    printf("Enter the block memory details\n");
    for(int i = 0; i < b; i++) {
        printf("Block %d:", i + 1);
        scanf("%d", &blocks[i]);
    }
    worst_fit(process, blocks, p, b);
    return 0;
}
