#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define GROESSE 150000

double ergebnisarray[15][4];                                                    //ersten 3 Spalten sind für das Ergebnis der drei Durchläufe, letzte Spalte für den Durchschnitt
static int N;

/**
 * Implementierung des Selection- Sorts zur Zeitmessung der Dauer dieses Sortierverfahrens.
 * @param sort: Das zu sortierende Array
 * @param n: Die Laenge des zu sortienden Arrays
 * @return: Die Dauer, die das Sortierverfahren gebraucht hat
 */
double selectionSort(int sort[], int n){
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
double insertionsort(int sort[], int n){
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

/**
 * Implementierung des Shell- Sorts zur Zeitmessung der Dauer dieses Sortierverfahrens.
 * @param sort: Das zu sortierende Array
 * @param n: Die Laenge des zu sortienden Arrays
 * @return: Die Dauer, die das Sortierverfahren gebraucht hat
 */
double shellsort(int sort[], int n){
    clock_t start, end;
    double total;
    start = clock();

    int j, h;
    for(h = 1; h <= n/3; h = 3*h + 1);                                          //Das Array wird in mehrere Teile aufgeteilt, damit man das Tauschen von 2 Elementen mit der Entfernung "h" ermöglichen kann
    for( ; h > 0; h /= 3)                                                       //Solange h größer als "0" ist, soll der Abstand im Tauschen zwischen 2er Elemente immer geringer werden
        for(int i = h+1; i <= n; i++){                                          //Hier beginnt wieder der normale Insertionsort mit einer Verschiebung von "h"
            int v = sort[i];
            j = i;
            while((j > h)&&(sort[j-h] > v)){
                sort[j] = sort[j-h];
                j -= h;
            }
            sort[j] = v;
        }

    end = clock();
    total = ((double)(end-start))/CLOCKS_PER_SEC;
    return  total;
}

/**
 * Implementierung des Quick- Sorts zur Zeitmessung der Dauer dieses Sortierverfahrens.
 * @param sort: Das zu sortierende Array
 * @param l: Die linke Grenze des momentan zu sortienden Arrays
 * @param r: Die rechte Grenze des momentan zu sortienden Arrays
 * @return: Die Dauer, die das Sortierverfahren gebraucht hat
 */
double quicksort(int sort[], int l, int r){
    clock_t start, end;
    double total;
    start = clock();

    int t;
    if(r > l){                                                                  //solange es in der Rekursion mehr als ein Element gibt, also die linke und rechte Grenze setzbar sind
        int pivot = sort[r];                                                    //wähle das ganz rechte Element der momentanen Begrenzung als Pivotelement
        int i = l-1;
        int j = r;
        for(;;){                                                                //wiederholter Ablauf des Codes in der Schleife, bis "break" aufgerufen wird
            while(sort[++i] < pivot);                                           //verschiebe die linke Grenze "i", solange der Wert sort[i] kleiner ist als das rechte Element im momentanen Array, nach rechts
            while(sort[--j] > pivot);                                           //verschiebe die rechte Grenze "j", solange der Wert sort[j] größer ist als das rechte Element im momentanen Array, nach links
            if(i >= j) break;                                                   //mache dieses Verfahren solange, bis "i" >= "j", d.h. alle Elemente kleiner des Pivotelements im linken Teil und alle größer des Pivotelements im rechten Teil des Arrays stehen
            t = sort[i];                                                        //vertausche "j" mit "i"
            sort[i] = sort[j];
            sort[j] = t;
        }
        t = sort[i];                                                             //nun tausche noch das Pivotelement von ganz rechts an die Stelle von i, also in der Mitte von der linken Hälfte mit all den kleineren und der rechten Hälfte mit all den größeren Zahlen
        sort[i] = sort[r];
        sort[r] = t;
        quicksort(sort, l, i-1);                                                  //gehe nun mit der linken bzw. rechten Hälfte im Array, also dem Teil links bzw. rechts des Pivotelements rekursiv vor, bis man eine triviale Lösung der Sortierung erhält, sodass das Array sortiert ist
        quicksort(sort, i+1, r);
    }

    end = clock();
    total = ((double)(end-start))/CLOCKS_PER_SEC;
    return  total;
}



void downheap(int k, int sort[]){
    int j, v;
    v = sort[k];
    while (k <= N/2)
    {
        j = k+k;
        if (j < N && sort[j] < sort[j+1]) j++;
        if (v >= sort[j]) break;
        sort[k] = sort[j]; k = j;
    }
    sort[k] = v;
}
int heapRemove(int sort[]){
    int v = sort[1];
    sort[1] = sort[N--];
    downheap (1, sort);
    return v;
}
void upheap(int k, int sort[]){
    int v;
    v = sort[k];
    sort[0] = INT_MAX;
    while(sort[k/2] <= v){
        sort[k] = sort[k/2];
        k = k/2;
    }
    sort[k] = v;
}
void heapInsert(int v, int sort[]){
    sort[++N] = v;
    upheap(N, sort);
}
/**
 * Implementierung des Heap- Sorts zur Zeitmessung der Dauer dieses Sortierverfahrens.
 * @param sort: Das zu sortierende Array
 * @param laenge: Die Laenge des zu sortienden Arrays
 * @return: Die Dauer, die das Sortierverfahren gebraucht hat
 */
double heapsort(int sort[], int laenge){
    clock_t start, end;
    double total;
    start = clock();

    int k;
    N = 0;
    for(k = 1; k <= laenge; k++) heapInsert(sort[k], sort);
    for(k = laenge; k >= 1; k--) sort[k] = heapRemove(sort);

    end = clock();
    total = ((double)(end-start))/CLOCKS_PER_SEC;
    return  total;
}

/**
 * Sortiert das Array aufsteigend.
 */
void arrayAufsteigend(int arrayToSort[]){
    for (int i = 1; i <= GROESSE; i++) {                                      //Array aufsteigend befüllen:
        arrayToSort[i - 1] = i;
    }
}

/**
 * Sortiert das Array absteigend.
 */
void arrayAbsteigend(int arrayToSort[]) {
    int k = 1;                                                                 //Array absteigend befüllen:
    for (int j = GROESSE - 1; j >= 0; j--) {
        arrayToSort[j] = k;
        k++;
    }
}

/**
 * Sortiert das Array zufällig.
 */
void arrayZufaellig(int arrayToSort[]){
    srand((unsigned) time(NULL));                                              //Array zufällig befüllen:
    for (int l = 0; l < GROESSE; l++) {
        arrayToSort[l] = rand();
    }
}

int main(int argc, char* argv[]){
    int *arrayToSort = malloc(GROESSE*sizeof(int));
    for(int durchlauf = 0; durchlauf < 3; durchlauf++){                        //jedes Sortierverfahren soll drei Mal ausgeführt werden, um nachher ein Durchschnitt bilden zu können

        arrayAufsteigend(arrayToSort);
        ergebnisarray[0][durchlauf] = selectionSort(arrayToSort, GROESSE);      //Sortierungsverfahren für ein aufsteigendes Array ausführen
        arrayAufsteigend(arrayToSort);                                                     //verbrauchte Zeit des Sortierens wird in einem Ergebnisarray gespeichert
        ergebnisarray[3][durchlauf] = insertionsort(arrayToSort, GROESSE);
        arrayAufsteigend(arrayToSort);
        ergebnisarray[6][durchlauf] = shellsort(arrayToSort, GROESSE);
        //arrayAufsteigend(arrayToSort);
        //ergebnisarray[9][durchlauf] = quicksort(arrayToSort, 0, GROESSE-1);
        arrayAufsteigend(arrayToSort);
        ergebnisarray[12][durchlauf] = heapsort(arrayToSort, GROESSE);

        arrayAbsteigend(arrayToSort);
        ergebnisarray[1][durchlauf] = selectionSort(arrayToSort, GROESSE);      //Sortierungsverfahren für ein aufsteigendes Array ausführen
        arrayAbsteigend(arrayToSort);                                                      //verbrauchte Zeit des Sortierens wird in einem Ergebnisarray gespeichert
        ergebnisarray[4][durchlauf] = insertionsort(arrayToSort, GROESSE);
        arrayAbsteigend(arrayToSort);
        ergebnisarray[7][durchlauf] = shellsort(arrayToSort, GROESSE);
        //arrayAbsteigend(arrayToSort);
        //ergebnisarray[10][durchlauf] = quicksort(arrayToSort, 0, GROESSE);
        arrayAbsteigend(arrayToSort);
        ergebnisarray[13][durchlauf] = heapsort(arrayToSort, GROESSE);


        arrayZufaellig(arrayToSort);
        ergebnisarray[2][durchlauf] = selectionSort(arrayToSort, GROESSE);      //Sortierungsverfahren für ein aufsteigendes Array ausführen
        arrayZufaellig(arrayToSort);                                                       //verbrauchte Zeit des Sortierens wird in einem Ergebnisarray gespeichert
        ergebnisarray[5][durchlauf] = insertionsort(arrayToSort, GROESSE);
        arrayZufaellig(arrayToSort);
        ergebnisarray[8][durchlauf] = shellsort(arrayToSort, GROESSE);
        arrayZufaellig(arrayToSort);
        ergebnisarray[11][durchlauf] = quicksort(arrayToSort, 0, GROESSE);
        arrayZufaellig(arrayToSort);
        ergebnisarray[14][durchlauf] = heapsort(arrayToSort, GROESSE);
    }
    printf("Das Ergebnis der Laufzeiten- Analyse der Sortierverfahren ist:\n\n");
    printf("Sorierverfahren             |1\t\t\t\t\t|2\t\t\t\t\t|3\t\t\t\t\t|⌀\t\t\t\t\t|\n\n");
    printf("Selectionsort: Aufsteigend  |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[0][0], ergebnisarray[0][1], ergebnisarray[0][2], (ergebnisarray[0][0] + ergebnisarray[0][1] + ergebnisarray[0][2])/3);
    printf("Selectionsort: Absteigend   |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[1][0], ergebnisarray[1][1], ergebnisarray[1][2], (ergebnisarray[1][0] + ergebnisarray[1][1] + ergebnisarray[1][2])/3);
    printf("Selectionsort: Zufällig     |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[2][0], ergebnisarray[2][1], ergebnisarray[2][2], (ergebnisarray[2][0] + ergebnisarray[2][1] + ergebnisarray[2][2])/3);
    printf("Insertionsort: Aufsteigend  |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[3][0], ergebnisarray[3][1], ergebnisarray[3][2], (ergebnisarray[3][0] + ergebnisarray[3][1] + ergebnisarray[3][2])/3);
    printf("Insertionsort: Absteigend   |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[4][0], ergebnisarray[4][1], ergebnisarray[4][2], (ergebnisarray[4][0] + ergebnisarray[4][1] + ergebnisarray[4][2])/3);
    printf("Insertionsort: Zufällig     |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[5][0], ergebnisarray[5][1], ergebnisarray[5][2], (ergebnisarray[5][0] + ergebnisarray[5][1] + ergebnisarray[5][2])/3);
    printf("Shellsort: Aufsteigend      |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[6][0], ergebnisarray[6][1], ergebnisarray[6][2], (ergebnisarray[6][0] + ergebnisarray[6][1] + ergebnisarray[6][2])/3);
    printf("Shellsort: Absteigend       |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[7][0], ergebnisarray[7][1], ergebnisarray[7][2], (ergebnisarray[7][0] + ergebnisarray[7][1] + ergebnisarray[7][2])/3);
    printf("Shellsort: Zufällig         |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[8][0], ergebnisarray[8][1], ergebnisarray[8][2], (ergebnisarray[8][0] + ergebnisarray[8][1] + ergebnisarray[8][2])/3);
    printf("Quicksort: Aufsteigend      |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[9][0], ergebnisarray[9][1], ergebnisarray[9][2], (ergebnisarray[9][0] + ergebnisarray[9][1] + ergebnisarray[9][2])/3);
    printf("Quicksort: Absteigend       |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[10][0], ergebnisarray[10][1], ergebnisarray[10][2], (ergebnisarray[10][0] + ergebnisarray[10][1] + ergebnisarray[10][2])/3);
    printf("Quicksort: Zufällig         |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[11][0], ergebnisarray[11][1], ergebnisarray[11][2], (ergebnisarray[11][0] + ergebnisarray[11][1] + ergebnisarray[11][2])/3);
    printf("Heapsort: Aufsteigend       |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[12][0], ergebnisarray[12][1], ergebnisarray[12][2], (ergebnisarray[12][0] + ergebnisarray[12][1] + ergebnisarray[12][2])/3);
    printf("Heapsort: Absteigend        |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n", ergebnisarray[13][0], ergebnisarray[13][1], ergebnisarray[13][2], (ergebnisarray[13][0] + ergebnisarray[13][1] + ergebnisarray[13][2])/3);
    printf("Heapsort: Zufällig          |%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|%.5f\t\t\t|\n\n", ergebnisarray[14][0], ergebnisarray[14][1], ergebnisarray[14][2], (ergebnisarray[14][0] + ergebnisarray[14][1] + ergebnisarray[14][2])/3);
}