/*
Name: Rojal Bishwokarma      net-ID_ rb2298

course: CSE 4714 - Theory and implimentation of programming language

Lab2: PARSER
*/

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

int nextToken = 0;
//this will b the global variable that we are going to use later
int Acount =1; 
int Ncount = 1; 
int Vcount = 1; 

//******************************************************************************************************************************************************************************************
// Production functions
bool firstOf_sentence();
bool firstverbphrase();
bool firstadjectivephrase();
bool firstnounphrase();
void nounphrase();
void verbphrase();
void adjectvphrase();
string space(int n);


//******************************************************************************************************************************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*******************************************************************************************************************************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}


 // **************************************************************************************************************************************************************************************
 // all the error checking functios

bool firstOf_sentence() 
{//checking error for first of sentence
  return nextToken == ARTICLE || nextToken == POSSESSIVE; 
}

bool firstnounphrase()
{ // checking error for first of noun phrase
  return nextToken == ARTICLE || nextToken == POSSESSIVE;  
}

bool firstadjectivephrase()
{  // checking error for first of adjective phrase
  return nextToken == ARTICLE || nextToken == POSSESSIVE; 
}

bool firstverbphrase()
{ // error checking for first of verb phrase
  return nextToken == VERB || nextToken == ADVERB;  
}

 //*******************************************************************************************************************************************************************************************
 
 // indentation
string space(int n)
{
  string nest( n, ' '); 

  return nest; 
}


 //*****************************************************************************************************************************************************************************************
 // <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false ) // checking if first word did start with article or possessive or not
    throw( "<sentence> did not start with an article or possessive." );

  cout << "Enter <sentence>" << endl;
  
 nounphrase();
 verbphrase();
 nounphrase();

 cout << "Exit <sentence>" << endl;
} 

//*******************************************************************************************************************************************************************************************

 // Adjective Phrase
void adjectvphrase()
{
  int current_Acount = Acount++;

  if( firstadjectivephrase() != true ) //checking if start with an article of possessive
    throw( "<adjective phrase> did not start with an article or possessive." ); 
  // //this all diplayes all error the messages (have represented the spaces with each of the if statment)
  if (current_Acount == 1)
  {
    cout << space(current_Acount)<<" Enter <adjective phrase> " << current_Acount<<endl; 
  }
  if (current_Acount== 2)
  {
    cout << space(current_Acount)<<"  Enter <adjective phrase> " << current_Acount <<endl;
  }

  // now if we find ARTICLE OR POSSESSIVE then we have

  if (nextToken == ARTICLE || nextToken == POSSESSIVE) // checking if ARTICLE or POSSESSIVE is true
  {
    // if article is true then we outpout ARTICLE
    if (nextToken == ARTICLE) 
      output("ARTICLE"); 

    // if the POSSESSIVE is true then output POSSESSIVE
    if (nextToken == POSSESSIVE) 
      output("POSSESSIVE"); 
    
    lex();
  }

  // now for adjective
  if (nextToken == ADJECTIVE) //if adjective
  {
    output("ADJECTIVE"); //return adjective
    lex();
  }

  // if we dont find adjective
  
  else
  {
    throw "<adjective phrase> did not have an adjective."; 
  }
  //this all diplayes all the messages (have represented the spaces with each of the if statment)
  if (current_Acount == 1)
  {
    cout << space(current_Acount) << " Exit <adjective phrase> " << current_Acount << endl; 
  }
  if (current_Acount == 2)
  {
    cout << space(current_Acount) << "  Exit <adjective phrase> " << current_Acount << endl; 
  }

}


//******************************************************************************************************************************************************************************************
//Noun Phrase

void nounphrase()
{
  int currentA = Ncount++; // local incrementor

  if( firstnounphrase() != true ) //if sentence doesnot contain Noun
    throw( "<noun phrase> did not start with an article or possessive." ); 

  //this all diplayes all error the messages (have represented the spaces with each of the if statment)
  if (currentA == 1)
  {
    cout << space(currentA) << " Enter <noun phrase> " << currentA << endl; 
  }
  if (currentA == 2)
  {
    cout << space(currentA) << "  Enter <noun phrase> " << currentA << endl; 
  }

  adjectvphrase();
  //if Noun
  if (nextToken == NOUN) 
  {
    output("NOUN"); 
    lex();
  }
  //no Noun throw error
  else  
  {
    throw "<noun phrase> did not have a noun."; 
  }

  //this displayes all the messages (have represented the spaces with each of the if statment)
  if (currentA == 1)
  {
    cout << space(currentA) << " Exit <noun phrase> " << currentA << endl; 
  }

  if (currentA == 2)
  {
    cout << space(currentA) << "  Exit <noun phrase> " << currentA << endl;
  } 
}

 //*****************************************************************************************************************************************************************************************

 // For Verb
void verbphrase()
{
  int current_Vcount = Vcount++; //local incriment variable
  //if no verbphrase
  if (firstverbphrase() != true)  
    {
      throw "<verb phrase> did not start with a verb or an adverb."; 
    }


  //this all diplayes all error the messages (have represented the spaces with each of the if statment)

  if (current_Vcount == 1)
  {
    cout << space(current_Vcount) << " Enter <verb phrase> " << current_Vcount << endl; 
  }

  if (current_Vcount == 2)
  {
    cout << space(current_Vcount) << "  Enter <verb phrase> " << current_Vcount << endl; 
  }

  if (current_Vcount == 3)
  {
    cout << space(current_Vcount) << "   Enter <verb phrase> " << current_Vcount << endl; 
  }

  if (current_Vcount == 4)
  {
    cout << space(current_Vcount) << "    Enter <verb phrase> " << current_Vcount << endl; 
  }

  if (current_Vcount == 5)
  {
    cout << space(current_Vcount) << "     Enter <verb phrase> " << current_Vcount << endl; 
  }
  

  if (nextToken == VERB) //if verb
  {
    output("VERB"); 
    lex();
  }

  else if (nextToken == ADVERB) //if adverb
  {
    output("ADVERB"); 
    lex();
    verbphrase();
  }
  
  // this all diplayes the messages (we have represented the spaces with each of the if statment)
  if (current_Vcount == 1)
  {
    cout << space(current_Vcount) << " Exit <verb phrase> " << current_Vcount << endl; //display message
  }

  if (current_Vcount == 2)
  {
    cout << space(current_Vcount) << "  Exit <verb phrase> " << current_Vcount << endl; //display message
  }

  if (current_Vcount == 3)
  {
    cout << space(current_Vcount) << "   Exit <verb phrase> " << current_Vcount << endl; //display message
  }

  if (current_Vcount == 4)
  {
    cout << space(current_Vcount) << "    Exit <verb phrase> " << current_Vcount << endl; //display message
  }

  if (current_Vcount == 5){
    cout << space(current_Vcount) << "     Exit <verb phrase> " << current_Vcount << endl; //display message
  }
}
 

