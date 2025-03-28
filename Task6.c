#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct MyStruct {
	int nr;
	char* name;
} MyStruct;

typedef struct Node {
	MyStruct info;
	struct Node* prev;
	struct Node* next;
} Node;

typedef struct ListaDubla {
	Node* first;
	Node* last;

}ListaDubla;


Node* creeazaNod(MyStruct d) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = d;
	newNode->info.name = (char*)malloc((strlen(d.name) + 1) * sizeof(char));
	strcpy_s(newNode->info.name, strlen(d.name) + 1, d.name);
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void inserareLaInceput(ListaDubla* ld, MyStruct d) {
	Node* new = creeazaNod(d);
	if (ld->first == NULL) {
		ld->first = ld->last = new;
	}
	else {
		new->next = ld->first;
		ld->first->prev = new;
		ld->first = new;
	}
}

void inserareLaSfarsit(ListaDubla* ld, MyStruct d) {
	Node* new = creeazaNod(d);
	if (ld->last == NULL) {
		ld->first = ld->last = new;
	}
	else {
		new->prev = ld->last;
		ld->last->next = new;
		ld->last = new;
	}
}

void afisareLista(ListaDubla* ld) {
	Node* p = ld->first;
	while (p) {
		printf(" [ %i %s ] ->", p->info.nr, p->info.name);
		p = p->next;
	}
	printf(" [ NULL ] \n");

}

void afisareDeLaSfarsit(ListaDubla* ld) {
	Node* p = ld->last;
	while (p) {
		printf(" [ %i %s ] ->", p->info.nr, p->info.name);
		p = p->prev;
	}
	printf(" [ NULL ] \n");
}


void deleteFromBeginning(ListaDubla* ld) {
	if (ld->first == NULL) return;
	Node* temp = ld->first;
	if (ld->first->next != NULL) {
		ld->first = ld->first->next;
		ld->first->prev = NULL;
	}
	else {
		ld->first = ld->last = NULL;
	}
	free(temp->info.name);
	free(temp);
}

void deleteFromEnd(ListaDubla* ld) {
	if (ld->last == NULL) return;
	Node* temp = ld->last;
	if (ld->last->prev != NULL) {
		ld->last = ld->last->prev;
		ld->last->next = NULL;
	}
	else {
		ld->last = ld->first = NULL;
	}
	free(temp->info.name);
	free(temp);
}

int findSize(ListaDubla* ld) {
	int size = 0;
	Node* p = ld->first;
	while (p) {
		p = p->next;
		size++;
	}
	return size;
}


void inserareLaPozitie(ListaDubla* ld,MyStruct d, int pos) {
	int size = findSize(ld);
	Node* newNode = creeazaNod(d);
	if (size < pos)
        fprintf(stderr, "MAX LENGTH < POS");
	int index ;
	if (pos == 0) {
		inserareLaInceput(ld, d);
		return;
	}
	if (pos == size ) {
		inserareLaSfarsit(ld, d);
		return;
	}

	Node* p;
	if(pos<size/2){
		index = 0;
		p = ld->first;
		while (p  &&index < pos) {
			p = p->next;
			index++;
		}	
	}
	else {
		index = size-1;
		p = ld->last;
		while (p && index > pos) {
			p = p->prev;
			index--;
		}
	}
	newNode->next = p;
	newNode->prev = p->prev;
	p->prev->next = newNode;
	p->prev = newNode;
}


void deleteFromPostion(ListaDubla* ld, int pos) {
	int size = findSize(ld);
	if (pos >= size) {
		fprintf(stderr, "MAX LENGTH < POS"); 
		return;
	}
	if (pos == 0) {
		deleteFromBeginning(ld); return;
	}
	if (pos == size - 1) {
		deleteFromEnd(ld); return;
	}
	Node* p;
	int index;
	if (pos < size / 2) {
		index = 0;
		p = ld->first;
		while (p&&index<pos) {
			p = p->next;
			index++;
		}
	}
	else {
		index = size - 1;
		p = ld->last;
		while (p && index > pos) {
			p = p->prev;
			index--;
		}
	}

	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p->info.name);
	free(p);
}

void sortareLdAsc(ListaDubla* ld) {
	Node* i, * j;
	MyStruct temp;
	for(i=ld->first;i!=NULL;i=i->next)
		for(j=i->next;j!=NULL;j=j->next)
			if (i->info.nr > j->info.nr) {
				temp = i->info;
				temp.name = (char*)malloc((strlen(i->info.name) + 1) * sizeof(char));
				strcpy_s(temp.name, strlen(i->info.name) + 1, i->info.name);
				i->info = j->info;
				i->info.name = (char*)malloc((strlen(j->info.name) + 1) * sizeof(char));
				strcpy_s(i->info.name, strlen(j->info.name) + 1, j->info.name);
				j->info =temp;
				j->info.name = (char*)malloc((strlen(temp.name) + 1) * sizeof(char));
				strcpy_s(j->info.name, strlen(temp.name) + 1, temp.name);
			}
}

void sortareLdDesc(ListaDubla* ld) {
	Node* i, * j;
	MyStruct temp;
	for (i = ld->first; i != NULL; i = i->next)
		for (j = i->next; j != NULL; j = j->next)
			if (i->info.nr < j->info.nr) {
				temp = i->info;
				temp.name = (char*)malloc((strlen(i->info.name) + 1) * sizeof(char));
				strcpy_s(temp.name, strlen(i->info.name) + 1, i->info.name);
				i->info = j->info;
				i->info.name = (char*)malloc((strlen(j->info.name) + 1) * sizeof(char));
				strcpy_s(i->info.name, strlen(j->info.name) + 1, j->info.name);
				j->info = temp;
				j->info.name = (char*)malloc((strlen(temp.name) + 1) * sizeof(char));
				strcpy_s(j->info.name, strlen(temp.name) + 1, temp.name);
			}
}

typedef struct SimpleNode {
	MyStruct info;
	struct SimpleNode* next;
} SimpleNode;


void writeIntoLinkedList(ListaDubla* ld, SimpleNode** ls) {
	Node* p = ld->first;
	while (p) {
		if (p->info.nr >=5) {
            SimpleNode* newNode = (SimpleNode*)malloc(sizeof(SimpleNode));
            newNode->info = p->info;
			newNode->info.name = (char*)malloc((strlen(p->info.name) + 1) * sizeof(char));
			strcpy_s(newNode->info.name, strlen(p->info.name) + 1, p->info.name);
			newNode->next = NULL;			
			if (*ls) {
				SimpleNode* s = *ls;
				while (s->next) {
					s = s->next;
				}
				s->next = newNode;			
			}
			else {
				*ls = newNode;
			}	
		}
		p = p->next;
	}
}


void afisareLS(SimpleNode* ls) {
	SimpleNode* p = ls;
	while (p) {
		printf(" [ %i %s ] ->", p->info.nr, p->info.name);
		p = p->next;
	}
	printf(" [ NULL ] \n");
}



void swapElements1(ListaDubla* ld, int pos1, int pos2) {
	int size = findSize(ld);
	if (size < 2) return;
	if (pos1 == pos2)return;
	if (pos1 >= size || pos2 >= size) {
		fprintf(stderr, "MAX LENGTH < POS"); return;
	}
	Node* p = ld->first;
	Node* n1=NULL;
	Node* n2 = NULL;
	int index = 0;
	while (p) {
		if (index == pos1)
			n1 = p;
		if (index == pos2)
			n2 = p;
		p = p->next;
		index++;
	}
	MyStruct aux = n1->info;
	aux.name = (char*)malloc((strlen(n1->info.name) + 1) * sizeof(char));
	strcpy_s(aux.name, strlen(n1->info.name) + 1, n1->info.name);

	free(n1->info.name);
	n1->info.nr = n2->info.nr;
	n1->info.name = (char*)malloc((strlen(n2->info.name) + 1) * sizeof(char));
	strcpy_s(n1->info.name, strlen(n2->info.name) + 1, n2->info.name);

	free(n2->info.name);
	n2->info.nr = aux.nr;
	n2->info.name = (char*)malloc((strlen(aux.name) + 1) * sizeof(char));
	strcpy_s(n2->info.name, strlen(aux.name) + 1, aux.name);

	free(aux.name);
}


void swapElements2(ListaDubla* ld, int pos1, int pos2) {
	int size = findSize(ld);
	if (size < 2) return;
	if (pos1 == pos2) return;
	if (pos1 >= size || pos2 >= size) {
		fprintf(stderr, "MAX LENGTH < POS\n");
		return;
	}

	if (pos1 > pos2) {
		int temp = pos1;
		pos1 = pos2;
		pos2 = temp;
	}

	Node* p = ld->first;
	Node* n1 = NULL;
	Node* n2 = NULL;
	int index = 0;

	while (p) {
		if (index == pos1) n1 = p;
		if (index == pos2) n2 = p;
		p = p->next;
		index++;
	}

	if (!n1 || !n2) return;


	if (n1->next == n2) {
		if (n1->prev) n1->prev->next = n2;
		if (n2->next) n2->next->prev = n1;

		n1->next = n2->next;
		n2->prev = n1->prev;
		n2->next = n1;
		n1->prev = n2;
	}
	else {
		Node* tempPrev = n1->prev;
		Node* tempNext = n1->next;

		if (n1->prev) n1->prev->next = n2;
		if (n1->next) n1->next->prev = n2;
		if (n2->prev) n2->prev->next = n1;
		if (n2->next) n2->next->prev = n1;

		n1->prev = n2->prev;
		n1->next = n2->next;
		n2->prev = tempPrev;
		n2->next = tempNext;
	}


	if (pos1 == 0) ld->first = n2;
	if (pos2 == size - 1) ld->last = n1;
}

void main() {
	MyStruct data0 = { 1,"Alpha" };
	MyStruct data1 = { 9,"Bravo"};
	MyStruct data2 = {8,"Charlie"};
	MyStruct data3 = {4,"Delta"};
	MyStruct data4 = { 5,"Echo"};

	ListaDubla dll = { NULL, NULL };
	inserareLaSfarsit(&dll, data0);
	inserareLaSfarsit(&dll, data1);
	inserareLaSfarsit(&dll, data2);
	inserareLaSfarsit(&dll, data3);
	inserareLaSfarsit(&dll, data4);
	sortareLdAsc(&dll);
	afisareLista(&dll);
	//afisareDeLaSfarsit(&dll);

	swapElements1(&dll, 1, 3);
	afisareLista(&dll);

	//SimpleNode* ls = NULL;
	//writeIntoLinkedList(&dll, &ls);
	//afisareLS(ls);



}