#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "src/analex/Analex.h"
#include "src/anasynt/Anasynt.h"
#include "src/Funcaux.h"
#include "src/idTable.h"

FILE *fd;
TOKEN t;
TOKEN tkLA;
ID_TAB idTable;
int lineCount;
bool printTree;
char TABS[200];

void runLex() {
    if((fd=fopen("expression.dat", "r")) == NULL) {
        printf("File not found!");
    }

    printf("LINE %d: ", lineCount);
    while(true) {
        t = Analex(fd, false);
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
        if(t.cat == EOFILE) break;
    }
    fclose(fd);
}

void runSynt() {
    if((fd=fopen("expression.dat", "r")) == NULL) {
        error("File not found!");
    }
    // if((fd=fopen("expression.obj", "w")) == NULL) {
    //     error("Could not create file!");
    // }

    InitIdTable();

    while(true) {
        t = Analex(fd, true);
        if (t.cat == EOFILE) {
            printf("\nEnd of File!\n");
            break;
        }
        Prog();
        if (t.cat == EOFILE) {
            printf("\nLINE %d: Syntax Analysis Passed!!\n\n", lineCount - 1);
        }
        else {
            error("Syntax error!");
        }
    }
    fclose(fd);
}

int main(int argc, char **argv) {

    // system("chcp 65001");
    lineCount = 1;
    if(argc < 2) {
        error("No Argument passed!\n\t Use either 'lex' or 'syn'!");
    }
    else if(strcmp(argv[1], "lex") == 0){
        printf("\n\n[Lexical Analysis---------------]\n");
        runLex();
    }
    else if(strcmp(argv[1], "syn") == 0){
        printTree = false;
        printf("\n\n[Syntax Analysis-------------]\n");
        runSynt();
    }
    else{
        error("Invalid Argument!\n\t Use either 'lex' or 'syn'!");
    }
}