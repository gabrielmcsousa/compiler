#ifndef ANALEX
#define ANALEX
#define LEXEME_MAX_SIZE 31
enum TOKEN_CAT {ID=0, OP, CONST_INT, CONST_REAL, CONST_CHAR, CONST_STR, COMMENT};
enum OPERATORS {ASSIGN=0, ADD, SUBT, MULT, DIV, PLUS, MINUS, 
                EQUAL, GREATER, LESS, GREATER_EQ, LESS_EQ, NOT_EQ, 
                AND, OR, NOT};
typedef struct{
    enum TOKEN_CAT cat;
    union {
        int op_code; //OPERATOR
        char lexeme[LEXEME_MAX_SIZE]; //ID
        int valInt; //CONST_INT
    };
} TOKEN;
#endif
int lineCount = 1;