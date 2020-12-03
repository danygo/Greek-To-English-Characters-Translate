#include <stdio.h>

#define accent 39
#define quotation 34

/*array declarations*/
char letters[256][3];
char englishLetters[] = "AVGDEZH8IKLMNNOPRSSTYFXXWavgdezh8iklmnnoprsstyfxxw";  /*the iso charactes match with the ansi in english so we can match them in this way*/

/*declaration of the the states of the fsm*/
enum letterState {
    dflt, capital_m, small_m, capital_n, small_n
}currentState;

/*a function to fill an array with the english letters at the index that the correct greek letter corresponds, based on its decimal representation*/
void fillArray() {
    int i = 0;
    int j = 0;

    /*initialing the array of english letters*/
    for (i = 0; i < 256; i++) {
        letters[i][0] = i;
        letters[i][1] = '\0';
        letters[i][2] = '\0';
    }

    /*filling the array with capital and small letters*/
    for (i = 193; i < 218; i++) {
        letters[i][0] = englishLetters[j];
        letters[i + 32][0] = englishLetters[j + 25];
        j++;
    }

    /*ks and ps sounds with capital letters*/
    letters[206][0] = 'K';
    letters[206][1] = 'S';
    letters[216][0] = 'P';
    letters[216][1] = 'S';

    /*ks and ps sounds with small letters*/
    letters[238][0] = 'k';
    letters[238][1] = 's';
    letters[248][0] = 'p';
    letters[248][1] = 's';

    /*capital letters with a ton*/
    letters[182][0] = accent;
    letters[182][1] = 'A';
    letters[184][0] = accent;
    letters[184][1] = 'E';
    letters[185][0] = accent;
    letters[185][1] = 'H';
    letters[186][0] = accent;
    letters[186][1] = 'I';
    letters[188][0] = accent;
    letters[188][1] = 'O';
    letters[190][0] = accent;
    letters[190][1] = 'Y';
    letters[191][0] = accent;
    letters[191][1] = 'W';

    /*small letters with a ton*/
    letters[220][0] = 'a';
    letters[220][1] = accent;
    letters[221][0] = 'e';
    letters[221][1] = accent;
    letters[222][0] = 'h';
    letters[222][1] = accent;
    letters[223][0] = 'i';
    letters[223][1] = accent;
    letters[252][0] = 'o';
    letters[252][1] = accent;
    letters[253][0] = 'y';
    letters[253][1] = accent;
    letters[254][0] = 'w';
    letters[254][1] = accent;

    /*capital letters with quotation mark*/
    letters[218][0] = 'I';
    letters[218][1] = quotation;
    letters[219][0] = 'Y';
    letters[219][1] = quotation;

    /*small letters with quotation mark*/
    letters[250][0] = 'i';
    letters[250][1] = quotation;
    letters[251][0] = 'y';
    letters[251][1] = quotation;

    /*small letters both with ton and quotation mark*/
    letters[192][0] = 'i';
    letters[192][1] = accent;
    letters[192][2] = quotation;
    letters[224][0] = 'y';
    letters[224][1] = accent;
    letters[224][2] = quotation;
}

/*a function that prints the correct character after translation to the output file*/
void printState(int c) {
    int i = 0;

    for (i = 0; i < 3; i++) {
        if (letters[c][i] != '\0') putchar(letters[c][i]);
    }
}

/*what the fsm does when it is at any state*/
enum letterState start(int c) {
    if (c == 204) return capital_m;
    else if (c == 236) return small_m;
    else if (c == 205) return capital_n;
    else if (c == 237) return small_n;

    printState(c);

    return dflt;
}

/*what the fsm does when a capital m letter is found*/
enum letterState M(int c) {
    if (c == 208 || c == 240) {
        printState(66);

        return dflt;
    } else if (c == 204 || c == 236 || c == 205 || c == 237) {
        printState(204);

        if (c == 204) return capital_m;
        else if (c == 236) return small_m;
        else if (c == 205) return capital_n;
        else if (c == 237) return small_n;
    }

    printState(204);
    printState(c);

    return dflt;
}

/*what the fsm does when a small m letter is found*/
enum letterState m(int c) {
    if (c == 208 || c == 240) {
        printState(98);

        return dflt;
    } else if (c == 204 || c == 236 || c == 205 || c == 237) {
        printState(236);

        if (c == 204) return capital_m;
        else if (c == 236) return small_m;
        else if (c == 205) return capital_n;
        else if (c == 237) return small_n;
    }

    printState(236);
    printState(c);

    return dflt;
}

/*what the fsm does when a capital n letter is found*/
enum letterState N(int c) {
    if (c == 212 || c == 244) {
        printState(68);

        return dflt;
    } else if (c == 204 || c == 236 || c == 205 || c == 237) {
        printState(205);

        if (c == 204) return capital_m;
        else if (c == 236) return small_m;
        else if (c == 205) return capital_n;
        else if (c == 237) return small_n;
    }

    printState(205);
    printState(c);

    return dflt;
}

/*what the fsm does when a small n letter is found*/
enum letterState n(int c) {
    if (c == 212 || c == 244) {
        printState(100);

        return dflt;
    } else if (c == 204 || c == 236 || c == 205 || c == 237) {
        printState(237);

        if (c == 204) return capital_m;
        else if (c == 236) return small_m;
        else if (c == 205) return capital_n;
        else if (c == 237) return small_n;
    }

    printState(237);
    printState(c);

    return dflt;
}

enum letterState(*action[])(int c) = { start, M, m, N, n };

/*the main function starts with a default value of the state machine
because its not known from beforehand what will be the first input character*/
int main(void) {
    int c;

    fillArray();
    currentState = dflt;

    while ((c = getchar()) != EOF) {
        currentState = (action[currentState])(c);
    }

    return 0;
}