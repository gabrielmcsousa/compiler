#include <stdlib.h>
#include <string.h>
#include "Funcaux.h"
#include "idTable.h"



void InitIdTable() {
    idTable.tabSize = 0;
}


int SearchIdTable(char idName[]) {

    int i;

    for (i=0; i<idTable.tabSize; i++) {
        if (!(strcmp(idName, idTable.id[i].idName))) return i;
    }
    return -1;
}


int InsertIdTable(char idName[], bool is_const, int scope, enum TOKEN_CAT cat) {

    int i;
    if (idTable.tabSize == ID_TAB_MAX_SIZE) error("ID Stack Overflow!");
    i = idTable.tabSize;
    strcpy(idTable.id[i].idName, idName);
    idTable.id[i].address = i;
    idTable.tabSize++;
    return i;
}

void setZombie(char idName[], bool state){
    int i = SearchIdTable(idName);
    idTable.id[i].zombie = state;
}