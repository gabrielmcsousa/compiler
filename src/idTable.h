#ifndef _ID_TABLE_
#define _ID_TABLE_

#include <stdlib.h>
#include <stdio.h>
#include "analex/Analex.h"

#define ID_TAB_MAX_SIZE 200

typedef
    struct {
        char idName[LEXEME_MAX_SIZE];
        int address;
        bool is_const;
        bool zombie;
        int scope;
        enum TOKEN_CAT cat;
        union {
            char charVal;
            int intVal;
            float realVal;
            bool boolVal;
        };
        
    } ID_REG;                      // Uma entrada na Tabela de Identificadores


typedef
    struct {
        int tabSize;
        ID_REG id[ID_TAB_MAX_SIZE];
    } ID_TAB;                      // Tabela de identificadores


extern TOKEN t;
extern ID_TAB idTable;

void InitIdTable();
int SearchIdTable(char []);
int InsertIdTable(char [], bool is_const, int scope, enum TOKEN_CAT cat);

#endif // _ID_TABLE_
