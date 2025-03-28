#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyData {
    int nr;
    char* name;
} MyData;

typedef struct Node {
    struct MyData data;
    struct Node* next;
} Node;

void printList(struct Node* head) {
    while (head != NULL) {
        printf(" %s -> ", head->data.name);
        head = head->next;
    }
    printf("NULL\n");
}

void insertAtBeginning(struct Node** head, struct MyData d) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = d;
    newNode->data.name = (char*)malloc((strlen(d.name) + 1) * sizeof(char));
    strcpy_s(newNode->data.name, strlen(d.name) + 1, d.name);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct Node** head, MyData d) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = d;
    newNode->data.name = (char*)malloc((strlen(d.name) + 1) * sizeof(char));
    strcpy_s(newNode->data.name, strlen(d.name) + 1, d.name);
    newNode->next = NULL;
    if (*head) {
        Node* p = *head;
        while (p->next) {
            p = p->next;
        }
        p->next = newNode;
    }
    else {
        *head = newNode;
    }
}

void insertAtPosition(Node** head, MyData d, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = d;
    newNode->data.name = (char*)malloc((strlen(d.name) + 1) * sizeof(char));
    strcpy_s(newNode->data.name, strlen(d.name) + 1, d.name);
    newNode->next = NULL;
    if (position == 0) {
        insertAtBeginning(&head, d);
    }
    if (*head) {
        int i = 0;
        Node* p = *head;

        while (p->next != NULL && i < position - 1) {
            p = p->next;
            i++;
        }


        newNode->next = p->next;
        p->next = newNode;
    }
}

void deleteFromBeginning(Node** head) {
    Node* temp = *head;
    *head = (*head)->next;
    free(temp->data.name);
    free(temp);
}

void deleteFromPosition(Node** head, int position) {
    if (position == 0)
        deleteFromBeginning(head);
    else {
        Node* temp = *head;
        Node* prev = NULL;
        int i = 0;
        while (temp != NULL && i < position) {
            prev = temp;
            temp = temp->next;
            i++;
        }
        if (temp == NULL) {
            fprintf(stderr, "Index out of range\n");
            return;
        }
        prev->next = temp->next;
        free(temp->data.name);
        free(temp);
    }
}

void stergereLista(Node** head) {
    while (*head) {
        Node* p = *head;
        *head = (*head)->next;
        free(p->data.name);
        free(p);

    }
    printf("%s", "memory freed");
}

void saveToVector(Node* head, MyData** list, int* dim) {
    *dim = 0;
    Node* p = head;

    while (p) {
        if (p->data.nr > 25) {
            (*dim)++;
        }
        p = p->next;
    }
    *list = (MyData*)malloc((*dim) * sizeof(MyData));
    Node* temp = head;
    int i = 0;
    while (temp) {
        if (temp->data.nr > 25) {
            (*list)[i] = temp->data;
            (*list)[i].name = (char*)malloc((strlen(temp->data.name) + 1) * sizeof(char));
            strcpy_s((*list)[i].name, strlen(temp->data.name) + 1, temp->data.name);

            i++;
        }
        temp = temp->next;
    }   
}

void printVector(MyData* vector, int dim) {
    for (int i = 0; i < dim; i++) {
        printf("List[%i] : nr=%i, name=%s \n", i, vector[i].nr, vector[i].name);
    }
}


void swapNodes(Node* head, int pos1, int pos2) {
    if (pos1 == pos2) return;
    Node* n1 = NULL;
    Node* n2 = NULL;
    Node* temp = head;
    int index = 0;
    while (temp) {
        if (index == pos1)
            n1 = temp;
        if (index == pos2)
            n2 = temp;
        temp = temp->next;
        index++;
    }
    MyData aux = n1->data;
    aux.name = (char*)malloc((strlen(n1->data.name) + 1) * sizeof(char));
    strcpy_s(aux.name, strlen(n1->data.name) + 1, n1->data.name);

    free(n1->data.name);
    n1->data.nr = n2->data.nr;
    n1->data.name = (char*)malloc((strlen(n2->data.name) + 1)*sizeof(char));
    strcpy_s(n1->data.name, strlen(n2->data.name) + 1, n2->data.name);

    free(n2->data.name);
    n2->data.nr = aux.nr;
    n2->data.name = (char*)malloc((strlen(aux.name) + 1)* sizeof(char));
    strcpy_s(n2->data.name, strlen(aux.name) + 1, aux.name);

    free(aux.name);
}

int main() {
    struct MyData data1 = { 10, "Node1" };
    struct MyData data2 = { 20, "Node2" };
    struct MyData data3 = { 30, "Node3" };
    struct MyData data4 = { 40, "Node4" };
    struct MyData data5 = { 50, "Node5" };

    struct Node* head = NULL;
    
    insertAtEnd(&head, data1);
    insertAtEnd(&head, data2);

    insertAtEnd(&head, data4);
    insertAtEnd(&head, data5);

    insertAtPosition(&head, data3, 5);
    printList(head);
    //deleteFromPosition(&head,10);
    //printList(head);

    //stergereLista(&head);

    swapNodes(head, 1, 2);
    printList(head);

    //MyData* list = NULL;
    //int dim = 0;
    //saveToVector(head, &list, &dim);
    //printVector(list,dim);

    return 0;
}
