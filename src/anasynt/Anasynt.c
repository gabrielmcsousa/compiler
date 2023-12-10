#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../analex/Analex.h"
#include "Anasynt.h"
#include "../Funcaux.h"

// !!OK!!
void Prog() {
    printf("\n! CHECKING PROG !\n");
    while(t.cat == RES_WORD && ((strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || 
                                (strcmp(t.lexeme, "int") == 0) || (strcmp(t.lexeme, "real") == 0) ||
                                (strcmp(t.lexeme, "bool") == 0))) {
                                    Decl_list_var();
                                    if(t.processed) t = Analex(fd, true);
                                }
    
    if(t.processed) t = Analex(fd, true);
    while((t.cat == RES_WORD && (strcmp(t.lexeme, "block") == 0)) && tkLA.cat == ID) {
        Decl_block_prot();
        if(t.processed) t = Analex(fd, true);
    }
    
    Block_main();
    
    if(t.processed) t = Analex(fd, true);
    while(t.cat == RES_WORD && (strcmp(t.lexeme, "block") == 0)) {
        t.processed = true;
        t = Analex(fd, true);
        Block_def();
        if(t.processed) t = Analex(fd, true);
    }
    printf("! PROG OK !\n");
}

// !!OK!!
void Decl_list_var() {
    printf("\n! CHECKING DECL_LIST_VAR !\n");
    if(strcmp(t.lexeme, "const") == 0) {
        t.processed = true;
        Tipo();
    }
    else{
        Tipo();
    }
    
    if(t.processed) t = Analex(fd, true);
    Decl_var();

    if(t.processed) t = Analex(fd, true);
    while(t.cat == SYMBOL && t.sy_code == COMMA){
        t.processed = true;
        t = Analex(fd, true);
        Decl_var();
        if(t.processed) t = Analex(fd, true);
    }
    printf("! DECL_LIST_VAR OK !\n");
}

// !!OK!!
void Tipo() {
    printf("\n! CHECKING TIPO !\n");
    if(t.processed) t = Analex(fd, true);
    if(t.cat != RES_WORD || ((strcmp(t.lexeme, "char") != 0) && (strcmp(t.lexeme, "int") != 0) && 
                             (strcmp(t.lexeme, "real") != 0) && (strcmp(t.lexeme, "bool") != 0))){
                                error("Missing type!");
                             }
    else{
        t.processed = true;
    }
    printf("! TIPO OK !\n");
}

// !!OK!!
void Decl_var() {
    printf("\n! CHECKING DECL_VAR !\n");
    //id
    if(t.processed) t = Analex(fd, true);
    if(t.cat != ID){
        error("Missing ID!");
    }
    else{
        t.processed = true;
        t = Analex(fd, true);
    }

    //{[intcon | idconst]}
    while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
        t.processed = true;
        t = Analex(fd, true);
        
        if(t.cat != CONST_INT || t.cat != ID_CONST){
            error("Missing length!");
        }
        else{
            t.processed = true;
            t = Analex(fd, true);
        }

        if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
            error("Missing close bracket!");
        }
        else{
            t.processed = true;
            t = Analex(fd, true);
        }
    }

    if(t.cat == SYMBOL && t.sy_code == ASSIGN){
        t.processed = true;
        t = Analex(fd, true);

        if(t.cat == CONST_INT || t.cat == CONST_REAL || t.cat == CONST_CHAR || t.cat == CONST_STR){
            t.processed = true;
            t = Analex(fd, true);
        }
        else if(t.cat == SYMBOL && t.sy_code == OPEN_BRACE){
            t.processed = true;
            t = Analex(fd, true);

            if(t.cat != CONST_INT && t.cat != CONST_REAL && t.cat != CONST_CHAR && t.cat != CONST_STR){
                error("Missing value!");
            }
            else{
                t.processed = true;
                t = Analex(fd, true);
            }

            while(t.cat == SYMBOL && t.sy_code == COMMA){
                t.processed = true;
                t = Analex(fd, true);

                if(t.cat != CONST_INT && t.cat != CONST_REAL && t.cat != CONST_CHAR && t.cat != CONST_STR){
                    error("Missing value after comma!");
                }
                else{
                    t.processed = true;
                    t = Analex(fd, true);
                }
            }

            if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACE){
                error("Missing close brace!");
            }
            else{
                t.processed = true;
                t = Analex(fd, true);
            }
        }
        else{
            error("Missing right side of attribution!");
        }
    }
    printf("! DECL_VAR OK !\n");
}

// !!OK!!
void Decl_block_prot() {
    printf("\n! CHECKING DECL_BLOCK_PROT !\n");
    if(t.processed) t = Analex(fd, true);
    if(strcmp(t.lexeme, "block") != 0){
        error("Missing 'Block'!");
    }
    else {
        t.processed = true;
    }

    if(t.processed) t = Analex(fd, true);
    if(t.cat != ID){
        error("Missing ID!");
    }
    else {
        t.processed = true;
    }

    if(t.processed) t = Analex(fd, true);
    if(strcmp(t.lexeme, "with") == 0){
        t.processed = true;
        
        if(t.processed) t = Analex(fd, true);
        if(t.cat == SYMBOL && t.sy_code == ADDR_OF){
            t.processed = true;
            Tipo();
        }
        else{
            Tipo();
        }

        if(t.processed) t = Analex(fd, true);
        while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
            t.processed = true;
            t = Analex(fd, true);
            if(t.cat == SYMBOL && t.sy_code == CLOSE_BRACK){
                t.processed = true;
            }
            else {
                error("Missing Close Bracket!");
            }
            if(t.processed) t = Analex(fd, true);
        }

        if(t.processed) t = Analex(fd, true);
        while(t.cat == SYMBOL && t.sy_code == COMMA){
            t.processed = true;
            t = Analex(fd, true);
            
            if(t.cat == SYMBOL && t.sy_code == ADDR_OF){
                t.processed = true;
                Tipo();
            }
            else{
                Tipo();
            }

            if(t.processed) t = Analex(fd, true);
            while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
                t.processed = true;
                t = Analex(fd, true);
                
                if(t.cat == SYMBOL && t.sy_code == CLOSE_BRACK){
                    t.processed = true;
                }
                else {
                    error("Missing Close Bracket!");
                }
                if(t.processed) t = Analex(fd, true);
            }
            if(t.processed) t = Analex(fd, true);
        }
    }
    printf("! DECL_BLOCK_PROT OK !\n");
}

// !!OK!!
void Block_main(){
    printf("\n! CHECKING BLOCK_MAIN !\n");
    if(t.processed) t = Analex(fd, true);   
    if(t.cat != RES_WORD || (strcmp(t.lexeme, "block") != 0)){
        error("Missing 'block' !");
    }
    t.processed = true;
    t = Analex(fd, true);

    if(t.cat != RES_WORD || (strcmp(t.lexeme, "main") != 0)){
        error("Missing 'main' !");
    }
    t.processed = true;
    t = Analex(fd, true);

    while((t.cat == RES_WORD && ((strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || 
                                (strcmp(t.lexeme, "int") == 0) || (strcmp(t.lexeme, "real") == 0) ||
                                (strcmp(t.lexeme, "bool") == 0)))){
                                    Decl_list_var();
                                    if(t.processed) t = Analex(fd, true);
                                }

    while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                (strcmp(t.lexeme, "putchar") == 0)))){
        Cmd();
        if(t.processed) t = Analex(fd, true);
    }

    if(t.cat != RES_WORD || (strcmp(t.lexeme, "endblock") != 0)){
        error("Missing 'endblock' !");
    }
    t.processed = true;
    printf("! BLOCK_MAIN OK !\n");
}

// !!OK!!
void Block_def(){
    printf("\n! CHECKING BLOCK_DEF !\n");
    if(t.processed) t = Analex(fd, true);
    if(t.cat != RES_WORD || (strcmp(t.lexeme, "block") != 0)){
        error("Missing 'block' !");
    }
    t.processed = true;
    t = Analex(fd, true);

    if(t.cat != ID){
        error("Missing ID !");
    }
    t.processed = true;
    t = Analex(fd, true);

    if(t.cat == RES_WORD && (strcmp(t.lexeme, "with") == 0)){
        t.processed = true;
        t = Analex(fd, true);
        Tipo();

        if(t.processed) t = Analex(fd, true);
        if(t.cat != ID){
            error("Missing ID !");
        }
        t.processed = true;
        t = Analex(fd, true);

        while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
            t.processed = true;
            t = Analex(fd, true);
            
            if(t.cat != CONST_INT || t.cat != ID_CONST){
                error("Missing length!");
            }
            else{
                t.processed = true;
                t = Analex(fd, true);
            }

            if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
                error("Missing close bracket!");
            }
            else{
                t.processed = true;
                t = Analex(fd, true);
            }
        }

        while(t.cat == SYMBOL && t.sy_code == COMMA){
            t.processed = true;
            t = Analex(fd, true);
            Tipo();

            if(t.processed) t = Analex(fd, true);
            if(t.cat != ID){
                error("Missing ID !");
            }
            t.processed = true;
            t = Analex(fd, true);

            while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
                t.processed = true;
                t = Analex(fd, true);
                
                if(t.cat != CONST_INT || t.cat != ID_CONST){
                    error("Missing length!");
                }
                else{
                    t.processed = true;
                    t = Analex(fd, true);
                }

                if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
                    error("Missing close bracket!");
                }
                else{
                    t.processed = true;
                    t = Analex(fd, true);
                }
                if(t.processed) t = Analex(fd, true);
            }
            if(t.processed) t = Analex(fd, true);
        }

        if(t.processed) t = Analex(fd, true);
        while(t.cat == RES_WORD && ((strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || 
                                (strcmp(t.lexeme, "int") == 0) || (strcmp(t.lexeme, "real") == 0) ||
                                (strcmp(t.lexeme, "bool") == 0))) {
                                    t.processed = true;
                                    t = Analex(fd, true);
                                    Decl_list_var();
                                    if(t.processed) t = Analex(fd, true);
                                }

        if(t.processed) t = Analex(fd, true);
        while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd, true);
            Cmd();
            if(t.processed) t = Analex(fd, true);
        }

        if(t.processed) t = Analex(fd, true);
        if(t.cat != RES_WORD || (strcmp(t.lexeme, "endblock") != 0)){
            error("Missing 'endblock' !");
        }
        t.processed = true;
    }
    t.processed = true;
    t = Analex(fd, true);
    printf("! BLOCK_DEF OK !\n");
}

// !!OK!!
void Cmd(){
    printf("\n! CHECKING CMD !\n");
    if(t.processed) t = Analex(fd, true);
    if(t.cat == RES_WORD && (strcmp(t.lexeme, "do") == 0)){
        t.processed = true;
        t = Analex(fd, true);

        if(t.cat == ID){
            t.processed = true;
            t = Analex(fd, true);
            if(t.cat == RES_WORD && (strcmp(t.lexeme, "with") == 0)){
                t.processed =  true;
                t = Analex(fd, true);

                if(t.cat != ID){
                    error("Missing ID !");
                }
                t.processed = true;
                t = Analex(fd, true);

                while(t.cat == SYMBOL && t.sy_code == COMMA){
                    t.processed = true;
                    t = Analex(fd, true);
                    
                    if(t.cat != ID){
                        error("Missing ID !");
                    }
                    
                    t.processed = true;
                    t = Analex(fd, true);
                }
            }
        }
        else if(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd, true);
            Cmd();
        }
        else{
            error("Missing id or cmd !");
        }

        if(t.processed) t = Analex(fd, true);
        if(t.cat == RES_WORD && (strcmp(t.lexeme, "varying") == 0)){
            t.processed = true;
            t = Analex(fd, true);

            if(t.cat != ID){
                error("Missing ID !");
            }
            t.processed = true;
            t = Analex(fd, true);

            if(t.cat != RES_WORD || (strcmp(t.lexeme, "from") != 0)){
                error("Missing 'from' !");
            }
            t.processed = true;
            t = Analex(fd, true);

            Expr();

            if(t.processed) t = Analex(fd, true);
            if(t.cat != RES_WORD || ((strcmp(t.lexeme, "to") != 0) && (strcmp(t.lexeme, "downto") != 0))){
                error("Missing 'to' or 'downto' !");
            }
            t.processed = true;
            t = Analex(fd, true);

            Expr();
        }
        else if(t.cat == RES_WORD && (strcmp(t.lexeme, "while") == 0)){
            t.processed = true;
            t = Analex(fd, true);

            if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
                error("Missing '(' !");
            }
            t.processed = true;
            t = Analex(fd, true);

            Expr();

            if(t.processed) t = Analex(fd, true);
            if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
                error("Missing ')' !");
            }
            t.processed = true;
        }
        else if(t.cat == RES_WORD && (strcmp(t.lexeme, "for") == 0)){
            t.processed = true;
            t = Analex(fd, true);

            Expr();
            
            if(t.processed) t = Analex(fd, true);
            if(t.cat != RES_WORD || (strcmp(t.lexeme, "times") == 0)){
                error("Missing 'times' !");
            }
        }
    }
    // END IF 'do'
    else if(t.cat == RES_WORD && (strcmp(t.lexeme, "if") == 0)){
        t.processed = true;
        t = Analex(fd, true);
        
        if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
            error("Missing '(' !");
        }
        t.processed = true;
        t = Analex(fd, true);

        Expr();

        if(t.processed) t = Analex(fd, true);
        if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
            error("Missing ')' !");
        }
        t.processed = true;
        t = Analex(fd, true);

        while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd, true);
            Cmd();
            if(t.processed) t = Analex(fd, true);
        }
        
        if(t.processed) t = Analex(fd, true);
        while(t.cat == RES_WORD || (strcmp(t.lexeme, "elseif") == 0)){
            t.processed = true;
            t = Analex(fd, true);

            if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
                error("Missing '(' !");
            }
            t.processed = true;
            t = Analex(fd, true);

            Expr();

            if(t.processed) t = Analex(fd, true);
            if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
                error("Missing ')' !");
            }
            t.processed = true;
            t = Analex(fd, true);

            while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
                t.processed = true;
                t = Analex(fd, true);
                Cmd();
                if(t.processed) t = Analex(fd, true);
            }
            if(t.processed) t = Analex(fd, true);
        }

        if(t.processed) t = Analex(fd, true);
        if(t.cat == RES_WORD && (strcmp(t.lexeme, "else") == 0)){
            t.processed = true;
            t = Analex(fd, true);
            while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
                t.processed = true;
                t = Analex(fd, true);
                Cmd();
                if(t.processed) t = Analex(fd, true);
            }
        }

        if(t.processed) t = Analex(fd, true);
        if(t.cat != RES_WORD || (strcmp(t.lexeme, "endif") != 0)){
            error("Missing 'endif' !");
        }
    }
    // END IF 'if'
    else if(t.cat == RES_WORD && (strcmp(t.lexeme, "while") == 0)){
        t.processed = true;
        t = Analex(fd, true);
        
        if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
            error("Missing '(' !");
        }
        t.processed = true;
        t = Analex(fd, true);

        Expr();

        if(t.processed) t = Analex(fd, true);
        if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
            error("Missing ')' !");
        }
        t.processed = true;
        t = Analex(fd, true);

        while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd, true);
            Cmd();
            if(t.processed) t = Analex(fd, true);
        }

        if(t.cat != RES_WORD || (strcmp(t.lexeme, "endwhile") != 0)){
            error("Missing 'endwhile' !");
        }
        t.processed = true;
    }
    // END IF 'while'
    else if(t.cat == ID){
        Atrib();
    }
    // END IF 'atrib'
    else if(t.cat == RES_WORD && (strcmp(t.lexeme, "goback") == 0)){
        t.processed = true;
    }
    else if(t.cat == RES_WORD && ((strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || (strcmp(t.lexeme, "getchar") == 0) ||
                                  (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || (strcmp(t.lexeme, "putchar") == 0))){
        t.processed = true;
        t = Analex(fd, true);

        if(t.cat != ID){
            error("Missing ID !");
        }
        t.processed = true;
    }
    printf("! CMD OK !\n");
}

void Atrib(){
    printf("\n! CHECKING ATRIB !\n");
    if(t.processed) t = Analex(fd, true);
    if(t.cat != ID){
        error("Missing ID");
    }
    t.processed = true;
    t = Analex(fd, true);

    while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
        t.processed = true;
        t = Analex(fd, true);

        Expr();

        if(t.processed) t = Analex(fd, true);
        if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
            error("Missing ']' !");
        }
        t.processed = true;
        t = Analex(fd, true);
    }

    if(t.cat != SYMBOL || t.sy_code != ASSIGN){
        error("Missing '=' !");
    }
    t.processed = true;
    t = Analex(fd, true);

    Expr();
    printf("! ATRIB OK !\n");
}

void Expr(){
    printf("\n! CHECKING EXPR !\n");
    Expr_simp();

    if(t.processed) t = Analex(fd, true);
    if(t.cat == SYMBOL){
        Op_rel();
        if(t.processed) t = Analex(fd, true);
        Expr_simp();
    }
    printf("! EXPR OK !\n");
}

void Expr_simp(){
    printf("\n! CHECKING EXPR_SIMP !\n");
    if(t.processed) t = Analex(fd, true);
    if(t.cat == SYMBOL && (t.sy_code == ADD || t.sy_code == SUBT)){
        t.processed = true;
    }

    if(t.processed) t = Analex(fd, true);
    Termo();

    if(t.processed) t = Analex(fd, true);
    while(t.cat == SYMBOL){
        if(t.sy_code != ADD && t.sy_code != SUBT && t.sy_code != OR){
            error("Invalid Symbol!");
        }
        t.processed = true;
        t = Analex(fd, true);

        Termo();
        if(t.processed) t = Analex(fd, true);
    }
    printf("! EXPR_SIMP OK !\n");
}

void Termo(){
    printf("\n! CHECKING TERMO !\n");
    Fator();

    if(t.processed) t = Analex(fd, true);
    while(t.cat == SYMBOL){
        if(t.sy_code != MULT || t.sy_code != DIV || t.sy_code != AND){
            error("Invalid Symbol!");
        }
        t.processed = true;
        t = Analex(fd, true);

        Fator();
        if(t.processed) t = Analex(fd, true);
    }
    printf("! TERMO OK !\n");
}

void Fator(){
    printf("\n! CHECKING FATOR !\n");
    if(t.cat == ID){
        t.processed = true;
        t = Analex(fd, true);

        while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
            t.processed = true;
            t = Analex(fd, true);

            Expr();

            if(t.processed) t = Analex(fd, true);
            if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
                error("Missing ']' !");
            }
            t.processed = true;
            t = Analex(fd, true);
        }    
    }
    else if(t.cat == CONST_INT || t.cat == CONST_REAL || t.cat == CONST_CHAR){
        t.processed = true;
    }
    else if(t.cat == SYMBOL && t.sy_code == OPEN_PAR){
        t.processed = true;
        t = Analex(fd, true);

        Expr();

        if(t.processed) t = Analex(fd, true);
        if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
            error("Missing ')' !");
        }    
    }
    else if(t.cat == SYMBOL && t.sy_code == NOT){
        t.processed = true;
        t = Analex(fd, true);
        Fator();
    }
    printf("! FATOR OK !\n");
}

void Op_rel(){
    printf("\n! CHECKING OP_REL !\n");
    if(t.processed) t = Analex(fd, true);
    if(t.cat != SYMBOL || t.sy_code != EQUAL || t.sy_code != NOT_EQ || t.sy_code != LESS 
                       || t.sy_code != LESS_EQ || t.sy_code != GREATER || t.sy_code != GREATER_EQ){
            error("Invalid Operator!");
    }
    else{
        t.processed = true;
    }
    printf("! OP_REL OK !\n");   
}