#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 7                          //Primzahl, damit alle Zahlen berücksichtigt werden!
#define ZUFALLARRAYGROESSE 49
#define DURCHLAEUFE 1
#define UEBERSICHT 100

/**
 * Erstelle eine Vorlage für einen Knoten, um die Werte zu speichern und gegebenenfalls bei gleichem Hash- Wert an der gleichen Stelle des Arrays zu verketten.
 */
static struct node {
    int key;
    int info;
    struct node *next;
};

static struct node *koepfe[M], *ende, *newNode, *temp, *start, *freetemp;    //erstelle einen Knotenarray mit insgesamt M Plätzen

/**
 * Befülle den Pool mit Zufallszahlen.
 * @param array: Das Array, was mit Zufallszahlen befüllt werden soll
 */
void fillArray(int array[]) {
    srand((unsigned) time(NULL));
    for (int i = 0; i < ZUFALLARRAYGROESSE; i++) {
        array[i] = rand() % UEBERSICHT;
    }
}

/**
 * Initialisiere das Köpfearray.
 */
void hashlistinitialize() {
    ende = malloc (sizeof *ende);
    ende->next = ende;
    ende->info = -1;
    for(int i = 0; i < M; i++){
        koepfe[i] = malloc (sizeof *ende);
        koepfe[i]->next = ende;
    }
}

/**
 * Berechne Hash für den Key.
 * @param v
 * @return
 */
unsigned hash (int v)
{
    return (unsigned)v % M;
}

/**
 * Füge Element an seinen durch den Hash bestimmten Platz hinzu.
 * @param key: Der Wert aus dem Zufallsarray der in die Liste eingespeichert werden soll
 * @param hash: Der berechnete Hashwert, auf dem der Wert aus dem Array gespeichert werden soll
 * @param uberlaufCounter: Zaehlt die Ueberlaeufe im Koepfe- Array pro Stelle im Array, also immer dort, wo sich mehr als ein Knoten an Stelle X im Array befindet
 */
void hashinsert(int key, int hash, int uberlaufCounter[]){
    newNode = malloc(sizeof(*ende));                       //erstellt einen neuen Knoten für den einzufügenden Wert

    if(koepfe[hash]->next == ende){                        //wenn an der Stelle des Hash- Wertes im Array noch KEIN ANDERER KNOTEN eingefügt wurde
        temp = koepfe[hash]->next;                         //damit man den Pointer auf den Ende- Knoten nicht verliert, wird dort ein temporaerer Pointer drauf gesetzt
        koepfe[hash]->next = newNode;                      //neuer Knoten wird eingefügt
        newNode->key = key;                                //befuelle newNode mit Werten
        newNode->info = hash;
        newNode->next = temp;
    }
    else{                                                  //wenn an der Stelle des Hash- Wertes im Array BEREITS EIN ANDERER KNOTEN eingefügt wurde
        start = koepfe[hash];
        while(start->next != ende){                        //laufe an das Ende der Liste
            start = start->next;
        }                                                  //Neue Verpointerung:
        temp = start->next;                                //damit man den Pointer auf den Ende- Knoten nicht verliert, wird dort ein temporaerer Pointer drauf gesetzt
        start->next = newNode;                             //neuer Knoten wird eingefügt
        newNode->key = key;                                //befuelle newNode mit Werten
        newNode->info = hash;
        newNode->next = temp;
        uberlaufCounter[hash]+=1;
    }
}

/**
 * Ausgabe der Liste
 */
void printListe() {
    for(int i = 0; i < M; i++) {                           //alle Listenkoepfe sollen abgelaufen werden
        start = koepfe[i];
        printf("%d: ", i);                               //welcher Listenkopf?
        while(start->next != ende){                        //alle Elemente im jeweiligen Listenkopf ausgeben
            start = start->next;
            printf("%2d ", start->key);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Berechne den maximalen, minimalen und durchschnittlichen Ueberlauf der Liste und gebe ihn tabellarisch aus.
 * @param ueberlaufCounter: hierin wurden die Ueberlaeufe beim jeweiligen Listenkopf gespeichert
 */
void printUeberlauf(int ueberlaufCounter[]) {
    int max = ueberlaufCounter[0], min = ueberlaufCounter[0], durchschnitt = ueberlaufCounter[0], maxcounter = 1, mincounter = 1; //zunaechst werden Anfangswerte gesetzt, damit man diese mit den Werten fuer die folgende Liste vergleichen kann

    for (int i = 1; i < M; i++) {                   //die gesamte Liste durchlaufen, um die gewünschten Werte zu suchen
        durchschnitt += ueberlaufCounter[i];        //um nachher einen Durchschnitt berechnen zu können, addiere zunaechst alle Ueberlaeufe

        if(ueberlaufCounter[i] > max){              //wenn es einen Wert im Ueberlauf- Array gibt, der groesser als das aktuelle Maximum ist
            max = ueberlaufCounter[i];
            maxcounter = 1;
            continue;                               //naechster Schleifendurchlauf, damit die Haeufigkeit nicht inkrementiert wird
        }
        if(ueberlaufCounter[i] == max){             //wenn der maximale Wert oefters auftritt, inkrementiere die Haeufigkeit um eins
            maxcounter++;
        }

        if(ueberlaufCounter[i] < min){              //wenn es einen Wert im Ueberlauf- Array gibt, der kleiner als das aktuelle Minimum ist
            min = ueberlaufCounter[i];
            mincounter = 1;
            continue;                               //naechster Schleifendurchlauf, damit die Haeufigkeit nicht inkrementiert wird
        }
        if(ueberlaufCounter[i] == min){             //wenn der minimale Wert oefters auftritt, inkrementiere die Haeufigkeit um eins
            mincounter++;
        }
    }

    printf("\t\t\t\t|Überlauflänge:\t|Häufigkeit:\t|\nMinimum:\t\t|%2d\t\t\t\t|%2d\t\t\t\t|\nMaximum:\t\t|%2d\t\t\t\t|%2d\t\t\t\t|\nDurchschnitt:\t|%2d\t\t\t\t| /\t\t\t\t|\n",min, mincounter, max, maxcounter, durchschnitt/M);
}

/**
 * Gebe den Speicher vor Beendigung des Programms frei
 */
void freeSpeicher(){
    for (int i = 0; i < M; i++) {       //durchlaufe alle Kopfpositionen
        temp = koepfe[i]->next;

        while(temp != ende){            //den Speicher fuer alle Listen an den jeweiligen Kopfpositionen freigeben
            freetemp = temp;
            temp = temp->next;
            free(freetemp);
        }
        free(koepfe[i]);                //zuletzt auch immer den jeweiligen Kopf- Knoten an der jeweiligen Position freigeben
    }
    free(temp);
}

/**
 * Hier werden Werte eines zufaellig initialisiertes Array mit Hilfe eines Hashverfahrens in die jeweilige einfach verkettete Liste einsortiert,
 * wobei der Anfang einer solchen Liste immer den mit der Hashzahl jeweilig passenden Listenkoepf darstellt.
 * Die Listen werden am Schluss mit dem jeweiligen Listenkopf ausgeben, wobei der X. Listenkopf der X. Aequivalenzklasse von M entspricht.
 * Zudem wird noch die maximale, minimale und durchschnittliche Laenge aller Listen berechnet und ausgegeben.
 * @param argc: Anzahl der Parameter (in der Shell)
 * @param argv: einzelnen übergebenen Werte (in der Shell)
 * @return: Abbruchbeding
 */
int main(int argc, char* argv[]) {
    int zufallArray[ZUFALLARRAYGROESSE];                                                                       //ein Array fuer zufaellige Werte
    int uberlaufCounter[M] = {0};                                                                              //an M- ter Stelle in der Listenkoepfe der Knotenliste wird gezaehlt, wie oft es einen Ueberlauf gibt und diese Anzahl wird an der jeweiligen Stelle im ueberlaufCounter- Array festgehalten

    for (int k = 0; k < DURCHLAEUFE; k++) {                                                                    //Anzahl der Durchläufe des Programms
        fillArray(zufallArray);                                                                                //fülle Array mit Zufallszahlen
        hashlistinitialize();                                                                                  //initialisiere Koepfearray
        for(int i = 0; i < ZUFALLARRAYGROESSE; i++){                                                           //hashe jede Zahl im Array und füge sie der Liste hinzu. Zähle zudem die Überläufe.
            hashinsert(zufallArray[i], hash(zufallArray[i]), uberlaufCounter);
        }
        printListe();                                                                                          //Ausgabe der Listenkoepfe- Listen
        printUeberlauf(uberlaufCounter);                                                                       //berechne die Ueberlaeufe und gebe sie tabellarisch aus
        freeSpeicher();                                                                                        //den Speicher wieder freigeben
    }
    return 0;
}