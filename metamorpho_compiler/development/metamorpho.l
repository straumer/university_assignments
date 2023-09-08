%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

static void copy() 
{
	char temptext[32768];
	strncpy(temptext, yytext, yyleng);
	temptext[yyleng] = 0;
	yylval.sval = strdup(temptext);
}
//|  "/*".*"*/" | "//".*\\n
%}

IGNORE      [ \t\n]+
DIGIT		[0-9]
DOUBLE		{DIGIT}+\.{DIGIT}+([eE][+-]?{DIGIT}+)?
INT		    {DIGIT}+
OP_1  		[*/%]
OP_2        [\+\-]
BOOLOP      !=|<=|=>|<|>|==
STRING		\"([^\"\\]|\\b|\\t|\\n|\\f|\\r|\\\"|\\\'|\\\\|(\\[0-3][0-7][0-7])|\\[0-7][0-7]|\\[0-7]|{ALPHA})*\"
CHAR		\'([^\'\\]|\\b|\\t|\\n|\\f|\\r|\\\"|\\\'|\\\\|(\\[0-3][0-7][0-7])|(\\[0-7][0-7])|(\\[0-7])|{ALPHA})\'
DELIM       [,{}\(\);]
ALPHA		[a-zA-Z]
NAME		(_|{ALPHA})(_|{ALPHA}|{DIGIT})*
NUM         {DOUBLE}|{INT}
BOOL        "satt"|"osatt"|"oskilgreint"
STRLIT      {STRING}|{CHAR}

%%

{IGNORE}    /* Do nothing */
ef          return(IF);
annars      return(ELSE);
lykkja      return(WHILE);
skila       return(RETURN);
og          return(AND);
ogeda       return(OR);
ekki        return(NOT);
fall        return(FUNCTION);
skrifa      return(WRITE);
{STRLIT}    { copy(); return(STRLIT); }
{NUM}       { copy(); return(NUM); }
{BOOL}      { copy(); return(BOOL); }
{NAME}      { copy(); return(NAME); }
{BOOLOP}    { copy(); return(BOOLOP); }
{OP_1}      { copy(); return(OP_1); }
{OP_2}      { copy(); return(OP_2); }
{DELIM}     { return(yytext[0]); }
=           { return(yytext[0]); }

