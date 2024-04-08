#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

// Structura pentru student
typedef struct {
    int nrm;
    char CNP[14];
    char nume[30];
    int an;
    int grupa;
    unsigned char note[20];
    char is;
} STUDENT;

// Funcție pentru calculul dimensiunii fișierului
int filesize(FILE* f, int rec_size) {
    long crt_pos;
    int size;

    crt_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size = ftell(f) / rec_size;
    fseek(f, crt_pos, SEEK_SET);
    return size;
}

// Funcție pentru a scrie informațiile despre studenți într-un fișier text
void scrie_in_fisier_text(FILE* fisier_binar, FILE* fisier_text) {
    STUDENT x;
    int dimensiune = filesize(fisier_binar, sizeof(STUDENT));

    fprintf(fisier_text, "| Nr. Matricol |      Nume      | An | Grupa | Nota ATP |\n");
    fprintf(fisier_text, "--------------------------------------------------------\n");

    for (int i = 0; i < dimensiune; ++i) {
        fread(&x, sizeof(STUDENT), 1, fisier_binar);
        if (x.is == 1) {
            fprintf(fisier_text, "| %-13d| %-15s| %-3d| %-6d| %-9d|\n",
                x.nrm, x.nume, x.an, x.grupa, x.note[5]);
        }
    }
}

int main() {
    char numefr[] = "Studenti_r.dat";
    char nume_ft[] = "Studenti_text.txt";
    FILE* f;
    FILE* fisier_text;
    STUDENT x;
    int key, dimensiune;
    unsigned char new_grade;

    // Deschide fișierul binar
    f = fopen(numefr, "rb+");
    if (!f) {
        printf("Fisierul nu a fost gasit!");
        return 1;
    }

    // Deschide fișierul text pentru scriere
    fisier_text = fopen(nume_ft, "w");
    if (!fisier_text) {
        printf("Eroare la deschiderea fisierului text!");
        fclose(f);
        return 1;
    }

    // Calculează dimensiunea fișierului binar
    dimensiune = filesize(f, sizeof(STUDENT));

    // Scrie informațiile despre studenți în fișierul text
    scrie_in_fisier_text(f, fisier_text);

    // Închide fișierele
    fclose(f);
    fclose(fisier_text);

    printf("Operatia a fost realizata cu succes!");

    _getch();
    return 0;
}
