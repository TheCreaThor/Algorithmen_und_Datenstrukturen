#include <stdio.h>
#include <stdlib.h>

/**
 *  Erstellen eines Templates eines Knotens, um eine Liste erstellen zu können.
 */
 struct Knoten
 {
     int key;               //der Wert des Keys
     struct Knoten *next;   //Zeiger auf das nächste Element
 };

int ldelete(struct Knoten** schlange, int key){
    struct Knoten* zwischenspeicher;
    zwischenspeicher = (struct Knoten *) malloc(sizeof(*zwischenspeicher)); // Erzeuge einen neuen Knoten
    if (zwischenspeicher == NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
        printf("Fehler bei malloc()\n");
        exit(EXIT_FAILURE);
    }

    while(*schlange != NULL){
        if(key == (*schlange)->key){
            if((*schlange)->next == NULL){
                (*schlange)->next = *schlange;
            }
            else {
                zwischenspeicher = *schlange;
                *schlange = (*schlange)->next;
                free(zwischenspeicher);
            }
        }
        schlange = &(*schlange)->next;
    }
    return 0;
}

/**
 * Funktion, um einzelne Knoten in sortierter Reihenfolge einzufügen. Ein Element wird in die Liste "schlange" einsortiert.
 * @param schlange Liste, wo das Element/ Der Key eingefügt werden soll
 * @param key Das einzufügende Element
 */
void linsert(struct Knoten **schlange, int key)
{
    if(*schlange != NULL) {
        if (key < (*schlange)->key) {
            struct Knoten *neuesElement;
            neuesElement = (struct Knoten *) malloc(sizeof(*neuesElement)); // Erzeuge einen neuen Knoten
            if (neuesElement ==
                NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
                printf("Fehler bei malloc()\n");
                exit(EXIT_FAILURE);
            }
            neuesElement->key = key;
            neuesElement->next = *schlange;
            *schlange = neuesElement;
            return;
        }
    }
    //Bis zum Ende der Schlange laufen, damit man den neuen Knoten einfügen kann
    while( *schlange != NULL ) {
        if (key >= (*schlange)->key) {
            if ((*schlange)->next != NULL) {
                if (key < ((*schlange)->next)->key) {
                    struct Knoten *neuesElement;
                    neuesElement = (struct Knoten *) malloc(sizeof(*neuesElement)); // Erzeuge einen neuen Knoten
                    if (neuesElement ==
                        NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
                        printf("Fehler bei malloc()\n");
                        exit(EXIT_FAILURE);
                    }

                    neuesElement->key = key;
                    if ((*schlange)->next == NULL) {
                        neuesElement->next = NULL;
                        (*schlange)->next = neuesElement;
                        return;
                    } else {
                        neuesElement->next = (*schlange)->next;
                        (*schlange)->next = neuesElement;
                        return;
                    }
                }
            }
        }
        schlange = &(*schlange)->next;
    }

    if(*schlange == NULL){
        struct Knoten *neuesElement;
        neuesElement = (struct Knoten *) malloc(sizeof(*neuesElement)); // Erzeuge einen neuen Knoten
        if (neuesElement == NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
            printf("Fehler bei malloc()\n");
            exit(EXIT_FAILURE);
        }

        neuesElement->key = key;
        neuesElement->next = NULL;

        *schlange = neuesElement;
        return;
    }

}

int isempty(struct Knoten* schlange){
    if(schlange == NULL){
        return 1;
    }
    else{
        return 0;
    }

}

/**
 * Die komplette Liste wird ausgegeben.
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
 * Hier wird eine leere Liste erstellt.Es wird Speicherplatz für den Listenanfang aluziiert.
 * @return Die leere Liste wird zurückgegeben.
 */
    struct Knoten* linit(){
        struct Knoten *anfang;
        anfang = (struct Knoten *) malloc(sizeof(*anfang)); // Erzeuge einen neuen Knoten
        if (anfang == NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
            printf("Fehler bei malloc()\n");
            exit(EXIT_FAILURE);
        }
        anfang = NULL; //Leere Liste
        return anfang;
    }

/**
 * Hier läuft der gesamte Prozess ab und die Fuktionen werden, je nach Benutzereinabe, aufgerufen.
 * @return Gibt 0 zurück, wenn das Programm erfolgreich beendet wurde, andernfalls gibt return einen anderen Wert außer 0 zurück
 */
int main(void) {

    int entscheidung = 0;
    //char buffer[MAX]; //Um unnötige Eingaben zu ignorieren

    struct Knoten *schlange;
    schlange = linit();

    while (entscheidung != 5) {
        entscheidung = 0;

        printf("Menue zur Warteschlangenverwaltung:\n");
        printf("Sortiertes Einfuegen eines Elementes(1)\nLoeschen und Ausgeben des Elements mit Schluessel(2)\nAusgeben der Liste(3)\nListe leer?(4)\nProgramm beenden(5)\n");
        fflush(stdout);

        scanf("%d", &entscheidung);
        //fgets(buffer, MAX, stdin); //Um unnötige Eingaben zu ignorieren, die keine Zahlen sind

        if (entscheidung == 1) {
            int key;
            printf("Geben Sie einen Wert ein:\n");
            scanf("%d", &key);
            linsert(&schlange, key);
        }

        if (entscheidung == 2) {
            int key;
            printf("Geben Sie einen Wert ein:\n");
            scanf("%d", &key);
            ldelete(&schlange, key);
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