#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void ausgabe(int brett[]) {
    char feld[8][8];
    //Feld leeren:
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            feld[i][j] = ' ';
        }
    }
    //Feld mit Positionen befüllen:
    for (int i = 0; i < 8; i++) {
        feld[brett[i] - 1][i] = 'D';
    }

    //Feld ausdrucken:
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("|%c", feld[i][j]);
        }
        printf("|");
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int brett[8];
    for (int i = 0; i < 8; i++) {
        brett[i] = 2;
    }

    ausgabe(brett);
    return EXIT_SUCCESS;
}