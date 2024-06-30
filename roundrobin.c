#include<stdio.h>

struct process{
    int pid,at,bt;
    int wt,tat,ct;
    int rembt,done;
    int avbl;
};
struct rrq{
    int id;
    int d;
    int t;
};
struct rrq q[25];
int k=0;
int n,qt;

struct process p[10];
void RR();
void gantt();

void main()
{
    int i,tottat=0,totwt=0;
    float avgwait=0.0f,avgturn=0.0f;

    printf("Enter the total no. of processes:");
    scanf("%d",&n);

    printf("PID\tAT\tBT\n");
    for(i=0;i<n;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
    }

    printf("Enter the time quantum:");
    scanf("%d",&qt);

    RR();
    gantt();

    //avg turn around time
    for(i=0;i<n;i++){
        tottat+=p[i].tat;
        totwt+=p[i].wt;
    }

    printf("PID\tAT\tBT\tTAT\tWT\tCT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].tat,p[i].wt,p[i].ct);
    }

    avgwait=(totwt+0.0)/n;
    avgturn=(tottat+0.0)/n;

    printf("\nAverage Waiting Time: %.2fns",avgwait);
    printf("\nAverage Turnaround Time: %.2fns",avgturn);
}

void RR(){
    int currenttime=p[0].at;
    int i,j;
    int rem=n;

    for ( i = 0; i < n; i++){
        p[i].rembt=p[i].bt;
        p[i].done=0;
        p[i].avbl=p[i].at;
        if (p[i].at<currenttime){
            currenttime=p[i].at;
        }
    }
    while (rem>0){
        for(j=0;j<n;j++){   
            for(int k=0; k<n; k++){

            }     
            if(p[i].avbl<=currenttime &&!p[i].done){
                q[k].id=p[i].pid;
                if(p[i].rembt<=qt){
                    currenttime+=p[i].rembt;
                    p[i].ct=currenttime;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                    p[i].done=1;
                    p[i].rembt=0;
                    rem--;
                    q[k].t=currenttime;
                    q[k].d=p[i].rembt;
                    p[i].avbl=100;
                }
                else{
                    p[i].rembt-=qt;
                    currenttime+=qt;
                    p[i].avbl=currenttime;
                    q[k].t=currenttime;
                    q[k].d=qt;
                }
                k++;
            }                       
        }
    }
}
void gantt(){
    int i,j,size=0;
    for ( i = 0; i < k; i++){
        size+=q[i].d;
    }
    printf("\nGANTT CHART\n\n");
    printf("+");
    for ( i = 0; i < size+2; i++){
        printf("-");
    }
    printf("+\n");
    printf("|");
    for ( i = 0; i < k; i++){
        printf("P%d",q[i].id);
        for(j=0;j<q[i].d;j++){
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
    printf("0");
    for(i=0; i<k; i++){
        for (j = 0; j < q[i].d; j++){
            printf(" ");
        }
        printf("%d", q[i].t);
    }
    for (j = 0; j < q[k-1].d; j++)
        printf(" ");
    printf("%d\n",q[k-1].t);
}