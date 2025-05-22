#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Pacient {
	char* nume;
	int varsta;
	int gradUrgenta;
}Pacient;

typedef struct UPU {
	Pacient* pacienti;
	int nrPacienti;
	int lungimeVector;
}UPU;

UPU initializareUPU(int lungime) {
	UPU upu;
	upu.lungimeVector = lungime;
	upu.nrPacienti = 0;
	upu.pacienti = (Pacient*)malloc(lungime * sizeof(Pacient));
	return upu;
}

Pacient citirePacientDinFisier(FILE* f) {
	char buffer[50];
	char sep[3] = ",\n";
	fgets(buffer, 50, f);
	char* aux;
	aux = strtok(buffer, sep);
	Pacient p;
	p.nume = (char*)malloc((strlen(aux) + 1) * sizeof(aux));
	strcpy_s(p.nume, strlen(aux) + 1, aux);
	p.varsta = atoi(strtok(NULL, sep));
	p.gradUrgenta = atoi(strtok(NULL, sep));
	return p;
}

void filtreazaUPU(UPU upu, int pozitieNod) {
	int pozitieFiuSt = 2 * pozitieNod + 1;
	int pozitieFiuDr = 2 * pozitieNod + 2;
	int pozitieMax = pozitieNod;
	if (pozitieFiuSt < upu.nrPacienti && upu.pacienti[pozitieMax].gradUrgenta < upu.pacienti[pozitieFiuSt].gradUrgenta) {
		pozitieMax = pozitieFiuSt;
	}
	if (pozitieFiuDr < upu.nrPacienti && upu.pacienti[pozitieMax].gradUrgenta < upu.pacienti[pozitieFiuDr].gradUrgenta) {
		pozitieMax = pozitieFiuDr;
	}
	if (pozitieNod != pozitieMax) {
		Pacient aux = upu.pacienti[pozitieMax];
		upu.pacienti[pozitieMax] = upu.pacienti[pozitieNod];
		upu.pacienti[pozitieNod] = aux;
		if (pozitieMax <= (upu.nrPacienti - 2) / 2) {
			filtreazaUPU(upu, pozitieMax);
		}
	}

}

UPU citirePacienti(const char* fileName, int no) {
	UPU upu = initializareUPU(no);
	FILE* f = fopen(fileName, "r");
	while (!feof(f)) {
		Pacient p = citirePacientDinFisier(f);
		upu.pacienti[upu.nrPacienti++] = p;
	}
	fclose(f);

	for (int i = (upu.nrPacienti - 2) / 2; i >= 0; i--) {
		filtreazaUPU(upu, i);
	}
	return upu;
}



void adaugaPacient(UPU* upu, Pacient p) {
	upu->pacienti[upu->nrPacienti++] = p;//shallow
}

void afiseazaPacient(Pacient p) {
	printf("Nume: %s, varsta: %d, gradUrgenta: %d\n", p.nume, p.varsta, p.gradUrgenta);
}

void afiseazaUPU(UPU upu) {
	for (int i = 0; i < upu.nrPacienti; i++) {
		afiseazaPacient(upu.pacienti[i]);
	}
}

Pacient extragePacient(UPU* upu) {
	if (upu->nrPacienti > 0) {
		Pacient aux = upu->pacienti[0];
		upu->pacienti[0] = upu->pacienti[upu->nrPacienti - 1];
		upu->pacienti[upu->nrPacienti - 1] = aux;
		upu->nrPacienti--;
		for (int i = (upu->nrPacienti - 2) / 2; i >= 0; i--) {
			filtreazaUPU(*upu, i);
		}
		return aux;
	}
}

void afisarePacientiInordineaUrgentei(UPU upu, int nrPacienti) {
	printf("\nAfisare pacienti in ordinea urgentei:\n");
		for (int i = nrPacienti-1; i >=0; i--) {
			afiseazaPacient(upu.pacienti[i]);
		}

}

void dezalocare(UPU* upu) {
	for (int i=0; i < upu->lungimeVector; i++) {
		if (upu->pacienti[i].nume != NULL) {
			free(upu->pacienti[i].nume);
		}
	}
	free(upu->pacienti);
	upu->pacienti = NULL;
	upu->lungimeVector = 0;
	upu->nrPacienti = 0;
}


void main() {

	UPU upu = citirePacienti("pacienti.txt",9);
	afiseazaUPU(upu);
	int n = upu.nrPacienti;
	for (int i = 0; i < n; i++) {
		extragePacient(&upu);
	}

	
	afisarePacientiInordineaUrgentei(upu, n);
	
	afiseazaUPU(upu);

	dezalocare(&upu);
}