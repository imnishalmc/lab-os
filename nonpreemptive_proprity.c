#include <stdio.h>
#include <stdlib.h>
struct Process
{
    int pid;
    int priority;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};
void swap(struct Process *a, struct Process *b)
{
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}
void sort_by_priority(struct Process *process_list, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (process_list[j].priority < process_list[j + 1].priority)
            {
                swap(&process_list[j], &process_list[j + 1]);
            }
        }
    }
}
void calculate_waiting_time(struct Process *process_list, int n)
{
    process_list[0].waiting_time = 0;
    for (int i = 1; i < n; i++)
    {
        process_list[i].waiting_time = process_list[i - 1].waiting_time + process_list[i - 1].burst_time;
    }
}
void calculate_turnaround_time(struct Process *process_list, int n)
{
    for (int i = 0; i < n; i++)
    {
        process_list[i].turnaround_time = process_list[i].waiting_time + process_list[i].burst_time;
    }
}
void calculate_average_times(struct Process *process_list, int n, float *avg_waiting_time, float *avg_turnaround_time)
{
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += process_list[i].waiting_time;
        total_turnaround_time += process_list[i].turnaround_time;
    }
    *avg_waiting_time = total_waiting_time / n;
    *avg_turnaround_time = total_turnaround_time / n;
}
void print_table(struct Process *process_list, int n)
{
    printf("\nProcess ID\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_list[i].pid, process_list[i].priority, process_list[i].burst_time, process_list[i].waiting_time, process_list[i].turnaround_time);
    }
}
int main()
{
    int n;
     printf("lab 5.5(non-preemptive priority cpu S.A.)\n");
    printf("Name:Nisha Lamichhane\n");
    printf("Roll no:21 \t\t\t section:'A:\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Invalid number of processes. Please enter a positive integer.\n");
        return 1;
    }
    struct Process *process_list = (struct Process *)malloc(n * sizeof(struct Process));
    if (process_list == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        process_list[i].pid = i + 1;
        printf("Enter the priority of process %d: ", process_list[i].pid);
        scanf("%d", &process_list[i].priority);
        if (process_list[i].priority < 0)
        {
            printf("Invalid priority. Please enter a non-negative integer.\n");
            free(process_list);
            return 1;
        }
        printf("Enter the burst time of process %d: ", process_list[i].pid);
        scanf("%d", &process_list[i].burst_time);
        if (process_list[i].burst_time < 0)
        {
            printf("Invalid burst time. Please enter a non-negative integer.\n");
            free(process_list);
            return 1;
        }
    }
    sort_by_priority(process_list, n);
    calculate_waiting_time(process_list, n);
    calculate_turnaround_time(process_list, n);
    float avg_waiting_time, avg_turnaround_time;
    calculate_average_times(process_list, n, &avg_waiting_time, &avg_turnaround_time);
    print_table(process_list, n);
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    free(process_list);
    return 0;
}