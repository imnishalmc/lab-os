#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX_SIZE = 100; // Define a maximum size for the disk requests
// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
void LOOK(int arr[], int n, int head, char *direction) {
    int seek_count = 0;
    int distance, cur_track;
    int left[MAX_SIZE], right[MAX_SIZE];
    int left_size = 0, right_size = 0;
    // Appending values which are currently at left and right direction from the head.
    for (int i = 0; i < n; i++) {
        if (arr[i] < head)
            left[left_size++] = arr[i];
        else if (arr[i] > head)
            right[right_size++] = arr[i];
    }
    // Sorting left and right arrays for servicing tracks in the correct sequence.
    qsort(left, left_size, sizeof(int), compare);
    qsort(right, right_size, sizeof(int), compare);
    // Run the while loop two times, one by one scanning right and left side of the head.
    int run = 2; // We will run the loop twice: once for left and once for right
    while (run--) {
        if (strcmp(direction, "left") == 0) {
            // Service left requests
            for (int i = left_size - 1; i >= 0; i--) {
                cur_track = left[i];
                // Appending current track to seek sequence
                printf("%d ", cur_track);
                // Calculate absolute distance
                distance = abs(cur_track - head);
                // Increase the total count
                seek_count += distance;
                // Accessed track is now the new head
                head = cur_track;
            }
            // Reversing the direction
            strcpy(direction, "right");
        } else if (strcmp(direction, "right") == 0) {
            // Service right requests
            for (int i = 0; i < right_size; i++) {
                cur_track = right[i];
                // Appending current track to seek sequence
                printf("%d ", cur_track);
                // Calculate absolute distance
                distance = abs(cur_track - head);
                // Increase the total count
                seek_count += distance;
                // Acessed track is now the new head
                head = cur_track;
            }
            // Reversing the direction
            strcpy(direction, "left");
        }
    }
    printf("\nTotal number of seek operations = %d\n", seek_count);
}
// Driver code
int main() {
    int n, head;
     printf("Lab 10.5(LOOK:\n");
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
    char direction[10];
    printf("Enter the direction of head movement (left/right): ");
    scanf("%s", direction);
    LOOK(arr, n, head, direction);
    return 0; // Return success
}