#include <stdio.h>
#include <stdlib.h>
//test
/**
 *  Erstellen eines Templates eines Knotens, um eine Liste erstellen zu koennen.
 */
 struct Knoten
 {
     int key;               //der Wert des Keys
     struct Knoten *next;   //Zeiger auf das naechste Element
 };

/**
 * Diese Methode loescht ein vom Benutzer uebergebenes Element, wenn es in der Liste vorhanden ist. Wenn nicht, wird eine Meldung ausgegeben.
 * @param schlange Liste aus der das Element geloescht werden soll
 * @param key Das zu loeschende Element
 * @return Return 0: Das zu loeschende Element wurde nicht gefunden und konnte somit nicht geloescht werden, Return 1: Das Element wurde erfolgreich geloescht.
 */
int ldelete(struct Knoten** schlange, int key){
    struct Knoten* zwischenspeicher; //Hilfreich beim Verschieben eines Zeiger, sodass man ein Element nicht in der Leere zu verliert
    zwischenspeicher = (struct Knoten *) malloc(sizeof(*zwischenspeicher)); // Erzeuge einen neuen Knoten
    if (zwischenspeicher == NULL) { //Fehlerueberpruefung ob ueberhaupt genuegend Speicher alluziiert werden kann
        printf("Fehler bei malloc()\n");
        exit(EXIT_FAILURE);
    }

    while(*schlange != NULL){ //Alle Elemente durchgehen
        if(key == (*schlange)->key){
            if((*schlange)->next == NULL){ //Wenn das Element am Ende der Liste ist (bzw alleine, was dann ja gleichzeitig das Ende ist)
                zwischenspeicher = *schlange;
                *schlange = NULL;
                free(zwischenspeicher);
                return 1;
            }
            else {                         //Wenn das Element in der Mitte der Liste ist
                zwischenspeicher = *schlange;
                *schlange = (*schlange)->next;
                free(zwischenspeicher);
                return 1;
            }
        }
        schlange = &(*schlange)->next;
    }
    return 0;
}

/**
 * Funktion, um einzelne Knoten in sortierter Reihenfolge einzufuegen. Ein Element wird in die Liste "schlange" einsortiert.
 * @param schlange Liste, wo das Element/ Der Key eingefuegt werden soll
 * @param key Das einzufuegende Element
 */
void linsert(struct Knoten **schlange, int key)
{
    if(*schlange != NULL) {
        if (key < (*schlange)->key) { //Wenn das Element bereits kleiner als das Element des Anfangs ist, dann sortiere das Neue vor den Anfang
            struct Knoten *neuesElement;
            neuesElement = (struct Knoten *) malloc(sizeof(*neuesElement)); //Erzeuge einen neuen Knoten
            if (neuesElement ==
                NULL) { //Fehlerueberpruefung ob ueberhaupt genuegend Speicher alluziiert werden kann
                printf("Fehler bei malloc()\n");
                exit(EXIT_FAILURE);
            }
            neuesElement->key = key;
            neuesElement->next = *schlange;
            *schlange = neuesElement;
            return;
        }
    }
    //Bis zum Ende der Schlange laufen, damit man den neuen Knoten einfuegen kann
    while( *schlange != NULL ) {
        if (key >= (*schlange)->key) { //Laufe solange durch, bis ein Element der Liste kleiner ist als das einzufuegende Element und fuege es dann dort ein
            if ((*schlange)->next != NULL) {
                if (key < ((*schlange)->next)->key) {
                    struct Knoten *neuesElement;
                    neuesElement = (struct Knoten *) malloc(sizeof(*neuesElement)); // Erzeuge einen neuen Knoten
                    if (neuesElement ==
                        NULL) { //Fehlerueberpruefung ob ueberhaupt genuegend Speicher alluziiert werden kann
                        printf("Fehler bei malloc()\n");
                        exit(EXIT_FAILURE);
                    }

                    neuesElement->key = key;
                    if ((*schlange)->next == NULL) { //Wenn das Element erst am Ende einfuegen muss
                        neuesElement->next = NULL;
                        (*schlange)->next = neuesElement;
                        return;
                    } else {
                        neuesElement->next = (*schlange)->next; //Wenn man das Element in der Mitte einfuegen muss
                        (*schlange)->next = neuesElement;
                        return;
                    }
                }
            }
        }
        schlange = &(*schlange)->next;
    }

    if(*schlange == NULL){ //Wenn die Liste leer ist, dann fuege es als erstes Element in die Liste ein
        struct Knoten *neuesElement;
        neuesElement = (struct Knoten *) malloc(sizeof(*neuesElement)); // Erzeuge einen neuen Knoten
        if (neuesElement == NULL) { //Fehlerueberpruefung ob ueberhaupt genuegend Speicher alluziiert werden kann
            printf("Fehler bei malloc()\n");
            exit(EXIT_FAILURE);
        }

        neuesElement->key = key;
        neuesElement->next = NULL;

        *schlange = neuesElement;
        return;
    }

}

/**
 * Ueberprueft, ob die Liste leer ist oder mit Elementen befuellt ist.
 * @param schlange Die Liste, die ueberprueft werden soll
 * @return Return 1: Wenn die Liste leer ist, Return 0: Wenn die Liste mit mindestens einem Element befuellt ist
 */
int isempty(struct Knoten* schlange){
    if(schlange == NULL){
        return 1;
    }
    else{
        return 0;
    }

}

/**
 * Die komplette Liste wird ausgegeben, wenn sie leer ist, wird dieses mitgeteilt.
 * @param schlange Ist die Liste die ausgegeben werden soll
 */
 void printList(struct Knoten *schlange)
 {
     if(isempty(schlange) == 1){
         printf("Die Liste ist leer!");
     }
     while(schlange != NULL){
         printf("%d,", schlange->key);
         schlange = schlange->next;
     }
     printf("\n\n");
 }

/**
 * Hier wird eine leere Liste erstellt.Es wird Speicherplatz fuer den Listenanfang aluziiert.
 * @return Die leere Liste wird zurueckgegeben.
 */
    struct Knoten* linit(){
        struct Knoten *anfang;
        anfang = (struct Knoten *) malloc(sizeof(*anfang)); // Erzeuge einen neuen Knoten
        if (anfang == NULL) { //Fehlerueberpruefung ob ueberhaupt genuegend Speicher alluziiert werden kann
            printf("Fehler bei malloc()\n");
            exit(EXIT_FAILURE);
        }
        anfang = NULL; //Leere Liste
        return anfang;
    }

/**
 * Hier laeuft der gesamte Prozess ab und die Fuktionen werden, je nach Benutzereinabe, aufgerufen.
 * @return Gibt 0 zurueck, wenn das Programm erfolgreich beendet wurde, andernfalls gibt return einen anderen Wert außer 0 zurueck
 */
int main(void) {

    int entscheidung = 0;
    //char buffer[MAX]; //Um unnoetige Eingaben zu ignorieren

    struct Knoten *schlange;
    schlange = linit();

    while (entscheidung != 5) {
        entscheidung = 0;

        printf("Menue zur Warteschlangenverwaltung:\n");
        printf("Sortiertes Einfuegen eines Elementes(1)\nLoeschen und Ausgeben des Elements mit Schluessel(2)\nAusgeben der Liste(3)\nListe leer?(4)\nProgramm beenden(5)\n");
        fflush(stdout);

        scanf("%d", &entscheidung);
        //fgets(buffer, MAX, stdin); //Um unnoetige Eingaben zu ignorieren, die keine Zahlen sind

        if (entscheidung == 1) {
            int key;
            printf("Geben Sie einen Wert ein:\n");
            scanf("%d", &key);
            linsert(&schlange, key);
        }

        if (entscheidung == 2) {
            int key;
            int ergebnis;
            printf("Geben Sie einen Wert ein:\n");
            scanf("%d", &key);
            ergebnis = ldelete(&schlange, key);
            if(ergebnis == 1){
                printf("Das Element wurde erfolgreich geloescht!\n\n");
            }
            else{
                printf("Das Element konnte nicht gefunden und somit nicht geloescht werden!\n\n");
            }
        }

        if (entscheidung == 3)
            printList(schlange);

        if (entscheidung == 4){
            int ergebnis;
            ergebnis = isempty(schlange);
            if(ergebnis){
                printf("Die Liste ist leer.\n\n");
            }
            else{
                printf("Die Liste ist nicht leer.\n\n");
            }
        }
    }
    return EXIT_SUCCESS;
}
