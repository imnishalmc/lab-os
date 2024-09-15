#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 200 // Define maximum disk size

int cmpfunc(const void *a, const void *b);

void SCAN(int arr[], int size, int head, char *direction) {
    int seek_count = 0;
    int distance, cur_track;
    int left[MAX_SIZE], right[MAX_SIZE];
    int left_count = 0, right_count = 0;

    // Separate requests into left and right based on the head position
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[left_count++] = arr[i];
        else if (arr[i] > head)
            right[right_count++] = arr[i];
    }

    // Sort the left and right arrays
    qsort(left, left_count, sizeof(int), cmpfunc);
    qsort(right, right_count, sizeof(int), cmpfunc);

    int seek_sequence[size];
    int sequence_count = 0;

    // If the direction is left, process left requests first
    if (strcmp(direction, "left") == 0) {
        // Serve left requests
        for (int i = left_count - 1; i >= 0; i--) {
            cur_track = left[i];
            seek_sequence[sequence_count++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        // After finishing left, go to the end of the disk and then serve right requests
        seek_count += abs(head - 0); // Move to the start of the disk
        head = 0;

        // Serve right requests
        for (int i = 0; i < right_count; i++) {
            cur_track = right[i];
            seek_sequence[sequence_count++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    } 
    // If the direction is right, process right requests first
    else if (strcmp(direction, "right") == 0) {
        // Serve right requests
        for (int i = 0; i < right_count; i++) {
            cur_track = right[i];
            seek_sequence[sequence_count++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
        // After finishing right, go to the end of the disk and then serve left requests
        seek_count += abs(head - MAX_SIZE); // Move to the end of the disk
        head = MAX_SIZE;

        // Serve left requests
        for (int i = left_count - 1; i >= 0; i--) {
            cur_track = left[i];
            seek_sequence[sequence_count++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    }

    printf("Total number of seek operations = %d\n", seek_count);
    printf("Seek sequence: ");
    for (int i = 0; i < sequence_count; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n");
}

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, head;
     printf("Lab 10.3(SCAN):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the head position: ");
    scanf("%d", &head);

    char direction[10];
    printf("Enter the direction (left/right): ");
    scanf("%s", direction);

    SCAN(arr, n, head, direction);

    return 0;
}