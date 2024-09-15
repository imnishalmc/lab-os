#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 8
#define MAX_BLOCKS 8
#define BLOCK_SIZE 4 // Each block can hold 4 bytes of dat
typedef struct {
    int size; // Size of the file
    int blocks[MAX_BLOCKS]; // Pointers to the data blocks
} Inode;
typedef struct {
    int isFree; // 1 if the block is free, 0 if allocated
    char data[BLOCK_SIZE]; // Data stored in the block
} Block;
Inode inodeTable[MAX_FILES]; // Table of inodes
Block disk[MAX_BLOCKS]; // Simulated disk
void initialize() {
    for (int i = 0; i < MAX_FILES; i++) {
        inodeTable[i].size = 0;
        memset(inodeTable[i].blocks, -1, sizeof(inodeTable[i].blocks)); // Initialize pointers to -1
    }
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i].isFree = 1; // All blocks are initially free
        memset(disk[i].data, 0, sizeof(disk[i].data)); // Initialize block data to 0
    }
}
int allocateFile(int fileSize) {
    if (fileSize > MAX_BLOCKS) {
        printf("File size exceeds maximum blocks available.\n");
        return -1;
    }
    int blocksNeeded = (fileSize + BLOCK_SIZE - 1) / BLOCK_SIZE; // Calculate number of blocks needed
    int startBlock = -1;
    int count = 0;
    // Find free blocks
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i].isFree) {
            if (startBlock == -1) {
                startBlock = i; // Mark the start of the file
            }
            count++;
            if (count == blocksNeeded) {
                break; // Found enough free blocks
            }
        } else {
            startBlock = -1; // Reset if a block is occupied
            count = 0; // Reset count
        }
    }
    // Allocate the blocks if enough free blocks are found
    if (count == blocksNeeded) {
        int inodeIndex = -1;
        for (int i = 0; i < MAX_FILES; i++) {
            if (inodeTable[i].size == 0) { // Find an empty inode
                inodeIndex = i;
                break;
            }
        }
        if (inodeIndex == -1) {
            printf("No available inodes to allocate the file.\n");
            return -1;
        }
        inodeTable[inodeIndex].size = fileSize;
        for (int i = startBlock; i < startBlock + blocksNeeded; i++) {
            disk[i].isFree = 0; // Mark the block as allocated
            inodeTable[inodeIndex].blocks[i - startBlock] = i; // Store the block number in the inode
        }
        printf("File allocated with inode index %d, starting at block %d\n", inodeIndex, startBlock);
        return inodeIndex; // Return the inode index
    } else {
        printf("Not enough space to allocate the file.\n");
        return -1;
    }
}
void deallocateFile(int inodeIndex) {
    if (inodeIndex < 0 || inodeIndex >= MAX_FILES || inodeTable[inodeIndex].size == 0) {
        printf("Invalid inode index.\n");
        return;
    }
    for (int i = 0; i < MAX_BLOCKS && inodeTable[inodeIndex].blocks[i] != -1; i++) {
        int blockIndex = inodeTable[inodeIndex].blocks[i];
        disk[blockIndex].isFree = 1; // Mark the block as free
        inodeTable[inodeIndex].blocks[i] = -1; // Clear the block pointer
    }
    inodeTable[inodeIndex].size = 0; // Clear the inode
    printf("File with inode index %d deallocated.\n", inodeIndex);
}
void displayInodes() {
    printf("Inode Table:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (inodeTable[i].size > 0) {
            printf("Inode %d: Size = %d, Blocks = ", i, inodeTable[i].size);
            for (int j = 0; j < MAX_BLOCKS && inodeTable[i].blocks[j] != -1; j++) {
                printf("%d ", inodeTable[i].blocks[j]);
            }
            printf("\n");
        }
    }
}
int main() {
    initialize(); // Initialize the file system
printf("Lab 8.4(File Allocation using inode):\n");
    printf("Name: Nisha Lamichhane\n");
    printf("Roll No: 21 \t\t\t Section: 'A'\n");
    int choice, fileSize, inodeIndex;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Allocate File\n");
        printf("2. Deallocate File\n");
        printf("3. Display Inodes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the size of the file to allocate: ");
                scanf("%d", &fileSize);
                allocateFile(fileSize);
                break;
            case 2:
                printf("Enter the inode index of the file to deallocate: ");
                scanf("%d", &inodeIndex);
                deallocateFile(inodeIndex);
                break;
            case 3:
                displayInodes();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}