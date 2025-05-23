#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiti structura rezervare 
typedef struct Rezervare {
    unsigned int id_rezervare;
    char* denumire_hotel;
    unsigned char numar_camere_rezervare;
    char* nume_client;
    float suma_de_plata;
} Rezervare;

typedef struct Nod
{
    Rezervare rezervare;
    struct Nod* stanga;
    struct Nod* dreapta;
} Nod;


Nod* inserare(Nod* radacina, Rezervare rez){
    if (!radacina) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->rezervare.id_rezervare = rez.id_rezervare;
        nou->rezervare.denumire_hotel = rez.denumire_hotel;
        nou->rezervare.numar_camere_rezervare = strdup(rez.numar_camere_rezervare);
        nou-> rezervare.suma_de_plata = rez.suma_de_plata;
        nou-> rezervare.nume_client = strdup(rez.nume_client);
        nou->stanga = nou->dreapta = NULL;
        return nou;
    }

    if(rez.id_rezervare < radacina->rezervare.id_rezervare) {
        radacina->stanga = inserare(radacina->stanga, rez);
    } else {
        radacina->dreapta = inserare(radacina->dreapta, rez);
    }

    return radacina;
}

Nod* citireDinFisier(const char* numeFisier){
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf('Eroare la deschiderea fisierului');
        return NULL;
    }

    Nod* radacina = NULL;
    Rezervare rezervare;
    char denumire[100];
    char nume[100];

    while (fscanf(f, "%d, %s %d %s %f", &rezervare.id_rezervare, &denumire, 
    &rezervare.numar_camere_rezervare, &nume, &rezervare.suma_de_plata) == 5){
        rezervare.denumire_hotel = strdup(denumire);
        rezervare.nume_client = strdup(nume);
        radacina = inserare(radacina, rezervare);
    }

    fclose(f);
    return radacina;
}

int main() {
    //  create nodes by reading from a file

    // free space
    // free();
    return 0;
}