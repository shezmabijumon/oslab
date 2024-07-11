#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int rembt,done;
    int avbl;  //when process is avlbl to execute next
};
struct rrq{
    int id,d,t;
};
struct process p[10];
struct rrq q[30];

int n,qt,k=0;

void RR();
void gantt();

void main(){
    int i;
    int tottat = 0, totwt = 0;
    float avgwait = 0.0f, avgturn = 0.0f;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("PID\tAT\tBT\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
    }
    printf("Enter time quantum: ");
    scanf("%d",&qt);

    RR();
    gantt();

    for (i = 0; i < n; i++) {
        tottat += p[i].tat;
        totwt += p[i].wt;
    }
    printf("PID\tAT\tBT\tTAT\tWT\tCT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].tat, p[i].wt, p[i].ct);
    }

    avgwait = (totwt + 0.0) / n;
    avgturn = (tottat + 0.0) / n;
    printf("\nAverage Waiting Time: %.2f ns", avgwait);
    printf("\nAverage Turnaround Time: %.2f ns\n", avgturn);
}
void RR(){
    int i,j;
    int rem=n;
    int currenttime=p[0].at;

    for ( i = 0; i < n; i++){
        p[i].rembt=p[i].bt;
        p[i].done=0;
        p[i].avbl=p[i].at;
        if(p[i].at<currenttime){
            currenttime=p[i].at;
        }
    }
    while(rem>0){
        int process_executed=0;
        for(i=0;i<n;i++){
            if(!p[i].done && p[i].avbl<=currenttime){
                q[k].id=p[i].pid;
                if(p[i].rembt<=qt){
                    currenttime += p[i].rembt;
                    p[i].ct=currenttime;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                    p[i].done=1;
                    rem--;
                    q[k].t=currenttime;
                    q[k].d=p[i].rembt;
                    p[i].rembt=0;
                }
                else{
                    p[i].rembt -= qt;
                    currenttime += qt;
                    p[i].avbl=currenttime;
                    q[k].t=currenttime;
                    q[k].d=qt;
                }
                k++;
                process_executed=1;
            }
        }
        if (!process_executed){
            currenttime++;
        }
    }
}
void gantt(){
    int i,j;
    int size;
    for (i=0;i<k;i++){
        size += q[i].d;
    }
    printf("\nGANTT CHART\n\n");
    printf("+");
    for (i = 0; i < size + k; i++) {
        printf("-");
    }
    printf("+\n");
    printf("|");
    for (i = 0; i < k; i++) {
        printf("P%d", q[i].id);
        for (j = 0; j < q[i].d-2; j++) {
            printf(" ");
        }
        printf("|");
    }

    printf("\n+");
    for (i = 0; i < size + k; i++) {
        printf("-");
    }
    printf("+\n0");
    for (i = 0; i < k; i++) {
        for (j = 0; j < q[i].d; j++) {
            printf(" ");
        }
        printf("%d", q[i].t);
    }
    printf("\n");
}
