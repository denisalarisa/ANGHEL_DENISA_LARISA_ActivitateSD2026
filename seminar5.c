#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char *model;
    char *numeSofer;
    unsigned char serie;
};

typedef struct StructuraMasina Masina;

typedef struct Nod {
    Masina info;
    struct Nod *next;
    struct Nod *prev;
} Nod;

typedef struct ListaDuble {
    Nod *first;
    Nod *last;
    int nrNoduri;
} ListaDubla;

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

void afisareListaMasini(ListaDubla listaDubla) {
    //afiseaza toate elemente de tip masina din lista dublu inlantuita
    //prin apelarea functiei afisareMasina()
    Nod *aux = listaDubla.first;
    while (aux) {
        afisareMasina(aux->info);
        aux = aux->next;
    }
}

void adaugaMasinaInLista(ListaDubla *listaDubla, Masina masinaNoua) {
    Nod *nodNou = (Nod *) malloc(sizeof(Nod));
    nodNou->info = masinaNoua;
    nodNou->next = NULL;
    nodNou->prev = listaDubla->last;
    if (listaDubla->last) {
        listaDubla->last->next = nodNou;
    } else {
        listaDubla->first = nodNou;
    }
    listaDubla->last = nodNou;
}

void adaugaLaInceputInLista(ListaDubla *listaDubla, Masina masinaNoua) {
    Nod *nodNou = (Nod *) malloc(sizeof(Nod));
    nodNou->info = masinaNoua;
    nodNou->next = listaDubla->first;
    nodNou->prev = NULL;
    if (listaDubla->first) {
        listaDubla->first->prev = nodNou;
    } else {
        listaDubla->last = nodNou;
    }
    listaDubla->first = nodNou;
}

ListaDubla citireLDMasiniDinFisier(const char *numeFisier) {
    FILE *file = fopen(numeFisier, "r");
    Masina masina;
    ListaDubla listaDubla;
    listaDubla.first = NULL;
    listaDubla.last = NULL;
    while (!feof(file)) {
        masina = citireMasinaDinFisier(file);
        adaugaMasinaInLista(&listaDubla, masina);
    }
    fclose(file);
    return listaDubla;
}

void dezalocareLDMasini(ListaDubla listaDubla) {
    //sunt dezalocate toate masinile si lista dublu inlantuita de elemente
    Nod *aux;
    if (listaDubla.first) {
        aux = listaDubla.first->next;
        while (aux) {
            free(aux->prev->info.model);
            free(aux->prev->info.numeSofer);
            free(aux->prev);
            aux = aux->next;
        }
        free(listaDubla.last->info.model);
        free(listaDubla.last->info.numeSofer);
        free(listaDubla.last);
    }else{
            free(listaDubla.first->info.model);
            free(listaDubla.first->info.numeSofer);
            free(listaDubla.first);
        listaDubla.first = NULL;
        listaDubla.last = NULL;
        }
}

float calculeazaPretMediu(ListaDubla listaDubla) {
   
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
    //sterge masina cu id-ul primit.
    //tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char *getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
    //cauta masina cea mai scumpa si
    //returneaza numele soferului acestei maasini.
    return NULL;
}

int main() {
    ListaDubla listaDubla;
    listaDubla = citireLDMasiniDinFisier("masini.txt");
    afisareListaMasini(listaDubla);

    dezalocareLDMasini(listaDubla);

    return 0;
}
