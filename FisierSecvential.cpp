#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definirea structurii pentru datele studentului
struct Student {
    int nr_matricol;
    char nume_prenume[30];
    int grupa;
    char puncte_proba_practica[3]; // 0-30, maxim 2 caractere
    char puncte_teme[2]; // 0-10, maxim 2 caractere
    char puncte_examen[3]; // 0-50, maxim 2 caractere
};

// Funcția pentru afișarea datelor din fișierul binar într-un fișier text
void afisare_studenti(FILE* fisier_bin, FILE* fisier_text) {
    struct Student student;

    fprintf(fisier_text, "Nr. matricol\tNume si prenume\tGrupa\tPuncte proba practica\tPuncte teme\tPuncte examen\n");
    fprintf(fisier_text, "----------------------------------------------------------------------------------------------\n");

    // Citim structurile din fișierul binar și le scriem în fișierul text în format tabular
    while (fread(&student, sizeof(struct Student), 1, fisier_bin)) {
        fprintf(fisier_text, "%-13d\t%-30s\t%-5d\t%-22s\t%-10s\t%-13s\n",
            student.nr_matricol, student.nume_prenume, student.grupa,
            student.puncte_proba_practica, student.puncte_teme, student.puncte_examen);
    }
}

int main() {
    FILE* fisier_bin, * fisier_text;

    // Deschidem fișierul binar pentru citire
    fisier_bin = fopen("Studenti_s.dat", "rb");
    if (fisier_bin == NULL) {
        perror("Eroare la deschiderea fisierului binar");
        return EXIT_FAILURE;
    }

    // Deschidem fișierul text pentru scriere
    fisier_text = fopen("studenti.txt", "w");
    if (fisier_text == NULL) {
        perror("Eroare la deschiderea fisierului text");
        fclose(fisier_bin);
        return EXIT_FAILURE;
    }

    // Apelăm funcția de afișare a datelor
    afisare_studenti(fisier_bin, fisier_text);

    // Închidem fișierele
    fclose(fisier_bin);
    fclose(fisier_text);

    printf("Datele au fost scrise in fisierul text.\n");

    return EXIT_SUCCESS;
}
