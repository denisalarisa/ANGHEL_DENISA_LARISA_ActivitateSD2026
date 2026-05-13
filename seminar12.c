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
    char *model;
    char *numeSofer;
    unsigned char serie;
};

typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE *file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char *aux;
    Masina m1;
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy(m1.model, aux);

    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy(m1.numeSofer, aux);

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

//1.
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara
typedef struct NodP NodP;
typedef struct NodS NodS;

struct NodP {
    Masina m;
    NodP *next;
    NodS *vecini;
};

struct NodS {
    NodS *next;
    NodP *info;
};

//2.
//functii de inserare in liste
//si in principala si in secundara
void inserareListaPrincipala(NodP **graf, Masina m) {
    NodP* nodNou = (NodP*) malloc(sizeof(NodP));
    nodNou->m=m;
    nodNou->next=NULL;
    nodNou->vecini=NULL;
    if(*graf) {
        NodP *aux = *graf;
        while(aux->next) {
            aux = aux->next;
        }
        aux->next = nodNou;
    }else {
        *graf = nodNou;
    }
}

void inserareListaSecundara(NodS** lista, NodP* vecin) {
    NodS* nodNou = (NodS*) malloc(sizeof(NodS));
    nodNou->info=vecin;
    nodNou->next=NULL;
    if(*lista) {
        NodS* aux = *lista;
        while(aux->next) {
            aux = aux->next;
        }
        aux->next = nodNou;
    }else {
        *lista = nodNou;
    }
}

//3.
//functie de cautarea in lista principala dupa ID
NodP* cautaNodDupaID(NodP* listaPrincipala, int id) {
    NodP* temp = listaPrincipala;
    while (temp) {
        if (temp->m.id == id) {
            return temp;
            temp=temp->next;
        }
return NULL;
    }
}

//4.
//inserare muchie
void inserareMuchie(NodP*listaPrincipala, int idStart, int idStop) {
    NodP* start = cautaNodDupaID(listaPrincipala, idStart);
    NodP* stop = cautaNodDupaID(listaPrincipala, idStop);
    if (start != NULL && stop != NULL) {
        inserareListaSecundara(&(start->vecini),stop);
        inserareListaSecundara(&(stop->vecini),start);
    }
}


NodP* citireNoduriMasiniDinFisier(const char *numeFisier) {
    //functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
    //prin apelul repetat al functiei citireMasinaDinFisier()
    //ATENTIE - la final inchidem fisierul/stream-ul
    FILE *f = fopen(numeFisier, "r");
    NodP* graf = NULL;
    while (!feof(f)) {
        inserareListaPrincipala(&graf, citireMasinaDinFisier(f));
    }
    fclose(f);
    return graf;
}

void citireMuchiiDinFisier(const char *numeFisier, NodP* graf) {
    FILE *f = fopen(numeFisier, "r");
    while (!feof(f)) {
        int idStart=0;
        int idStop=0;
        fscanf(f, "%d %d", &idStart, &idStop );
        inserareMuchie(graf, idStart, idStop);
    }
    fclose(f);
}

void afisareListaVecini(NodP* graf, int id) {

    NodP* temp = cautaNodDupaID(graf, id);
    NodS* cap = temp->vecini;
    while (cap) {
        afisareMasina(cap->info->m);
        cap = cap->next;
    }
}

void dezalocareNoduriGraf(void *listaPrincipala) {
    //sunt dezalocate toate masinile din graf
    //si toate nodurile celor doua liste

}

int main() {
    NodP* graf = NULL;
    graf = citireNoduriMasiniDinFisier("masini.txt");
    citireMuchiiDinFisier("muchii.txt", graf);
    afisareListaVecini(graf, 8);

    return 0;
}
