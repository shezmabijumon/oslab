#include<stdio.h>
#include<stdlib.h>

void display(int[], int);
void fcfs(int[], int, int, int[]);
void scan(int[], int, int, int[]);
void c_scan(int[], int, int, int[]);
int size, T_Head_Mv = 0;

void main() {
    int rq[100], temp[100], c = 1, i, j, n, init_pos, ch, order[100];
    printf("Enter total disk size: ");
    scanf("%d", & size);
    printf("Enter the number of Requests: ");
    scanf("%d", & n);
    printf("Enter Request sequence: \n");
    for (i = 0; i < n; i++)
        scanf("%d", & temp[i]);
    printf("Enter initial head position: ");
    scanf("%d", & init_pos);
    printf("\n[0]\tExit\n[1]\tFCFS\n[2]\tSCAN\n[3]\tC SCAN");
    while (c) {
        for (i = 0; i < n; i++)
        rq[i] = temp[i];
        printf("\n\nEnter your choice: ");
        scanf("%d", & ch);
        switch (ch) {
            case 0:
            c = 0;
            break;
            case 1:
            printf("FCFS\n");
            fcfs(rq, n, init_pos, order);
            break;
            case 2:
            printf("SCAN\n");
            scan(rq, n, init_pos, order);
            break;
            case 3:
            printf("C-SCAN\n");
            c_scan(rq, n, init_pos, order);
            break;
            default:
            printf("Invalid choice\n");
        }
    }
}
void fcfs(int rq[], int n, int init_pos, int order[]) {
    for (int i = 0; i < n; i++) {
        T_Head_Mv += abs(rq[i] - init_pos);
        order[i] = rq[i];
        init_pos = rq[i];
    }
    display(order, n);
}
void display(int order[], int n) {
    printf("Seek sequence: ");
    for (int i = 0; i < n; i++)
        printf("%d ", order[i]);
    printf("\nTotal Head Movement = %d ", T_Head_Mv);
}
void scan(int rq[], int n, int init_pos, int order[]) {
    int move, i, j, k = 0, index;
    printf("Enter direction to move (0 - low / 1 - high): ");
    scanf("%d", & move);
    //sorting rq
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (rq[j] > rq[j + 1]) {
                int temp = rq[j];
                rq[j] = rq[j + 1];
                rq[j + 1] = temp;
            }
        }
    }
    //display sorted rq
    printf("Sorted requests: ");
    for (i = 0; i < n; i++)
        printf("%d ", rq[i]);
    printf("\n");
    //to find the starting position in the sorted rq
    for (i = 0; i < n; i++) {
        if (init_pos < rq[i]) {
            index = i;
            break;
        }
    }
    //if movement is towards right side
    if (move == 1) {
        for (i = index; i < n; i++) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
        //last movement for max size
        T_Head_Mv += abs(size - rq[i - 1] - 1);
        init_pos = size - 1;
        for (i = index - 1; i >= 0; i--) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
    }
    //if the movement is towards left side
    else {
        for (i = index - 1; i >= 0; i--) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
        //last movement for min size
        T_Head_Mv += abs(rq[i + 1]);
        init_pos = 0;
        for (i = index; i < n; i++) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
    }
    display(order, k);
}
void c_scan(int rq[], int n, int init_pos, int order[]) {
    int move, i, j, k = 0, index;
    printf("Enter direction to move (0 - low / 1 = high): ");
    scanf("%d", & move);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (rq[j] > rq[j + 1]) {
                int temp = rq[j];
                rq[j] = rq[j + 1];
                rq[j + 1] = temp;
            }
        }
    }
    //display sorted rq
    printf("Sorted requests: ");
    for (i = 0; i < n; i++)
        printf("%d ", rq[i]);
    printf("\n");
    //to find the starting position in the sorted rq
    for (i = 0; i < n; i++) {
        if (init_pos < rq[i]) {
            index = i;
            break;
        }
    }
    //if movement is towards right side
    if (move == 1) {
        for (i = index; i < n; i++) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
        //last movement for max size
        T_Head_Mv += abs(size - rq[i - 1] - 1);
        //head movement to starting position
        T_Head_Mv += abs(size - 1 - 0);
        init_pos = 0;
        for (i = 0; i <= index - 1; i++) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
    }
    //if the movement is towards left side
    else {
        for (i = index - 1; i >= 0; i--) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
        //last movement for min size
        T_Head_Mv += abs(rq[i + 1]);
        T_Head_Mv += abs(size - 1 - 0);
        init_pos = size - 1;
        for (i = n - 1; i >= index; i--) {
            T_Head_Mv += abs(rq[i] - init_pos);
            init_pos = rq[i];
            order[k++] = rq[i];
        }
    }
    display(order, k);
}