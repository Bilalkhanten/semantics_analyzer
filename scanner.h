/* 
 * You should not need to modify this file. It declare a few
 * constants, types, variables,and functions that are used and/or
 * exported by the lex-generated scanner.
 */

#ifndef _scanner_h
#define _scanner_h

#include <stdio.h>

#define MaxIdentLen 31    // Maximum length for identifiers

extern char *yytext;      // Text of lexeme just scanned


int yylex();              // Defined in the generated lex.yy.c file

void InitScanner();                 // Defined in scanner.l user subroutines
const char *GetLineNumbered(int n); // ditto
 
#endif
