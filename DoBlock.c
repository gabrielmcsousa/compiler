#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "src/analex/Analex.h"
// #include "src/anasynt/Anasynt.h"

FILE *fd;
TOKEN t;
int lineCount;
bool printTree;

void runLex() {
    if((fd=fopen("expression.dat", "r")) == NULL) {
        printf("File not found!");
    }

    printf("LINE %d: ", lineCount);
    while(true) {
        t = Analex(fd);
        switch (t.cat) {
            case ID: 
                    if( (strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || (strcmp(t.lexeme, "int") == 0) || 
                        (strcmp(t.lexeme, "float") == 0) || (strcmp(t.lexeme, "real") == 0) || (strcmp(t.lexeme, "bool") == 0) || 
                        (strcmp(t.lexeme, "true") == 0) || (strcmp(t.lexeme, "false") == 0) || (strcmp(t.lexeme, "block") == 0) ||
                        (strcmp(t.lexeme, "with") == 0) || (strcmp(t.lexeme, "main") == 0) || (strcmp(t.lexeme, "const") == 0) ||
                        (strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "while") == 0) || (strcmp(t.lexeme, "endblock") == 0) || 
                        (strcmp(t.lexeme, "varying") == 0) || (strcmp(t.lexeme, "from") == 0) || (strcmp(t.lexeme, "to") == 0) ||
                        (strcmp(t.lexeme, "downto") == 0) || (strcmp(t.lexeme, "for") == 0) || (strcmp(t.lexeme, "times") == 0) ||
                        (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "elseif") == 0) || (strcmp(t.lexeme, "else") == 0) || 
                        (strcmp(t.lexeme, "endif") == 0) || (strcmp(t.lexeme, "endwhile") == 0) || (strcmp(t.lexeme, "goback") == 0) ||
                        (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || (strcmp(t.lexeme, "getchar") == 0) ||
                        (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || (strcmp(t.lexeme, "putchar") == 0)){
                            t.cat = RES_WORD;
                            printf("<RES_WORD, %s> ", t.lexeme);
                    }
                    else {
                        printf("<ID, %s> ", t.lexeme);
                    }
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

// void runSynt() {
//     if((fd=fopen("expression.dat", "r")) == NULL) {
//         printf("File not found!");
//     }

//     while(true) {
//         t = Analex(fd);
//         if (t.cat == EOFILE) {
//             printf("\nEnd of File!\n");
//             break;
//         }
//         Prog();
//         if (t.cat == EOEXP) {
//             printf("\nLINE %d: Syntactic Error!\n\n", lineCount - 1);
//         }
//         else {
//             error("Syntax error!");
//         }
//     }
//     fclose(fd);
// }

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