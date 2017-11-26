#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GROESSE 10000

int arrayToSort[GROESSE];
double ergebnisarray[6][4];                                                    //ersten 3 Spalten sind für das Ergebnis der drei Durchläufe, letzte Spalte für den Durchschnitt

/**
 * Implementierung des Selection- Sorts zur Zeitmessung der Dauer dieses Sortierverfahrens.
 * @param sort: Das zu sortierende Array
 * @param n: Die Laenge des zu sortienden Arrays
 * @return: Die Dauer, die das Sortierverfahren gebraucht hat
 */
double SelectionSort(int sort[], int n){
    clock_t start, end;
    double total;
    start = clock();

    int min, zwspeicher;
    for(int i = 0; i < n-1; i++){                                              //nur "<", da das letzte Element im Array bereits automatisch sortiert sein muss, wenn der Teil davor sortiert ist
        min = i;                                                               //das zu überprüfende Element ist automatisch das kleinste
        for(int j = i+1; j <= n; j++){                                         //"<=", da man alle Elemente durchlaufen muss, um zu schauen, ob es ein kleiners gibt
            if(sort[j] < sort[min]) min = j;
        }
        zwspeicher = sort[min];
        sort[min] = sort[i];
        sort[i] = zwspeicher;
    }

    end = clock();
    total = ((double)(end-start))/CLOCKS_PER_SEC;
    return  total;
}

/**
 * Implementierung des Insertion- Sorts zur Zeitmessung der Dauer dieses Sortierverfahrens.
 * @param sort: Das zu sortierende Array
 * @param n: Die Laenge des zu sortienden Arrays
 * @return: Die Dauer, die das Sortierverfahren gebraucht hat
 */
double Insertionsort(int sort[], int n){
    clock_t start, end;
    double total;
    start = clock();

    int vorherig, momentan;
    for(int i = 1; i < n; i++){                                                //das 0. Element der zu sortierten Liste ist bereits im sortierten Teil
        momentan = sort[i];                                                    //der Wert des Elements, das eingefügt werden soll
        vorherig = i-1;                                                        //die Stelle des Elements vor dem was eingefügt werden soll
        while((momentan < sort[vorherig]) && (vorherig >= 0)){                 //solange das aktuell betrachtende Element in das vom Element relativ nächste Feld im Array verschieben, wie der einzufügende Wert kleiner ist als der Wert des aktuellen Elementes
            sort[vorherig+1] = sort[vorherig];                                 //Verschiebung des Elements an die nächste Position im Array
            vorherig--;                                                        //nächste Stelle im sortierten Array überprüfen
        }
        sort[vorherig+1] = momentan;                                           //nun kann der einzufügende Wert an die Stelle, wo der alte Wert, vor der letzten Verschiebung, steht
        }

    end = clock();
    total = ((double)(end-start))/CLOCKS_PER_SEC;
    return  total;
    }

int main(int argc, char* argv[]){
    for(int durchlauf = 0; durchlauf < 3; durchlauf++){                        //jedes Sortierverfahren soll drei Mal ausgeführt werden, um nachher ein Durchschnitt bilden zu können

        for(int i = 1; i <= GROESSE; i++){                                      //Array aufsteigend befüllen:
            arrayToSort[i - 1] = i;
        }
        ergebnisarray[0][durchlauf] = SelectionSort(arrayToSort, GROESSE);      //Sortierungsverfahren für ein aufsteigendes Array ausführen
        ergebnisarray[3][durchlauf] = Insertionsort(arrayToSort, GROESSE);      //verbrauchte Zeit des Sortierens wird in einem Ergebnisarray gespeichert

        int k = 1;                                                             //Array absteigend befüllen:
        for(int j = GROESSE-1; j >= 0; j--){
            arrayToSort[j] = k;
            k++;
        }
        ergebnisarray[1][durchlauf] = SelectionSort(arrayToSort, GROESSE);      //Sortierungsverfahren für ein aufsteigendes Array ausführen
        ergebnisarray[4][durchlauf] = Insertionsort(arrayToSort, GROESSE);      //verbrauchte Zeit des Sortierens wird in einem Ergebnisarray gespeichert

        srand((unsigned) time(NULL));                                          //Array zufällig befüllen:
        for(int l = 0; l < GROESSE; l++){
            arrayToSort[l] = rand();
        }
        ergebnisarray[2][durchlauf] = SelectionSort(arrayToSort, GROESSE);      //Sortierungsverfahren für ein aufsteigendes Array ausführen
        ergebnisarray[5][durchlauf] = Insertionsort(arrayToSort, GROESSE);      //verbrauchte Zeit des Sortierens wird in einem Ergebnisarray gespeichert
    }
    printf("Das Ergebnis der Laufzeiten- Analyse der Sortierverfahren ist:\n\n");
    printf("Sorierverfahren             |1\t\t\t\t\t|2\t\t\t\t\t|3\t\t\t\t\t|⌀\t\t\t\t\t|\n\n");
    printf("Selectionsort: Aufsteigend  |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[0][0], ergebnisarray[0][1], ergebnisarray[0][2], (ergebnisarray[0][0] + ergebnisarray[0][1] + ergebnisarray[0][2])/3);
    printf("Selectionsort: Absteigend   |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[1][0], ergebnisarray[1][1], ergebnisarray[1][2], (ergebnisarray[1][0] + ergebnisarray[1][1] + ergebnisarray[1][2])/3);
    printf("Selectionsort: Zufällig     |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[2][0], ergebnisarray[2][1], ergebnisarray[2][2], (ergebnisarray[2][0] + ergebnisarray[2][1] + ergebnisarray[2][2])/3);
    printf("Insertionsort: Aufsteigend  |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[3][0], ergebnisarray[3][1], ergebnisarray[3][2], (ergebnisarray[3][0] + ergebnisarray[3][1] + ergebnisarray[3][2])/3);
    printf("Insertionsort: Absteigend   |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[4][0], ergebnisarray[4][1], ergebnisarray[4][2], (ergebnisarray[4][0] + ergebnisarray[4][1] + ergebnisarray[4][2])/3);
    printf("Insertionsort: Zufällig     |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[5][0], ergebnisarray[5][1], ergebnisarray[5][2], (ergebnisarray[5][0] + ergebnisarray[5][1] + ergebnisarray[5][2])/3);
}