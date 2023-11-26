#ifndef ANALEX
#define ANALEX

#include <stdio.h>
#include <stdbool.h>

#define LEXEME_MAX_SIZE 31
#define STRING_MAX_SIZE 100
#define COMMENT_MAX_SIZE 300

enum TOKEN_CAT {ID=0, SYMBOL, CONST_INT, CONST_REAL, CONST_CHAR, CONST_STR, COMMENT, EOEXP, EOFILE};

enum SYMBOLS {ASSIGN=0, ADD, SUBT, MULT, DIV, PLUS, MINUS, ADDR_OF,
                EQUAL, GREATER, LESS, GREATER_EQ, LESS_EQ, NOT_EQ, 
                AND, OR, NOT, OPEN_PAR, CLOSE_PAR, OPEN_BRACK, 
                CLOSE_BRACK, OPEN_BRACE, CLOSE_BRACE};

typedef struct{
    enum TOKEN_CAT cat;
    bool processed;
    union {
        int sy_code; //OPERATOR
        char lexeme[LEXEME_MAX_SIZE]; //ID
        int intVal; //CONST_INT
        float realVal; //CONST_REAL
        char charVal; //CONST_CHAR
        char string[STRING_MAX_SIZE]; //CONST_STR
        char comment[COMMENT_MAX_SIZE]; //COMMENT
    };
} TOKEN;

int lineCount = 1;

TOKEN Analex(FILE *);

#endif