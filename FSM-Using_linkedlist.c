#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int start;       // Starting index of the free block
    int end;         // Ending index of the free block
    struct Node *next; // Pointer to the next node
} Node;

typedef struct {
    int size;       // Total size of the memory
    Node *head;     // Head of the linked list
} LinkedList;

// Function to initialize the linked list with a single node representing the entire memory
void initLinkedList(LinkedList *list, int size) {
    list->size = size;
    list->head = (Node *)malloc(sizeof(Node));
    list->head->start = 0;
    list->head->end = size - 1;
    list->head->next = NULL;
}

// Function to allocate blocks in the linked list
int allocate(LinkedList *list, int blocks) {
    Node *curr = list->head;
    Node *prev = NULL;

    while (curr) {
        // Check if there is enough space in the current block
        if (curr->end - curr->start + 1 >= blocks) {
            int allocatedStart = curr->start; // Starting index of allocated blocks
            
            // If the exact number of blocks is available
            if (curr->end - curr->start + 1 == blocks) {
                // Remove the current node
                if (prev) {
                    prev->next = curr->next; // Link previous node to next
                } else {
                    list->head = curr->next; // Update head if it's the first node
                }
                free(curr); // Free the current node
            } else { // If there is excess space
                curr->start += blocks; // Move the start index forward
            }
            return allocatedStart; // Return the starting index of allocated blocks
        }
        prev = curr;
        curr = curr->next; // Move to the next node
    }
    return -1; // Not enough space available
}

// Function to deallocate blocks in the linked list
void deallocate(LinkedList *list, int start, int blocks) {
    Node *curr = list->head;
    Node *prev = NULL;

    // Create a new node for the deallocated block
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->start = start;
    newNode->end = start + blocks - 1;
    newNode->next = NULL;

    // Find the correct position to insert the new node
    while (curr && curr->start < start) {
        prev = curr;
        curr = curr->next;
    }

    // Merge with the previous block if adjacent
    if (prev && prev->end + 1 == start) {
        prev->end += blocks; // Extend the previous block
        free(newNode); // Free the new node since we merged it
        newNode = prev; // Use the existing node
    } else {
        // Insert the new node in the correct position
        if (prev) {
            newNode->next = prev->next;
            prev->next = newNode;
        } else {
            newNode->next = list->head;
            list->head = newNode;
        }
    }

    // Merge with the next block if adjacent
    if (curr && curr->start - 1 == newNode->end) {
        newNode->end = curr->end; // Extend the new node
        newNode->next = curr->next; // Link to the next block
        free(curr); // Free the merged node
    }
}

// Function to print the linked list representing memory blocks
void printLinkedList(LinkedList *list) {
    Node *curr = list->head;
    while (curr) {
        printf("(%d, %d) -> ", curr->start, curr->end);
        curr = curr->next;
    }
    printf("NULL\n");
}

// Function to free the linked list memory
void freeLinkedList(LinkedList *list) {
    Node *curr = list->head;
    Node *next;

    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

// Main function to demonstrate allocation and deallocation
int main() {
    LinkedList list;
     printf("Lab 9.2(Free space management techniques using LL):\n");
     printf("Name: Nisha Lamichhane\n");
     printf("Roll No: 21 \t\t\t Section: 'A'\n");
    int size = 16; // Total size of memory
    initLinkedList(&list, size); // Initialize the linked list
    printf("Initial Linked List: ");
    printLinkedList(&list);

    int start = allocate(&list, 5); // Allocate 3 blocks
    if (start != -1) {
        printf("Allocated blocks at index %d\n", start);
    } else {
        printf("Allocation failed: Not enough free blocks.\n");
    }
    printf("Updated Linked List: ");
    printLinkedList(&list);

    deallocate(&list, start, 8); // Deallocate the previously allocated blocks
    printf("Deallocated blocks at index %d\n", start);
    printf("Updated Linked List: ");
    printLinkedList(&list);

    freeLinkedList(&list); // Free the linked list memory

    return 0;
}