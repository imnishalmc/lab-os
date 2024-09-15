#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200 // Define a maximum size for the disk requests

// Function prototype for compare
int compare(const void *a, const void *b);

// Function to perform C-LOOK on the request array starting from the given head
void CLOOK(int arr[], int n, int head) {
    int seek_count = 0;
    int distance, cur_track;
    int left[MAX_SIZE], right[MAX_SIZE];
    int left_count = 0, right_count = 0;

    // Separate requests into left and right based on the head position
    for (int i = 0; i < n; i++) {
        if (arr[i] < head) {
            left[left_count++] = arr[i];
        } else if (arr[i] > head) {
            right[right_count++] = arr[i];
        }
    }

    // Sorting left and right arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Service the requests on the right side of the head
    for (int i = 0; i < right_count; i++) {
        cur_track = right[i];

        // Calculate absolute distance
        distance = abs(cur_track - head);

        // Increase the total count
        seek_count += distance;

        // Accessed track is now the new head
        head = cur_track;
    }

    // Jump to the first track on the left
    if (left_count > 0) {
        seek_count += abs(head - left[0]);
        head = left[0];
    }

    // Now service the requests again which are left
    for (int i = 0; i < left_count; i++) {
        cur_track = left[i];

        // Calculate absolute distance
        distance = abs(cur_track - head);

        // Increase the total count
        seek_count += distance;

        // Accessed track is now the new head
        head = cur_track;
    }

    printf("Total number of seek operations = %d\n", seek_count);
}

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, head;
      printf("Lab 10.6(C-LOOK:\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    printf("Enter the number of queue requests: ");
    scanf("%d", &n);

    // Validate the number of requests
    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid number of requests. Please enter a number between 1 and %d.\n", MAX_SIZE);
        return 1; // Exit if the limit is invalid
    }

    int arr[n];
    printf("Enter the queue requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    CLOOK(arr, n, head);

    return 0; // Return success
}