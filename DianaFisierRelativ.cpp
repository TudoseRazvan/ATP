#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

typedef struct {
	int nrm;
	char CNP[14];
	char nume[30];
	int an;
	int grupa;
	unsigned char note[20];
	char is;
} STUDENT;

void main()
{
	char numefr[197] = "..\\Studenti_r.dat"; //Trebuie in proiect
	char numeft[30] = "..\\List_r.txt";
	FILE* f, * g;
	STUDENT x;
	int crt, j;

	f = fopen(numefr, "rb");
	if (!f)
		printf("\nYou have probably misplaced your file. Stopping here.");
	else
	{
		g = fopen(numeft, "wt");
		fprintf(g, "Crt. Is Nrm. %-30s %-14s Yr Gr. Grades", "Nume", "CNP");
		crt = 0;

		while (fread(&x, sizeof(STUDENT), 1, f))
		{
			if (x.is == 1)
			{
				fprintf(g, "\n%4d %2d %4d %-30s %14s %2d %2d ", crt, x.is, x.nrm, x.nume, x.CNP, x.an, x.grupa);
				for (j = 0; j < 20; j++)
					fprintf(g, "%2d ", x.note[j]);
			}
			else {
				fprintf(g, "\n%4d %2d %4d %-30s %14s %2d %2d ", crt, x.is, 0, "", 0, 0, 0);
			}
			crt++;
		}

		fclose(g);
		fclose(f);
		printf("\nThe full list is in <%s>.", numeft);
	}

	printf("\nDone. Press a key", numeft);
	_getch();
}
