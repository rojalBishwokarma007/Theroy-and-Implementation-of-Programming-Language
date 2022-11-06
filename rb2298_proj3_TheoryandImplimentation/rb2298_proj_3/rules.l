/******************************************************************* 
Starting point your rules.l file for TIPS
*******************************************************************/
%option noyywrap
%{
#include "lexer.h"

// global variable to hold current line number being read
int line_number = 1;

int string_line = 0; //variable to hold line number inside string

//global variable to hold yytext when end of file
char str[83]; 
//global variable to hold yyleng when end of file
int str_length=0;
%}


%%

 /* Encountering new line */
\n		{	line_number++;
		if(string_line > 0){
			line_number += string_line;
			string_line = 0;
		}
		
		}
 
 /* Keywords */ 
BEGIN		{return TOK_BEGIN;}
BREAK		{return TOK_BREAK;}
CONTINUE	{return TOK_CONTINUE;}
DOWNTO		{return TOK_DOWNTO;}
ELSE		{return TOK_ELSE;}
END		{return TOK_END;}
FOR		{return TOK_FOR;}
IF		{return TOK_IF;}
LET		{return TOK_LET;}
PROGRAM	{return TOK_PROGRAM;}
READ		{return TOK_READ;}
THEN		{return TOK_THEN;}
TO		{return TOK_TO;}
VAR		{return TOK_VAR;}
WHILE		{return TOK_WHILE;}
WRITE		{return TOK_WRITE;}

 /* Datatype Specifiers */
INTEGER	{return TOK_INTEGER;}
REAL		{return TOK_REAL;}

 /* Punctuation */
\;		{return TOK_SEMICOLON;}	  
:		{return TOK_COLON; }
\(		{return TOK_OPENPAREN;}
\)		{return TOK_CLOSEPAREN;}
\{		{return TOK_OPENBRACE;}
\}		{return TOK_CLOSEBRACE;}


 /* Operators */
\+        	{ return TOK_PLUS; }
-         	{ return TOK_MINUS; }
\*        	{ return TOK_MULTIPLY; }
\/        	{ return TOK_DIVIDE; }
:=		{return TOK_ASSIGN;}
=		{return TOK_EQUALTO;}
\<		{return TOK_LESSTHAN;}
\>		{return TOK_GREATERTHAN;}
\<\>		{return TOK_NOTEQUALTO;}
MOD		{return TOK_MOD;}
NOT		{return TOK_NOT;}
OR		{return TOK_OR;}
AND		{return TOK_AND;}

 /* Abstractions */
[A-Z][A-Z0-9]{0,7} 	{return TOK_IDENT;}
[0-9]+			{return TOK_INTLIT;}
[0-9]+"."[0-9]+		{return TOK_FLOATLIT;}


"'"[^']{0,80}"'"	{
	//see if there is new line inside string
	string_line= 0;
	for (int i=0; i < yyleng; i++){
		if(yytext[i]=='\n'){
			string_line++;  //increasing the line number
		}
	}
	return TOK_STRINGLIT;}



"'"[^']{0,80}			{

str_length=yyleng; 	//storing yyleng

//copying yytext to str
for (int i=0; i<yyleng; i++){
	str[i]=yytext[i];
}

//reading next char to see if it is end of file
if(input()==0){  

yyleng=str_length;	//restoring yyleng's value due to EOF reset 

//restoring yytext's value
for(int i=0; i<yyleng; i++){
yytext[i]=str[i];
}

//returning EOF_SL token
return TOK_EOF_SL;

}else{

//if not end of file
//putting back other characters execpt the first one i.e. character "'" back to the input stream
yyless(1);

//return UNKOWN token for "'" character
return TOK_UNKNOWN;
}
}
	
	
				
 /* Eat any whitespace */

[ \t\r]+               /* nop */

 /* Found an unknown character */

.        { return TOK_UNKNOWN; }

		
 /* Recognize end of file */

<<EOF>>   {return TOK_EOF;}
