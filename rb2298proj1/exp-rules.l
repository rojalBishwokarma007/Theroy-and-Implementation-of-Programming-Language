/*********************************************************************
  Name: Rojal Bishwokarma            NetID: rb2298
  Course: CSE 4714              
  Lab: 01 - Lexical Analyzer 

**********************************************************************/

%option noyywrap
%{
#include "lexer.h"
// global variable to hold current line number being read
int line_number = 1;
%}

%%

 //code for lexemes
 //Lexeme for punctuation
\,                                                 { return SEPARATOR; } // if there is a comma then it pics it up



[0-9]{4}\/[0-9]{2}\/[0-9]{2}                          { return DATE; } //here [0-9] represent the decimal number value and {2} represent the length and it is same for all and acept in format ex 1998/12/32

[Yy]es                                                {return YES;}//it is for the YES and the same for all [yY] will accept the lower as well as the upper case value same for all instances

[Nn]o                                                 {return NO; }

[Uu]nknown                                            { return UNKNOWN_VALUE; } 

[Mm]issing                                            {return MISSING; }
 /*recognizes specific data values*/
[Ll]aboratory-[Cc]onfirmed\ [Cc]ase	                  { return LABORATORY; }
[Pp]robable\ [Cc]ase                                	{return PROBABLE; }
[Mm]ale			                                          {return MALE; }
[Ff]emale		                                          {return FEMALE; }
[Oo]ther	        	                                  {return OTHER; }
0\ \-\ 9\ [Yy]ears                                    {return AGE_0X; }  //this is for 0-9 basicall for age 0 to 9 years same for all below
10\ \-\ 19\ [Yy]ears                                  {return AGE_1X; }
20\ \-\ 39\ [Yy]ears                                  { return AGE_2X; }
40\ \-\ 49\ [Yy]ears                                  { return AGE_4X; }
50\ \-\ 59\ [Yy]ears                                  { return AGE_5X; }
60\ \-\ 69\ [Yy]ears                                  { return AGE_6X; }
70\ \-\ 79\ [Yy]ears                                  { return AGE_7X; }
80\+\ [Yy]ears                                        { return AGE_8X; }
\"[Hh]ispanic\/[Ll]atino\"                            {return HISPANIC; }  


\"[Aa]merican\ [Ii]ndian\ \/\ [aA]laska\ [Nn]ative,\ [Nn]on-[Hh]ispanic\"                   { return NATIVE_AMERICAN; }
\"[Aa]sian,\ [Nn]on-[Hh]ispanic\"                     { return ASIAN; }
\"[Bb]lack,\ [Nn]on-[Hh]ispanic\"                     { return BLACK; }
\"[Nn]ative\ [Hh]awaiian\ \/\ [Oo]ther\ [Pp]acific\ [Ii]slander,\ [Nn]on-[Hh]ispanic\"     { return PACIFIC_ISLANDER; }
\"[Ww]hite,\ [Nn]on-[Hh]ispanic\"                     { return WHITE; }
\"[Mm]ultiple\/[oO]ther,\ [Nn]on-[Hh]ispanic\"        { return MULTIPLE_OTHER; }


 /* Eat any whitespace*/
 /*\r stands for return, this will return*/
 /*recognize new line*/
[\n\r]           {line_number++;}
 
[ \t]+             /* nop */
 /*eat any whitespace except for return*/




 /* Found an unknown character */

.         { return UNKNOWN_TOKEN; }

 /* This will recognize the end of the file */

<<EOF>>   { return EOF_TOKEN; }
