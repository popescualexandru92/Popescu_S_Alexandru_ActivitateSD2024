#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector

typedef struct NodeStack {
	Masina masina;
	struct NodeStack* next;
}NodeStack;

typedef struct Stack {
	NodeStack* top;
	int count;
}Stack;

Stack* createStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;
	stack->count = 0;
	return stack;
}


typedef struct NodeQueue {
	Masina masina;
	struct NodeQueue* next;
} NodeQueue;

typedef struct Queue{
	NodeQueue* front;
	NodeQueue* rear;
	int count;
} Queue;

Queue* createQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = queue->rear = NULL;
	queue->count = 0;
	return queue;
}

void pushStack(Stack* stack, Masina masina) {
	NodeStack* node = (NodeStack*)malloc(sizeof(NodeStack));
	node->masina = masina;
	node->next = stack->top;
	stack->top = node;
	stack->count++;
}

Masina popStack(Stack* stack) {
	Masina m;
	if (stack->top) {
		NodeStack* aux = stack->top;
		m = aux->masina;
		stack->top = aux->next;
		free(aux);
		stack->count--;
	}
	return m;
}

int emptyStack(Stack* stack) {
	return stack->top == NULL;
}

void* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Stack* stack = createStack();
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		pushStack(stack, m);
	}
	fclose(f);
	return stack;
}

void dezalocareStivaDeMasini(Stack* stack) {
	//sunt dezalocate toate masinile si stiva de elemente
	while (!emptyStack(stack)) {
		Masina m = popStack(stack);
		free(m.model);
		free(m.numeSofer);
	}
	free(stack);
}

int size(Stack* stack) {
	//returneaza numarul de elemente din stiva
	return stack->count;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(Queue* queue, Masina masina) {
	NodeQueue* node = (NodeQueue*)malloc(sizeof(NodeQueue));
	node->masina = masina;
	node->next = NULL;
	if (queue->rear) {
		queue->rear->next = node;
		queue->rear = node;
	}
	else {
		queue->front = queue->rear = node;
	}
	queue->count++;
}

Masina dequeue(Queue* queue) {
	Masina m;
	if (queue->front) {
		NodeQueue* aux = queue->front;
		m = aux->masina;
		queue->front = aux->next;
		if (!queue->front)
			queue->rear = NULL;
		free(aux);
		queue->count--;
	}
	return m;

}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	Queue* queue = createQueue();
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		enqueue(queue, m);
	}
	fclose(f);
	return queue;
}

int emptyQueue(Queue* queue) {
	return queue->front == NULL;
}

int sizeQueue(Queue* queue) {
	return queue->count;
}

void dezalocareCoadaDeMasini(Queue* queue) {
	while (!emptyQueue(queue)) {
		Masina m = dequeue(queue);
		free(m.numeSofer);
		free(m.model);
	}
	free(queue);
}




void afisareStack(Stack* stack) {
	NodeStack* p = stack->top;
	while (p->next) {
		afisareMasina(p->masina);
		p = p->next;
	}
}

void afisareQueue(Queue* queue) {
	NodeQueue* p = queue->front;
	while (p->next) {
		afisareMasina(p->masina);
		p = p->next;
	}

}

int main() {

	Stack* stack=citireStackMasiniDinFisier("masini.txt");
	//afisareStack(stack);
	//afisareMasina(popStack(stack));
	dezalocareStivaDeMasini(stack);

	Queue* queue = citireCoadaDeMasiniDinFisier("masini.txt");
	afisareQueue(queue);
	afisareMasina(dequeue(queue));
	dezalocareCoadaDeMasini(queue);


	


	return 0;
}