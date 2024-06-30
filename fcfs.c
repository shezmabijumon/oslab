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
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("PID\tArrivalTime\tBurstTime\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
    }
    FCFS();
}

void FCFS(){
    int i,j;
    int total_tat=0,total_wt=0;

    p[0].wt=p[0].at;
    for(i=1;i<n;i++){
        p[i].wt=p[i-1].wt+p[i-1].bt;
    }
    for(i=0;i<n;i++){
        p[i].ct=p[i].wt+p[i].bt+p[i].at;
    }
    for(i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
    }
    //print table
    
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    
    gantt();
    for(i=0;i<n;i++){
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
}

void gantt(){
    int i,j;
    int size=p[n-1].ct;
    printf("\nGANTT CHART\n\n");
    printf("+");
    for ( i = 0; i < size+2; i++){
        printf("-");
    }
    printf("+\n");
    printf("|");
    for ( i = 0; i < n; i++){
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
    printf("%d", p[0].at);
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < p[i].bt; j++)
            printf(" ");
        printf("%d", p[i].ct);
    }
    for (j = 0; j < p[n-1].bt; j++)
        printf(" ");
    printf("%d\n",p[n-1].ct);
}