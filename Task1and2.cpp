#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <stdlib.h>


typedef struct Vapor {
	int cod;
	char* denumire;
	int nrMagazii;
	float* cantitati;
}Vapor;

void afisare(const struct Vapor v) {
	printf("Cod: %d, denumire: %s, nr_magazii: %d, cantitati: ", v.cod, v.denumire, v.nrMagazii);
	for (int i = 0; i < v.nrMagazii; i++) {
		printf("%.2f, ",v.cantitati[i]);
	}
	printf("\n");
}

struct Vapor citire() {
	struct Vapor v;
	printf("%s", "Cod: ");
	scanf_s("%d", &v.cod);
	char buffer[20];
	printf("%s", "Denumire: ");
	scanf_s("%s", buffer, 20);
	v.denumire = (char*)malloc((strlen(buffer)+1) * sizeof(char));
	strcpy_s(v.denumire, strlen(buffer) + 1, buffer);
	printf("%s", "Nr magazii: ");
	scanf_s("%d", &v.nrMagazii);
	v.cantitati = (float*)malloc(v.nrMagazii * sizeof(float));
	for (int i = 0; i < v.nrMagazii; i++) {
		printf("Magazia%d: ", i + 1);
		scanf_s("%f", &v.cantitati[i]);
	}
	return v;
}

float totalIncarcatura(const Vapor& v) {
	float sum = 0;
	for (int i = 0; i < v.nrMagazii; i++)
		sum += v.cantitati[i];
	return sum;
}

void modificaDenumire(Vapor& v, const char* denumireNoua) {
	free(v.denumire);
	v.denumire = (char*)malloc((strlen(denumireNoua) + 1) * sizeof(char));
	strcpy_s(v.denumire, strlen(denumireNoua) + 1, denumireNoua);
}

struct Vapor initializare(int cod, const char* denumire, int nrMagazii, const float* cantitati) {
	struct Vapor v;
	v.cod = cod;
	v.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy_s(v.denumire, strlen(denumire) + 1, denumire);
	v.nrMagazii = nrMagazii;
	v.cantitati = (float*)malloc(nrMagazii * sizeof(float));
	for (int i = 0; i < nrMagazii; i++) {
		v.cantitati[i] = cantitati[i];
	}
	return v;
}

void afisareVector(const struct  Vapor* f, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare(f[i]);
	}
}

void copiereInVectorNou( struct Vapor* f, int dimensiuneF, int nrMagaziiSelectat, struct Vapor** vectorNou, int* dimensiuneVectorNou) {	
	*dimensiuneVectorNou = 0;
	for (int i = 0; i < dimensiuneF; i++) {
		if (f[i].nrMagazii == nrMagaziiSelectat)
			(*dimensiuneVectorNou)++;
	}
	*vectorNou = (struct Vapor*)malloc((*dimensiuneVectorNou) * sizeof(Vapor));
	int k = 0;
	for (int i = 0; i < dimensiuneF; i++) {
		if (f[i].nrMagazii == nrMagaziiSelectat) {
			(*vectorNou)[k] = f[i];
			(*vectorNou)[k].denumire = (char*)malloc((strlen(f[i].denumire) + 1) * sizeof(char));
			strcpy_s((*vectorNou)[k].denumire, strlen(f[i].denumire) + 1, f[i].denumire);
			(*vectorNou)[k].cantitati = (float*)malloc((f[i].nrMagazii * sizeof(float)));
			for (int j = 0; j < f[i].nrMagazii; j++) {
				(*vectorNou)[k].cantitati[j] = f[i].cantitati[j];
			}
		
			k++;
		}
	}
}

void mutareVapoare(struct Vapor** f, int* dimensiuneF, int capacitateMinima, struct Vapor** vectorNou, int* dimensiuneVectorNou) {
	*dimensiuneVectorNou = 0;
	for (int i = 0; i < *dimensiuneF; i++) {
		if (totalIncarcatura((*f)[i]) > capacitateMinima) {
			(*dimensiuneVectorNou)++;
		}
	}

	*vectorNou = (struct Vapor*)malloc((*dimensiuneVectorNou) * sizeof(Vapor));

	int k = 0;
	int newDimensiuneF = *dimensiuneF - *dimensiuneVectorNou;
	struct Vapor* temp = (struct Vapor*)malloc(newDimensiuneF * sizeof(Vapor));

	int j = 0;
	for (int i = 0; i < *dimensiuneF; i++) {
		if (totalIncarcatura((*f)[i]) > capacitateMinima) {
			(*vectorNou)[k].cod = (*f)[i].cod;
			(*vectorNou)[k].denumire = (char*)malloc((strlen((*f)[i].denumire) + 1) * sizeof(char));
			strcpy_s((*vectorNou)[k].denumire, strlen((*f)[i].denumire) + 1, (*f)[i].denumire);
			(*vectorNou)[k].nrMagazii = (*f)[i].nrMagazii;
			(*vectorNou)[k].cantitati = (float*)malloc((*f)[i].nrMagazii * sizeof(float));

			for (int l = 0; l < (*f)[i].nrMagazii; l++) {
				(*vectorNou)[k].cantitati[l] = (*f)[i].cantitati[l];
			}
			k++;
		}
		else {
			temp[j].cod = (*f)[i].cod;
			temp[j].denumire = (char*)malloc((strlen((*f)[i].denumire) + 1) * sizeof(char));
			strcpy_s(temp[j].denumire, strlen((*f)[i].denumire) + 1, (*f)[i].denumire);
			temp[j].nrMagazii = (*f)[i].nrMagazii;
			temp[j].cantitati = (float*)malloc((*f)[i].nrMagazii * sizeof(float));
			for (int l = 0; l < (*f)[i].nrMagazii; l++) {
				temp[j].cantitati[l] = (*f)[i].cantitati[l];
			}
			j++;
		}
	}

	free(*f);
	*f = temp;
	*dimensiuneF = newDimensiuneF;
}


int main() {
	int nrVapoare = 5;
	struct Vapor* flota;
	flota = (struct Vapor*)malloc(nrVapoare * sizeof(Vapor));

	flota[0] = initializare(1, "V1", 3, new float[3] {1, 2, 3});
	flota[1] = initializare(2, "V2", 4, new float[4] {1, 2, 3, 45});
	flota[2] = initializare(3, "V3", 3, new float[5] {1, 11.22f, 13.31f});
	flota[3] = initializare(4, "V4", 5, new float[5] {1, 2, 3, 88, 22});
	flota[4] = initializare(5, "V5", 5, new float[5] {1, 2, 32, 1, 1});

	//afisareVector(flota,nrVapoare);

	struct Vapor* f2=NULL;
	int nrVapF2 = 0;

	copiereInVectorNou( flota, nrVapoare, 3, &f2, &nrVapF2);
	//afisareVector(f2,nrVapF2);
	
	struct Vapor* f3 = NULL;
	int nrVapF3 = 0;
	int capacitateMinima = 40;
	mutareVapoare(&flota, &nrVapoare, capacitateMinima, &f3, &nrVapF3);
	afisareVector(flota, nrVapoare);
	afisareVector(f3, nrVapF3);



	//Vapor v;
	//v = citire();

	//afisare(v);

	//printf("Total: %.2f", totalIncarcatura(v2));

   
	//const char* denumireNoua = "Titanic";
	//modificaDenumire(v2, denumireNoua);
	//afisare(v2);


	/*printf("Cod: %d, denumire: %s, nr_magazii: %d, ", v1.cod, v1.denumire, v1.nrMagazii);*/

}