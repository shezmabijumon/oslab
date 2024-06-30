#include<stdio.h>
typedef struct {
    int size;
    int allocation;
} process;
void firstfit(process[], int);
void worstfit(process[], int);
void bestfit(process[], int);
void display_table(process[], int);

int bn, memory[40];

void main() {
    process p[30];
    int pn, i, j, temp[10], c = 1, choice;
    printf("Enter number of blocks: ");
    scanf("%d", & bn);
    printf("Enter size of each block: \n");
    for (i = 0; i < bn; i++)
        scanf("%d", & temp[i]);
    printf("Enter no. of processes: ");
    scanf("%d", & pn);
    printf("Enter size of each process: \n");
        for (i = 0; i < pn; i++)
    scanf("%d", & p[i].size);
    printf("[0]\tExit\n[1]\tFirst Fit\n[2]\tBest Fit\n[3]\tWorstFit\n");
    while (c) {
        for (i = 0; i < 10; i++)
            p[i].allocation = -1;
        for (i = 0; i < bn; i++)
            memory[i] = temp[i];
        printf("Enter your choice: ");
        scanf("%d", & choice);
        switch (choice) {
            case 1:
            firstfit(p, pn);
            break;
            case 2:
            bestfit(p, pn);
            break;
            case 3:
            worstfit(p, pn);
            break;
            case 0:
            c = 0;
            break;
        }
    }
}
void firstfit(process p[], int pn) {
    int i, j;
    printf("\nFirst Fit\n");
    for (i = 0; i < pn; i++) {
        for (j = 0; j < bn; j++) {
            if (memory[j] >= p[i].size) {
                p[i].allocation = j;
                memory[j] -= p[i].size;
                break;
            }
        }
    }
    display_table(p, pn);
}
void bestfit(process p[], int pn) {
    int i, j, lowest, best;
    printf("\nBest Fit\n");
    for (i = 0; i < pn; i++) {
        best = -1;
        lowest = 9999;
        for (j = 0; j < bn; j++) {
            if (memory[j] >= p[i].size && memory[j] < lowest) {
                lowest = memory[j];
                best = j;
            }
        }
        if (best != -1) {
            p[i].allocation = best;
            memory[best] -= p[i].size;
        }
    }
    display_table(p, pn);
}
void worstfit(process p[], int pn) {
    int i, j, largest, worst;
    printf("\nWorst Fit\n");
    for (i = 0; i < pn; i++) {
        largest = 0, worst = -1;
        for (j = 0; j < bn; j++){
            if (memory[j] >= p[i].size && memory[j] > largest) {
                largest = memory[j];
                worst = j;
            }
        }
        if (worst != -1) {
            p[i].allocation = worst;
            memory[worst] -= p[i].size;
        }
    }
    display_table(p, pn);
}
void display_table(process p[], int pn) {
    printf("\n======================================================\n");
    printf("\tProcess No.\tProcess Size\tBlock No.");
    printf("\n======================================================\n");
    for (int i = 0; i < pn; i++) {
        printf("\t%d\t\t%d\t\t", i + 1, p[i].size);
        if (p[i].allocation != -1)
            printf("%d\n", p[i].allocation + 1);
        else
            printf("--\n");
    }
    printf("======================================================\n");
}