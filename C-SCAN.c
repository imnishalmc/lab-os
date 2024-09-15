#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200 // Define maximum disk size

int cmpfunc(const void *a, const void *b);

void CSCAN(int arr[], int n, int head) {
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

    // Sort the left and right arrays
    qsort(left, left_count, sizeof(int), cmpfunc);
    qsort(right, right_count, sizeof(int), cmpfunc);

    // Move to the right and service requests
    for (int i = 0; i < right_count; i++) {
        cur_track = right[i];
        seek_count += abs(cur_track - head);
        head = cur_track;
    }

    // Move to the end of the disk and jump to the start
    seek_count += (MAX_SIZE - 1 - head); // Move to the end of the disk
    head = 0; // Jump to the start of the disk

    // Service left requests
    for (int i = 0; i < left_count; i++) {
        cur_track = left[i];
        seek_count += abs(cur_track - head);
        head = cur_track;
    }

    printf("Total number of seek operations = %d\n", seek_count);
}

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, head;
     printf("Lab 10.4(C-SCAN):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of requests must be greater than 0.\n");
        return 1; // Exit if the limit is invalid
    }

    int arr[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the head position: ");
    scanf("%d", &head);

    CSCAN(arr, n, head);

    return 0; // Return success
}