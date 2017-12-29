#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABETGROESSE 26

/**
 * Gibt, egal ob Klein- oder Grossbuchstabe, die i. Position des uebergebenen Buchstaben im deutschen Alphabet an.
 * @param c: Der uebergebene Buchstabe, von dem man die i. Position wissen möchte
 * @return: 0: Wenn 'c' ein Leerzeichen ist, 1-26: ein i. Buchstabe im Alphabet, -1: kein Leerzeichen oder Buchstabe
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
 * @param suchText: Der zu suchende suchText im Text
 * @param skip: Das als Tabelle dienende skip- Array
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
 * @param suchText: Der zu suchende Text/Zeichenfolge
 * @param text: Der Text worin gesucht wird
 * @param skip: Die Tabelle(Array), worin steht, wie weit das SuchWort nach rechts verschoben werden kann,
 *              wenn es zu einen Unterschied zwischen den Buchstaben im SuchWort und im zu suchenden Text gibt
 * @return
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
    return i+2;
}

/**
 * @param argc: Anzahl der Parameter (in der Shell)
 * @param argv: einzelnen übergebenen Werte (in der Shell)
 * @return: Abbruchbeding
 */
    int main(int argc, char *argv[]) {
        char suchText[] = "Weit hintene";
        char text[] = "Weit hinten, hinter den Wortbergen, fern der Länder Vokalien und Konsonantien leben die Blindtexte";
        int skip[ALPHABETGROESSE]; //Buchstaben von 1-26; 0. Stelle fuer Leerzeichen reserviert

        int ergebnis = mischarsearch(suchText, text, skip);
    if(ergebnis == -1){
        printf("Das Wort wurde nicht gefunden!");
    }else{
        printf("Das Wort wurde ab %d. Stelle im zu suchenden Text gefunden!", ergebnis);
    }
        return 0;
    }