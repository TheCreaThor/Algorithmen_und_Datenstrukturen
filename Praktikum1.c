#include <stdio.h>
#include <stdlib.h>

 struct Knoten
 {
     int key;               //der Wert des Keys
     struct Knoten *next;   //Zeiger auf das nächste Element
 };

void linsert(struct Knoten **schlange, int key)
{
    //Bis zum Ende der Schlange laufen, damit man den neuen Knoten einfügen kann
    while( *schlange != NULL )
    {
        if(key > (*schlange)->key) {
            struct Knoten *neuesElement;
            neuesElement = (struct Knoten*)malloc(sizeof(*neuesElement)); // Erzeuge einen neuen Knoten
            if (neuesElement == NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
                printf("Fehler bei malloc()\n");
                exit(EXIT_FAILURE);
            }

            neuesElement->key = key;
            if((*schlange)->next == NULL){
                neuesElement->next = NULL;
                (*schlange)->next = neuesElement;
                return;
            } else{
                neuesElement->next = (*schlange)->next;
                (*schlange)->next = neuesElement;
                return;
            }
        }
        schlange = &(*schlange)->next;
    }

    if( *schlange == NULL ) {
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

 void printList(const struct Knoten *schlange)
 {
     for( ; schlange != NULL ; schlange = schlange->next )
     {
         printf("%d,", schlange->key);
         printf("\n");
     }
 }

int main(void) {

    int entscheidung = 0;
    //char buffer[MAX]; //Um unnötige Eingaben zu ignorieren

    struct Knoten *schlange;
    schlange = NULL; //Leere Liste
    //schlange = linit();

    while (entscheidung != 4) {
        entscheidung = 0;

        printf("Menue zur Warteschlangenverwaltung:\n\n");
        printf("Sortiertes Einfuegen eines Elementes(1)\nLoeschen und Ausgeben des Elements mit Schluessel(2)\nAusgeben der Liste(3)\nProgramm beenden(4)\n");
        fflush(stdout);

        scanf("%d", &entscheidung);
        //fgets(buffer, MAX, stdin); //Um unnötige Eingaben zu ignorieren, die keine Zahlen sind

        if (entscheidung == 1) {
            int key;
            printf("Geben Sie einen Wert ein:\n");
            scanf("%d", &key);

            linsert(&schlange, key);
        }

        //if (entscheidung == 2)
        //    ldelete(schlange, key);

        if (entscheidung == 3)
            printList(schlange);
    }
    return EXIT_SUCCESS;
}