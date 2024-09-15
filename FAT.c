#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 5  // Maximum number of blocks in the disk

// Function to initialize the file allocation table
void initializeFAT(int fat[], int size) {
    for (int i = 0; i < size; i++) {
        fat[i] = -1; // -1 indicates that the block is free
    }
}

// Function to allocate a file
void allocateFile(int fat[], int fileSize) {
    int startBlock = -1;
    int count = 0;

    // Find free blocks
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (fat[i] == -1) {
            if (startBlock == -1) {
                startBlock = i; // Mark the start of the file
            }
            count++;
            if (count == fileSize) {
                break; // Found enough free blocks
            }
        } else {
            startBlock = -1; // Reset if a block is occupied
            count = 0; // Reset count
        }
    }

    // Allocate the blocks if enough free blocks are found
    if (count == fileSize) {
        for (int i = startBlock; i < startBlock + fileSize; i++) {
            fat[i] = startBlock; // Link the blocks
        }
        printf("File allocated from block %d to block %d\n", startBlock, startBlock + fileSize - 1);
    } else {
        printf("Not enough space to allocate the file of size %d\n", fileSize);
    }
}

// Function to deallocate a file
void deallocateFile(int fat[], int startBlock) {
    for (int i = startBlock; i < MAX_BLOCKS && fat[i] != -1; i++) {
        fat[i] = -1; // Mark the blocks as free
    }
    printf("File deallocated starting from block %d\n", startBlock);
}

// Function to display the FAT
void displayFAT(int fat[]) {
    printf("Block Allocation Table:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Block %d: %d\n", i, fat[i]);
    }
}

int main() {
    int fat[MAX_BLOCKS];
    initializeFAT(fat, MAX_BLOCKS); // Initialize the FAT
printf("Lab 8.3(File Allocation Table):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    int choice, fileSize, startBlock;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Allocate File\n");
        printf("2. Deallocate File\n");
        printf("3. Display FAT\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size of the file to allocate: ");
                scanf("%d", &fileSize);
                allocateFile(fat, fileSize);
                break;
            case 2:
                printf("Enter the starting block of the file to deallocate: ");
                scanf("%d", &startBlock);
                deallocateFile(fat, startBlock);
                break;
            case 3:
                displayFAT(fat);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}