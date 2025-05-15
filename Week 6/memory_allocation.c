/* Write a C program to simulate the following contiguous
memory allocation techniques. (Any one)
a) Worst-fit
b) Best-fit
c) First-fit
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 20
#define MAX_PROCESSES 20

void print_allocation(int allocation[], int np) {
    printf("Process No.\tBlock No.\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t\t", i + 1);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // block number (1-based)
        else
            printf("Not Allocated\n");
    }
}

// First Fit Memory Allocation
void first_fit(int blockSize[], int nb, int processSize[], int np) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < np; i++)
        allocation[i] = -1;

    int tempBlockSize[MAX_BLOCKS];
    for (int i = 0; i < nb; i++)
        tempBlockSize[i] = blockSize[i];

    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    print_allocation(allocation, np);
}

// Best Fit Memory Allocation
void best_fit(int blockSize[], int nb, int processSize[], int np) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < np; i++)
        allocation[i] = -1;

    int tempBlockSize[MAX_BLOCKS];
    for (int i = 0; i < nb; i++)
        tempBlockSize[i] = blockSize[i];

    for (int i = 0; i < np; i++) {
        int bestIdx = -1;
        for (int j = 0; j < nb; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || tempBlockSize[j] < tempBlockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    print_allocation(allocation, np);
}

// Worst Fit Memory Allocation
void worst_fit(int blockSize[], int nb, int processSize[], int np) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < np; i++)
        allocation[i] = -1;

    int tempBlockSize[MAX_BLOCKS];
    for (int i = 0; i < nb; i++)
        tempBlockSize[i] = blockSize[i];

    for (int i = 0; i < np; i++) {
        int worstIdx = -1;
        for (int j = 0; j < nb; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || tempBlockSize[j] > tempBlockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    print_allocation(allocation, np);
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int nb, np;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter size of each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    first_fit(blockSize, nb, processSize, np);
    best_fit(blockSize, nb, processSize, np);
    worst_fit(blockSize, nb, processSize, np);

    return 0;
}
