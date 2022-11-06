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
int yylineno_saved = 1;
 
#define YY_USER_ACTION  \
  yylineno_initial = yylineno_saved; \
  yylineno_saved = yylineno;
%}

%%
   int yylineno_initial; //keep track of the line number
  //eat up whitespaces
[[:space:]]            // nop





  /* Keywords */ 
  
\BEGIN           { return TOK_BEGIN; }
\BREAK           { return TOK_BREAK; }
\CONTINUE        { return TOK_CONTINUE; }
\DOWNTO          { return TOK_DOWNTO; }
\ELSE            { return TOK_ELSE; }
\END             { return TOK_END; }
\FOR             { return TOK_FOR; }
\IF              { return TOK_IF; }
\LET             { return TOK_LET; }
\PROGRAM         { return TOK_PROGRAM; }
\READ            { return TOK_READ; }
\THEN            { return TOK_THEN; }
\TO              { return TOK_TO; }
\VAR             { return TOK_VAR; }
\WHILE           { return TOK_WHILE; }
\WRITE           { return TOK_WRITE; }



 /* Datatype Specifiers */
 
\INTEGER         { return TOK_INTEGER; }
\REAL            { return TOK_REAL; }

 /* Punctuation */
 
\;               { return TOK_SEMICOLON; }
\:               { return TOK_COLON; }
\(               { return TOK_OPENPAREN; }
\)               { return TOK_CLOSEPAREN; }
\{               { return TOK_OPENBRACE; }
\}               { return TOK_CLOSEBRACE; }




 /* Operators */
 
\+               { return TOK_PLUS; }
\-               { return TOK_MINUS; }
\*               { return TOK_MULTIPLY; }
\/               { return TOK_DIVIDE; }
\:=              { return TOK_ASSIGN; }
\=               { return TOK_EQUALTO; }
\<               { return TOK_LESSTHAN; }
\>               { return TOK_GREATERTHAN; }
\<>              { return TOK_NOTEQUALTO; }
\MOD             { return TOK_MOD; }
\NOT             { return TOK_NOT; }
\OR              { return TOK_OR; }
\AND             { return TOK_AND; }





 /* Abstractions*/
 
 
[A-Z][A-Z0-9]{0,7}         { return TOK_IDENT; }   
[0-9]+                     { return TOK_INTLIT; }  
[0-9]+\.[0-9]+             { return TOK_FLOATLIT; } 
'[^'\n]{0,79}'             { return TOK_STRINGLIT; }     



.         { return TOK_UNKNOWN; }    /* Found an unknown character */
'[^\n]{80,}'		   { return TOK_UNKNOWN; }
[A-Z][A-Z0-9]{7,80}          { return TOK_UNKNOWN; } 



 /* Recognize end of file */
<<EOF>>   { return TOK_EOF; }


