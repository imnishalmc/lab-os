#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes based on arrival time
void sort_processes(int *bt, int *at, int *p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

// Function to calculate completion time, turnaround time, and waiting time
void get_timings(int *bt, int *at, int *ct, int *tat, int *wt, int *p, int n) {
    sort_processes(bt, at, p, n);

    ct[0] = bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];

    for (int i = 1; i < n; i++) {
        // Calculate the completion time of the current process
        if (at[i] > ct[i - 1]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i - 1] + bt[i];
        }

        // Calculate the turnaround time and waiting time of the current process
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

// Function to print process details
void print_table(int *p, int *at, int *bt, int *ct, int *tat, int *wt, int n) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

// Function to print Gantt chart (you can implement this as needed)
void print_gantt_chart(int *at, int *ct, int *p, int n) {
    // Implement your Gantt chart printing logic here
    // This function will depend on your specific requirements
    // You can print a timeline or any other representation
}

int main() {
    int n;
    printf("lab 5.1 (simulate FCFS cpu S.A.)\n");
    printf("Name:Nisha Lamichhane\n");
    printf("Roll no:21 \t\t\t section:'A:\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int p[n], bt[n], at[n];
    int ct[n], tat[n], wt[n];

    // Input process details (arrival times and burst times)
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Assign process IDs
    }

    get_timings(bt, at, ct, tat, wt, p, n);
    print_table(p, at, bt, ct, tat, wt, n);
    // Call print_gantt_chart if needed

    return 0;
}

