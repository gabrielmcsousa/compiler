#ifndef _ANALEX_
#define _ANALEX_

#include <stdio.h>
#include <stdbool.h>

#define LEXEME_MAX_SIZE 31
#define STRING_MAX_SIZE 100
#define COMMENT_MAX_SIZE 300

enum TOKEN_CAT {ID=0, RES_WORD, SYMBOL, ID_CONST, CONST_INT, CONST_REAL, CONST_CHAR, CONST_STR, CONST_BOOL, COMMENT, EOEXP, EOFILE};

enum SYMBOLS {ASSIGN=0, ADD, SUBT, MULT, DIV, PLUS, MINUS, ADDR_OF,
                EQUAL, GREATER, LESS, GREATER_EQ, LESS_EQ, NOT_EQ, 
                AND, OR, NOT, OPEN_PAR, CLOSE_PAR, OPEN_BRACK, 
                CLOSE_BRACK, OPEN_BRACE, CLOSE_BRACE, COMMA,
                PERIOD, COLON, SEMI_COLON};

typedef struct{
    enum TOKEN_CAT cat;
    bool processed;
    union {
        int sy_code; //OPERATOR
        char lexeme[LEXEME_MAX_SIZE]; //ID | RES_WORD
        int intVal; //CONST_INT
        float realVal; //CONST_REAL
        char charVal; //CONST_CHAR
        char string[STRING_MAX_SIZE]; //CONST_STR
        char comment[COMMENT_MAX_SIZE]; //COMMENT
    };
} TOKEN;

extern int lineCount;
extern TOKEN t;
extern TOKEN tkLA;
extern FILE *fd;

TOKEN AnalexTLA(FILE *, bool skip_EOEXP);
TOKEN Analex(FILE *fd, bool skip_EOEXP);

#endif