#include <stdio.h>
    typedef struct {
    int max[10];
    int allocated[10];
    int need[10];
}process_info;
int np, nr;
void input(process_info[], int[]);
void showTheInfo(process_info[]);
int isSafeState(process_info[], int[], int[]);

int main() {
    printf("Enter No of Processes and Resource types in system: ");
    scanf("%d%d", & np, & nr);
    int available[nr], safeSequence[np];
    process_info process[np];
    printf("****************Enter details of processes*****************\n");
    input(process, available);
    showTheInfo(process);
    if (isSafeState(process, available, safeSequence)) {
        printf("System is in safe state\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < np; i++)
            printf("P[%d] ", safeSequence[i]);
        printf("\n");
    } 
    else
        printf("System is not in Safe State\n");
    return 0;
}
//Take the input
void input(process_info process[np], int available[nr]) {
    for (int i = 0; i < np; i++) {
        printf("Enter process[%d] info\n", i);
        printf("Enter Maximum need: ");
        for (int j = 0; j < nr; j++)
            scanf("%d", & process[i].max[j]);
        printf("Enter No. of Allocated Resources: ");
        for (int j = 0; j < nr; j++) {
            scanf("%d", & process[i].allocated[j]);
            process[i].need[j] = process[i].max[j] -
            process[i].allocated[j];
        }
    }
    printf("Enter Available Resources: ");
    for (int i = 0; i < nr; i++)
        scanf("%d", & available[i]);
}
//Print the Info in Tabular form
void showTheInfo(process_info process[np]) {
    printf("PID\tMaximum\t\tAllocated\tNeed\n");
    for (int i = 0; i < np; i++) {
        printf("P[%d]\t", i);
        for (int j = 0; j < nr; j++)
            printf("%d ", process[i].max[j]);
        printf("\t\t");
        for (int j = 0; j < nr; j++)
            printf("%d ", process[i].allocated[j]);
        printf("\t\t");
        for (int j = 0; j < nr; j++)
            printf("%d ", process[i].need[j]);
        printf("\n");
    }
}
int isSafeState(process_info process[np], int available[nr], int safeSequence[np]) {
    int finish[np], work[nr], proceed = 1, k = 0, i, j, flag;
    for (i = 0; i < nr; i++)
        work[i] = available[i];
    for (i = 0; i < np; i++)
        finish[i] = 0;
    while (proceed) {
        proceed = 0;
        for (i = 0; i < np; i++) {
            flag = 1;
            if (finish[i] == 0) {
                for (j = 0; j < nr; j++) {
                    if (process[i].need[j] <= work[j])
                        continue;
                    else {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 0) 
                    continue;
                for (j = 0; j < nr; j++)
                    work[j] = work[j] + process[i].allocated[j];
                finish[i] = 1;
                safeSequence[k++] = i;
                proceed = 1;
            }
        }
    }
    for (i = 0; i < np && finish[i] == 1; i++)
        continue;
    if (i == np) 
        return 1;
    else 
        return 0;
}