/******************************************************************* 
Name: Rojal Bishwokarma
Net-ID- rb2298
Production header file containing functions 


*******************************************************************/
#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H
using namespace std;
#include <cstring>
#include <stdexcept>

extern int nextToken;
extern int level;
extern set<string> symbolTable;

//**********************************************************************************************************************************************************
//This are all the function declerations.
ExprNode *program();
blockNode *block();
statementNode *statement();
compoundNode *compound_statement();
expressionNode *expression();
simpleExpressionNode *simple_expression();
assignmentNode *assignment_statement();
TermNode *term();
FactorNode *factor();
ifNode *if_statement();
whileNode *while_statement();
readNode *read_statement();
writeNode *write_statement();
bool FTOK_IDENT();
bool FTOK_OPENPAREN();


//***********************************************************************************************************************************************************



extern "C"
{
	// Instantiate global variables used by flex
	extern char *yytext; // text of current lexeme
	extern int yylex();	 // the generated lexical analyzer
}

//This function handels all the indent 
string spaces()
{
	string str(level * 4, ' ');
	return str;
}

//This handels all the output and spacing
void output_lexeme()
{
	cout << spaces() << "    -->found " << yytext << endl;
}

//This handels the end of files
void getToken()
{
	nextToken = yylex();
	if (nextToken == TOK_EOF)
	{
		yytext[0] = 'E';
		yytext[1] = 'O';
		yytext[2] = 'F';
		yytext[3] = 0;
	}
}

//******************************************************************************************************************************************************

//Function for the program
ExprNode *program()
{
	++level;//incrimenting the counter as we go
	cout << spaces() << "enter <program>" << endl;
	ExprNode *program = NULL;
	output_lexeme();
	getToken();
	output_lexeme();//Prints if the rules are met
	if (FTOK_IDENT())
	{
		string name = yytext;
		getToken();
		output_lexeme();
		if (nextToken == TOK_SEMICOLON)
		{
			getToken();
			program = new ExprNode(name, block());
		}
		else
			throw "14: ';' expected";
	}
	else
		throw "2: identifier expected";
	cout << spaces() << "exit <program>" << endl;
	--level;//decrimenting the counter as we go
	return program;
}

//Function for the block
blockNode *block()
{

	++level;//incrimentar
	cout << spaces() << "enter <block>" << endl;

	blockNode *block = NULL;
	// now we parce the tokens to match the hence forward
	if (nextToken == TOK_VAR)
	{
		output_lexeme();
		getToken();
		output_lexeme();// out put the lexime throught the program
		if (FTOK_IDENT())
		{
			while (FTOK_IDENT())
			{
				if (symbolTable.find(yytext) == symbolTable.end())
					symbolTable.insert(yytext);
				else
					throw "101: identifier declared twice";
				getToken();
				output_lexeme();
				if (nextToken == TOK_COLON)
				{
					getToken();
					output_lexeme();
					if (nextToken == TOK_INTEGER || nextToken == TOK_REAL)
					{
						getToken();

						output_lexeme();
						if (nextToken == TOK_SEMICOLON)
						{
							std::cout << std::endl;
							getToken();
							if (nextToken != TOK_BEGIN)
							{
								output_lexeme();
							}
							if (nextToken == TOK_BEGIN)
							{
								block = new blockNode(compound_statement());
								break;
							}
							else if (!FTOK_IDENT() && nextToken != TOK_BEGIN)
							{
								throw "17: 'BEGIN' expected";
							}
						}
						else
							throw "14: ';' expected";
					}
					else
						throw "10: error in type";
				}
				else
					throw "5: ':' expected";
			}
		}
		else
		{
			throw "2: identifier expected";
		}
	}
	else
	{

		block = new blockNode(compound_statement());
	}

	cout << spaces() << "exit <block>" << endl;
	--level;//decrement
	return block;
}



//Function for compound statment
compoundNode *compound_statement()
{
	++level;//incrimentor
	cout << spaces() << "enter <compound_statement>" << endl;
	compoundNode *compound = new compoundNode();
	output_lexeme();
	if (nextToken == TOK_BEGIN)
	{
		getToken();
		compound->setStatementNode(statement());
		output_lexeme();
		if (nextToken == TOK_SEMICOLON)
		{
			while (nextToken == TOK_SEMICOLON)
			{
				getToken();
				compound->setStatementNode(statement());
				output_lexeme();
				if (nextToken != TOK_SEMICOLON && nextToken != TOK_END)
				{
					throw "13: 'END' expected";
				}
				else if (nextToken == TOK_END)
				{
					getToken();
					break;
				}
			}
		}
		else if (nextToken == TOK_END)
		{
			getToken();
		}
		else if (nextToken != TOK_END)
		{
			throw "13: 'END' expected";
		}
	}
	else
		throw "18: error in declaration part OR 17: 'BEGIN' expected";

	cout << spaces() << "exit <compound_statement>" << endl;
	--level;
	return compound;
}

//Function for statment
statementNode* statement()
{
	++level;
	cout << spaces() << "enter <statement>" << endl;

	statementNode* state = NULL;
	if (FTOK_IDENT())
	{
		state = (assignment_statement());
	}
	else if (nextToken == TOK_BEGIN)
	{
		state = (compound_statement());
	}
	else if (nextToken == TOK_IF)
	{
		state = (if_statement());
	}
	else if (nextToken == TOK_WHILE)
	{
		state = (while_statement());
	}
	else if (nextToken == TOK_READ)
	{
		state = (read_statement());
	}
	else if (nextToken == TOK_WRITE)
	{
		state = (write_statement());
	}
	else
	{
		output_lexeme();
		throw "900: illegal type of statement";
	}
	cout << spaces() << "exit <statement>" << endl;
	--level;
	return state;
}

//Function for Expression
expressionNode *expression()
{
	++level;
	cout << spaces() << "enter <expression>" << endl;
	expressionNode *expression = NULL;
	if (nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || FTOK_IDENT() || FTOK_OPENPAREN() || nextToken == TOK_NOT || nextToken == TOK_MINUS)
	{
		expression = new expressionNode(simple_expression());
	}
	else
	{
		output_lexeme();
		throw "144: illegal type of expression";
	}

	if (nextToken == TOK_EQUALTO || nextToken == TOK_LESSTHAN || nextToken == TOK_GREATERTHAN || nextToken == TOK_NOTEQUALTO)
	{
		expression->setExpressionOperator(nextToken);
		output_lexeme();
		getToken();
		expression->setOtherSimpleExpression(simple_expression());
	}
	cout << spaces() << "exit <expression>" << endl;
	--level;
	return expression;
}


//Function for simple_expression
simpleExpressionNode *simple_expression()
{
	++level;
	cout << spaces() << "enter <simple expression>" << endl;
	simpleExpressionNode *simple_exp = NULL;
	if (nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || FTOK_IDENT() || FTOK_OPENPAREN() || nextToken == TOK_NOT || nextToken == TOK_MINUS)
	{
		simple_exp = new simpleExpressionNode(term());
	}
	else
	{
		output_lexeme();
		throw "901: illegal type of simple expression";
	}

	while (nextToken == TOK_PLUS || nextToken == TOK_MINUS || nextToken == TOK_OR)
	{
		simple_exp->setSimpleExpressionOperator(nextToken);
		output_lexeme();
		getToken();
		simple_exp->setOtherTerm(term());
	}

	cout << spaces() << "exit <simple expression>" << endl;
	--level;
	return simple_exp;
}

//Function for term
TermNode *term()
{
	++level;
	cout << spaces() << "enter <term>" << endl;
	TermNode *ter = NULL;
	if (nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || FTOK_IDENT() || FTOK_OPENPAREN() || nextToken == TOK_NOT || nextToken == TOK_MINUS)
	{
		ter = new TermNode(factor());
	}
	else
	{
		output_lexeme();
		throw "902: illegal type of term";
	}

	while (nextToken == TOK_MULTIPLY || nextToken == TOK_DIVIDE || nextToken == TOK_AND)
	{
		ter->setTermOperator(nextToken);
		output_lexeme();
		getToken();

		ter->setOtherFactor(factor());
	}
	cout << spaces() << "exit <term>" << endl;
	--level;
	return ter;
}

//Function for the factor
FactorNode *factor()
{
	++level;//incrimenting the counter
	cout << spaces() << "enter <factor>" << endl;//Indent and Print
	FactorNode *fact = NULL;
	//checking for type of factor Token
	if (FTOK_IDENT() && symbolTable.find(yytext) == symbolTable.end())
	{
		std::string error_message = yytext + std::string(", error type 104: identifier not declared");
		throw (const char *)error_message.c_str();
	}
	output_lexeme();
	if (nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || FTOK_IDENT())
	{
		if (nextToken == TOK_FLOATLIT){
			fact = new FactorNode((stof(yytext)));
		}
		else
		fact = new FactorNode(yytext);
		getToken();
	}
	else if (FTOK_OPENPAREN())
	{
		getToken();

		fact = new FactorNode(expression());

		output_lexeme();
		if (nextToken = TOK_CLOSEPAREN)
		{

			getToken();
		}
		else
		{
			throw "4: ')' expected";
		}
	}
	else if (nextToken == TOK_NOT || nextToken == TOK_MINUS)
	{
		int nextToken = nextToken;
		getToken();
		fact = new FactorNode(nextToken, factor());
	}
	else
	{
		throw "903: illegal type of factor";
	}

	cout << spaces() << "exit <factor>" << endl;
	--level;
	return fact;
}

//Function for assignment_statment
assignmentNode *assignment_statement()
{
	++level;
	cout << spaces() << "enter <assignment>" << endl;
	assignmentNode *assignment = NULL;
	string id = yytext;
	if (symbolTable.find(yytext) == symbolTable.end())
	{
		std::string error_message = yytext + std::string(", error type 104: identifier not declared");
		throw (const char *)error_message.c_str();
	}
	output_lexeme();
	
	getToken();
	output_lexeme();
	if (nextToken == TOK_ASSIGN)
	{
		getToken();
		assignment = new assignmentNode(id, expression());
	}
	else
	{
		throw "51: ':=' expected";
	}
	cout << spaces() << "exit <assignment>" << endl;
	--level;
	return assignment;
}

//Function for if statment
ifNode *if_statement()
{
	++level;
	cout << spaces() << "enter <if statement>" << endl;
	ifNode *if_node = NULL;
	expressionNode *exp = NULL;
	output_lexeme();
	getToken();
	exp = expression();
	output_lexeme();
	if (nextToken == TOK_THEN)
	{
		getToken();

		if_node = new ifNode(exp, statement());

		if (nextToken == TOK_ELSE)
		{
			output_lexeme();
			getToken();
			if_node->elsestatement(statement());
		}
	}
	else
	{
		throw "52: 'THEN' expected";
	}

	cout << spaces() << "exit <if statement>" << endl;
	--level;
	return if_node;
}

//Function for while statment
whileNode *while_statement()
{
	++level;
	cout << spaces() << "enter <while statement>" << endl;
	whileNode *while_node = NULL;
	output_lexeme();
	getToken();
	while_node = new whileNode(expression(), statement());
	cout << spaces() << "exit <while statement>" << endl;
	--level;
	return while_node;
}

//Function for read_Statment
readNode *read_statement()
{
	++level;
	cout << spaces() << "enter <read>" << endl;
	readNode *read_node = NULL;
	output_lexeme();
	getToken();
	output_lexeme();
	if (FTOK_OPENPAREN())
	{
		getToken();
		if (FTOK_IDENT() && symbolTable.find(yytext) == symbolTable.end())
		{
			std::string error_message = yytext + std::string(", error type 104: identifier not declared");
			throw (const char *)error_message.c_str(); //This throws throw "104: identifier not declared";
		}
		output_lexeme();
		if (FTOK_IDENT())
		{
			read_node = new readNode(yytext);
			getToken();
			output_lexeme();
			if (nextToken == TOK_CLOSEPAREN)
			{
				getToken();
			}
			else
				throw "4: ')' expected";
		}
		else
			throw "2: identifier expected";
	}
	else
		throw "9: '(' expected";

	cout << spaces() << "exit <read>" << endl;
	--level;
	return read_node;
}


//Function for write_statment
writeNode *write_statement()
{
	++level;
	cout << spaces() << "enter <write>" << endl;

	writeNode *write_node = NULL;

	output_lexeme();

	getToken();
	output_lexeme();
	if (FTOK_OPENPAREN())
	{
		getToken();
		
		if (FTOK_IDENT() && symbolTable.find(yytext) == symbolTable.end())
		{
			std::string error_message = yytext + std::string(", error type 104: identifier not declared");
			throw (const char *)error_message.c_str();
			//throw "106: identifier not declared";
		}
			
		output_lexeme();

		if (FTOK_IDENT() || nextToken == TOK_STRINGLIT)
		{

			

			write_node = new writeNode(yytext);

			getToken();
			output_lexeme();

			if (nextToken == TOK_CLOSEPAREN)
			{
				getToken();
			}
			else
				throw "4: ')' expected";
		}
		else
			throw "134: illegal type of operand(s)";
	}
	else
		throw "9: '(' expected";

	cout << spaces() << "exit <write>" << endl;
	--level;
	return write_node;
}
//*******************************************************************************************************************************************************

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
