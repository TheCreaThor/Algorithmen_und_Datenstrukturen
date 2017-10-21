#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Knoten {
    int key;
    struct Knoten *next;
};

void linsert(struct Knoten *schlange, int key) {


    /*if (anfang == NULL) { //Wenn die Liste leer ist, das neue Element am Anfang einfügen
        anfang = neues_element;
        neues_element->next = NULL; //Da das neue Element am Ende der Liste eingefügt werden soll, muss der nächste Pointer auch auf NULL zeigen
        neues_element->previous = NULL; //Da das neue Element bei leerer Liste am Anfang steht, kann auch der previous- Pointer auf NULL gesetzt werden
    } else {
        struct vokabel *ptr = anfang; //Durchlaufs- Pointer für die Liste erstellen

        while (ptr->next != NULL) { //Bis an das Ende der Liste laufen
            ptr = ptr->next;
        }
        neues_element->previous = ptr; //neues Element muss auf das letzte "alte" Element der Liste zeigen
        ptr->next = neues_element; //Das neue Element wird hinter dem Pointer EINGEFÜGT
        neues_element->next = NULL; //neues Element ist AM ENDE der Liste und muss somit einen NULL- POINTER bekommen

    }*/

}

/*
 * Gib alle Vokabeln aus der Liste aus
 */
void printList(struct vokabel *schlange) {
    struct vokabel *ptr = anfang; //Durchlaufs- Pointer erstellen

    printf("Der Inhalt der Liste ist(vorwärts ausgegeben):\n");

    if (anfang == NULL) { //man kann nichts ausgeben
        printf("Die Liste ist leer! Es kann nichts ausgegeben werden.\n\n");
    }

    while (ptr != NULL) { //Die ganze Liste durchlaufen
        printf("%s;%s\n", ptr->deutsch, ptr->englisch); //Element an der jeweiligen Stelle ausgeben
        ptr = ptr->next;
    }
}

int ldelete(struct Knoten *schlange, int key) {
    char deutsch[MAX];

    if (anfang == NULL) { //man kann nichts löschen
        printf("Die Liste ist leer! Es kann nichts gelöscht werden.\n\n");
        return 0;
    } else {
        printf("Geben sie die zu löschende deutsche Vokabel ein:\n");
        fflush(stdout);
        fgets(deutsch, MAX, stdin);
        strtok(deutsch, "\r");
    }

    struct vokabel *prev = NULL;
    struct vokabel *cur = anfang;
    struct vokabel *later = cur->next;

    while (cur != NULL) { //Solange man nicht am Ende der Liste angekommen ist
        if (strcmp(cur->deutsch, deutsch) ==
            0) { //bei ==o sind die strings gleich, negativer Wert ist s1 kleiner als s2, positiver Wert ist s1 größer als s2
            if (prev == NULL) {
                printf("Erstes Element kann nicht gelöscht werden!\n\n");
                return 0;
            }

            prev->next = cur->next; //Der vorherige Zeiger(vor dem Aktuellen) bekommt den nächsten Zeiger des Aktuellen zugewiesen
            if (later != NULL) {
                later->previous = cur->previous; //Der nächste Zeiger(nach dem Aktuellen) bekommt den vorherigen Zeiger des Aktuellen zugewiesen
            }
            free(cur);
            printf("Das Element wurde erfolgreich gelöscht!\n\n");
            return 1;
        }
        if (cur->next == NULL) {
            printf("Element nicht vorhanden!\n\n");
            return 0;
        } else {
            prev = cur; //Zeiger rücken jeweils um eine Stelle weiter
            cur = later;
            later = later->next;
        }
    }
    return 0;
}

struct Knoten *linit(){
    struct Knoten *end;//Das Template für das Ende- Element wird erstellt
    end = malloc(sizeof(struct Knoten)); //Größe für das Ende- Element wird alluziiert
    if (end == NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
        printf("Fehler bei malloc()\n");
        exit(EXIT_FAILURE);
    }
    return end;
}

int main(void) {

    int entscheidung = 0;
    //char buffer[MAX]; //Um unnötige Eingaben zu ignorieren

    struct Knoten *list;
    list = linit();

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

            struct Knoten *neues_element;//Das Template für das einzuordnende Element wird erstellt
            neues_element = malloc(sizeof(struct Knoten)); //Größe für das neue Element wird alluziiert
            if (neues_element == NULL) { //Fehlerüberprüfung ob überhaupt genügend Speicher alluziiert werden kann
                printf("Fehler bei malloc()\n");
                exit(EXIT_FAILURE);
            }
            linsert(neues_element, key);
        }

        if (entscheidung == 2)
            ldelete(schlange, key);

        if (entscheidung == 3)
            printList(schlange);
    }
    return EXIT_SUCCESS;
}