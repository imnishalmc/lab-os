#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

typedef struct {
    int page;
    int frequency;
} page_info;

int compare(const void *a, const void *b) {
    page_info *p1 = (page_info *)a;
    page_info *p2 = (page_info *)b;
    return p1->frequency - p2->frequency; // Sort by frequency in ascending order
}

void lfu_page_replacement(int pages[], int num_pages, int num_frames) {
    page_info *frames = (page_info *)malloc(num_frames * sizeof(page_info));
    int i, j, page_faults = 0;

    // Initialize frames
    for (i = 0; i < num_frames; i++) {
        frames[i].page = -1;
        frames[i].frequency = 0;
    }

    for (i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (j = 0; j < num_frames; j++) {
            if (frames[j].page == page) {
                frames[j].frequency++; // Increment frequency
                found = 1;
                break;
            }
        }

        // If the page was not found, we have a page fault
        if (!found) {
            page_faults++;

            // Find the frame with the lowest frequency
            int lfu_frame = -1;
            for (j = 0; j < num_frames; j++) {
                if (frames[j].page == -1) { // If there's an empty frame
                    lfu_frame = j;
                    break;
                }
                if (lfu_frame == -1 || frames[j].frequency < frames[lfu_frame].frequency) {
                    lfu_frame = j; // Update the least frequently used frame
                }
            }

            // Replace the page in the least frequently used frame
            frames[lfu_frame].page = page;
            frames[lfu_frame].frequency = 1; // Reset frequency for the new page
        }

        // Display current frames
        printf("Current Frames: ");
        for (j = 0; j < num_frames; j++) {
            if (frames[j].page != -1) {
                printf("%d ", frames[j].page);
            }
        }
        printf(" | Page Faults: %d\n", page_faults);
    }

    printf("Total Page Faults: %d\n", page_faults);
    free(frames);
}

int main() {
    printf("Lab 7.5 (LFU Page Replacement Algorithm):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    
    int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 8, 3, 2, 1};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    int num_frames = 3;

    lfu_page_replacement(pages, num_pages, num_frames);

    return 0;
}