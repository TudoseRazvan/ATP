#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGIME_INREGISTRARE sizeof(struct Absenta)

// Definirea structurii pentru datele despre absențe
struct Absenta {
    char stare; // Indicator de stare (0/1)
    int nr_matricol;
    char nume_prenume[25];
    int grupa;
    char an;
    char absente[15]; // Absențele pentru fiecare disciplină
};

// Funcția pentru afișarea datelor din fișierul relativ într-un fișier text
void afisare_absente(FILE* fisier_rel, FILE* fisier_text) {
    struct Absenta absenta;

    fprintf(fisier_text, "Indicator de stare\tNr. matricol\tNume si prenume\tGrupa\tAn\tAbsente\n");
    fprintf(fisier_text, "--------------------------------------------------------------------------------\n");

    // Ne poziționăm la începutul fișierului relativ
    fseek(fisier_rel, 0, SEEK_SET);

    // Citim structurile din fișierul relativ și le scriem în fișierul text în format tabular
    while (fread(&absenta, LUNGIME_INREGISTRARE, 1, fisier_rel)) {
        fprintf(fisier_text, "%-18c\t%-13d\t%-25s\t%-5d\t%-2c\t",
            absenta.stare, absenta.nr_matricol, absenta.nume_prenume,
            absenta.grupa, absenta.an);

        // Scriem absențele pentru fiecare disciplină
        for (int i = 0; i < 15; ++i) {
            fprintf(fisier_text, "%c ", absenta.absente[i]);
        }
        fprintf(fisier_text, "\n");

        // Ne deplasăm la următoarea înregistrare
        fseek(fisier_rel, 0, SEEK_CUR);
    }
}

int main() {
    FILE* fisier_rel, * fisier_text;

    // Deschidem fișierul relativ pentru citire
    fisier_rel = fopen("Studenti_r.dat", "rb");
    if (fisier_rel == NULL) {
        perror("Eroare la deschiderea fisierului relativ");
        return EXIT_FAILURE;
    }

    // Deschidem fișierul text pentru scriere
    fisier_text = fopen("absente.txt", "w");
    if (fisier_text == NULL) {
        perror("Eroare la deschiderea fisierului text");
        fclose(fisier_rel);
        return EXIT_FAILURE;
    }

    // Apelăm funcția de afișare a datelor
    afisare_absente(fisier_rel, fisier_text);

    // Închidem fișierele
    fclose(fisier_rel);
    fclose(fisier_text);

    printf("Datele au fost scrise in fisierul text.\n");

    return EXIT_SUCCESS;
}
