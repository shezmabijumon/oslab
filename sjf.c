#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int executed;
};
int n;
struct process p[10];
int a[10];

void SJF();
void gantt();

void main(){
    int i;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("PID\tAT\tBT\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
    }
    SJF();

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

void SJF(){
    int currenttime,i,j=0;
    int nextprocess;
    int shortestburst;

    for(i=0;i<n;i++){
        p[i].executed=0;
    }
    currenttime=p[0].at;
    for(i=1;i<n;i++){
        if(p[i].at<=currenttime){
            currenttime=p[i].at;
        }
    }
    while (1){
        shortestburst=100;
        nextprocess=-1;
        for ( i = 0; i < n; i++){
            if(!p[i].executed && currenttime>=p[i].at && p[i].bt<=shortestburst){
                nextprocess=i;
                shortestburst=p[i].bt;
            }
        }
        if (nextprocess==-1){
            break;
        }
        a[j]=nextprocess;
        j++;
        currenttime+=p[nextprocess].bt;
        p[nextprocess].ct=currenttime;
        p[nextprocess].tat = p[nextprocess].ct - p[nextprocess].at;
        p[nextprocess].wt = p[nextprocess].tat - p[nextprocess].bt;
        p[nextprocess].executed = 1;
    }
}
void gantt(){
    int i,j,k;
    int size = 0;
    for (i = 0; i < n; i++) {
        size += p[i].bt;
    }
    printf("\nGANTT CHART\n\n");
    printf("+");
    for ( i = 0; i < size+2; i++){
        printf("-");
    }
    printf("+\n");
    printf("|");
    for ( k = 0; k < n; k++){
        for(i=0;i<n;i++){
            if (a[k]==i){
                printf("P%d",p[i].pid);
                for(j=0;j<p[i].bt-2;j++){
                    printf(" ");
                }
                printf("|");
                break;
            }
        }
    }
    printf("\n");
    printf("+");
    for ( i = 0; i < size+2; i++){
        printf("-");
    }
    printf("+\n");
    printf("%d", p[0].at);
    for (k = 0; k < n; k++) {
        for(i=0; i<n; i++){
            if (a[k]==i){
                for (j = 0; j < p[i].bt; j++)
                    printf(" ");
                printf("%d", p[i].ct);
                break;
            }
        }
    }
}