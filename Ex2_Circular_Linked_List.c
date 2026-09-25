#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Define the structure for a Circular Linked List
typedef struct {
    Node *head;
} CircularLinkedList;

// Initialize the Circular Linked List
void initCircularLinkedList(CircularLinkedList *list) {
    list->head = NULL;
}

// Function to add an element to the Circular Linked List
void addCircular(CircularLinkedList *list, int element) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = element;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        new_node->next = list->head;
    } else {
        Node *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = list->head;
    }
}

// Function to remove an element from the Circular Linked List
void removeCircular(CircularLinkedList *list, int element) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *current = list->head;
    Node *prev = NULL;

    do {
        if (current->data == element) {
            if (current == list->head && current->next == list->head) {
                // Only one node
                free(current);
                list->head = NULL;
                printf("Element %d removed\n", element);
                return;
            } else if (current == list->head) {
                // Removing head
                Node *last = list->head;
                while (last->next != list->head) {
                    last = last->next;
                }
                list->head = current->next;
                last->next = list->head;
                free(current);
                printf("Element %d removed\n", element);
                return;
            } else {
                prev->next = current->next;
                free(current);
                printf("Element %d removed\n", element);
                return;
            }
        }
        prev = current;
        current = current->next;
    } while (current != list->head);

    printf("Element %d not found\n", element);
}

// Function to display the Circular Linked List
void displayCircular(CircularLinkedList *list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *current = list->head;
    printf("Circular Linked List: ");
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(back to head)\n");
}

int main() {
    CircularLinkedList list;
    initCircularLinkedList(&list);
    int choice, element;

    while (1) {
        printf("\nCircular Linked List Menu:\n");
        printf("1. Add Element\n");
        printf("2. Remove Element\n");
        printf("3. Display List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to add: ");
                scanf("%d", &element);
                addCircular(&list, element);
                break;
            case 2:
                printf("Enter element to remove: ");
                scanf("%d", &element);
                removeCircular(&list, element);
                break;
            case 3:
                displayCircular(&list);
                break;
            case 4:
                // Free remaining nodes
                if (list.head != NULL) {
                    Node *current = list.head->next;
                    while (current != list.head) {
                        Node *temp = current;
                        current = current->next;
                        free(temp);
                    }
                    free(list.head);
                }
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
