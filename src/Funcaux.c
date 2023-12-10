#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analex/Analex.h"
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

void checkToken(){
    printf("CHECK LINE %d: ", lineCount);
    switch (t.cat) {
        case ID: 
            printf("<ID, %s> ", t.lexeme);
            break;
        case RES_WORD:
            printf("<RES_WORD, %s> ", t.lexeme);
            break;
        case SYMBOL: switch (t.sy_code) {
                        case ASSIGN: printf("<SYMBOL, ASSIGN> ");
                                        break;
                        case ADD: printf("<SYMBOL, ADD> ");
                                        break;
                        case SUBT: printf("<SYMBOL, SUBT> ");
                                        break;
                        case MULT: printf("<SYMBOL, MULT> ");
                                        break;
                        case DIV: printf("<SYMBOL, DIV> ");
                                        break;
                        case ADDR_OF: printf("<SYMBOL, ADDR_OF> ");
                                        break;
                        case EQUAL: printf("<SYMBOL, EQUAL> ");
                                        break;
                        case GREATER: printf("<SYMBOL, GREATER> ");
                                        break;
                        case LESS: printf("<SYMBOL, LESS> ");
                                        break;
                        case GREATER_EQ: printf("<SYMBOL, GREATER_EQ> ");
                                        break;
                        case LESS_EQ: printf("<SYMBOL, LESS_EQ> ");
                                        break;
                        case NOT_EQ: printf("<SYMBOL, NOT_EQ> ");
                                        break;
                        case AND: printf("<SYMBOL, AND> ");
                                        break;
                        case OR: printf("<SYMBOL, OR> ");
                                        break;
                        case NOT: printf("<SYMBOL, NOT> ");
                                        break;
                        case OPEN_PAR: printf("<SYMBOL, OPEN_PAR> ");
                                        break;
                        case CLOSE_PAR: printf("<SYMBOL, CLOSE_PAR> ");
                                        break;
                        case OPEN_BRACK: printf("<SYMBOL, OPEN_BRACK> ");
                                        break;
                        case CLOSE_BRACK: printf("<SYMBOL, CLOSE_BRACK> ");
                                        break;
                        case OPEN_BRACE: printf("<SYMBOL, OPEN_BRACE> ");
                                        break;
                        case CLOSE_BRACE: printf("<SYMBOL, CLOSE_BRACE> ");
                                        break;
                    }
                    break;
        case CONST_INT: printf("<CONST_INT, %d> ", t.intVal);
                        break;
        case CONST_REAL: printf("<CONST_REAL, %f> ", t.realVal);
                            break;
        case CONST_CHAR: printf("<CONST_CHAR, %c> ", t.charVal);
                            break;
        case CONST_STR: printf("<CONST_STR, %s> ", t.string);
                        break;
        case COMMENT: printf("<COMMENT, %s> ", t.comment);
                        break;
        case EOEXP: printf("<END_OF_EXP, %d>\n", 0);
                    printf("LINE %d: ", lineCount);
                    break;
        case EOFILE: printf(" <END OF FILE REACHED>\n");
                        break;
    }
    switch (tkLA.cat) {
        case ID: 
            printf(" <LA_ID, %s> ", tkLA.lexeme);
            break;
        case RES_WORD:
            printf(" <LA_RES_WORD, %s> ", tkLA.lexeme);
            break;
        case SYMBOL: switch (tkLA.sy_code) {
                        case ASSIGN: printf(" <LA_SYMBOL, ASSIGN> ");
                                        break;
                        case ADD: printf(" <LA_SYMBOL, ADD> ");
                                        break;
                        case SUBT: printf(" <LA_SYMBOL, SUBT> ");
                                        break;
                        case MULT: printf(" <LA_SYMBOL, MULT> ");
                                        break;
                        case DIV: printf(" <LA_SYMBOL, DIV> ");
                                        break;
                        case ADDR_OF: printf(" <LA_SYMBOL, ADDR_OF> ");
                                        break;
                        case EQUAL: printf(" <LA_SYMBOL, EQUAL> ");
                                        break;
                        case GREATER: printf(" <LA_SYMBOL, GREATER> ");
                                        break;
                        case LESS: printf(" <LA_SYMBOL, LESS> ");
                                        break;
                        case GREATER_EQ: printf(" <LA_SYMBOL, GREATER_EQ> ");
                                        break;
                        case LESS_EQ: printf(" <LA_SYMBOL, LESS_EQ> ");
                                        break;
                        case NOT_EQ: printf(" <LA_SYMBOL, NOT_EQ> ");
                                        break;
                        case AND: printf(" <LA_SYMBOL, AND> ");
                                        break;
                        case OR: printf(" <LA_SYMBOL, OR> ");
                                        break;
                        case NOT: printf(" <LA_SYMBOL, NOT> ");
                                        break;
                        case OPEN_PAR: printf(" <LA_SYMBOL, OPEN_PAR> ");
                                        break;
                        case CLOSE_PAR: printf(" <LA_SYMBOL, CLOSE_PAR> ");
                                        break;
                        case OPEN_BRACK: printf(" <LA_SYMBOL, OPEN_BRACK> ");
                                        break;
                        case CLOSE_BRACK: printf(" <LA_SYMBOL, CLOSE_BRACK> ");
                                        break;
                        case OPEN_BRACE: printf(" <LA_SYMBOL, OPEN_BRACE> ");
                                        break;
                        case CLOSE_BRACE: printf(" <LA_SYMBOL, CLOSE_BRACE> ");
                                        break;
                    }
                    break;
        case CONST_INT: printf(" <LA_CONST_INT, %d> ", tkLA.intVal);
                        break;
        case CONST_REAL: printf(" <LA_CONST_REAL, %f> ", tkLA.realVal);
                            break;
        case CONST_CHAR: printf(" <LA_CONST_CHAR, %c> ", tkLA.charVal);
                            break;
        case CONST_STR: printf(" <LA_CONST_STR, %s> ", tkLA.string);
                        break;
        case COMMENT: printf(" <LA_COMMENT, %s> ", tkLA.comment);
                        break;
        case EOEXP: printf(" <LA_END_OF_EXP, %d>\n", 0);
                    printf("LINE %d: ", lineCount);
                    break;
        case EOFILE: printf("  <LA_END OF FILE REACHED>\n");
                        break;
    }
}