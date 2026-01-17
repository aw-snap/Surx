#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    void *value;
    struct _Node *next;
    struct _Node *prev;
    int len;
} Node;

void appendNode(Node **head, void *value, int len);

void appendNode(Node **head, void *value, int len) {
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        printf("Node allocation failed!\n");
        exit(1);
    }

    //*newNode = (Node){0}; // Replaced by calloc
    newNode->value = value;
    newNode->len = len;
    //newNode->next = NULL; // Replaced by calloc

    if (*head == NULL) {
        //newNode->prev = NULL; // Replaced by calloc
        *head = newNode;
        return;
    }

    Node *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    newNode->prev = current;
    current->next = newNode;

    return;
}

int main(void) {
    char *x = "h";
    char *y = "e";
    char *z = "l";

    Node *head = NULL;

    appendNode(&head, x, 1);
    appendNode(&head, y, 1);
    appendNode(&head, z, 1);

    printf("%s", (char*)head->value);
    printf("%s", (char*)head->next->value);
    printf("%s", (char*)head->next->next->value);
    printf("%s", (char*)head->next->next->prev->value);

    return 0;
}
