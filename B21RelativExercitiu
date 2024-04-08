#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definim structura pentru student
typedef struct {
    int nrm;        // Număr matricol, cheie relativă
    char nume[30];  // Nume
    int grupa;      // Număr grupa
    char pp;        // Puncte pentru proba practică, 0-30
    char teme[10];  // Puncte pentru teme (10 x (0 or 1))
    char ex;        // Puncte pentru examen 0-50
    char is;        // Indicator de stare: 0 or 1
} STUDENT;

// Functie pentru inregistrarea punctelor pentru o tema pentru un student
void inregistrarePuncteTema(STUDENT* student, int tema, int puncte) {
    if (tema >= 0 && tema < 10) {
        student->teme[tema] = puncte ? '1' : '0'; // '1' pentru 1 punct, '0' pentru 0 puncte
        printf("Studentul %d a obtinut %d punct la tema %d.\n", student->nrm, puncte, tema + 1);
    }
    else {
        printf("Numar de tema invalid!\n");
    }
}

// Functie pentru consultarea integrală a fișierului binar și scrierea rezultatului într-un fișier text
void consultareSiScriere(STUDENT* students, int numStudents) {
    FILE* outputFile = fopen("Lista_control.txt", "wt");
    if (outputFile == NULL) {
        printf("Nu s-a putut deschide fisierul de iesire!");
        return;
    }

    fprintf(outputFile, "Gr PP EX Teme\n"); // Scriem antetul în fișierul text

    for (int i = 0; i < numStudents; i++) {
        fprintf(outputFile, "%-5d%-3hhu%-3hhu", students[i].grupa, students[i].pp, students[i].ex);
        for (int j = 0; j < 10; j++) {
            fprintf(outputFile, "%-2c", students[i].teme[j]);
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    printf("Consultarea s-a incheiat cu succes. Rezultatele au fost scrise in fisierul Lista_control.txt.\n");
}

int main() {
    // Deschidem fisierul binar pentru citire
    FILE* inputFile = fopen("R_Points.dat", "rb");
    if (inputFile == NULL) {
        printf("Nu s-a putut deschide fisierul de intrare!");
        return 1;
    }

    // Determinam numarul de studenti in fisier
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    int numStudents = fileSize / sizeof(STUDENT);
    rewind(inputFile);

    // Alocam memorie pentru vectorul de studenti
    STUDENT* students = (STUDENT*)malloc(numStudents * sizeof(STUDENT));
    if (students == NULL) {
        printf("Eroare la alocarea memoriei!");
        fclose(inputFile);
        return 1;
    }

    // Citim datele despre studenti din fisier
    fread(students, sizeof(STUDENT), numStudents, inputFile);
    fclose(inputFile);

    // Meniu pentru înregistrarea punctelor pentru teme pentru un student
    char choice;
    do {
        int studentIndex, tema, puncte;
        printf("Introduceti numarul studentului pentru care doriti sa inregistrati punctele pentru tema: ");
        scanf("%d", &studentIndex);
        if (studentIndex >= 1 && studentIndex <= numStudents) {
            printf("Introduceti numarul temei (1-10): ");
            scanf("%d", &tema);
            printf("Introduceti numarul de puncte (0 sau 1): ");
            scanf("%d", &puncte);
            inregistrarePuncteTema(&students[studentIndex - 1], tema - 1, puncte); // Indexarea porneste de la 1, deci scadem 1 pentru a accesa corect vectorul de studenti
        }
        else {
            printf("Numar de student invalid!\n");
        }

        printf("Doriti sa inregistrati puncte pentru alta tema? (Da - d, Nu - n): ");
        scanf(" %c", &choice);
    } while (choice == 'd' || choice == 'D');

    // Apelul functiei pentru consultarea integrală a fișierului binar și scrierea rezultatului într-un fișier text
    consultareSiScriere(students, numStudents);

    // Eliberarea memoriei alocate pentru vectorul de studenti
    free(students);

    return 0;
}
