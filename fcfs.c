#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
};
int n;
struct process p[10];
void FCFS();
void gantt();

void main(){
    int i;
    printf("enter the number of processes:");
    scanf("%d",&n);
    printf("PID\tARRIVAL TIME\tBURST TIME\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
    }
    FCFS();
}

void FCFS(){
    int i;
    int total_tat=0,total_wt=0;

    p[0].ct=p[0].bt;
    for(i=1;i<n;i++){
        p[i].ct=p[i-1].ct+p[i].bt;
    }
    for(i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
    }
    for(i=0;i<n;i++){
        p[i].wt=p[i].tat-p[i].bt;
    }
    //print table

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    for(i=0;i<n;i++){
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    gantt();
}
void gantt(){
    int i,j;
    int size=p[n-1].ct;
    printf("\nGANTT CHART\n\n");
    printf("+");
    for(i=0;i<size+2;i++){
        printf("-");
    }
    printf("+\n");
    printf("|");
    for(i=0;i<n;i++){
        printf("P%d",p[i].pid);
        for(j=0;j<p[i].bt-2;j++){
            printf(" ");
        }
        printf("|");
    }
    printf("\n");
    printf("+");
    for ( i = 0; i < size+2; i++){
        printf("-");
    }
    printf("+\n");
    printf("%d",p[0].at);
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].bt; j++)
            printf(" ");
        printf("%d", p[i].ct);
    }
    printf("\n");
}
