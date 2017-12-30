#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABETGROESSE 26
#define MAX 100

/**
 * Gibt, egal ob Klein- oder Grossbuchstabe, die i. Position des uebergebenen Buchstaben im deutschen Alphabet an.
 * @param c: der uebergebene Buchstabe, von dem man die i. Position wissen möchte
 * @return: 0: wenn 'c' ein Leerzeichen ist, 1-26: ein i. Buchstabe im Alphabet, -1: kein Leerzeichen oder Buchstabe
 */
int returnIndex(char c) {
    if (c == ' ') {
        return 0;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 1;
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else return -1;
}

/**
 * Befüllt ein skip- Array, das als eine Art Tabelle dient, um nachher beim Suchen des SuchWortes zu schauen,
 * wie weit man das zu suchende Wort(je nach aktuellen Buchstabe des Textes) nach rechts verschieben darf,
 * wenn die zu vergleichenden Buchstaben(einmal vom SuchWort und einmal vom Text) unterschiedlich sind.
 * @param suchText: der zu suchende suchText im Text
 * @param skip: das als Tabelle dienende skip- Array
 */
void initskip(char suchText[], int skip[]){
    int m = (int)strlen(suchText);

    for(int i = 0; i < ALPHABETGROESSE; i++) {
        skip[i] = m;
    }

    for(int j = 0; j<m-1; j++){
        skip[returnIndex(suchText[j])] = m-j-1;
    }
}

/**
 * Funktion um eine bestimmte Buchstabenfolge in einem Text zu suchen.
 * @param suchText: der zu suchende Text/Zeichenfolge
 * @param text: der Text worin gesucht wird
 * @param skip: die Tabelle(Array), worin steht, wie weit das SuchWort nach rechts verschoben werden kann,
 *              wenn es zu einen Unterschied zwischen den Buchstaben im SuchWort und im zu suchenden Text gibt
 * @return: -1: die zu suchende Zeichenkette im Text wurde nicht gefunden
 *           X: die zu suchende Zeichenkette wurde ab X. Stelle im Text gefunden
 */
int mischarsearch(char suchText[], char text[], int skip[]) {
    int laengeSuche = (int)strlen(suchText);
    int laengeText = (int)strlen(text);
    int i, j, t;

    initskip(suchText, skip);
                                                                      //i: für die i. Stelle im zu suchenden Text, j: für die j. Stelle in der Zeichenfolge
    for (i = laengeSuche-1, j = laengeSuche-1; j >= 0; i--, j--) {    //"-1", da strlen-1 die letzte Stelle des Array angibt
        while (text[i] != suchText[j]) {                              //wenn die Buchstaben an der gleichen Stelle ungleich sind
            t = skip[returnIndex(text[i])];                           //suche den Wert aus der skip- Tabelle wie weit man nach rechts springen muss, um weiter zu suchen
            i += (laengeSuche - j > t) ? laengeSuche - j : t;         //springe um skip(t), mindestens aber um 1 nach rechts oder springe um ein ganzes Wort(Fall, wenn if wahr ist)
            if (i >= laengeText) return -1;                           //der Fall, wenn das Wort nicht gefunden wurde und man am Ende des Textes angelangt ist
            j = laengeSuche - 1;                                      //setze Musterzeiger ganz nach rechts, um eine erneute Suche der Zeichenfolge vorzubereiten
        }
    }
    return i+1;
}

/**
 * Der Benutzer gibt ein zu suchendes Wort ein. Dieses Wort wird mithilfe des mischarsearch- Algorithmus gesucht.
 * Danach wird eine dazu passende Ausgabe gemacht, ob das Wort gefunden wurde oder nicht.
 * @param text: der konstante Text, in dem gesucht werden soll
 * @param suchText: das zu suchende Suchwort
 * @param skip: die Tabelle(Array), worin steht, wie weit das SuchWort nach rechts verschoben werden kann,
 *              wenn es zu einen Unterschied zwischen den Buchstaben im SuchWort und im zu suchenden Text gibt
 */
int ergebnisMischarsearch(char text[], char suchText[], int skip[]) {
    int ergebnis = mischarsearch(suchText, text, skip);
    if(ergebnis == -1){
        printf("Das Wort wurde nicht gefunden!\n\n");
    }else{
        printf("Das Wort wurde ab %d. Stelle im zu suchenden Text gefunden!\n\n", ergebnis+1);
    }
    return ergebnis;
}

/**
 * Gibt den gesamten Text mit markiertem Suchtwort aus.
 * @param text: der konstante Text, in dem gesucht werden soll
 * @param suchText: das zu suchende Suchwort
 * @param ergebnis: die Stelle, ab der das Suchwort gefunden wurde, bei Wert '-1' wurde das Wort nicht gefunden
 */
void ergebnisAusgabe(char text[], char suchText[], int ergebnis) {
    if(ergebnis == -1){
        printf("Das Suchwort konnte nicht gefunden und somit nicht im Text angezeigt werden!\n\n");
        return;
    }
    for (int i = 0; i < ergebnis ; ++i) {
        printf("%c", text[i]);
    }
    printf("--->%s<---",suchText);
    for (int j = ergebnis+(int)strlen(suchText); j < (int)strlen(text); j++) {
        printf("%c", text[j]);
    }
    printf("\n\n");
}

/**
 * @param argc: Anzahl der Parameter (in der Shell)
 * @param argv: einzelnen übergebenen Werte (in der Shell)
 * @return: Abbruchbeding
 */
    int main(int argc, char *argv[]) {
        char text[] = "Weit hinten, hinter den Wortbergen, fern der Länder Vokalien und Konsonantien leben die Blindtexte";
        int skip[ALPHABETGROESSE]; //Buchstaben von 1-26; 0. Stelle fuer Leerzeichen reserviert
        char suchText[MAX];

        printf("Menü\nGeben Sie an, was Sie machen wollen:\n\n");
        int eingabe = 1;
        int ergebnis = -1;
        while(eingabe != 5){
            printf("1) konstanten Text ausgeben\n2) Suchwort eingeben und prüfen[mit Boyer- Moore]\n3) Suchwort eingeben und prüfen[mit Rabin- Karp]\n4) Suchwort im Text anzeigen lassen\n5) Programm beenden\n\n");
            scanf("%d",&eingabe);
            switch(eingabe){
                case 1: printf("%s\n\n",text); break;
                case 2: printf("Geben sie ein zu suchendes Wort ein:\n");
                        scanf("%s",suchText);
                        ergebnis = ergebnisMischarsearch(text, suchText, skip); break;
                case 4: ergebnisAusgabe(text, suchText, ergebnis);
                default: break;
            }
        }
        return 0;
    }