#include <stdio.h>
#include <stdlib.h>

int calculate_seek_time(int requests[], int n, int start) {
    int total_seek_time = 0;
    int current_position = start;

    for (int i = 0; i < n; i++) {
        int seek_distance = abs(requests[i] - current_position);
        total_seek_time += seek_distance;
        current_position = requests[i];
    }
    return total_seek_time;
}

int main() {
    int n, starting_position;
 printf("Lab 10.1 (FCFS):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    // Input the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    // Validate the number of requests
    if (n <= 0) {
        printf("Number of requests must be greater than 0.\n");
        return 1; // Exit with error
    }

    int requests[n]; // Dynamic array for requests

    // Input the disk request queue
    printf("Enter the disk request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Input the starting position of the disk head
    printf("Enter the starting position of the disk head: ");
    scanf("%d", &starting_position);

    // Calculate the total seek time
    int seek_time = calculate_seek_time(requests, n, starting_position);
    printf("Total Seek Time: %d\n", seek_time);

    return 0;
}