// #include <stdio.h>
// #include <stdlib.h>

// #define SIZE 16

// typedef struct {
//     int size;       // Size of the bitmap
//     int *bitmap;    // Pointer to the bitmap array
// } Bitmap;

// // Function to initialize the bitmap
// void initBitmap(Bitmap *bitmap, int size) {
//     bitmap->size = size;
//     bitmap->bitmap = (int *)malloc(sizeof(int) * size);
//     for (int i = 0; i < size; i++) {
//         bitmap->bitmap[i] = 0; // Set all blocks to free (0)
//     }
// }

// // Function to allocate blocks in the bitmap
// int allocate(Bitmap *bitmap, int blocks) {
//     int start = -1; // Start index of the free blocks
//     int count = 0;  // Count of consecutive free blocks

//     for (int i = 0; i < bitmap->size; i++) {
//         if (bitmap->bitmap[i] == 0) { // Check if the block is free
//             if (count == 0) {
//                 start = i; // Mark the start of free blocks
//             }
//             count++;

//             // Check if we have enough free blocks
//             if (count == blocks) {
//                 for (int j = start; j < start + blocks; j++) {
//                     bitmap->bitmap[j] = 1; // Mark blocks as allocated (1)
//                 }
//                 return start; // Return the starting index of allocated blocks
//             }
//         } else {
//             count = 0; // Reset count if a block is occupied
//         }
//     }
//     return -1; // Not enough free blocks available
// }

// // Function to deallocate blocks in the bitmap
// void deallocate(Bitmap *bitmap, int start, int blocks) {
//     for (int i = start; i < start + blocks; i++) {
//         bitmap->bitmap[i] = 0; // Mark blocks as free (0)
//     }
// }

// // Function to print the bitmap
// void printBitmap(Bitmap *bitmap) {
//     for (int i = 0; i < bitmap->size; i++) {
//         printf("%d ", bitmap->bitmap[i]);
//     }
//     printf("\n");
// }

// // Main function to demonstrate bitmap allocation and deallocation
// int main() {
//     printf("Lab 9.1(Free space management techniques):\n");
//     printf("Name: Nisha Lamichhane\n");
//     printf("Roll No: 21 \t\t\t Section: 'A'\n");
//     Bitmap bitmap;
//     initBitmap(&bitmap, SIZE); // Initialize the bitmap
//     printf("\nInitial Bitmap: ");
//     printBitmap(&bitmap);
//     // Allocate 3 blocks
//     int start = allocate(&bitmap, 3);
//     if (start != -1) {
//         printf("\nAllocated blocks at index %d\n", start);
//     } else {
//         printf("\nAllocation failed: Not enough free blocks.\n");
//     }
//     printf("Updated Bitmap: ");
//     printBitmap(&bitmap);

//     // Deallocate the previously allocated blocks
//     deallocate(&bitmap, start, 3);
//     printf("\nDeallocated blocks at index %d\n", start);
//     printf("Updated Bitmap: ");
//     printBitmap(&bitmap);

//     free(bitmap.bitmap); // Free the allocated memory for the bitmap

//     return 0;
// }

