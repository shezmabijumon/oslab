#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int executed, prio;
};
int n;
struct process p[10];
struct process g[10];

void PRIO();
void gantt();

void main(){
    int i;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("\nPID\tAT\tBT\tPriority\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].prio);
    }
    PRIO();
    printf("PID\tAT\tBT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].tat,p[i].wt);
    }
    gantt();

    // Avg waiting and turnaround time
    int totwt = 0, tottat = 0;
    for (i = 0; i < n; i++) {
        totwt += p[i].wt;
        tottat += p[i].tat;
    }
    float avgwait = (totwt + 0.0) / n;
    float avgturn = (tottat + 0.0) / n;

    printf("Average Waiting Time: %.2f\n", avgwait);
    printf("Average Turnaround Time: %.2f\n", avgturn);
}

void PRIO(){
    int currenttime;
    int i,k=0;
    int nextprocess,highprio;

    for (i = 0; i < n; i++){
        p[i].executed = 0;
    }
    currenttime=p[0].at;
    for(i=1;i<n;i++){
        if(p[i].at<=currenttime){
            currenttime=p[i].at;
        }
    }
    while(1){
        highprio=100;
        nextprocess=-1;
        for (i=0; i<n; i++){
            if(!p[i].executed && p[i].at<=currenttime && p[i].prio<=highprio){
                nextprocess=i;
                highprio=p[i].prio;
            }
        }
        
        if(nextprocess==-1){
            break;
        }

        currenttime+=p[nextprocess].bt;
        p[nextprocess].ct=currenttime;
        p[nextprocess].tat = p[nextprocess].ct - p[nextprocess].at;
        p[nextprocess].wt = p[nextprocess].tat - p[nextprocess].bt;
        p[nextprocess].executed = 1;

        g[k]=p[nextprocess];
        k++;
    }
}
void gantt(){
    int i,j,k;
    int size = g[n-1].ct;
    printf("\nGANTT CHART\n\n");
    printf("+");
    for ( i = 0; i < size+2; i++){
        printf("-");
    }
    printf("+\n");
    printf("|");
    for ( i = 0; i < n; i++){
        printf("P%d",g[i].pid);
        for(j=0;j<g[i].bt-2;j++){
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
    printf("%d", g[0].at);
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < g[i].bt; j++){
            printf(" ");
        }
        printf("%d", g[i].ct);
    }
    for (j = 0; j < g[n-1].bt; j++)
        printf(" ");
    printf("%d\n",g[n-1].ct);
}