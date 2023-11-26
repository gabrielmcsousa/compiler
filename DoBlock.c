#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "src/analex/Analex.h"

FILE *fd;
TOKEN t;
int lineCount;
bool printTree;

void runLex() {
    if((fd=fopen("expression.dat", "r")) == NULL) {
        printf("File not found!");
    }

    printf("LINHA %d: ", lineCount);
    while (1) {
        t = Analex(fd);
        switch (t.cat) {
            case ID: printf("<ID, %s> ", t.lexeme);
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
                        printf("LINHA %d: ", lineCount);
                        break;
            case EOFILE: printf(" <END OF FILE REACHED>\n");
                         break;
        }
        if(t.cat == EOFILE) break;
    }
    fclose(fd);
}

int main() {

    system("chcp 65001");

    lineCount = 1;
    printf("\n\n[Lexical Analysis---------------]\n");
    runLex();

    // lineCount = 1;
    // printTree = false;
    // printf("\n\n[Syntactic Analysis-------------]\n");
    // runSynt();

}