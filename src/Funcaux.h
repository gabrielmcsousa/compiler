#ifndef _FUNC_AUX_
#define _FUNC_AUX_

#include <stdbool.h>

enum MOVIM {FORWARD, STAY, BACKWARD};

extern bool printTree;
extern char TABS[200];
extern int lineCount;

void error(char msg[]);
void PrintNode(char info[], int move);
void PrintNodeInt(int val, int move);


#endif