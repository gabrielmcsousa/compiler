#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Funcaux.h"

void error(char msg[]) {
    printf("LINE %d: %s\n", lineCount, msg);
    exit(1);
}

void PrintNode(char info[], int move) {
 
    if (move == FORWARD) { printf("%s%s\n", TABS, info); strcat(TABS, "\t"); }
    else if (move == STAY) { printf("%s%s\n", TABS, info); }
    else if (move == BACKWARD) { TABS[strlen(TABS)-1] = '\0'; }
}

void PrintNodeInt(int val, int move) {
 
    if (move == FORWARD) { printf("%s%d\n", TABS, val); strcat(TABS, "\t"); }
    else if (move == STAY) { printf("%s%d\n", TABS, val); }
    else if (move == BACKWARD) { TABS[strlen(TABS)-1] = '\0'; }
}