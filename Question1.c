#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for Doubly Linked List
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Doubly Linked List structure
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Function prototypes
Node* createNode(int data);
void initList(DoublyLinkedList* list);
void insertFront(DoublyLinkedList* list, int data);
void insertRear(DoublyLinkedList* list, int data);
int deleteFront(DoublyLinkedList* list);
int deleteRear(DoublyLinkedList* list);
bool searchElement(DoublyLinkedList* list, int key);
void displayForward(DoublyLinkedList* list);
void displayReverse(DoublyLinkedList* list);
void freeList(DoublyLinkedList* list);

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Initialize an empty list
void initList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Insert at the front of the list - O(1) time complexity
void insertFront(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    
    if (list->head == NULL) {
        // If list is empty, set both head and tail
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Link the new node before the current head
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    
    list->size++;
}

// Insert at the rear of the list - O(1) time complexity
void insertRear(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    
    if (list->tail == NULL) {
        // If list is empty, set both head and tail
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Link the new node after the current tail
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
    list->size++;
}

// Delete from the front of the list - O(1) time complexity
int deleteFront(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    Node* temp = list->head;
    int data = temp->data;
    
    // Update head
    list->head = list->head->next;
    
    if (list->head == NULL) {
        // If list becomes empty
        list->tail = NULL;
    } else {
        // Remove previous link
        list->head->prev = NULL;
    }
    
    free(temp);
    list->size--;
    return data;
}

// Delete from the rear of the list - O(1) time complexity
int deleteRear(DoublyLinkedList* list) {
    if (list->tail == NULL) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    Node* temp = list->tail;
    int data = temp->data;
    
    // Update tail
    list->tail = list->tail->prev;
    
    if (list->tail == NULL) {
        // If list becomes empty
        list->head = NULL;
    } else {
        // Remove next link
        list->tail->next = NULL;
    }
    
    free(temp);
    list->size--;
    return data;
}

// Search an element in the list - O(n) time complexity
bool searchElement(DoublyLinkedList* list, int key) {
    Node* current = list->head;
    
    while (current != NULL) {
        if (current->data == key) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// Display list in forward direction - O(n) time complexity
void displayForward(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    printf("Forward List: ");
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Display list in reverse direction - O(n) time complexity
void displayReverse(DoublyLinkedList* list) {
    if (list->tail == NULL) {
        printf("List is empty\n");
        return;
    }
    
    printf("Reverse List: ");
    Node* current = list->tail;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

// Free all memory allocated for the list
void freeList(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Main function to demonstrate Doubly Linked List operations
int main() {
    DoublyLinkedList list;
    initList(&list);
    
    // Demonstration of operations
    printf("Inserting elements at front and rear\n");
    insertFront(&list, 10);
    insertRear(&list, 20);
    insertFront(&list, 5);
    insertRear(&list, 30);
    
    // Display list
    displayForward(&list);
    displayReverse(&list);
    
    // Search demonstration
    int searchKey = 20;
    printf("\nSearching for %d: %s\n", 
           searchKey, 
           searchElement(&list, searchKey) ? "Found" : "Not Found");
    
    // Deletion demonstration
    printf("\nDeleting front element: %d\n", deleteFront(&list));
    printf("Deleting rear element: %d\n", deleteRear(&list));
    
    // Display after deletion
    displayForward(&list);
    displayReverse(&list);
    
    // Free the list
    freeList(&list);
    
    return 0;
}