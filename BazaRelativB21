struct Student {
    int nr_matricol;
    char nume_prenume[30];
    int grupa;
    char puncte_proba_practica;
    char puncte_teme[10];
    char puncte_examen;
    char indicator_stare;
};

void scrie_lista_in_fisier(FILE* fisier_binar, FILE* fisier_text) {
    struct Student student;
    fprintf(fisier_text, "| %-11s | %-30s | %-6s | %-18s | %-11s | %-16s | %-16s |\n",
        "Nr. Matricol", "Nume si Prenume", "Grupa", "Puncte Practica", "Puncte Teme", "Puncte Examen", "Stare");
    fprintf(fisier_text, "|-------------|--------------------------------|--------|-------------------|-------------|-----------------|-----------------|\n");

    while (fread(&student, sizeof(struct Student), 1, fisier_binar) == 1) {
        fprintf(fisier_text, "| %-11d | %-30s | %-6d | %-18c | ", student.nr_matricol, student.nume_prenume, student.grupa, student.puncte_proba_practica);

        for (int i = 0; i < 10; ++i) {
            fprintf(fisier_text, "%c", student.puncte_teme[i]);
        }

        fprintf(fisier_text, " | %-13c | %-13c |\n", student.puncte_examen, student.indicator_stare);
    }
}

int main() {
    FILE* fisier_binar, * fisier_text;
    fisier_binar = fopen("R_points.dat", "rb"); // Deschideți fișierul binar în modul citire binară ("rb")

    if (fisier_binar == NULL) {
        perror("Eroare la deschiderea fisierului binar");
        return 1;
    }

    fisier_text = fopen("lista_studenti2.txt", "w"); // Deschideți fișierul text în modul scriere ("w")

    if (fisier_text == NULL) {
        perror("Eroare la deschiderea fisierului text");
        return 1;
    }

    scrie_lista_in_fisier(fisier_binar, fisier_text);

    fclose(fisier_binar);
    fclose(fisier_text);

    return 0;
}
