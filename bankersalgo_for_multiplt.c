#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main()
{
    int num_processes, num_resources; // Number of processes and resources
    int available[MAX_RESOURCES];    // Available instances of each resource
    int max_claim[MAX_PROCESSES][MAX_RESOURCES]; // Maximum claim of each process
    int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Allocated resources for each process
    int need[MAX_PROCESSES][MAX_RESOURCES];       // Remaining resource need for each process
    int work[MAX_RESOURCES];                      // Work array for Banker's Algorithm
    int finish[MAX_PROCESSES];                     // Finish array for Banker's Algorithm
    int safe_sequence[MAX_PROCESSES];              // Safe sequence array for Banker's Algorithm

printf("lab 6.1(implement Bankers Algorithm for multiple type of resources to decidesafe/unsafe state. .)\n");
    printf("Name:Nisha Lamichhane\n");
    printf("Roll no:21 \t\t\t section:'A:\n");
    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    // Input the available instances of each resource
    printf("Enter the available instances of each resource:\n");
    for (int i = 0; i < num_resources; i++)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Input the maximum claim of each process
    printf("Enter the maximum claim of each process:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d:\n", i + 1);
        for (int j = 0; j < num_resources; j++)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max_claim[i][j]);
        }
    }

    // Input the allocated resources for each process
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d:\n", i + 1);
        for (int j = 0; j < num_resources; j++)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
            need[i][j] = max_claim[i][j] - allocation[i][j];
        }
    }

    // Initialize the work array and finish array
    for (int i = 0; i < num_resources; i++)
        work[i] = available[i];
    for (int i = 0; i < num_processes; i++)
        finish[i] = 0;

    // Banker's Algorithm
    int count = 0; // Number of processes in the safe sequence
    while (count < num_processes)
    {
        int found = 0; // Flag to check if a process can be executed
        for (int i = 0; i < num_processes; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources)
                {
                    // Process i can be executed
                    for (int k = 0; k < num_resources; k++)
                        work[k] += allocation[i][k];
                    finish[i] = 1;
                    safe_sequence[count++] = i;
                    found = 1;
                }
            }
        }
        if (found == 0)
            break; // No process can be executed
    }

    // Check if the system is in a safe or unsafe state
    if (count == num_processes)
    {
        printf("\nSystem is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < num_processes; i++)
            printf("%d ", safe_sequence[i] + 1);
        printf("\n");
    }
    else
    {
        printf("\nSystem is in an unsafe state.\n");
    }

    return 0;
}