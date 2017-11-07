#include <stdio.h>
#include <stdlib.h>

void ausgabe(int brett[]) {
    char feld[8][8];
    for (int i = 0; i < 8; i++) {                   //Feld leeren:
        for (int j = 0; j < 8; j++) {
            feld[i][j] = ' ';
        }
    }
    for (int i = 0; i < 8; i++) {                   //Feld mit Positionen befüllen:
        feld[brett[i]][i] = 'D';
    }
    for (int i = 0; i < 8; i++) {                   //Feld ausdrucken:
        for (int j = 0; j < 8; j++) {
            printf("|%c", feld[i][j]);
        }
        printf("|");
        printf("\n");
    }
}

int bedroht(int brett[], int dame, int i){
    for(int j=0;j<dame;j++){                        //Spaltenweise die Damen absuchen (nur die vor der zu setzenden Dame, deswegen '<Dame') und schauen,
                                                    //ob die zu setzende Dame von den vorherigen bedroht wird oder nicht
        if((brett[j]==i) || (abs(brett[j]-i)==abs(j-dame))){
            return 1;                               //Die Dame wird bedroht
        }
    }
    return 0;                                       //Die Dame wird nicht bedroht
}

void setze(int brett[], int dame){
    if(dame != 8){                                  //Wenn noch nicht alle Damen gesetzt wurden:
        for(int i=0;i<8;i++){                       //Zeilenweise durch das Schachbrett laufen und nach einer Möglichkeit zum setzen der Dame suchen:
            if(!(bedroht(brett, dame, i))){         //'i' = i-te Zeile, in der bereits eine Dame vor zu setzenden Dame 'dame' stehen kann und diese sich dann gegenseitig schlagen könnten
                brett[dame]=i;                      //Die n-te Dame ist gleichzeitig auch die n-te Spalte auf dem Spielfeld
                setze(brett, dame+1);               //Überprüft im Falle eines Treffers die nächste Dame und geht rekursiv vor,
                                                    //damit die Dame nicht entgültig gesetzt wird, sondern bei einem Fehlschlagen des Algorithmusses, umgesetzt wird
            }
        }
    }
    else{                                           //Der Fall, wenn alle Damen gesetzt wurden:
        return;
    }
}

int main(int argc, char *argv[]){
    int brett[8];                                   //Schachbrett anlegen(8x8):
    for (int i = 0; i < 8; i++){                    //brett[i] = j := in der i-ten Spalte des Schachbrettes, steht die Dame auf der j-ten Reihe
        brett[i] = -9999;
    }
    int dame = 0;                                   //Am Anfang muss zunächst die 0. (=erste) Dame gesetzt werden
    setze(brett, dame);
    ausgabe(brett);
    return EXIT_SUCCESS;
}