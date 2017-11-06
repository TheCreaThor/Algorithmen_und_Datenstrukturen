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
        feld[brett[i]][i] = 'D';
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

void setze (int brett[]){
    brett[0]=0;



}

int main(int argc, char *argv[]) {
    //Schachbrett anlegen(8x8):
    int brett[8]; //brett[i] = j, in der i-ten Spalte des Schachbrettes, steht die Dame auf der j-ten Reihe
    for (int i = 0; i < 8; i++) {
        brett[i] = -9999;
    }
    setze(brett);
    ausgabe(brett);
    return EXIT_SUCCESS;
}