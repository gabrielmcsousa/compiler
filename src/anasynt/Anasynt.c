#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Anasynt.h"
#include "../Funcaux.h"

// !!OK!!
void Prog() {

    while(t.cat == RES_WORD && ((strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || 
                                (strcmp(t.lexeme, "int") == 0) || (strcmp(t.lexeme, "real") == 0) ||
                                (strcmp(t.lexeme, "bool") == 0))) {
                                    Decl_list_var();
                                }
    
    if(t.processed) t = Analex(fd);
    while(t.cat == RES_WORD && (strcmp(t.lexeme, "block") == 0)) {
        Decl_block_prot();
    }
    
    if(t.processed) t = Analex(fd);
    Block_main();
    
    if(t.processed) t = Analex(fd);
    while(t.cat == RES_WORD && (strcmp(t.lexeme, "block") == 0)) {
        Block_def();
    }
}

// !!OK!!
void Decl_list_var() {
    if(strcmp(t.lexeme, "const") == 0) {
        t.processed = true;
        Tipo();
    }
    else{
        Tipo();
    }
    
    if(t.processed) t = Analex(fd);
    Decl_var();

    if(t.processed) t = Analex(fd);
    while(t.cat == SYMBOL && t.sy_code == COMMA){
        t.processed = true;
        Decl_var();
    }
}

// !!OK!!
void Tipo() {
    if(t.processed) t = Analex(fd);
    if(t.cat != RES_WORD || ((strcmp(t.lexeme, "char") != 0) && (strcmp(t.lexeme, "int") != 0) && 
                             (strcmp(t.lexeme, "real") != 0) && (strcmp(t.lexeme, "bool") != 0))){
                                error("Missing type!");
                             }
    else{
        t.processed = true;
    }
}

// !!OK!!
void Decl_var() {
    //id
    if(t.processed) t = Analex(fd);
    if(t.cat != ID){
        error("Missing ID!");
    }
    else{
        t.processed = true;
        t = Analex(fd);
    }

    //{[intcon | idconst]}
    while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
        t.processed = true;
        t = Analex(fd);
        
        if(t.cat != CONST_INT || t.cat != ID_CONST){
            error("Missing length!");
        }
        else{
            t.processed = true;
            t = Analex(fd);
        }

        if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
            error("Missing close bracket!");
        }
        else{
            t.processed = true;
            t = Analex(fd);
        }
    }

    if(t.cat == SYMBOL && t.sy_code == EQUAL){
        t.processed = true;
        t = Analex(fd);

        if(t.cat == CONST_INT || t.cat == CONST_REAL || t.cat == CONST_CHAR || t.cat == CONST_STR){
            t.processed = true;
            t = Analex(fd);
        }
        else if(t.cat == SYMBOL && t.sy_code == OPEN_BRACE){
            t.processed = true;
            t = Analex(fd);

            if(t.cat != CONST_INT && t.cat != CONST_REAL && t.cat != CONST_CHAR && t.cat != CONST_STR){
                error("Missing value!");
            }
            else{
                t.processed = true;
                t = Analex(fd);
            }

            while(t.cat == SYMBOL && t.sy_code == COMMA){
                t.processed = true;
                t = Analex(fd);

                if(t.cat != CONST_INT && t.cat != CONST_REAL && t.cat != CONST_CHAR && t.cat != CONST_STR){
                    error("Missing value after comma!");
                }
                else{
                    t.processed = true;
                    t = Analex(fd);
                }
            }

            if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACE){
                error("Missing close brace!");
            }
        }
        else{
            error("Missing right side of attribution!");
        }
    }
}

// !!OK!!
void Decl_block_prot() {
    if(t.processed) t = Analex(fd);
    if(strcmp(t.lexeme, "block") != 0){
        error("Missing 'Block'!");
    }
    else {
        t.processed = true;
    }

    if(t.processed) t = Analex(fd);
    if(t.cat != ID){
        error("Missing ID!");
    }
    else {
        t.processed = true;
    }

    if(t.processed) t = Analex(fd);
    if(strcmp(t.lexeme, "with") == 0){
        t.processed = true;
        
        if(t.processed) t = Analex(fd);
        if(t.cat == SYMBOL && t.sy_code == ADDR_OF){
            t.processed = true;
            Tipo();
        }
        else{
            Tipo();
        }

        if(t.processed) t = Analex(fd);
        while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
            t.processed = true;
            if(t.processed) t = Analex(fd);
            if(t.cat == SYMBOL && t.sy_code == CLOSE_BRACK){
                t.processed = true;
            }
            else {
                error("Missing Close Bracket!");
            }
        }

        if(t.processed) t = Analex(fd);
        while(t.cat == SYMBOL && t.sy_code == COMMA){
            t.processed = true;
            
            if(t.processed) t = Analex(fd);
            if(t.cat == SYMBOL && t.sy_code == ADDR_OF){
                t.processed = true;
                Tipo();
            }
            else{
                Tipo();
            }

            if(t.processed) t = Analex(fd);
            while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
                t.processed = true;
                
                if(t.processed) t = Analex(fd);
                if(t.cat == SYMBOL && t.sy_code == CLOSE_BRACK){
                    t.processed = true;
                }
                else {
                    error("Missing Close Bracket!");
                }
            }
        }
    }
}

// !!OK!!
void Block_main(){
    if(t.processed) t = Analex(fd);
    if(t.cat != RES_WORD || (strcmp(t.lexeme, "block") != 0)){
        error("Missing 'block' !");
    }
    t.processed = true;
    t = Analex(fd);

    if(t.cat != RES_WORD || (strcmp(t.lexeme, "main") != 0)){
        error("Missing 'main' !");
    }

    while((t.cat == RES_WORD && ((strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || 
                                (strcmp(t.lexeme, "int") == 0) || (strcmp(t.lexeme, "real") == 0) ||
                                (strcmp(t.lexeme, "bool") == 0)))){
                                    Decl_list_var();
                                }
    if(t.processed) t = Analex(fd);

    while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                (strcmp(t.lexeme, "putchar") == 0)))){
        t.processed = true;
        t = Analex(fd);
        Cmd();
    }
    if(t.processed) t = Analex(fd);

    if(t.cat != RES_WORD || (strcmp(t.lexeme, "endblock") != 0)){
        error("Missing 'endblock' !");
    }
    t.processed = true;
}

// !!OK!!
void Block_def(){
    if(t.processed) t = Analex(fd);
    if(t.cat != RES_WORD || (strcmp(t.lexeme, "block") != 0)){
        error("Missing 'block' !");
    }
    t.processed = true;
    t = Analex(fd);

    if(t.cat != ID){
        error("Missing ID !");
    }
    t.processed = true;
    t = Analex(fd);

    if(t.cat == RES_WORD && (strcmp(t.lexeme, "with") == 0)){
        t.processed = true;
        t = Analex(fd);
        Tipo();

        if(t.processed) t = Analex(fd);
        if(t.cat != ID){
            error("Missing ID !");
        }
        t.processed = true;
        t = Analex(fd);

        while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
            t.processed = true;
            t = Analex(fd);
            
            if(t.cat != CONST_INT || t.cat != ID_CONST){
                error("Missing length!");
            }
            else{
                t.processed = true;
                t = Analex(fd);
            }

            if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
                error("Missing close bracket!");
            }
            else{
                t.processed = true;
                t = Analex(fd);
            }
        }

        while(t.cat == SYMBOL && t.sy_code == COMMA){
            t.processed = true;
            t = Analex(fd);
            Tipo();

            if(t.processed) t = Analex(fd);
            if(t.cat != ID){
                error("Missing ID !");
            }
            t.processed = true;
            t = Analex(fd);

            while(t.cat == SYMBOL && t.sy_code == OPEN_BRACK){
                t.processed = true;
                t = Analex(fd);
                
                if(t.cat != CONST_INT || t.cat != ID_CONST){
                    error("Missing length!");
                }
                else{
                    t.processed = true;
                    t = Analex(fd);
                }

                if(t.cat != SYMBOL || t.sy_code != CLOSE_BRACK){
                    error("Missing close bracket!");
                }
                else{
                    t.processed = true;
                    t = Analex(fd);
                }
            }
        }

        if(t.processed) t = Analex(fd);
        while(t.cat == RES_WORD && ((strcmp(t.lexeme, "const") == 0) || (strcmp(t.lexeme, "char") == 0) || 
                                (strcmp(t.lexeme, "int") == 0) || (strcmp(t.lexeme, "real") == 0) ||
                                (strcmp(t.lexeme, "bool") == 0))) {
                                    Decl_list_var();
                                }

        if(t.processed) t = Analex(fd);
        while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd);
            Cmd();
        }

        if(t.processed) t = Analex(fd);
        if(t.cat != RES_WORD || (strcmp(t.lexeme, "endblock") != 0)){
            error("Missing 'endblock' !");
        }
        t.processed = true;
    }
    t.processed = true;
    t = Analex(fd);
}

// !!OK!!
void Cmd(){
    if(t.processed) t = Analex(fd);
    if(t.cat == RES_WORD && (strcmp(t.lexeme, "do") == 0)){
        t.processed = true;
        t = Analex(fd);

        if(t.cat == ID){
            t.processed = true;
            t = Analex(fd);
            if(t.cat == RES_WORD && (strcmp(t.lexeme, "with") == 0)){
                t.processed =  true;
                t = Analex(fd);

                if(t.cat != ID){
                    error("Missing ID !");
                }
                t.processed = true;
                t = Analex(fd);

                while(t.cat == SYMBOL && t.sy_code == COMMA){
                    t.processed = true;
                    t = Analex(fd);
                    
                    if(t.cat != ID){
                        error("Missing ID !");
                    }
                    
                    t.processed = true;
                    t = Analex(fd);
                }
            }
        }
        else if(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd);
            Cmd();
        }
        else{
            error("Missing id or cmd !");
        }

        if(t.processed) t = Analex(fd);
        if(t.cat == RES_WORD && (strcmp(t.lexeme, "varying") == 0)){
            t.processed = true;
            t = Analex(fd);

            if(t.cat != ID){
                error("Missing ID !");
            }
            t.processed = true;
            t = Analex(fd);

            if(t.cat != RES_WORD || (strcmp(t.lexeme, "from") != 0)){
                error("Missing 'from' !");
            }
            t.processed = true;
            t = Analex(fd);

            Expr();

            if(t.processed) t = Analex(fd);
            if(t.cat != RES_WORD || ((strcmp(t.lexeme, "to") != 0) && (strcmp(t.lexeme, "downto") != 0))){
                error("Missing 'to' or 'downto' !");
            }
            t.processed = true;
            t = Analex(fd);

            Expr();
        }
        else if(t.cat == RES_WORD && (strcmp(t.lexeme, "while") == 0)){
            t.processed = true;
            t = Analex(fd);

            if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
                error("Missing '(' !");
            }
            t.processed = true;
            t = Analex(fd);

            Expr();

            if(t.processed) t = Analex(fd);
            if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
                error("Missing ')' !");
            }
            t.processed = true;
        }
        else if(t.cat == RES_WORD && (strcmp(t.lexeme, "for") == 0)){
            t.processed = true;
            t = Analex(fd);

            Expr();
            
            if(t.processed) t = Analex(fd);
            if(t.cat != RES_WORD || (strcmp(t.lexeme, "times") == 0)){
                error("Missing 'times' !");
            }
        }
    }
    // END IF 'do'
    else if(t.cat == RES_WORD && (strcmp(t.lexeme, "if") == 0)){
        t.processed = true;
        t = Analex(fd);
        
        if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
            error("Missing '(' !");
        }
        t.processed = true;
        t = Analex(fd);

        Expr();

        if(t.processed) t = Analex(fd);
        if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
            error("Missing ')' !");
        }
        t.processed = true;
        t = Analex(fd);

        while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd);
            Cmd();
        }
        
        if(t.processed) t = Analex(fd);
        while(t.cat == RES_WORD || (strcmp(t.lexeme, "elseif") == 0)){
            t.processed = true;
            t = Analex(fd);

            if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
                error("Missing '(' !");
            }
            t.processed = true;
            t = Analex(fd);

            Expr();

            if(t.processed) t = Analex(fd);
            if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
                error("Missing ')' !");
            }
            t.processed = true;
            t = Analex(fd);

            while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
                t.processed = true;
                t = Analex(fd);
                Cmd();
            }
        }

        if(t.processed) t = Analex(fd);
        if(t.cat == RES_WORD && (strcmp(t.lexeme, "else") == 0)){
            t.processed = true;
            t = Analex(fd);
            while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
                t.processed = true;
                t = Analex(fd);
                Cmd();
            }
        }

        if(t.processed) t = Analex(fd);
        if(t.cat != RES_WORD || (strcmp(t.lexeme, "endif") != 0)){
            error("Missing 'endif' !");
        }
    }
    // END IF 'if'
    else if(t.cat == RES_WORD && (strcmp(t.lexeme, "while") == 0)){
        t.processed = true;
        t = Analex(fd);
        
        if(t.cat != SYMBOL || t.sy_code != OPEN_PAR){
            error("Missing '(' !");
        }
        t.processed = true;
        t = Analex(fd);

        Expr();

        if(t.processed) t = Analex(fd);
        if(t.cat != SYMBOL || t.sy_code != CLOSE_PAR){
            error("Missing ')' !");
        }
        t.processed = true;
        t = Analex(fd);

        while(t.cat == ID || (t.cat == RES_WORD && ((strcmp(t.lexeme, "do") == 0) || (strcmp(t.lexeme, "if") == 0) || (strcmp(t.lexeme, "while") == 0) || 
                                    (strcmp(t.lexeme, "goback") == 0) || (strcmp(t.lexeme, "getint") == 0) || (strcmp(t.lexeme, "getreal") == 0) || 
                                    (strcmp(t.lexeme, "getchar") == 0) || (strcmp(t.lexeme, "putint") == 0) || (strcmp(t.lexeme, "putreal") == 0) || 
                                    (strcmp(t.lexeme, "putchar") == 0)))){
            t.processed = true;
            t = Analex(fd);
            Cmd();
        }

        if(t.processed) t = Analex(fd);
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
        t = Analex(fd);

        if(t.cat != ID){
            error("Missing ID !");
        }
        t.processed = true;
    }
}