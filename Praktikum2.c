#include <stdio.h>
#include <stdlib.h>

int counter = 0; //Speicher für die gesamte Anzahl der gefundenen Lösungen
/**
 * Eine Funktion, um das Spielfeld auszugeben.
 * @param brett Das Spielfeld, was ausgegeben werden soll
 */
void ausgabe(int brett[]) {
    printf("%d. Lösung: [ ",counter+1);             //Ausgabe der Lösung in Zahlen
    for(int i = 0; i < 8;i++){
        printf("%d ", brett[i]);
    }
    printf("]\n");
    char feld[8][8];                                //char- Feld erzeugen, um die Informationen des eindimensionalen Arrays "brett" in das zweidimensionale Array zu übertragen und auszugeben
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
    counter ++;
    printf("\n");
}

/**
 * Funktion, um zu überprüfen, ob eine bereits gesetzte Dame in den vorherigen Spalten,
 * die aktuelle zu setztende Dame in der i-ten Zeile schlagen würde oder nicht.
 * @param brett Das Brett, auf dem diese Überprüfung stattfinden soll
 * @param dame Die Dame, die gesetzt und somit überprüft werden soll
 * @param i Die i-te Zeile, in der die Überprüfung stattfinden soll
 * @return 1: Wenn die zu setzende Dame bedroht wird, 0: Wenn die zu setzende Dame nicht bedroht wird
 */
int bedroht(int brett[], int dame, int i){
    for(int j=0;j<dame;j++){                        //Spaltenweise die Damen absuchen (nur die vor der zu setzenden Dame, deswegen '<Dame') und schauen,
                                                    //ob die zu setzende Dame von den vorherigen bedroht wird oder nicht
        if((brett[j]==i) || (abs(brett[j]-i)==abs(j-dame))){ //1.: Die zu setzende Dame ist in der gleichen Zeile, wie eine der vorherigen Damen
                                                             //2.: Die zu setzende Dame ist auf der gleichen Schräge, wie eine der vorherigen Damen
            return 1;                               //Die Dame wird bedroht
        }
    }
    return 0;                                       //Die Dame wird nicht bedroht
}

/**
 * Funktion, um eine Dame auf das Spielfeld zu setzen. Hier wird zeilenweise geprüft, ob sich eine Dame setzen lässt oder nicht und wenn ja,
 * dann wird die Position dieser in einem Array abgespeichert und in einem rekursiven Verfahren fortgefahren. Wenn eine Dame sich nicht setzen lässt,
 * wird die nächste Zeile überprüft. Es erfolgt eine Ausgabe, wenn alle 8 Damen auf das Spielfeld gesetzt wurden.
 * @param brett Auf welches Spielfeld die Damen gesetzt werden sollen
 * @param dame Die n-te Dame, die auf das Spielfeld gesetzt werden soll
 */
void setze(int brett[], int dame){
    if(dame != 8){                                  //Wenn noch nicht alle Damen gesetzt wurden:
        for(int i=0;i<8;i++){                       //Zeilenweise durch das Schachbrett laufen und nach einer Möglichkeit zum setzen der Dame suchen:
            if(!(bedroht(brett, dame, i))){         //'i' = i-te Zeile, in der bereits eine Dame vor der zu setzenden Dame 'dame' stehen kann und diese sich dann gegenseitig schlagen könnten
                brett[dame]=i;                      //Die n-te Dame ist gleichzeitig auch die n-te Spalte auf dem Spielfeld
                setze(brett, dame+1);               //Überprüft im Falle eines Treffers die nächste Dame und geht rekursiv vor,
                                                    //damit die Dame nicht entgültig gesetzt wird, sondern bei einem Fehlschlagen des Algorithmusses, umgesetzt wird
            }
        }
    }
    else{                                           //Der Fall, wenn alle Damen gesetzt wurden und man über dem 8x8- Feld hinaus keine weitere Dame mehr setzen darf:
        ausgabe(brett);
    }
}

/**
 * Hier wird das Schachbrett erzeugt, sowie gesagt, dass man bei der ersten Dame in der ersten Spalte starten soll zu suchen und eine Dame zu setzen.
 * @param argc Anzahl der Parameter (in der Shell)
 * @param argv Einzelnen übergebenen Werte (in der Shell)
 * @return Abbruchbeding
 */
int main(int argc, char *argv[]){
    int brett[8];                                   //Schachbrett anlegen(8x8):
    int dame = 0;                                   //Am Anfang muss zunächst die 0. (=erste) Dame gesetzt werden
    setze(brett, dame);
    printf("Die Anzahl der gefundenen Lösungen lautet: %d", counter);
    return EXIT_SUCCESS;
}