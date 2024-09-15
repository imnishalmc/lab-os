#include <stdio.h>
#include <stdlib.h> // Include for abs() function

struct head {
    int num; // Disk location
    int flag; // Flag to check if the location has been processed
};

int main() {
    struct head h[33]; // Array to hold disk locations
    int array_1[33], array_2[33]; // Arrays to hold seek distances
    int count = 0, j, x, limit, minimum, location, disk_head, sum = 0;
    int INT_MAX;
     printf("Lab 10.2(SSTF):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    printf("\nEnter total number of locations (max 33): ");
    scanf("%d", &limit);

    // Check for valid limit
    if (limit <= 0 || limit > 33) {
        printf("Invalid number of locations. Please enter a number between 1 and 33.\n");
        return 1; // Exit if the limit is invalid
    }

    printf("\nEnter position of disk head: ");
    scanf("%d", &disk_head);

    printf("\nEnter elements of disk head queue:\n");
    while (count < limit) {
        scanf("%d", &h[count].num);
        h[count].flag = 0; // Initialize flag to 0
        count++;
    }

    // Disk scheduling algorithm
    for (count = 0; count < limit; count++) {
        x = 0;
        minimum = INT_MAX; // Initialize minimum to maximum integer value
        location = 0;

        for (j = 0; j < limit; j++) {
            if (h[j].flag == 0) {
                // Calculate the seek distance
                array_1[j] = abs(disk_head - h[j].num); // Use abs() to get absolute value

                // Find the minimum seek distance and its location
                if (minimum > array_1[j]) {
                    minimum = array_1[j];
                    location = j;
                }
            }
        }

        // Mark the location as processed
        h[location].flag = 1;
        array_2[count] = minimum; // Store the seek time
        disk_head = h[location].num; // Move the disk head to the new location
    }

    // Calculate total seek time
    for (count = 0; count < limit; count++) {
        sum += array_2[count];
    }

    printf("\nTotal seek time: %d\n", sum);

    return 0; // Return success
}