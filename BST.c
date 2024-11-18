#include <stdio.h>
#include <stdlib.h>

struct node {
    int element;
    struct node *left;
    struct node *right;
};

typedef struct node* Tree;

Tree makeEmpty(Tree T) {
    if(T !=NULL) {
        makeEmpty(T->right);
        makeEmpty(T->left);
        free(T);
    }
    return NULL;
}

Tree find(Tree T,int X) {
    if(T==NULL) {
        printf("Empty Tree\n");
        return NULL;
    }
    else {
        if(X<T->element) {
            return find(T->left,X);
        }
        else if(X>T->element) {
            return find(T->right,X);
        }
        else {
            return T;
        }
    }
}

Tree FindMin(Tree T) {
    if(T==NULL) {
        return NULL;
    }
    else {
        if(T->left==NULL) {
            return T;
        }
        else {
            return FindMin(T->left);
        }
    }
}

Tree FindMax(Tree T) {
    if(T==NULL) {
        return NULL;
    }
    else {
        if(T->right==NULL) {
            return T;
        }
        else {
            return FindMax(T->right);
        }
    }
}

Tree insert(Tree T, int X) {
    if(T==NULL) {
        Tree newNode = (Tree)malloc(sizeof(struct node));
        if(newNode==NULL) {
            printf("Memory Allocation Failed\n");
            return NULL;
        }
        newNode->element = X;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if(X < T->element) {
        T->left = insert(T->left,X);
    }
    else if(X > T->element) {
        T->right = insert(T->right,X);
    }
    return T;
}

Tree delete(Tree T, int X){
    if(T==NULL) {
        printf("Empty Tree\n");
        return NULL;
    }
    if(X < T->element) {
        T->left = delete(T->left,X);
    }
    else if(X > T->element) {
        T->right = delete(T->right,X);
    }
    else {
        if(T->left == NULL) {
            Tree temp = T->right;
            free(T);
            return temp;
        }
        else if(T->right==NULL) {
            Tree temp=T->left;
            free(T);
            return temp;
        }
        else {
            Tree temp = FindMin(T->right);
            T->element = temp->element;
            T->right = delete(T->right,temp->element);
        }
    }
    return T;
}

int findKthSmallest(Tree T, int k, int *count) {
    if (T == NULL) {
        return -1;
    }
    int left = findKthSmallest(T->left, k, count);
    if (left != -1) {
        return left;
    }
    (*count)++;
    if (*count == k) {
        return T->element;
    }
    return findKthSmallest(T->right, k, count);
}

int kthSmallest(Tree T, int k) {
    int count = 0;
    return findKthSmallest(T, k, &count);
}


// Function to print tree in in-order traversal
void inOrder(Tree T) {
    if (T != NULL) {
        inOrder(T->left);
        printf("%d ", T->element);
        inOrder(T->right);
    }
}

// Function to print tree in pre-order traversal
void preOrder(Tree T) {
    if (T != NULL) {
        printf("%d ", T->element);
        preOrder(T->left);
        preOrder(T->right);
    }
}

// Function to print tree in post-order traversal
void postOrder(Tree T) {
    if (T != NULL) {
        postOrder(T->left);
        postOrder(T->right);
        printf("%d ", T->element);
    }
}

int main() {
    int nodes,k;
    Tree T = NULL;
    makeEmpty(T);
    printf("Enter The Number Of Nodes\n");
    scanf("%d",&nodes);
    while(nodes!=0) {
        int N;
        printf("Enter The Element\n");
        scanf("%d",&N);
        T = insert(T,N);
        nodes--;
    }

    inOrder(T);
    printf("\n");

    printf("Minimum element: %d\n", FindMin(T)->element);
    printf("Maximum element: %d\n", FindMax(T)->element);

    int deleteElement;
    printf("Enter an element to delete: ");
    scanf("%d",&deleteElement);
    T= delete(T,deleteElement);

    printf("Tree after deletion:\n");
    inOrder(T);

    printf("\nEnter the position: \n");
    scanf("%d",&k);
    int result = kthSmallest(T, k);
    if (result == -1) {
        printf("Invalid value of k or the tree is empty.\n");
    } else {
        printf("The %d-th smallest element is: %d\n", k, result);
    }
}