#include <stdio.h>
#include <stdlib.h>

void recurse(int files[]) {
    int flag = 0, startBlock, len, j, ch;

    printf("Enter the starting block and the length of the files: ");
    scanf("%d%d", &startBlock, &len);

    // Check if the starting block and length are within bounds
    if (startBlock < 0 || startBlock >= 50 || len < 1 || (startBlock + len) > 50) {
        printf("Invalid starting block or length. Please try again.\n");
        recurse(files); // Ask for input again
        return;
    }

    // Check for available blocks
    for (j = startBlock; j < (startBlock + len); j++) {
        if (files[j] == 0)
            flag++;
    }

    // If enough blocks are available
    if (len == flag) {
        for (int k = startBlock; k < (startBlock + len); k++) {
            files[k] = 1; // Allocate the block
            printf("Block %d allocated.\n", k);
        }
        printf("The file is allocated to the disk.\n");
    } else {
        printf("The file is not allocated to the disk (not enough space).\n");
    }

    // Ask if the user wants to enter more files
    printf("Do you want to enter more files?\n");
    printf("Press 1 for YES, 0 for NO: ");
    scanf("%d", &ch);
    if (ch == 1)
        recurse(files);
    else
        exit(0);
}

int main() {
     printf("Lab 8.1(Contigeous file allocation):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    int files[50];
    for (int i = 0; i < 50; i++)
        files[i] = 0; // Initialize all blocks to 0 (free)

    printf("Files Allocated are :\n");
    recurse(files); // Start the recursive allocation process
    return 0;
}