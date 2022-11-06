 /*
 ****************************************************************** 
 Name: Rojal Bishwokarma      net-ID_ rb2298

 course: CSE 4714 - Theory and implimentation of programming language

 ******************************************************************
 */
%option yylineno
%option noyywrap
%{
#include "lexer.h"
#include <stdio.h>
#include <string.h>

// global variable to hold current line number to be read
int line_number = 1;

%}

%%
 /* Keywords */ 


\BEGIN  { return TOK_BEGIN; }
\BREAK  { return TOK_BREAK; }
\CONTINUE { return TOK_CONTINUE; }
\DOWNTO { return TOK_DOWNTO; }
\ELSE   { return TOK_ELSE; }
\END    { return TOK_END; }
\FOR    { return TOK_FOR; }
\IF     { return TOK_IF; }
\LET    { return TOK_LET; }
\PROGRAM { return TOK_PROGRAM; }
\READ   { return TOK_READ; }
\THEN   { return TOK_THEN; }
\TO     { return TOK_TO; }
\VAR    { return TOK_VAR; }
\WHILE  { return TOK_WHILE; }
\WRITE  { return TOK_WRITE; }



 /* Datatype Specifiers */

\INTEGER    { return TOK_INTEGER; }
\REAL       { return TOK_REAL; }


 /* Puncutuatuin*/

 \;        { return TOK_SEMICOLON; }
 \:        { return TOK_COLON; }
 \(        { return TOK_OPENPAREN; }
 \)        { return TOK_CLOSEPAREN; }
 \{        { return TOK_OPENBRACE; }
 \}        { return TOK_CLOSEBRACE; }



 /* Operators */

\+      { return TOK_PLUS; }
\-      { return TOK_MINUS; }
\*      { return TOK_MULTIPLY; }
\/      { return TOK_DIVIDE; }
\:=     { return TOK_ASSIGN; }
\=      { return TOK_EQUALTO; }
\<      { return TOK_LESSTHAN; }
\>      { return TOK_GREATERTHAN; }
\<>     { return TOK_NOTEQUALTO; }
\MOD    { return TOK_MOD; }
\NOT    { return TOK_NOT; }
\OR     { return TOK_OR; }
\AND    { return TOK_AND; }



 /*abstraction lexeme */
 
 
[A-Z]{1}  {return TOK_IDENT;} //Lexime to read only one alphabet
[A-Z]{1}[A-Z0-9]{1,7}    {return TOK_IDENT;} //lexeme to read identifyier 8 chararacters long
[A-Z]{1}[A-Z0-9]{8,}         {return TOK_UNKNOWN;}//if the lexime to read identifyier is more than or rather greater than 8 then read as token volume
-?[0-9]+            {return TOK_INTLIT;}//Lexeme to accept the negative as option for integer literal
-?[0-9]+\.[0-9]+    {return TOK_FLOATLIT;}//Lexeme to accept the negative as option for double literal
'[^'\n]{0,80}'     {return TOK_STRINGLIT;}// not accepting single inverted appostophy and new line
'[0-9]{80,}'        {return TOK_UNKNOWN;}//it accept integer with lenghth greater than 8 inclosed with '_'
 
 /* Eat whitespaec */
 [ \t\r\n]+       /* nop */



 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }



