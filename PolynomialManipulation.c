#include <stdio.h>
#include <stdlib.h>

struct PolyNode {
    int coefficient;
    int exponent;
    struct PolyNode *next;
};

typedef struct PolyNode* PolyNodePtr;

PolyNodePtr createNode(int coef, int exp) {
    PolyNodePtr new_node = (PolyNodePtr)malloc(sizeof(struct PolyNode));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    new_node->coefficient = coef;
    new_node->exponent = exp;
    new_node->next = NULL;
    return new_node;
}

PolyNodePtr insertTerm(PolyNodePtr head, int coef, int exp) {
    PolyNodePtr new_node = createNode(coef, exp);
    if (head == NULL || head->exponent < exp) {
        new_node->next = head;
        return new_node;
    }

    PolyNodePtr temp = head;
    while (temp->next != NULL && temp->next->exponent >= exp) {
        temp = temp->next;
    }

    new_node->next = temp->next;
    temp->next = new_node;
    return head;
}

void printPolynomial(PolyNodePtr head) {
    PolyNodePtr temp = head;
    while (temp != NULL) {
        if (temp->coefficient > 0 && temp != head) {
            printf(" + ");
        }
        printf("%dx^%d", temp->coefficient, temp->exponent);
        temp = temp->next;
    }
    printf("\n");
}

PolyNodePtr addPolynomials(PolyNodePtr poly1, PolyNodePtr poly2) {
    PolyNodePtr result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            result = insertTerm(result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            result = insertTerm(result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int coef_sum = poly1->coefficient + poly2->coefficient;
            if (coef_sum != 0) {
                result = insertTerm(result, coef_sum, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        result = insertTerm(result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        result = insertTerm(result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}

PolyNodePtr subtractPolynomials(PolyNodePtr poly1, PolyNodePtr poly2) {
    PolyNodePtr result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            result = insertTerm(result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            result = insertTerm(result, -poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int coef_diff = poly1->coefficient - poly2->coefficient;
            if (coef_diff != 0) {
                result = insertTerm(result, coef_diff, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        result = insertTerm(result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        result = insertTerm(result, -poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}


PolyNodePtr multiplyPolynomials(PolyNodePtr poly1, PolyNodePtr poly2) {
    PolyNodePtr result = NULL;
    PolyNodePtr temp_poly2 = poly2;

    while (poly1 != NULL) {
        while (temp_poly2 != NULL) {
            int coef_product = poly1->coefficient * temp_poly2->coefficient;
            int exp_sum = poly1->exponent + temp_poly2->exponent;
            result = insertTerm(result, coef_product, exp_sum);
            temp_poly2 = temp_poly2->next;
        }
        poly1 = poly1->next;
        temp_poly2 = poly2;
    }

    return result;
}

int main() {
    PolyNodePtr poly1 = NULL;
    PolyNodePtr poly2 = NULL;

    poly1 = insertTerm(poly1, 3, 4); // 3x^4
    poly1 = insertTerm(poly1, 5, 2); // 5x^2
    poly1 = insertTerm(poly1, 6, 0); // 6x^0

    poly2 = insertTerm(poly2, 4, 3); // 4x^3
    poly2 = insertTerm(poly2, 5, 2); // 5x^2
    poly2 = insertTerm(poly2, -1, 1); // -x^1

    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);

    PolyNodePtr sum = addPolynomials(poly1, poly2);
    printf("Sum: ");
    printPolynomial(sum);

    PolyNodePtr diff = subtractPolynomials(poly1, poly2);
    printf("Difference: ");
    printPolynomial(diff);

    PolyNodePtr product = multiplyPolynomials(poly1, poly2);
    printf("Product: ");
    printPolynomial(product);

    return 0;
}

