#include<stdio.h>
#include<stdlib.h>
struct node {
    int data;
    struct node *next;
};
typedef struct node* node_ptr;
typedef node_ptr Position;
typedef node_ptr List;

int is_last(Position P,List L) {
    return(P->next==NULL);
}
Position find(int X,List L) {
    Position P;
    P = L->next;
    while((P!=NULL) && (P->data!=X)) {
        P=P->next;
    }
    return(P);
}

void insert(int X, List L, Position P) {
    Position tmp_cell;
    tmp_cell = (Position)malloc(sizeof(List));
    if(tmp_cell == NULL) {
        printf("Memory allocation failed in insert()\n");
    }
    else {
        tmp_cell->data = X;
        tmp_cell->next = P->next;
        P->next = tmp_cell;
    }
}

List find_previous(int X, List L) {
    Position P;
    P=L;
    while((P!=NULL) && (P->next->data!=X)) {
        P=P->next;
    }
    return P;
}

void delete(int X, List L){
    Position P;
    Position tmp_cell;
    P = find_previous(X,L);
    if(P->next != NULL) {
        tmp_cell = P->next;
        P->next = tmp_cell->next;
        free(tmp_cell);
    }
}

int main() {
    List L = (List)malloc(sizeof(struct node));
    if (L == NULL) {
        printf("Memory allocation failed for header node\n");
        return 1;
    }
    L->next = NULL;

    insert(10, L, L);
    insert(20, L, L->next);
    insert(30, L, L->next->next);

    printf("List contents after insertion: ");
    Position P = L->next;
    while (P != NULL) {
        printf("%d ", P->data);
        P = P->next;
    }
    printf("\n");

    int target = 20;
    Position found = find(target, L);
    if (found != NULL) {
        printf("Element %d found in the list.\n", target);
    } else {
        printf("Element %d not found in the list.\n", target);
    }

    printf("Deleting element %d...\n", target);
    delete(target, L);

    printf("List contents after deletion: ");
    P = L->next;
    while (P != NULL) {
        printf("%d ", P->data);
        P = P->next;
    }
    printf("\n");

    P = L;
    while (P != NULL) {
        Position tmp = P->next;
        free(P);
        P = tmp;
    }

    return 0;
}