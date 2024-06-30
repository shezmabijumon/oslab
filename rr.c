#include <stdio.h>

struct process {
    int pid, at, bt;
    int wt, tat, ct;
    int rembt, done;
};

struct queue {
    int id, t, d;
};

int n, qt;
struct process p[10];
struct queue q[10];

void RR();

int main() {
    int i, tottat = 0, totwt = 0;
    float avgwait = 0.0f, avgturn = 0.0f;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    printf("PID\tAT\tBT\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &qt);

    RR();

    // Calculate average turn around time and average waiting time
    for (i = 0; i < n; i++) {
        tottat += p[i].tat;
        totwt += p[i].wt;
    }

    // Print process details
    printf("PID\tAT\tBT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    }

    avgwait = (float)totwt / n;
    avgturn = (float)tottat / n;

    printf("\nAverage Waiting Time: %.2f\n", avgwait);
    printf("Average Turnaround Time: %.2f\n", avgturn);

    return 0;
}

void RR() {
    int currenttime = p[0].at;
    int i, rem = n;
    int k = 0; // Initialize the index variable for the queue

    for (i = 0; i < n; i++) {
        p[i].rembt = p[i].bt;
        p[i].done = 0;
        if (p[i].at < currenttime) {
            currenttime = p[i].at;
        }
    }

    while (rem > 0) {
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= currenttime) {
                q[k].id = p[i].pid;

                if (p[i].rembt <= qt) {
                    currenttime += p[i].rembt;
                    p[i].ct = currenttime;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    p[i].done = 1;
                    rem--;
                    q[k].t = currenttime; // Update time in the queue
                    q[k].d = p[i].rembt;  // Update remaining burst time in the queue
                } else {
                    p[i].rembt -= qt;
                    currenttime += qt;
                    q[k].t = currenttime; // Update time in the queue
                    q[k].d = qt;          // Update time quantum in the queue
                }
                k++;
            }
        }
    }
}
