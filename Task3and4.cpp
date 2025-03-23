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

void eliberareMemorie(Vapor* v, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		free(v[i].denumire);
		free(v[i].cantitati);
	}
	free(v);
}

struct Vapor citireVapordDinFisier(FILE* file) {
	struct Vapor vdinf;
	char line[256];
	char sep[3] = ",\n";

	if (fgets(line, sizeof(line), file) == NULL) {
		vdinf.cod = -1; 
		vdinf.denumire = NULL;
		vdinf.nrMagazii = 0;
		vdinf.cantitati = NULL;
		return vdinf;
	}

	char* next_token = NULL;
	int cod = atoi(strtok_s(line, sep, &next_token));
	vdinf.cod = cod;
	char* aux;
	aux = strtok_s(NULL, sep, &next_token);
	if (aux != NULL) {
		vdinf.denumire = (char*)malloc(strlen(aux) + 1);
		if (vdinf.denumire != NULL) {
			strcpy_s(vdinf.denumire, strlen(aux) + 1, aux);
		}
	}
	else {
		vdinf.denumire = NULL;
	}
	aux = strtok_s(NULL, sep, &next_token);
	if (aux != NULL) {
		vdinf.nrMagazii = atoi(aux);
	}
	else {
		vdinf.nrMagazii = 0;
	}
	vdinf.cantitati = (float*)malloc(vdinf.nrMagazii * sizeof(float));
	if (vdinf.cantitati != NULL) {
		for (int i = 0; i < vdinf.nrMagazii; i++) {
			aux = strtok_s(NULL, sep, &next_token);
			if (aux != NULL) {
				vdinf.cantitati[i] = atof(aux);
			}
			else {
				vdinf.cantitati[i] = 0.0f;
			}
		}
	}
	return vdinf;
}

void inserareInVector(struct Vapor** vector, int* dim, struct Vapor vapor) {
	struct Vapor* aux = (struct Vapor*)malloc(sizeof(struct Vapor) * ((*dim) + 1));
	if (aux != NULL) {
		for (int i = 0; i < *dim; i++) {
			aux[i] = (*vector)[i];
		}
		aux[(*dim)] = vapor;

		aux[*dim].denumire = (char*)malloc((strlen(vapor.denumire) + 1) * sizeof(char));
		if (aux[*dim].denumire != NULL) {
			strcpy_s(aux[*dim].denumire, strlen(vapor.denumire) + 1, vapor.denumire);
		}
		aux[*dim].cantitati = (float*)malloc(vapor.nrMagazii * sizeof(float));
		if (aux[*dim].cantitati != NULL) {
			for (int i = 0; i < vapor.nrMagazii; i++) {
				aux[*dim].cantitati[i] = vapor.cantitati[i];
			}
		}

		free(*vector);
		*vector = aux;
		(*dim)++;
	}
}

struct Vapor* citireVapoareDinFisier(FILE* file, int* dim) {
	struct Vapor* vapoare = NULL;
	(*dim) = 0;
	while (!feof(file)) {
		struct Vapor v = citireVapordDinFisier(file);
		if (v.cod != -1) {
			inserareInVector(&vapoare, dim, v);
		}
	}
	return vapoare;
}


void scriereVaporInFisier(FILE* f, const struct Vapor& v) {
	fprintf(f, "\n%d,%s,%i", v.cod, v.denumire, v.nrMagazii);
	for (int i = 0; i < v.nrMagazii; i++) {
		fprintf(f, ",%.2f", v.cantitati[i]);
	}
}

void scriereVapoareInFisier(FILE* f, const struct Vapor* vapoare, int dim) {
	for (int i = 0; i < dim; i++) {
		scriereVaporInFisier(f, vapoare[i]);
	}
}

void copiereInMatrice(Vapor** matrix, int* nrLinii, int* nrColoane, Vapor* vector, int dimVector) {
	nrLinii = 0;
	nrColoane = 0;
	
	for (int i = 0; i < dimVector; i++) {

	}
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

	//struct Vapor* f2=NULL;
	//int nrVapF2 = 0;

	//copiereInVectorNou( flota, nrVapoare, 3, &f2, &nrVapF2);
	////afisareVector(f2,nrVapF2);
	//
	//struct Vapor* f3 = NULL;
	//int nrVapF3 = 0;
	//int capacitateMinima = 40;
	//mutareVapoare(&flota, &nrVapoare, capacitateMinima, &f3, &nrVapF3);
	//afisareVector(flota, nrVapoare);
	//afisareVector(f3, nrVapF3);



	//Vapor v;
	//v = citire();

	//afisare(v);

	//printf("Total: %.2f", totalIncarcatura(v2));

   
	//const char* denumireNoua = "Titanic";
	//modificaDenumire(v2, denumireNoua);
	//afisare(v2);


	/*printf("Cod: %d, denumire: %s, nr_magazii: %d, ", v1.cod, v1.denumire, v1.nrMagazii);*/




	FILE* file;
	 fopen_s(&file, "vapoare.txt", "r"); // Open file in read mode



	struct Vapor vdinf=citireVapordDinFisier(file);

	//afisare(vdinf);

	struct Vapor* flotaDinFisier=NULL;
	int nrNaveDinFisier = 0;
	flotaDinFisier = citireVapoareDinFisier(file, &nrNaveDinFisier);
	afisareVector(flotaDinFisier,nrNaveDinFisier);



	fclose(file);
	FILE* file1;
	fopen_s(&file1, "vapoare.txt", "a");
	//scriereVaporInFisier(file1, flota[1]);
	//scriereVapoareInFisier(file1, flota,nrVapoare);

	fclose(file1);


    int nrLinii = 3;
    int nrColoane = 4;
    Vapor** matrix = new Vapor*[nrLinii];
	int v = 0;
    for (int i = 0; i < nrLinii; ++i) {
		matrix[i] = new Vapor[nrColoane];
    }

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			matrix[i][j] = flotaDinFisier[v++];
		}
	}

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			printf("matrix %i %i =  ", i, j );
			afisare(matrix[i][j]);
			printf("\n");

	
		}
	}



	//struct Client c;
	//char buffer[100];
	//char sep[3] = ",\n";
	//fgets(buffer, 100, f);
	//int id = atoi(strtok(buffer, sep));
	//c.id = id;
	//c.varsta = atoi(strtok(NULL, sep));
	//char* aux;
	//aux = strtok(NULL, sep);
	//c.nume = (char*)malloc(strlen(aux) + 1);
	//strcpy_s(c.nume, strlen(aux) + 1, aux);
	//c.buget = atof(strtok(NULL, sep));
	//c.initialaTata = strtok(NULL, sep)[0];
	//return c;



	eliberareMemorie(flota, nrVapoare);
	//eliberareMemorie(f2, nrVapF2);
	//eliberareMemorie(f3, nrVapF3);
}