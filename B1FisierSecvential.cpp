#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Student {
    char nr_matricol[10];
    char nume[30];
    char an;
    int grupa;
    char tip;
    char zi;
    char luna;
    int an_calendaristic;
    char ora_intrare[5];
    char minut_intrare[5];
    char ora_iesire[5];
    char minut_iesire[5];
};

// Functie pentru afisarea datelor intr-un format tabelar cu coloane corect aliniate
void afisare_tabel(struct Student* studenti, int numar_studenti) {
    printf("Nr. matricol  Nume                          An  Grupa  Tip  Data        Ora intrare  Ora iesire\n");
    printf("------------- ------------------------------ --- ------ ---- ----------- ------------ ------------\n");
    for (int i = 0; i < numar_studenti; ++i) {
        printf("%-12s %-30s %-3c %-6d %-4c %c/%c/%-8d %-12s %-12s\n",
            studenti[i].nr_matricol, studenti[i].nume, studenti[i].an, studenti[i].grupa,
            studenti[i].tip, studenti[i].zi, studenti[i].luna, studenti[i].an_calendaristic,
            studenti[i].ora_intrare, studenti[i].minut_intrare,
            studenti[i].ora_iesire, studenti[i].minut_iesire);
    }
}

int main() {
    FILE* fisier_bin;
    FILE* fisier_text;
    struct Student studenti[100]; // presupunem ca nu exista mai mult de 100 de studenti in fisierul binar
    int numar_studenti = 0;

    // Deschide fisierul binar in mod citire
    fisier_bin = fopen("Studenti_s.dat", "rb");
    if (fisier_bin == NULL) {
        printf("Nu am putut deschide fisierul binar.");
        return 1;
    }

    // Citeste datele din fisierul binar si le stocheaza in vectorul de studenti
    while (fread(&studenti[numar_studenti], sizeof(struct Student), 1, fisier_bin)) {
        numar_studenti++;
    }

    // Inchide fisierul binar
    fclose(fisier_bin);

    // Deschide fisierul text in mod scriere
    fisier_text = fopen("Lista_studenti.txt", "w");
    if (fisier_text == NULL) {
        printf("Nu am putut deschide fisierul text.");
        return 1;
    }

    // Afiseaza datele intr-un format tabelar cu coloane corect aliniate in fisierul text
    fprintf(fisier_text, "Nr. matricol  Nume                          An  Grupa  Tip  Data        Ora intrare  Ora iesire\n");
    fprintf(fisier_text, "------------- ------------------------------ --- ------ ---- ----------- ------------ ------------\n");
    for (int i = 0; i < numar_studenti; ++i) {
        fprintf(fisier_text, "%-12s %-30s %-3c %-6d %-4c %c/%c/%-8d %-12s %-12s\n",
            studenti[i].nr_matricol, studenti[i].nume, studenti[i].an, studenti[i].grupa,
            studenti[i].tip, studenti[i].zi, studenti[i].luna, studenti[i].an_calendaristic,
            studenti[i].ora_intrare, studenti[i].minut_intrare,
            studenti[i].ora_iesire, studenti[i].minut_iesire);
    }

    // Inchide fisierul text
    fclose(fisier_text);

    printf("Lista studentilor a fost generata cu succes in fisierul Lista_studenti.txt.\n");

    return 0;
}
