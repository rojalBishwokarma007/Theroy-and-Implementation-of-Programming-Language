/*************************************************************************
 Name: Rojal Bishwokarma      net-ID_ rb2298

course: CSE 4714 - Theory and implimentation of programming language

Project 2: PARSER
***************************************************************************/




#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H
#include <iostream>

int inital_value = 0;
int nextToken; 
int level = 0; 
extern set<string> symbolTable;



extern "C"
{
	extern char* yytext;       // text of current lexeme
	extern int   yylex();      // the generated lexical analyzer
}


//***********************************************************************************************************************************************************************************


//Forward declarations of production parsing functions
void program();  
void block();  
void comp_stat(); 
void statement();  
void expression(); 
void simp_expr();   
void term();  
void factor(); 
// Forward declarations of functions that check whether the current token is
// in the first set of a production rule
bool first_of_program();
bool FTOK_IDENT();
bool FTOK_OPENPAREN();


//**************************************************************************************************************************************************************************************

// handels the spacing
inline void indent()
{
    for (int i = 0; i<level; i++)
        cout << ("    ");
}

//to handle outputs and spacing
void output()
{
    indent();
    cout << "-->found " << yytext << endl;
}

//this handels the end of the file 
int lexeme() 
{
  nextToken = yylex();
  if (nextToken == TOK_EOF)
  {
      yytext[0] = 'E';
      yytext[1] = 'O';
      yytext[2] = 'F';
      yytext[3] = 0;
  }
  return nextToken;
}

//*****************************************************************************************************************************************************************************************
//function for the program 
void program()
 { 
     if (!first_of_program()) // Throws error if the first is not a Program
     {
         throw "3: 'PROGRAM' expected";
     }
    indent();// calling the indent function for spacing happens throught the program
    cout << "enter <program>" << endl;
    ++level;//incrimenter
    output();
    lexeme();
    // now we parce the tokens to match the hence forward
    if (FTOK_IDENT())
    {
        output();// out put the lexime throught the program
        lexeme();
        if (nextToken == TOK_SEMICOLON)
        {
            output();
            block();
        }
        else 
        {
            throw "14: ';' expected";
        }
    }
    else 
    {
        throw "2: identifier expected";
    }
    --level; // decriments throught the program
    indent();
    cout << "exit <program>" << endl;
    
}

// This function handel the block's
void block()
{ 
    indent();
    cout  << "enter <block>" << endl;
    ++level;
    lexeme();
    if (nextToken == TOK_VAR)
    {
        output();
        lexeme();
        while (inital_value == 0){ 
            if (FTOK_IDENT())
            {
                if (symbolTable.count(yytext))
                {
                    throw "101: identifier declared twice";
                }
                output();
                // now we update the symboltable as we progress with token
                symbolTable.insert(yytext); 
                lexeme();
                if(nextToken == TOK_COLON)
                {
                    output();
                    lexeme();
                    if(nextToken == TOK_INTEGER || nextToken == TOK_REAL)
                    {
                        output();
                        lexeme();
                        if(nextToken == TOK_SEMICOLON)
                        {
                            output();
                            lexeme();
                            cout<<'\n'; // line brake 
                            if(FTOK_IDENT())
                            {
                                inital_value = 0;
                            }
                            else if (nextToken == TOK_BEGIN)
                            {
                                inital_value = 1;
                                // now we call the compound statment if Begin is true
                                comp_stat(); 
                            }
                            else 
                            {
                                throw "17: 'BEGIN' expected";
                            }
                        }
                        else 
                        {
                            throw "14: ';' expected";
                        }
                    }
                    else 
                    {
                        throw "10: error in type";
                    }
                }
                else 
                {
                    throw "5: ':' expected";
                }
            }
            else 
            {
                throw "2: identifier expected";
            }
        }    
    }
    else if (nextToken == TOK_BEGIN){
        comp_stat(); // calling the compound statment if TOK_BEGIN
    }
    else 
    {
        throw "18: error in declaration part OR 17: 'BEGIN' expected";
    }
    --level; 
    indent();
    cout << "exit <block>" << endl;
    
}

void comp_stat()
{ 
    indent();
    cout << "enter <compound_statement>" << endl;
    ++level; 
    output();
    lexeme();
    statement(); 
    // we run it at least once and loop until the condition is not true
    while (nextToken == TOK_SEMICOLON)
    {
        output();
        lexeme();
        statement();
    }  
    
    
    if (nextToken == TOK_END) //now if next Token is TOK_END
    {
        output();
        lexeme();
    } 
    else
    {
        throw "13: 'END' expected";
    }
    --level; 
    indent();
    cout<< "exit <compound_statement>" << endl;  
    
}

// This handels the statment when called
void statement()
{ 
    indent();
    cout<< "enter <statement>" << endl;
    ++level; 
    
    if (FTOK_IDENT())// now we check the if the nextToken is TOK_IDENT
    {
            indent();
            cout << "enter <assignment>" << endl;
            ++level;
            output();
            // we are checking if the simbol table if the identfyier is already declared or not
            if (!symbolTable.count(yytext)) 
            {
                throw "104: identifier not declared";
            }
            lexeme();
            if (nextToken == TOK_ASSIGN)
            {
                output();
                lexeme();
                expression();
                --level; 
                indent();
                cout<< "exit <assignment>" << endl;
                
            }
            else 
            {
                throw "51: ':=' expected";
            }
        }

    else if (nextToken == TOK_READ)
        {
            indent();
            cout << "enter <read>" << endl;
            ++level;
            output();
            lexeme();
            if (FTOK_OPENPAREN())
            {
                output();
                lexeme();
                if(FTOK_IDENT())
                {
                    output();
                    if (!symbolTable.count(yytext)) 
                    {
                        throw "104: identifier not declared";
                    }
                    lexeme();
                    if(nextToken == TOK_CLOSEPAREN)
                    {
                        output();
                        lexeme();
                    }
                    else 
                    {
                        throw "4: ')' expected";
                    }
                }
                else 
                {
                    throw "2: identifier expected";
                }
            }
            else 
            {
                throw "9: '(' expected";
            }
            --level;
            indent();
            cout<< "exit <read>" << endl;
            
        }
    else if (nextToken == TOK_IF)
        {
            indent();
            cout<< "enter <if statement>" << endl;
            ++level;
            output();
            lexeme();
            expression();
            if(nextToken == TOK_THEN)
            {
                output();
                lexeme();
                statement();
                // we get out of the statment if the condition is not met
                if(nextToken == TOK_ELSE)
                { 
                    output();
                    lexeme();
                    statement();
                }
            }
            else 
            {
                throw "52: 'THEN' expected";
            }
            --level;
            indent();
            cout << "exit <if statement>" << endl;
            
        }

    else if(nextToken == TOK_WHILE)
        {
            indent();
            cout << "enter <while statement>" << endl;
            ++level;
            output();
            lexeme();
            expression();
            statement();
            --level;
            indent();
            cout << "exit <while statement>" << endl;
            
        }
        
    else if(nextToken == TOK_WRITE)
        {
            indent();
            cout << "enter <write>" << endl;
            ++level;
            output();
            lexeme();
            if(FTOK_OPENPAREN())
            {
                output();
                lexeme();
                if(FTOK_IDENT())
                {
                    output();
                    if (!symbolTable.count(yytext))
                    {
                        throw "104: identifier not declared";
                    }
                    lexeme();
                }
                else if(nextToken == TOK_STRINGLIT)
                {
                    output();
                    lexeme();
                }
                else 
                {
                    throw "134: illegal type of operand(s)";
                }
                if(nextToken == TOK_CLOSEPAREN)
                {
                    output();
                    lexeme();
                }
                else 
                {
                    throw "4: ')' expected";
                }
            }   
            else 
            {
                throw "9: '(' expected";
            }
            --level;
            indent();
            cout << "exit <write>" << endl;
            
        }   
        
    
        
    else if (nextToken == TOK_BEGIN)
        {
            comp_stat();
        }

    else 
        {
            throw "900: illegal type of statement"; 
        }
        --level; 
        indent();
        cout<< "exit <statement>" << endl;
        
}


void expression()
{
    indent();
    cout << "enter <expression>" << endl;
    ++level;
    if( nextToken != TOK_FLOATLIT && !FTOK_IDENT() && nextToken != TOK_INTLIT  && nextToken != TOK_NOT && nextToken != TOK_MINUS &&  !FTOK_OPENPAREN())
    {
       throw "144: illegal type of expression";
    }
    simp_expr();// calling the simple_expression here simp_expr() function
    if (nextToken == TOK_EQUALTO || nextToken == TOK_LESSTHAN || nextToken == TOK_GREATERTHAN || nextToken == TOK_NOTEQUALTO)
    {
        output();
        lexeme();
        simp_expr();
    }
    --level; 
    indent();
    cout<< "exit <expression>" << endl;
    

}


// This handels the simple Expressions
void simp_expr()
{ 
    indent();
    cout<< "enter <simple expression>" << endl;
    ++level; 
    if(nextToken != TOK_INTLIT && nextToken != TOK_FLOATLIT && !FTOK_IDENT() &&  !FTOK_OPENPAREN() && nextToken != TOK_NOT && nextToken != TOK_MINUS)
    {
       throw "901: illegal type of simple expression";
    }
    term();// calling the term function
    while (nextToken == TOK_PLUS || nextToken == TOK_MINUS || nextToken == TOK_OR)
    {
        output();
        lexeme();
        term();  
    }
    --level; 
    indent();
    cout<< "exit <simple expression>" << endl;
    
}

// This handels all the term
void term()
{ 
    indent();
    cout << "enter <term>" << endl;
    ++level; 
    // we check each of the token if the rules are met or not
    if(nextToken != TOK_INTLIT && nextToken != TOK_FLOATLIT && !FTOK_IDENT() && !FTOK_OPENPAREN() && nextToken != TOK_NOT && nextToken != TOK_MINUS)
    {
       throw "902: illegal type of term";
    }
    factor();
    //Lop until the desired output is met
    while (nextToken == TOK_MULTIPLY || nextToken == TOK_DIVIDE || nextToken == TOK_AND)
    {
        output();
        lexeme();
        factor(); 
    }
    --level; 
    indent();
    cout<< "exit <term>" << endl;
    
}


//this function handels the factor
void factor()
{ 
    indent();
    cout << "enter <factor>" << endl;
    ++level;   
    if(nextToken == TOK_INTLIT) // Here we check different conditions are met or not
    {
        output();
        lexeme();
    }
    else if(nextToken == TOK_FLOATLIT)
    {
        output();
        lexeme();
    }
    else if(FTOK_IDENT())
    {
        if (!symbolTable.count(yytext)) 
        {
            throw "104: identifier not declared";
        }
        output();
        lexeme();
    }
    else if(FTOK_OPENPAREN())
    {
        output();
        lexeme();
        expression();//here experssion is called then we check for other conditions
        if (nextToken == TOK_CLOSEPAREN)
        {
            output();
            lexeme();
        }
        else 
        {
            throw "4: ')' expected";
        }
    }
    else if(nextToken == TOK_NOT)
    {
        output();
        lexeme();
        factor();
    }
    else if(nextToken == TOK_MINUS)
    {
        output();
        lexeme();
        factor();
    }
    else // if all the above condition is not met we throw an error
    {
        throw "903: illegal type of factor"; 
    }
    --level; 
    indent();
    cout << "exit <factor>" << endl; 
    
}



//*****************************************************************************

bool first_of_program(void) 
{
   return nextToken == TOK_PROGRAM;
}

bool FTOK_IDENT(void)
{
    return nextToken == TOK_IDENT;

}
bool FTOK_OPENPAREN(void)
{
    return nextToken == TOK_OPENPAREN;
}
#endif

