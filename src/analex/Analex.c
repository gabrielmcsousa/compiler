#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Analex.h"

#define LEXEME_SIZE 50
#define STRING_SIZE 100
#define NUM_SIZE 20

TOKEN Analex(FILE *fd, bool skip_EOEXP){
    static bool firstTime = true;
    bool skip = true;
    if(!skip_EOEXP) skip = false;

    TOKEN tk;

    if(firstTime) {
        firstTime = false;
        tk = AnalexTLA(fd, skip);
        if(tk.cat == EOFILE) tkLA = tk;
        else tkLA = AnalexTLA(fd, skip);
        return tk;
    }
    else if(tkLA.cat == EOFILE){
        return(tkLA);
    }
    else{
        tk = tkLA;
        tkLA = AnalexTLA(fd, skip);
        return tk;
    }
}


TOKEN AnalexTLA(FILE *fd, bool skip_EOEXP) {

    int state;

    char lexeme[LEXEME_SIZE] = "";
    int sizeL = 0;
    
    char digits[NUM_SIZE] = "";
    int sizeD = 0;

    char string[STRING_SIZE] = "";
    int sizeS = 0;

    char constChar;

    state = 0;
    t.processed = false;
    while (true) {
        char c = fgetc(fd);
        switch (state) {
            case 0: if (c == ' ' || c == '\t') state = 0;
                    else if(c == '\n' && skip_EOEXP) state = 0;
                    else if(c == '\"') {
                        state = 34;
                    }
                    else if(c >= '0' && c <= '9') {
                        state = 1;
                        digits[sizeD] = c;
                        digits[++sizeD] = '\0';
                    }
                    else if((c >= 'a' && c<= 'z') || (c >= 'A' && c<= 'Z')) {
                        state = 5;
                        lexeme[sizeL] = c;
                        lexeme[++sizeL] = '\0';
                    }
                    else if(c == '_') {
                        state = 6;
                        lexeme[sizeL] = c;
                        lexeme[++sizeL] = '\0';
                    }
                    else if(c == '|') {
                        state = 25;
                    }
                    else if(c == '&') {
                        state = 18;
                    }
                    else if(c == '>') {
                        state = 22;
                    }
                    else if(c == '=') {
                        state = 23;
                    }
                    else if(c == '<') {
                        state = 20;
                    }
                    else if(c == '!') {
                        state = 17;
                    }
                    else if(c == '/') {
                        state = 8;
                    }
                    else if(c == '*') {
                        state = 7;
                        t.cat = SYMBOL;
                        t.sy_code = MULT;
                        return t;
                    }
                    else if(c == '+') {
                        state = 9;
                        t.cat = SYMBOL;
                        t.sy_code = ADD;
                        return t;
                    }
                    else if(c == '-') {
                        state = 10;
                        t.cat = SYMBOL;
                        t.sy_code = SUBT;
                        return t;
                    }
                    else if(c == '(') {
                        state = 11;
                        t.cat = SYMBOL;
                        t.sy_code = OPEN_PAR;
                        return t;
                    }
                    else if(c == ')') {
                        state = 12;
                        t.cat = SYMBOL;
                        t.sy_code = CLOSE_PAR;
                        return t;
                    }
                    else if(c == '[') {
                        state = 13;
                        t.cat = SYMBOL;
                        t.sy_code = OPEN_BRACK;
                        return t;
                    }
                    else if(c == ']') {
                        state = 14;
                        t.cat = SYMBOL;
                        t.sy_code = CLOSE_BRACK;
                        return t;
                    }
                    else if(c == '{') {
                        state = 15;
                        t.cat = SYMBOL;
                        t.sy_code = OPEN_BRACE;
                        return t;
                    }
                    else if(c == '}') {
                        state = 16;
                        t.cat = SYMBOL;
                        t.sy_code = CLOSE_BRACE;
                        return t;
                    }
                    else if(c == '\'') {
                        state = 30;
                    }
                    else if(c == ',') {
                        state = 50;
                        t.cat = SYMBOL;
                        t.sy_code = COMMA;
                        return t;
                    }
                    else if(c == '.') {
                        state = 51;
                        t.cat = SYMBOL;
                        t.sy_code = PERIOD;
                        return t;
                    }
                    else if(c == ':') {
                        state = 52;
                        t.cat = SYMBOL;
                        t.sy_code = COLON;
                        return t;
                    }
                    else if(c == ';') {
                        state = 53;
                        t.cat = SYMBOL;
                        t.sy_code = SEMI_COLON;
                        return t;
                    }
                    else if(c == '\n') {
                        state = 0;
                        t.cat = EOEXP;
                        lineCount++;
                        return t;
                    }
                    else if(c == EOF) {
                        t.cat = EOFILE;
                        return t;
                    }
                    else {
                        printf("Invalid character on STATE 0!");
                        exit(1);
                    }
                    break;
            case 34: if(isprint(c) != 0) {
                        state = 35;
                        string[sizeS] = c;
                        string[++sizeS] = '\0';
                    }
                    else {
                        printf("Invalid character on STATE 34!");
                        exit(1);
                    }
                    break;
            case 35: if(isprint(c) != 0 && c != '\n' && c != '\"') {
                        state = 35;
                        string[sizeS] = c;
                        string[++sizeS] = '\0';
                    }
                    else if(c == '\n') {
                        state = 35;
                    }
                    else if(c == '\"'){
                        state = 36;
                        t.cat = CONST_STR;
                        strcpy(t.string, string);
                        return t;
                    }
                    else {
                        printf("Invalid character on STATE 35!");
                        exit(1);
                    }
                    break;
            case 1: if(c == '.') {
                        state = 3;
                        digits[sizeD] = c;
                        digits[++sizeD] = '\0';
                    }
                    else if(c >= '0' && c <= '9') {
                        state = 1;
                        digits[sizeD] = c;
                        digits[++sizeD] = '\0';
                    }
                    else {
                        state = 38;
                        ungetc(c, fd);
                        t.cat = CONST_INT;
                        t.intVal = atoi(digits);
                        return t;
                    }
                    break;
            case 3: if(c >= '0' && c <= '9') {
                        state = 4;
                        digits[sizeD] = c;
                        digits[++sizeD] = '\0';
                    }
                    else {
                        printf("Invalid character on STATE 3!");
                        exit(1);
                    }
                    break;
            case 4: if(c >= '0' && c <= '9') {
                        state = 4;
                        digits[sizeD] = c;
                        digits[++sizeD] = '\0';
                    }
                    else {
                        state = 37;
                        ungetc(c, fd);
                        t.cat = CONST_REAL;
                        t.realVal = atof(digits);
                        return t;
                    }
                    break;
            case 5: if((c >= '0' && c <= '9') || (c >= 'a' && c<= 'z') || (c >= 'A' && c<= 'Z') || c == '_') {
                        state = 5;
                        lexeme[sizeL] = c;
                        lexeme[++sizeL] = '\0';
                    }
                    else {
                        state = 2;
                        ungetc(c, fd);
                        t.cat = ID;
                        strcpy(t.lexeme, lexeme);

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
                        }
                        return t;
                    }
                    break;
            case 6: if(c == '_') {
                        state = 6;
                        lexeme[sizeL] = c;
                        lexeme[++sizeL] = '\0';
                    }
                    else if(c >= 'a' && c<= 'z') {
                        state = 5;
                        lexeme[sizeL] = c;
                        lexeme[++sizeL] = '\0';
                    }
                    else {
                        printf("Invalid character on STATE 6!");
                        exit(1);
                    }
                    break;
            case 25: if(c == '|') {
                        state = 26;
                        t.cat = SYMBOL;
                        t.sy_code = OR;
                        return t;
                    }
                    else {
                        printf("Invalid character on STATE 25!");
                        exit(1);
                    }
                    break;
            case 18: if(c == '&') {
                        state = 24;
                        t.cat = SYMBOL;
                        t.sy_code = AND;
                        return t;
                    }
                    else {
                        state = 39;
                        ungetc(c, fd);
                        t.cat = SYMBOL;
                        t.sy_code = ADDR_OF;
                        return t;
                    }
                    break;
            case 22: if(c == '=') {
                        state = 43;
                        t.cat = SYMBOL;
                        t.sy_code = GREATER_EQ;
                        return t;
                    }
                    else {
                        state = 40;
                        ungetc(c, fd);
                        t.cat = SYMBOL;
                        t.sy_code = GREATER;
                        return t;
                    }
                    break;
            case 23: if(c == '=') {
                        state = 45;
                        t.cat = SYMBOL;
                        t.sy_code = EQUAL;
                        return t;
                    }
                    else {
                        state = 46;
                        ungetc(c, fd);
                        t.cat = SYMBOL;
                        t.sy_code = ASSIGN;
                        return t;
                    }
                    break;
            case 20: if(c == '=') {
                        state = 44;
                        t.cat = SYMBOL;
                        t.sy_code = LESS_EQ;
                        return t;
                    }
                    else {
                        state = 42;
                        ungetc(c, fd);
                        t.cat = SYMBOL;
                        t.sy_code = LESS;
                        return t;
                    }
                    break;
            case 17: if(c == '=') {
                        state = 21;
                        t.cat = SYMBOL;
                        t.sy_code = NOT_EQ;
                        return t;
                    }
                    else {
                        state = 41;
                        ungetc(c, fd);
                        t.cat = SYMBOL;
                        t.sy_code = NOT;
                        return t;
                    }
                    break;
            case 8: if(c == '/') {
                        state = 27;
                    }
                    else {
                        state = 19;
                        ungetc(c, fd);
                        t.cat = SYMBOL;
                        t.sy_code = DIV;
                        return t;
                    }
                    break;
            case 27: if(c == '\n') {
                        state = 28;
                        t.cat = COMMENT;
                        strcpy(t.comment, string);
                        return t;
                    }
                    else {
                        state = 27;
                        string[sizeS] = c;
                        string[++sizeS] = '\0';
                    }
                    break;
            case 30: if(c == '\\') {
                        state = 31;
                    }
                    else if(isprint(c) != 0 && c != '\'') {
                        state = 29;
                        constChar = c;
                    }
                    else {
                        printf("Invalid character on STATE 30!");
                        exit(1);
                    }
                    break;
            case 29: if(c == '\'') {
                        state = 47;
                        t.cat = CONST_CHAR;
                        t.charVal = constChar;
                        return t;
                    }
                    else {
                        printf("Invalid character on STATE 29!");
                        exit(1);
                    }
                    break;
            case 31: if(c == 'n') {
                        state = 32;
                        constChar = '\n';
                    }
                    else if(c == '0') {
                        state = 33;
                        constChar = '\0';
                    }
                    else {
                        printf("Invalid character on STATE 31!");
                        exit(1);
                    }
                    break;
            case 32: if(c == '\'') {
                        state = 48;
                        t.cat = CONST_CHAR;
                        t.charVal = constChar;
                        return t;
                    }
                    else {
                        printf("Invalid character on STATE 32!");
                        exit(1);
                    }
                    break;
            case 33: if(c == '\'') {
                        state = 49;
                        t.cat = CONST_CHAR;
                        t.charVal = constChar;
                        return t;
                    }
                    else {
                        printf("Invalid character on STATE 33!");
                        exit(1);
                    }
                    break;
        }
    }
}