//
//  main.c
//  beleg_C
//
//  Created by Kurt on 04.12.22.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

// size of the field
#define ROWS 10
#define COLS 10

// Global Varibales
int treader;
int gamefile;
int x;
int y;
int menu = 1;
int levelNumber = 1;
int generation = 5;
int end = 1;
int a;
int ausmenu = 0;
FILE* level;
char currentGen[ROWS][COLS];
char nextGen[ROWS][COLS];
int livingNeighbourCells;
int schritt;
char test;
FILE* explainFile;
char textExplain;

//declartion
void goToXY(int x, int y);
int getKey();
void rowBoundary();
int countLivingCellsNeighbour(char a[ROWS][COLS], int r, int c);
void menuLoadingScrean(int levelNumber, int generation);
void explain();
int close();
int change();
int generations();
int stepByStep();
void start(int durchlaufe);



//main
int main(int argc, const char* argv[]) {

    //laden des ersten Levels Standardmaessig
    if ((level = fopen("level1.txt", "r")) == NULL) {
        printf("Datwi wurde veraendert oder geloescht.\nProgramm wird beendet!\n");
        exit(1);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(level, "%c", &currentGen[i][j]) != 1) {
                printf("Konnte Matrix nicht laden.\nProgramm wird beendet!\n");
                exit(1);
            }
        }
        if (i != ROWS - 1)
            fscanf(level, "%c", &test);
    }
    fclose(level);

    system("cls");
    do {
        //Wenn der User aus einem Menü kommt, wird der Cursor auf die richtige Position gesetzt und das Menü ausgegeben

        if (ausmenu != 1) {
            system("cls");
            x = 0;
            y = 5;
            menuLoadingScrean(levelNumber, generation);
            goToXY(x, y);
        }
        ausmenu = 1;

        //Die Eingabe des Users wird entgegengenommen daraufhin die entsprechende Methode ausgelöst

        a = getKey();
        switch (a) {

            //Pfeiltaste unten
        case 592: {
            if (y <= 8) {
                y++;
                goToXY(x, y);
            }
        }
                break;

                //Pfeiltaste oben
        case 584: {
            if (y > 5) {
                y--;
                goToXY(x, y);

            }
        }
                break;

                //Entertaste
        case 13:

            switch (y) {
            case 5: {
                start(generation);
                ausmenu = 0;
            }
                  break;
            case 6: {
                explain();
                ausmenu = 0;
            }
                  break;
            case 7: {
                levelNumber = change();
                ausmenu = 0;
            }
                  break;
            case 8: {
                generation = generations();
                ausmenu = 0;
            }
                  break;
            case 9: {
                end = close();
                ausmenu = 0;
            }
                  break;
            }
        }
    } while (end != 0);
    return 0;
}


// Functions
void goToXY(int x, int y) {
    HANDLE hConsoleOutput;
    COORD koords;
    koords.X = x;
    koords.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, koords);
}

int getKey() {
    int result = _getch();
    if (result == 0)
        result = 256 + _getch();
    else if (result == 224)
        result = 512 + _getch();
    return result;
}

// Deko
void rowBoundary() {
    printf("\n");
    for (int i = 0; i < COLS; i++) {
        printf(" ---");
    }
    printf("\n");
}

// zaehlt die Zellennachbarn
int countLivingCellsNeighbour(char a[ROWS][COLS], int r, int c) {
    int count = 0;
    for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if ((i == r && j == c) || (i < 0 || j < 0) || (i >= ROWS || j >= COLS)) {
                continue;
            }
            if (a[i][j] == '*') {
                count++;
            }
        }
    }
    return count;
}

void menuLoadingScrean(int levelNumber, int generation) {
    printf("=================\nGame of Live\n=================\n\n");
    switch (levelNumber) {
    case 1:
        printf("Aktueller Spielstand: Level 1\n");
        break;
    case 2:
        printf("Aktueller Spielstand: Level 2\n");
        break;
    case 3:
        printf("Aktueller Spielstand: Level 3\n");
        break;
    case 4:
        printf("Aktueller Spielstand: Zufaellig\n");
        break;
    }
    printf("1 - Spiel starten\n");
    printf("2 - Erklaerung ansehen\n");
    printf("3 - Level wechseln\n");
    printf("4 - Generation: %10d\n", generation);
    printf("5 - Spiel beenden\n");
}

void explain() {
    system("cls");

    // Pruefen ob File geoeffnet werden konnte
    if ((explainFile = fopen("explain.txt", "r")) == NULL) {
        printf("Konnte Erklaerung nicht laden.\nProgramm wird beendet!\nn");
        exit(1);
    }
    else {
        do {
            textExplain = fgetc(explainFile);
            printf("%c", textExplain);
        } while (textExplain != EOF);
        fclose(explainFile);
        printf("\n\nDruecke ENTER, um ins Hauptmenu zurueckzugelangen.");
        while (getchar() != '\n') {}
    }
    system("cls");
}


int close() {
    system("cls");
    printf("Willst du das Game wirklich verlassen?\n");
    printf("Ja   Nein");

    x = 0; y = 1;

    goToXY(x, y);
    do {

        treader = getKey();
        switch (treader) {

            //Pfeiltaste rechts
        case 589: {
            x = 5;
            goToXY(x, y);
        }
                break;

                //Pfeiltaste links
        case 587: {
            x = 0;
            goToXY(x, y);
        }
                break;

                //Entertaste
        case 13:
            if (x == 5) {
                system("cls");
                return 1;
            }
            else {
                system("cls");
                return 0;
            }

        }

    } while (1);

    return 1;
}

//Wechselt den Spielstand indem es Level auf 1, 2, 3 oder zufaellig setzt
int change() {
    system("cls");
    printf("Wähle deinen Spielstand aus:\n");
    printf("Level 1\n");
    printf("Level 2\n");
    printf("Level 3\n");
    printf("Zufaellig");

    x = 12;
    y = 1;
    goToXY(x, y);

    do {
        treader = getKey();
        switch (treader) {

            //Pfeiltaste unten
        case 592: {
            if (y < 4) {
                y++;
                goToXY(x, y);
            }
        }
                break;

                //Pfeiltaste oben
        case 584: {
            if (y > 1) {
                y--;
                goToXY(x, y);
            }
        }
                break;

                //Enter Taste
        case 13: {
            switch (y) {
            case 1:
                system("cls");
                if ((level = fopen("level1.txt", "r")) == NULL) {
                    printf("Konnte Datei nicht laden.\nProgramm wird beendet!\n");
                    exit(1);
                }
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        if (fscanf(level, "%c", &currentGen[i][j]) != 1) {
                            printf("Konnte Matrix nicht laden.\nProgramm wird beendet!\n");
                            exit(1);
                        }
                    }
                    if (i != ROWS - 1)
                        fscanf(level, "%c", &test);
                }
                fclose(level);
                return 1;
            case 2:
                system("cls");
                if ((level = fopen("level2.txt", "r")) == NULL) {
                    printf("Konnte Datei nicht laden.\nProgramm wird beendet!\n");
                    exit(1);
                }
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        if (fscanf(level, "%c", &currentGen[i][j]) != 1) {
                            printf("Konnte Matrix nicht laden.\nProgramm wird beendet!\n");
                            exit(1);
                        }
                    }
                    if (i != ROWS - 1)
                        fscanf(level, "%c", &test);
                }
                fclose(level);
                return 2;
            case 3:
                system("cls");
                if ((level = fopen("level3.txt", "r")) == NULL) {
                    printf("Konnte Datei nicht laden.\nProgramm wird beendet!\n");
                    exit(1);
                }
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        if (fscanf(level, "%c", &currentGen[i][j]) != 1) {
                            printf("Konnte Matrix nicht laden.\nProgramm wird beendet!\n");
                            exit(1);
                        }
                    }
                    if (i != ROWS - 1)
                        fscanf(level, "%c", &test);
                }
                fclose(level);
                return 3;
            case 4:
                system("cls");
                int p;
                printf("Bitte eine Zahl eingeben, zu wieviel Pronzent ein Feld gefuellt werden soll (max 100 min 1): ");
                do {
                    scanf("%d", &p);
                    fgetc(stdin) != '\n';
                    if (p < 1 || p > 100) {
                        printf("Bitte eine gueltige Zahl eingeben: ");
                    }
                } while (p < 1 || p > 100);

                // Setuo fuer random generator
                srand(time(NULL));

                for (int i = 0; i < ROWS; i++)
                    for (int j = 0; j < COLS; j++) {
                        int prozent = rand() % 100 + 1;
                        if (prozent <= p)
                            currentGen[i][j] = '*';
                        else {
                            currentGen[i][j] = ' ';
                        }
                    }
                return 4;
            }
        }
        }
    } while (1);

}


int generations() {
    system("cls");

    int i = 0;
    printf("Bitte eine Zahl fuer die Generationen eingeben (0 ist ungueltig): ");
    do {
        scanf("%d", &i);
        fgetc(stdin) != '\n';
        if (i < 0) {
            printf("Bitte eine gueltige Zahl eingeben: ");
        }
    } while (i < 1);

    return i;
}

int stepByStep() {
    system("cls");
    printf("Willst du das Game Schrittweise ablaufen lassen?\n");
    printf("Ja   Nein");

    x = 0; y = 1;

    goToXY(x, y);
    do {

        treader = getKey();
        switch (treader) {

            //Pfeiltaste rechts
        case 589: {
            x = 5;
            goToXY(x, y);
        }
                break;

                //Pfeiltaste links
        case 587: {
            x = 0;
            goToXY(x, y);
        }
                break;

                //Entertaste
        case 13:
            if (x == 5) {
                system("cls");
                return 1;
            }
            else {
                system("cls");
                return 0;
            }

        }

    } while (1);
}

void start(int durchlaufe) {

    schritt = stepByStep();

    system("cls");
    // Start Feld printen 
    printf("=================\nGame of Live\n=================\n\n");
    printf("Generation 0:");
    rowBoundary();
    for (int i = 0; i < ROWS; i++) {
        printf(":");
        for (int j = 0; j < COLS; j++) {
            printf(" %c :", currentGen[i][j]);
        }
        rowBoundary();
    }


    for (int d = 0; d < durchlaufe; d++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                livingNeighbourCells = countLivingCellsNeighbour(currentGen, i, j);
                if (currentGen[i][j] == '*' && (livingNeighbourCells == 2 || livingNeighbourCells == 3)) {
                    nextGen[i][j] = '*';
                }
                else if (currentGen[i][j] == ' ' && livingNeighbourCells == 3) {
                    nextGen[i][j] = '*';
                }
                else {
                    nextGen[i][j] = ' ';
                }
            }
        }
        //Ausgabe neue Generation
        printf("Generation %d:", d + 1);
        rowBoundary();
        for (int i = 0; i < ROWS; i++) {
            printf(":");
            for (int j = 0; j < COLS; j++) {
                printf(" %c :", nextGen[i][j]);
            }
            rowBoundary();
        }

        //Speichern der neuen Generation
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                currentGen[i][j] = nextGen[i][j];

        if (schritt != 1) {

            if (d != durchlaufe - 1) {
                printf("\nBitte Druecke Enter, um mit der naechsten Generation fortzufahren.\n");
            }
            else {
                printf("\nDu hast erfolgreich %d Generationen durchlebt. Druecke ENTER um fortzufahren.\n", durchlaufe);
            }
            while (_getch() != 13) {}
        }
    }

    printf("\n\nDruecke ESCAPE, um ins Hauptmenu zurueckzugelangen.");
    while (_getch() != 27) {}
}