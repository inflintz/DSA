#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node* NodePtr;

NodePtr createNode(int new_data) {
    NodePtr new_node = (NodePtr)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

NodePtr insertAtEnd(NodePtr head_ref, int new_data) {
    NodePtr new_node = createNode(new_data);
    if (head_ref == NULL) {
        head_ref = new_node;
        return head_ref;
    }
    NodePtr last = head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    new_node->prev = last;
    return head_ref;
}

void printLL(NodePtr head_ref) {
    NodePtr temp = head_ref;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

NodePtr reverseLL(NodePtr head_ref) {
    NodePtr temp = NULL;
    NodePtr current = head_ref;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        head_ref = temp->prev;
    }
    return head_ref;
}

NodePtr joinLL(NodePtr list1, NodePtr list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    NodePtr last = list1;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = list2;
    list2->prev = last;
    return list1;
}

int main() {
    NodePtr head = NULL;
    for (int i = 0; i < 10; i++) {
        head = insertAtEnd(head, i);
    }
    printf("Original list:\n");
    printLL(head);

    head = reverseLL(head);
    printf("Reversed list:\n");
    printLL(head);

    NodePtr joined = joinLL(head, NULL); // For example, joining an empty list
    printf("Joined list:\n");
    printLL(joined);

    return 0;
}
