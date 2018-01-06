#include <stdio.h>
#include <string.h>

#define ALPHABETGROESSE 26//fuer mischarsearch
#define MAX 100           //fuer suchText

#define PRIMZAHL 33554393 //fuer rksearch
#define BASIS 32          //fuer rksearch

int anzahlSchritte;
//MISCHARSEARCH (BOYER- MOORE):
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
    for(int j = 0; j<m-1; j++){                     //"-1", da der letzte Buchstabe des suchWortes auch mit m Schritten initialisiert werden muss
        skip[returnIndex(suchText[j])] = m-j-1;
    }
}

/**
 * Funktion um eine bestimmte Buchstabenfolge in einem Text zu suchen. Beruht auf Verwendung einer Skip- Tabelle.
 * @param suchText: der zu suchende Text/Zeichenfolge
 * @param text: der Text worin gesucht wird
 * @param skip: die Tabelle(Array), worin steht, wie weit das SuchWort nach rechts verschoben werden kann,
 *              wenn es zu einen Unterschied zwischen den Buchstaben im SuchWort und im zu suchenden Text gibt
 * @return: -1: die zu suchende Zeichenkette im Text wurde nicht gefunden
 *           X: die zu suchende Zeichenkette wurde ab X. Stelle im Text gefunden
 */
int mischarsearch(char text[], char suchText[], int skip[]) {
    int laengeSuche = (int)strlen(suchText);
    int laengeText = (int)strlen(text);
    int i, j, t;

    initskip(suchText, skip);
                                                                      //i: für die i. Stelle im zu suchenden Text, j: für die j. Stelle in der Zeichenfolge
    for (i = laengeSuche-1, j = laengeSuche-1; j >= 0; i--, j--) {    //"-1", da strlen-1 die letzte Stelle des Array angibt
        anzahlSchritte++;
        while (text[i] != suchText[j]) {                              //wenn die Buchstaben an der gleichen Stelle ungleich sind
            t = skip[returnIndex(text[i])];                           //suche den Wert aus der skip- Tabelle wie weit man nach rechts springen muss, um weiter zu suchen
            i += (laengeSuche - j > t) ? laengeSuche - j : t;         //springe um skip(t), mindestens aber um 1 nach rechts oder springe um ein ganzes Wort(Fall, wenn if wahr ist)
            if (i >= laengeText) return -1;                           //der Fall, wenn das Wort nicht gefunden wurde und man am Ende des Textes angelangt ist
            j = laengeSuche - 1;                                      //setze Musterzeiger ganz nach rechts, um eine erneute Suche der Zeichenfolge vorzubereiten
        }
    }
    return i+1;                                                       //genau die Stelle, ab der das SuchWort im Text gefunden werden kann
}

//RKSEARCH (RABIN- KARB):
/**
 * Funktion um eine bestimmte Buchstabenfolge in einem Text zu suchen. Verfahren funktioniert mit der Berechnung des Hash- Wertes
 * des SuchWortes und einem genauso langen Abschnitt im Text, der solange nach rechts verschoben wird,
 * bis sich die Hashwerte gleichen, dann ist Wort gefunden.
 * @param suchText: der zu suchende Text/Zeichenfolge
 * @param text: der Text worin gesucht wird
 * @return: -1: die zu suchende Zeichenkette im Text wurde nicht gefunden
 *           X: die zu suchende Zeichenkette wurde ab X. Stelle im Text gefunden
 */
int rksearch(char text[], char suchText[]) {
    int dM = 1;
    int hashSuchText = 0, hashText = 0;
    int laengeSuche = (int)strlen(suchText);
    int laengeText = (int)strlen(text);

    int i;
    for(i = 1; i < laengeSuche; i++) dM = (BASIS*dM) % PRIMZAHL;
    for(i = 0; i < laengeSuche; i++) {
        hashSuchText = (hashSuchText*BASIS + returnIndex(suchText[i])) % PRIMZAHL;      //hier wird von den einzelnen Buchstaben aus der Hashwert des gesamten SuchWortes berechnet
        hashText = (hashText*BASIS + returnIndex(text[i])) % PRIMZAHL;                  //hier wird von den einzelnen Buchstaben aus der Hashwert des gesamten Abschnittes gleicher Laenge des SuchWortes im Text berechnet
    }
    for (i = 0; hashSuchText != hashText; i++) {                                        //solange ueber den Text gehen bis der Hash- Wert des Suchwortes mit dem Hashwert des Abschnittes, der die gleiche Laenge wie das Suchwort hat, gleich ist
        anzahlSchritte ++;
        hashText = (hashText + BASIS*PRIMZAHL - returnIndex(text[i])*dM) % PRIMZAHL;    //Produkt BASIS*PRIMZAHL zur Sicherstellung, dass hashText > 0
        hashText = (hashText*BASIS + returnIndex(text[i+laengeSuche])) % PRIMZAHL;      //beide "hashText="- Zeilen sind eine Rechnung mit dem HashText- Wert und tragen dazu bei, dass der Hash- Wert des naechsten Abschnittes(der um ein nach rechts gerutscht ist) berechnet wird
        if (i > laengeText-laengeSuche) return -1;                                      //wenn der Index 'i' an dem Punkt im Text angekommen ist, dass das zu suchende Wort gerade nicht mehr rein passt, wird zurückgegeben, dass das Wort nicht gefunden wurde
    }
    return i;                                                                           //genau die Stelle, ab der das SuchWort im Text gefunden werden kann
}

//ERGEBNISSE:
/**
 * Der Benutzer gibt ein zu suchendes Wort ein. Dieses Wort wird mithilfe des mischarsearch- Algorithmus gesucht.
 * Danach wird eine dazu passende Ausgabe gemacht, ob das Wort gefunden wurde oder nicht.
 * @param text: der konstante Text, in dem gesucht werden soll
 * @param suchText: das zu suchende Suchwort
 * @param skip: die Tabelle(Array), worin steht, wie weit das SuchWort nach rechts verschoben werden kann,
 *              wenn es zu einen Unterschied zwischen den Buchstaben im SuchWort und im zu suchenden Text gibt
 * @return: -1: die zu suchende Zeichenkette im Text wurde nicht gefunden
 *           X: die zu suchende Zeichenkette wurde ab X. Stelle im Text gefunden
 */
int ergebnisMischarsearch(char text[], char suchText[], int skip[]) {
    int ergebnis = mischarsearch(text, suchText, skip);
    if(ergebnis == -1){
        printf("Das Wort wurde nicht gefunden!(durchgeführt mit Boyer- Moore)\n(Benötigte Schritte: %d)\n\n",anzahlSchritte);
    }else{
        printf("Das Wort wurde ab %d. Stelle im zu suchenden Text gefunden!(durchgeführt mit Boyer- Moore)\n(Benötigte Schritte: %d)\n\n", ergebnis+1,anzahlSchritte);
    }
    return ergebnis;
}

/**
 * Der Benutzer gibt ein zu suchendes Wort ein. Dieses Wort wird mithilfe des rksearch- Algorithmus gesucht.
 * Danach wird eine dazu passende Ausgabe gemacht, ob das Wort gefunden wurde oder nicht.
 * @param text: der konstante Text, in dem gesucht werden soll
 * @param suchText: das zu suchende Suchwort
 * @return: -1: die zu suchende Zeichenkette im Text wurde nicht gefunden
 *           X: die zu suchende Zeichenkette wurde ab X. Stelle im Text gefunden
 */
int ergebnisRksearch(char text[], char suchText[]) {
    int ergebnis = rksearch(text, suchText);
    if(ergebnis == -1){
        printf("Das Wort wurde nicht gefunden!(durchgeführt mit Rabin- Karb)\n(Benötigte Schritte: %d)\n\n",anzahlSchritte);
    }else{
        printf("Das Wort wurde ab %d. Stelle im zu suchenden Text gefunden!(durchgeführt mit Rabin- Karb)\n(Benötigte Schritte: %d)\n\n", ergebnis+1,anzahlSchritte);
    }
    return ergebnis;
}

//AUSGABE DES ERGEBNISSES IM TEXT:
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
        char text[] = "Weit hinten, hinter den Wortbergen, fern der Laender Vokalien und Konsonantien leben die Blindtexte.";
        int skip[ALPHABETGROESSE]; //Buchstaben von 1-26; 0. Stelle fuer Leerzeichen reserviert //fuer mischarsearch
        char suchText[MAX];

        printf("Menü\nGeben Sie an, was Sie machen wollen:\n\n");
        int eingabe = 0;
        int ergebnis = 0;
        while(eingabe != 5){
            printf("1) konstanten Text ausgeben\n2) Suchwort eingeben und prüfen[mit Boyer- Moore]\n3) Suchwort eingeben und prüfen[mit Rabin- Karp]\n4) Suchwort im Text anzeigen lassen\n5) Programm beenden\n\n");
            scanf("%d",&eingabe);
            ergebnis = 0;
            anzahlSchritte = 0;
            switch(eingabe){
                case 1: printf("%s\n\n",text); break;
                case 2: printf("Geben sie ein zu suchendes Wort ein:\n");
                        scanf("%s",suchText);
                        ergebnis = ergebnisMischarsearch(text, suchText, skip); break;
                case 3: printf("Geben sie ein zu suchendes Wort ein:\n");
                        scanf("%s",suchText);
                        ergebnis = ergebnisRksearch(text, suchText); break;
                case 4: ergebnisAusgabe(text, suchText, ergebnis); break;
                default: break;
            }
        }
        return 0;
    }