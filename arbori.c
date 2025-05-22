#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct MyStruct {
	int id;
	char* name;
} MyStruct;

typedef struct Nod {
	MyStruct info;
	struct Nod* stanga;
	struct Nod* dreapta;
} Nod;

MyStruct initializareStruct(int id, const char* name) {
	MyStruct s;
	s.id = id;
	s.name = (char*)malloc(strlen(name) + 1);
	strcpy_s(s.name, strlen(name) + 1, name);
	return s;
}

void afisareStruct(MyStruct s) {
	printf("[ %i %s ]\n", s.id, s.name);
}

MyStruct citireDinFisier(FILE* f) {
	char buffer[50];
	char sep[3] = ",\n";
	char* aux;
	MyStruct m;
	fgets(buffer, 50, f);
	m.id = atoi(strtok(buffer, sep));
	aux = strtok(NULL, sep);
	m.name = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.name, strlen(aux) + 1, aux);
	return m;
}

void inserareInArbore(Nod** rad, MyStruct s) {
	if ((*rad)!=NULL) {
		if ((*rad)->info.id > s.id) {
			inserareInArbore(&(*rad)->stanga, s);
		}
		else {
			inserareInArbore(&(*rad)->dreapta, s);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = initializareStruct(s.id, s.name);
		nou->stanga = NULL;
		nou->dreapta = NULL;
		(*rad) = nou;
	}
}
int inaltime(Nod* rad) {
	if (rad == NULL) return 0;
	int st = inaltime(rad->stanga);
	int dr = inaltime(rad->dreapta);
	return 1 + (st > dr ? st : dr);
}



int calculareGE(Nod* rad) {
	if (rad) {
		int inaltimeST = inaltime(rad->stanga);
		int inaltimeDR = inaltime(rad->dreapta);
		return inaltimeST - inaltimeDR;
	}
	else return 0;
}

void rotireDreapta(Nod** rad) {
	Nod* temp = (*rad)->stanga;
	(*rad)->stanga = temp->dreapta;
	temp->dreapta = *rad;
	*rad = temp;
}

void rotireStanga(Nod** rad) {
	Nod* temp = (*rad)->dreapta;
	(*rad)->dreapta = temp->stanga;
	temp->stanga = *rad;
	*rad = temp;
}

void inserareInArboreAVL(Nod** rad, MyStruct s) {
	if ((*rad) != NULL) {
		if ((*rad)->info.id > s.id) {
			inserareInArboreAVL(&(*rad)->stanga, s);
		}
		else {
			inserareInArboreAVL(&(*rad)->dreapta, s);
		}

		int GE = calculareGE(*rad);
		if (GE == -2) {
			if (calculareGE((*rad)->dreapta) == 1) {
				rotireDreapta(&(*rad)->dreapta);
			}
			rotireStanga(rad);
		}
		if (GE == 2) {
			if (calculareGE((*rad)->stanga) == -1) {
				rotireStanga(&(*rad)->stanga);
			}
			rotireDreapta(rad);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = initializareStruct(s.id, s.name);
		nou->stanga = NULL;
		nou->dreapta = NULL;
		(*rad) = nou;
	}
}

Nod* initialziareArboreDinFisier(const char* filename) {
	FILE* f = fopen(filename, "r");
	Nod* nou = NULL;
	while (!feof(f)) {
		MyStruct s = citireDinFisier(f);
		inserareInArboreAVL(&nou, s);
	}
	fclose(f);
	return nou;
}

void afisareArbore(Nod* rad) {
	if (rad) {
		afisareArbore(rad->stanga);
		afisareStruct(rad->info);
		afisareArbore(rad->dreapta);
	}
}

void dezalocareArbore(Nod** rad) {
	if ((*rad) != NULL) {
		dezalocareArbore(&(*rad)->stanga);
		dezalocareArbore(&(*rad)->dreapta);
		free((*rad)->info.name);
		free(*rad);
		(*rad) = NULL;

	}
}

MyStruct cautareStruct(Nod* rad, int id) {  
	MyStruct s;  
	s.id = -1;  
	s.name = NULL; // Initialize name to NULL to avoid undefined behavior  
	if (rad != NULL) {  
		if (rad->info.id < id) {  
			return cautareStruct(rad->dreapta, id);  
		}  
		else if (rad->info.id > id) {  
			return cautareStruct(rad->stanga, id);  
		}  
		else {  
			return rad->info;  
		}  
	}  
	return s;  
}

void main() {
	Nod* radacina=initialziareArboreDinFisier("test.txt");
	afisareArbore(radacina);

	afisareStruct(cautareStruct(radacina, 16));
}