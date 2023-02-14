#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

struct OrderedList {
    struct Node* head;
    struct Node* tail;
};

// Function prototypes
void displayAll(struct OrderedList* list);
void displayNth(struct OrderedList* list);
void appendHeadOrTail(struct OrderedList* list);
void appendNthPosition(struct OrderedList* list);
void deleteHeadOrTail(struct OrderedList* list);
void deleteNthNode(struct OrderedList* list);
void find(struct OrderedList* list);
void getNumberOfNodes(struct OrderedList* list);
void displayEven(struct OrderedList* list);
void displayOdd(struct OrderedList* list);
void reverseList(struct OrderedList* list); 


int main() {
    // Open the input file
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    // Read the number of nodes
    int n;
    if (fscanf(fp, "%d", &n) != 1) {
        printf("Error: Cannot read the number of nodes.\n");
        fclose(fp);
        return 1;
    }

    // Create the ordered list
    struct OrderedList list = { NULL, NULL };

    // Read the integers from the file and add them to the list
    for (int i = 0; i < n; i++) {
        int value;
        if (fscanf(fp, "%d", &value) != 1) {
            printf("Error: Cannot read node value.\n");
            fclose(fp);
            return 1;
        }

        // Check for duplicate values
        struct Node* node = list.head;
        while (node != NULL) {
            if (node->value == value) {
                printf("Error: Duplicate node value: %d.\n", value);
                fclose(fp);
                return 1;
            }
            node = node->next;
        }

        // Create a new node
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->next = NULL;
        new_node->prev = list.tail;

        // Add the new node to the tail of the list
        if (list.tail == NULL) {
            // The list is empty
            list.head = new_node;
            list.tail = new_node;
        } else {
            list.tail->next = new_node;
            list.tail = new_node;
        }
    }

    fclose(fp);

    // Display the menu and handle user choices
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display all nodes\n");
        printf("2. Display nth node\n");
        printf("3. Append a new node - Head or Tail? (H/T)\n");
        printf("4. Append a new node in the nth position\n");
        printf("5. Delete a node - Head or Tail? (H/T)\n");
        printf("6. Delete the nth node\n");
        printf("7. Find a node\n");
        printf("8. Get number of nodes\n");
        printf("9. Display even numbered nodes\n");
        printf("10. Display odd numbered nodes\n");
	      printf("11. Reverse the list\n"); 
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input.\n");
            choice = -1;
        }

        switch (choice) {
        case 1:
            displayAll(&list);
            break;
        case 2:
            displayNth(&list);
            break;
        case 3:
            appendHeadOrTail(&list);
            break;
        case 4:
            appendNthPosition(&list);
            break;
        case 5:
            deleteHeadOrTail(&list);
            break;
        case 6:
            deleteNthNode(&list);
            break;
        case 7:
            find(&list);
            break;
        case 8:
            getNumberOfNodes(&list);
            break;
        case 9:
            displayEven(&list);
            break;
        case 10:
            displayOdd(&list);
            break;
        case 11: 
	    reverseList(&list);
	    break; 
	case 0:
            // Exit the program
            break;
        default:
            printf("Error: Invalid choice.\n");
    }
} while (choice != 0);

// Free the memory used by the nodes
struct Node* node = list.head;
while (node != NULL) {
    struct Node* next_node = node->next;
    free(node);
    node = next_node;
}

return 0;
}

void displayAll(struct OrderedList* list) {
printf("List:\n");
struct Node* node = list->head;
while (node != NULL) {
printf("%d ", node->value);
node = node->next;
}
printf("\n");
}

void displayNth(struct OrderedList* list) {
printf("Enter n: ");
int n;
if (scanf("%d", &n) != 1 || n < 1) {
printf("Error: Invalid input.\n");
return;
}
struct Node* node = list->head;
for (int i = 1; i < n && node != NULL; i++) {
node = node->next;
}
if (node != NULL) {
printf("Node %d: %d\n", n, node->value);
} else {
printf("Error: Invalid node.\n");
}
}
void appendHeadOrTail(struct OrderedList* list) {
    printf("Enter H or T: ");
    char c;
    if (scanf(" %c", &c) != 1) {
        printf("Error: Invalid input.\n");
        return;
    }
    if (c == 'H') {
        if (list->head == NULL) {
            printf("Error: The list is empty.\n");
            return;
        }
        printf("Enter a value less than %d: ", list->head->value);
        int value;
        if (scanf("%d", &value) != 1 || value >= list->head->value) {
            printf("Error: Invalid input.\n");
            return;
        }
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->next = list->head;
        new_node->prev = NULL;
        list->head->prev = new_node;
        list->head = new_node;
    } else if (c == 'T') {
        if (list->tail == NULL) {
            printf("Error: The list is empty.\n");
            return;
        }
        printf("Enter a value greater than %d: ", list->tail->value);
        int value;
        if (scanf("%d", &value) != 1 || value <= list->tail->value) {
            printf("Error: Invalid input.\n");
            return;
        }
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->next = NULL;
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    } else {
        printf("Error: Invalid input.\n");
    }
    displayAll(list);
}

void appendNthPosition(struct OrderedList* list) {
    printf("Enter n: ");
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Error: Invalid input.\n");
        return;
    }
    struct Node* node = list->head;
    for (int i = 1; i < n - 1 && node != NULL; i++) {
        node = node->next;
    }
    if (node == NULL || node == list->tail) {
        printf("Error: Invalid position.\n");
        return;
    }
    printf("Node %d: %d\n", n - 1, node->value);
    printf("Node %d: %d\n", n + 1, node->next->value);
    printf("Enter a value between %d and %d: ", node->value, node->next->value);
    int value;
    if (scanf("%d", &value) != 1 || value <= node->value || value >= node->next->value) {
        printf("Error: Invalid input.\n");
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->next = node->next;
    new_node->prev = node;
    node->next->prev = new_node;
    node->next = new_node;
    displayAll(list);
}

void deleteHeadOrTail(struct OrderedList* list) {
    printf("Enter H or T: ");
    char c;
    if (scanf(" %c", &c) != 1) {
        printf("Error: Invalid input.\n");
        return;
    }
    if (c == 'H') {
        if (list->head == NULL) {
            printf("Error: The list is empty.\n");
            return;
        }
        struct Node* node = list->head;
        list->head = node->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
        free(node);
    } else if (c == 'T') {
        if (list->tail == NULL) {
            printf("Error: The list is empty.\n");
            return;
        }
        struct Node* node = list->tail;
        list->tail = node->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
        free(node);
    } else {
        printf("Error: Invalid input.\n");
    }
    displayAll(list);
}

void deleteNthNode(struct OrderedList* list) {
    printf("Enter n: ");
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Error: Invalid input.\n");
        return;
    }
    struct Node* node = list->head;
    for (int i = 1; i < n && node != NULL; i++) {
        node = node->next;
    }
    if (node == NULL) {
        printf("Error: Invalid node.\n");
        return;
    }
    if (node == list->head) {
        list->head = node->next;
    }
    if (node == list->tail) {
        list->tail = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    free(node);
    displayAll(list);
}

void find(struct OrderedList* list) {
    printf("Enter a value to find: ");
    int value;
    if (scanf("%d", &value) != 1) {
        printf("Error: Invalid input.\n");
        return;
    }
    struct Node* node = list->head;
    while (node != NULL && node->value < value) {
        node = node->next;
    }
    if (node != NULL && node->value == value) {
        printf("Node with value %d found.\n", value);
    } else {
        printf("Node with value %d not found.\n", value);
    }
}

void getNumberOfNodes(struct OrderedList* list) {
    int count = 0;
    struct Node* node = list->head;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    printf("Number of nodes: %d\n", count);
}

void displayEven(struct OrderedList* list) {
    printf("Even nodes: ");
    struct Node* node = list->head;
    int i = 1;
    while (node != NULL) {
        if (i % 2 == 0) {
            printf("%d ", node->value);
        }
        node = node->next;
        i++;
    }
    printf("\n");
}

void displayOdd(struct OrderedList* list) {
    printf("Odd numbered nodes: ");
    struct Node* node = list->head;
    int i = 1;
    while (node != NULL) {
        if (i % 2 != 0) {
            printf("%d ", node->value);
        }
        node = node->next;
        i++;
    }
    printf("\n");
}

void reverseList(struct OrderedList* list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }
    struct Node* current = list->head;
    struct Node* previous = NULL;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    list->tail = list->head;
    list->head = previous;
    printf("List reversed!\n");
}
