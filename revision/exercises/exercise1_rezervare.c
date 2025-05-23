#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Urmatoarea rezolvare este facuta in urma cerintelor din imaginea acestui folder
// Ce am invatat:
// - Lucrul cu arbori
// - Citirea dintr-un fisier text
// - Manipularea(CRUD) datelor dintr-un arbore
// - Recursivitatea si aplicarea ei in diverse situatii


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

// functia de inserare foloseste o metoda recursiva care verifica prezenta unei radacini initial
Nod* inserare(Nod* radacina, Rezervare rez){
    if (!radacina) {
        // folosim functia malloc pentru a aloca un bloc de memorie inlantuit in heap la runtime
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->rezervare.id_rezervare = rez.id_rezervare;
        nou->rezervare.denumire_hotel = rez.denumire_hotel;
        // folosim functia strdup pentru a preveni folosirea pointerilor catre memoria originala (poate fi stearsa intre timp)
        nou->rezervare.numar_camere_rezervare = strdup(rez.numar_camere_rezervare);
        nou-> rezervare.suma_de_plata = rez.suma_de_plata;
        nou-> rezervare.nume_client = strdup(rez.nume_client);
        nou->stanga = nou->dreapta = NULL;
        return nou;
    }

    // consideram ca id-urile cu valoare mai mica decat id-ul radacinii merg catre stanga si invers pentru dreapta
    if(rez.id_rezervare < radacina->rezervare.id_rezervare) {
        radacina->stanga = inserare(radacina->stanga, rez);
    } else {
        radacina->dreapta = inserare(radacina->dreapta, rez);
    }

    return radacina;
}

// serviciul citeste dintr-un fisier text si returneaza un nod, de accea tipul structurii de date este un nod
Nod* citireDinFisier(const char* numeFisier){
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf('Eroare la deschiderea fisierului');
        return NULL;
    }

    Nod* radacina = NULL;
    Rezervare rezervare;
    // abordam metoda de stocare a noii valori intr-o variabla intermediara
    char denumire[100];
    char nume[100];

    // iteram prin fisierul text si verificam ca acesta are doar 5 coloane
    while (fscanf(f, "%d, %s %d %s %f", &rezervare.id_rezervare, &denumire, 
    &rezervare.numar_camere_rezervare, &nume, &rezervare.suma_de_plata) == 5){
        // folosim functia strdup pentru a preveni folosirea pointerilor catre memoria originala (poate fi stearsa intre timp)
        rezervare.denumire_hotel = strdup(denumire);
        rezervare.nume_client = strdup(nume);
        radacina = inserare(radacina, rezervare);
    }

    fclose(f);
    return radacina;
}

int nrCamereInFrunze(Nod* rad) {
    if (!rad) return 0;
    if (!rad->stanga && !rad->dreapta) return rad->rezervare.numar_camere_rezervare;
    return nrCamereInFrunze(rad->stanga) + nrCamereInFrunze(rad->dreapta);
}

int inaltime(Nod* rad) {
    if (!rad) return 0;
    int st = inaltime(rad->stanga);
    int dr = inaltime(rad->dreapta);
    return (st > dr ? st : dr) + 1;
}

// folosim unsigned int pentru id pentru a preveni introducerea unui id cu valoare negativa
Nod* stergeNod(Nod* rad, unsigned int id) {
    if (!rad) return NULL;

    if (id < rad->rezervare.id_rezervare)
        rad->stanga = stergeNod(rad->stanga, id);
    else if (id > rad->rezervare.id_rezervare)
        rad->dreapta = stergeNod(rad->dreapta, id);
    else {
        // Nodul a fost găsit
        if (!rad->stanga) {
            Nod* temp = rad->dreapta;
            // functia free elibereaza memoria declarata dinamic, in felul acesta reducem risipa de memorie (memory waste)
            free(rad->rezervare.denumire_hotel);
            free(rad->rezervare.nume_client);
            free(rad);
            return temp;
        } else if (!rad->dreapta) {
            Nod* temp = rad->stanga;
            free(rad->rezervare.denumire_hotel);
            free(rad->rezervare.nume_client);
            free(rad);
            return temp;
        } else {
            // Nod cu doi copii
            Nod* succ = rad->dreapta;
            while (succ->stanga) succ = succ->stanga;

            // Copiem succesorul
            free(rad->rezervare.denumire_hotel);
            free(rad->rezervare.nume_client);
            rad->rezervare = succ->rezervare;
            rad->dreapta = stergeNod(rad->dreapta, succ->rezervare.id_rezervare);
        }
    }

    return rad;
}

// folosim unsigned int pentru id pentru a preveni introducerea unui id cu valoare negativa
Nod* stergeNod(Nod* rad, unsigned int id) {
    if (!rad) return NULL;

    if (id < rad->rezervare.id_rezervare)
        rad->stanga = stergeNod(rad->stanga, id);
    else if (id > rad->rezervare.id_rezervare)
        rad->dreapta = stergeNod(rad->dreapta, id);
    else {
        // Nodul a fost găsit
        if (!rad->stanga) {
            Nod* temp = rad->dreapta;
            // functia free elibereaza memoria declarata dinamic, in felul acesta reducem risipa de memorie (memory waste)
            free(rad->rezervare.denumire_hotel);
            free(rad->rezervare.nume_client);
            free(rad);
            return temp;
        } else if (!rad->dreapta) {
            Nod* temp = rad->stanga;
            free(rad->rezervare.denumire_hotel);
            free(rad->rezervare.nume_client);
            free(rad);
            return temp;
        } else {
            // Nod cu doi copii
            Nod* succ = rad->dreapta;
            while (succ->stanga) succ = succ->stanga;

            // Copiem succesorul
            free(rad->rezervare.denumire_hotel);
            free(rad->rezervare.nume_client);
            rad->rezervare = succ->rezervare;
            rad->dreapta = stergeNod(rad->dreapta, succ->rezervare.id_rezervare);
        }
    }
    return rad;
}

// folosim unsigned int pentru id pentru a preveni introducerea unui id cu valoare negativa
int traseuPanaLaId(Nod* rad, unsigned int id, Rezervare* vec, int* index) {
    if (!rad) return 0;

    vec[*index] = rad->rezervare;
    (*index)++;

    if (rad->rezervare.id_rezervare == id) return 1;

    if (id < rad->rezervare.id_rezervare)
        return traseuPanaLaId(rad->stanga, id, vec, index);
    else
        return traseuPanaLaId(rad->dreapta, id, vec, index);
}

void eliberareArbore(Nod* rad) {
    if (!rad) return;
    eliberareArbore(rad->stanga);
    eliberareArbore(rad->dreapta);
    // functia free elibereaza memoria declarata dinamic, in felul acesta reducem risipa de memorie (memory waste)
    free(rad->rezervare.denumire_hotel);
    free(rad->rezervare.nume_client);
    free(rad);
}



int main() {
    Nod* rad = NULL;
    Rezervare r1 = {100, "Hotel A", 2, "Ion Popescu", 300.0f};
    Rezervare r2 = {50, "Hotel B", 1, "Maria Ionescu", 150.0f};
    Rezervare r3 = {150, "Hotel C", 3, "George Vasilescu", 450.0f};
    Rezervare r4 = {120, "Hotel D", 2, "Alina Georgescu", 400.0f};

    rad = inserare(rad, r1);
    rad = inserare(rad, r2);
    rad = inserare(rad, r3);
    rad = inserare(rad, r4);

    printf("Numar camere in frunze: %d\n", nrCamereInFrunze(rad));
    printf("Inaltime arbore: %d\n", inaltime(rad));

    Rezervare traseu[10];
    int index = 0;
    traseuPanaLaId(rad, 120, traseu, &index);
    printf("Traseu pana la id 120:\n");
    for (int i = 0; i < index; ++i)
        printf("%d - %s\n", traseu[i].id_rezervare, traseu[i].nume_client);

    rad = stergeNod(rad, 100);
    printf("Dupa stergerea nodului cu id 100, inaltime: %d\n", inaltime(rad));

    eliberareArbore(rad);
    return 0;
}
