#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int id;
    int need[10];
    int max[10];
    int alloc[10];
} process;

void main(){
    int n,r;
    printf("enter no.of processes: ");
    scanf("%d",&n);
    process p[10];
    printf("enter no.of resources: ");
    scanf("%d",&r);
    int resource[10];
    int available[10];
    for (int i=0;i<r;i++){
        printf("enter no.of instances of Resource %d: ",i+1);
        scanf("%d",&resource[i]);
        available[i]=0;
    }
    for (int i = 0; i < n; i++){
        p[i].id = i + 1;
        printf("Enter resource need and resource allocated to process %d\n", (i + 1));
        for (int j = 0; j < r; j++){
            printf("Enter no of instances of resource %d max needed:\n", (j + 1));
            scanf("%d", &p[i].max[j]);
            printf("Enter no of instances of resource %d allocted:\n", (j + 1));
            scanf("%d", &p[i].alloc[j]);
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
        }
    }
    //resource available
    for (int i = 0; i < r; i++){
        int sum=0;
        for (int j= 0; j < n; j++){
            sum += p[j].alloc[i];
        }
        available[i]=resource[i]-sum;        
    }
    printf("Process\t  Max  \t  Allocation     Need\n");
    for (int i = 0; i < n; i++){
        printf("  P%d \t", (i + 1));
        for (int j = 0; j < r; j++){
            printf("%d  ", p[i].max[j]);
        }
        for (int j = 0; j < r; j++){
            printf("%d  ", p[i].alloc[j]);
        }
        printf("\t");
        for (int j = 0; j < r; j++){
            printf("%d  ", p[i].need[j]);
        }
        printf("\n");
    }
    printf("available resources:\n");
    for (int i = 0; i < r; i++){
        printf("R%d\t",i+1);
    }
    printf("\n");
    for (int i = 0; i < r; i++){
        printf("%d\t",available[i]);
    }
    printf("\n");
    int completed[10],sequence[10];
    for (int i = 0; i < n; i++){
        completed[i]=0;
    }
    int count=0,index=0;
    while(count<n){
        int flag=0;
        for (int i=0; i<n; i++){
            if (completed[i]==0){
                int j;
                for(j=0;j<r;j++){
                    if(available[j]<p[i].need[j]){
                        break;
                    }
                }
                if (j==r){
                    flag=1;
                    completed[i]=1;
                    count++;
                    sequence[index++]=p[i].id;
                    for(int k=0;k<r;k++){
                        available[k] += p[i].alloc[k];
                    }
                    printf("process%d executed\n", p[i].id);
                    printf("New Available resource\n");
                    for (int k = 0; k < r; k++){
                        printf("R%d\t",k+1);
                    }
                    printf("\n");
                    for (int k = 0; k < r; k++){
                        printf("%d\t",available[k]);
                    }
                    printf("\n");
                }
                else{
                    printf("process%d cannot be executed as need > available\n", p[i].id);
                }
            }
        }
        if (flag == 0){
            printf("\nUnsafe State\n");
            break;
        }
    }
    if (count == n){
        printf("\nSafe sequence is:\n");
        for (int i = 0; i < n; i++){
            printf("P%d\t", sequence[i]);
        }
    }
    printf("\n");
}
