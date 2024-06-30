#include<stdio.h>
    typedef struct {
    int page;
    int freq;
}Freq;

void FIFO(int rs[], int n, int frames[], int nf);
void LRU(int rs[], int n, int frames[], int nf);
void LFU(int rs[], int n, int frames[], int nf);
int check_fault(int page, int frames[], int nf);
int find_min_freq(int frames[], int current, int nf, int rs[]);
void sort(Freq table[], int len);

void main() {
    int n, frames[50], rs[50], nf, i, c = 1;
    printf("Enter the number of pages: ");
    scanf("%d", & n);
    printf("Enter the page reference numbers : \n");
    for (i = 0; i < n; i++) {
        scanf("%d", & rs[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", & nf);
    printf("[0]\tExit\n[1]\tFIFO\n[2]\tLRU\n[3]\tLFU\n");
    int choice;
    while (c) {
        for (i = 0; i < nf; i++)
            frames[i] = -1;
        printf("Enter your choice: ");
        scanf("%d", & choice);
        switch (choice) {
            case 1:
            FIFO(rs, n, frames, nf);
            break;
            case 2:
            LRU(rs, n, frames, nf);
            break;
            case 3:
            LFU(rs, n, frames, nf);
            break;
            case 0:
            c = 0;
            break;
        }
    }
}
void FIFO(int rs[], int n, int frames[], int nf) {
    int j = 0, k, fcount = 0, avail;
    printf("\nFIFO");
    printf("\n==========================================================\nPage Ref");
    for (int i = 0; i < nf; i++) printf("\tF%d", i);
        printf("\tHit/Fault\n==========================================================\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t", rs[i]);
        avail = 0;
        for (k = 0; k < nf; k++) {
            if (frames[k] == rs[i]) {
                avail = 1;
                for (k = 0; k < nf; k++)
                    printf("%d\t", frames[k]);
                printf("H");
            }
        }
        if (avail == 0) {
            frames[j] = rs[i];
            j = (j + 1) % nf;
            fcount++;
            for (k = 0; k < nf; k++)
                printf("%d\t", frames[k]);
            printf("F");
        }
        printf("\n");
    }
    printf("==========================================================\n");
    printf("Number of page faults: %d\n", fcount);
}
void LRU(int rs[], int n, int frames[], int nf) {
    int fcount = 0, k = 0, c1, i, j, c2[100], b[100], t, r;
    printf("\nLRU");
    printf("\n==========================================================\nPage Ref");
    for (int i = 0; i < nf; i++) printf("\tF%d", i);
    printf("\tHit/Fault\n==========================================================\n");
    frames[k] = rs[k];
    printf("%d\t\t", rs[0]);
    for (i = 0; i < nf; i++)
        printf("%d\t", frames[i]);
    printf("F\n");
    fcount++;
    k++;
    for (i = 1; i < n; i++) {
        printf("%d\t\t", rs[i]);
        c1 = 0;
        for (j = 0; j < nf; j++)
            if (rs[i] != frames[j])
                c1++;
        if (c1 == nf) {
            fcount++;
            if (k < nf) {
                frames[k] = rs[i];
                k++;
                for (j = 0; j < nf; j++)
                printf("%d\t", frames[j]);
                printf("F\n");
            } 
            else {
                for (r = 0; r < nf; r++) {
                    c2[r] = 0;
                    for (j = i - 1; j >= 0; j--) {
                        if (frames[r] != rs[j])
                            c2[r]++;
                        else
                            break;
                    }
                }
                for (r = 0; r < nf; r++)
                    b[r] = c2[r];
                for (r = 0; r < nf; r++) {
                    for (j = r; j < nf; j++) {
                        if (b[r] < b[j]) {
                            t = b[r];
                            b[r] = b[j];
                            b[j] = t;
                        }
                    }
                }
                for (r = 0; r < nf; r++) {
                    if (c2[r] == b[0])
                    frames[r] = rs[i];
                    printf("%d\t", frames[r]);
                }
                printf("F\n");
            }
        } 
        else {
            for (j = 0; j < nf; j++)
                printf("%d\t", frames[j]);
            printf("H\n");
        }
    }
    printf("==========================================================\n");
    printf("Number of page faults: %d\n", fcount);
}
void sort(Freq table[], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len - i - 1; j++) {
            if (table[j].freq > table[j + 1].freq) {
                Freq temp;
                temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}
int check_fault(int page, int frames[], int nf) {
    for (int i = 0; i < nf; i++)
        if (frames[i] == page)
            return 0;
    return 1;
}
int find_min_freq(int frames[], int current, int nf, int rs[]) {
    Freq table[30];
    int count;
    for (int i = 0; i < nf; i++)
        table[i].page = frames[i];
    for (int i = 0; i < nf; i++) {
        count = 0;
        //consider table[i]
        for (int j = 0; j < current; j++)
            if (rs[j] == table[i].page)
                count++;
        table[i].freq = count;
    }
    sort(table, nf);
    for (int i = 0; i < nf; i++)
        if (frames[i] == table[0].page)
            return i;
    return -1;
}
void LFU(int rs[], int n, int frames[], int nf) {
    int front = 0, fcount = 0, j;
    printf("\nLFU");
    printf("\n==========================================================\nPage Ref");
    for (int i = 0; i < nf; i++) printf("\tF%d", i);
        printf("\tHit/Fault\n==========================================================\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t", rs[i]);
        if (check_fault(rs[i], frames, nf) && front >= nf) {
            int index = find_min_freq(frames, i, nf, rs);
            frames[index] = rs[i];
            fcount++;
            for (j = 0; j < nf; j++) {
                printf("%d\t", frames[j]);
            }
            printf("F\n");
        } 
        else if (check_fault(rs[i], frames, nf)) {
            frames[front] = rs[i];
            front++;
            fcount++;
            for (j = 0; j < nf; j++) {
                printf("%d\t", frames[j]);
            }
            printf("F\n");
        } 
        else if (!check_fault(rs[i], frames, nf)) {
            for (j = 0; j < nf; j++) {
                printf("%d\t", frames[j]);
            }
            printf("H\n");
        }
    }
    printf("==========================================================\n");
    printf("Number of page faults: %d\n", fcount);
}