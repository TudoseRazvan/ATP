#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGIME_INREGISTRARE sizeof(struct Student)

// Structura pentru datele despre un student
struct Student {
    int nr_matricol;
    char nume_prenume[25];
    int grupa;
    char absente[14]; // Absentele pentru fiecare săptămână
};

// Funcția pentru înregistrarea unui nou student
void inregistrare_student(FILE* fisier_bin) {
    struct Student student;

    printf("Introduceti numarul matricol: ");
    scanf("%d", &student.nr_matricol);
    printf("Introduceti numele si prenumele: ");
    getchar(); // Consumăm caracterul newline din buffer
    fgets(student.nume_prenume, sizeof(student.nume_prenume), stdin);
    strtok(student.nume_prenume, "\n"); // Eliminăm newline-ul de la sfârșitul numelui
    printf("Introduceti grupa: ");
    scanf("%d", &student.grupa);

    // Initializam absentele cu valori de la zero
    for (int i = 0; i < 14; ++i) {
        student.absente[i] = '0';
    }

    // Ne deplasăm la sfârșitul fișierului pentru a adăuga înregistrarea
    fseek(fisier_bin, 0, SEEK_END);

    // Scriem structura student în fișierul binar
    fwrite(&student, LUNGIME_INREGISTRARE, 1, fisier_bin);

    printf("Studentul a fost inregistrat cu succes.\n");
}

// Funcția pentru afișarea datelor din fișierul binar într-un fișier text
void afisare_studenti(FILE* fisier_bin, FILE* fisier_text) {
    struct Student student;

    fprintf(fisier_text, "Nr. matricol\tNume si prenume\tGrupa\tAbsente\n");
    fprintf(fisier_text, "--------------------------------------------------------\n");

    // Ne poziționăm la începutul fișierului binar
    fseek(fisier_bin, 0, SEEK_SET);

    // Citim structurile din fișierul binar și le scriem în fișierul text în format tabular
    while (fread(&student, LUNGIME_INREGISTRARE, 1, fisier_bin)) {
        fprintf(fisier_text, "%-13d\t%-25s\t%-5d\t",
            student.nr_matricol, student.nume_prenume,
            student.grupa);

        // Scriem absențele pentru fiecare săptămână
        for (int i = 0; i < 14; ++i) {
            fprintf(fisier_text, "%c ", student.absente[i]);
        }
        fprintf(fisier_text, "\n");
    }
}

int main() {
    FILE* fisier_bin, * fisier_text;
    char optiune;

    // Deschidem fișierul binar pentru citire și scriere
    fisier_bin = fopen("Fis_relativ_Absente.dat", "rb+");
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

    // Meniu pentru înregistrarea studenților
    do {
        inregistrare_student(fisier_bin);

        printf("Doriti sa inregistrati alt student? (da - d, nu - n): ");
        scanf(" %c", &optiune);
    } while (optiune == 'd' || optiune == 'D');

    // Generăm lista cu toți studenții în fișierul text
    afisare_studenti(fisier_bin, fisier_text);

    // Închidem fișierele
    fclose(fisier_bin);
    fclose(fisier_text);

    printf("Datele au fost scrise in fisierul text.\n");

    return EXIT_SUCCESS;
}
