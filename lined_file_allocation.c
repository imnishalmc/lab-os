#include <stdio.h>
#include <stdlib.h>

void recursivePart(int pages[]) {
    int st, len, k, c, j;
    printf("Enter the index of the starting block and its length: ");
    scanf("%d%d", &st, &len);

    // Check if starting index is valid
    if (st < 0 || st >= 50 || len < 1 || (st + len) > 50) {
        printf("Invalid starting block or length. Please try again.\n");
        recursivePart(pages);
        return;
    }

    k = len;

    // Check if the starting block is free
    if (pages[st] == 0) {
        for (j = st; j < (st + k); j++) {
            if (pages[j] == 0) {
                pages[j] = 1; // Allocate the block
                printf("Block %d allocated.\n", j);
            } else {
                printf("The block %d is already allocated.\n", j);
                k++; // Increase length to skip the already allocated block
            }
        }
        printf("The file is allocated to the disk.\n");
    } else {
        printf("The block %d is already allocated.\n", st);
    }

    // Ask if the user wants to enter more files
    printf("Do you want to enter more files? \n");
    printf("Enter 1 for Yes, Enter 0 for No: ");
    scanf("%d", &c);
    if (c == 1)
        recursivePart(pages);
    else
        exit(0);
}

int main() {
    int pages[50], p, a;

    // Initialize all blocks to 0 (free)
    for (int i = 0; i < 50; i++)
        pages[i] = 0;
  printf("Lab 8.2(linked file allocation):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    printf("Enter the number of blocks already allocated: ");
    scanf("%d", &p);
    if (p != 0) {
        printf("Enter the blocks already allocated (0-49): ");
        for (int i = 0; i < p; i++) {
            scanf("%d", &a);
            // Check for valid allocation
            if (a >= 0 && a < 50) {
                pages[a] = 1; // Mark the block as allocated
            } else {
                printf("Invalid block number %d. Please enter a number between 0 and 49.\n", a);
                i--; // Decrement to re-enter the invalid block
            }
        }
    }

    recursivePart(pages);
    return 0;
}