/******************************************************************* 
 Name: Rojal Bishwokarma
Net-ID- rb2298

Parcer_tree_nodes implimentation

*******************************************************************/

#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"

using namespace std;

// This are all the classes that we are going to use
class ExprNode;
class blockNode;
class compoundNode;
class statementNode;
class assignmentNode;
class ifNode;
class whileNode;
class readNode;
class writeNode;
class expressionNode;
class simpleExpressionNode;
class TermNode;
class FactorNode;
//***************************************************************************************************************************************************************************************************


//ExprNode class iplimentation
class ExprNode
{
public:

    //This stores all the identity
    string *name = NULL;    
    //This house all the block adress
    blockNode *block = NULL; 

    ExprNode(string id, blockNode *blk);//constructor
    ~ExprNode();//distructor
};

//blockNode class implimentation
class blockNode
{
public:
    //copmpoundNode pointer
    compoundNode *comp_Stat = NULL; 

    blockNode(compoundNode *);//constructor 
    ~blockNode();//distructor
};



//implimentation of the statementNode class
class statementNode
{
public:
    //This helps to make the class abstract
    virtual void printTo(ostream &os) = 0; 
    //Distructor
    virtual ~statementNode();       
};

//implementation of the assignmentNode class
class assignmentNode : public statementNode
{
public:
    //This holds the identifyier
    string *name = NULL;    
    // This holds the adress of the expression           
    expressionNode *expression = NULL; 

    //constructor
    assignmentNode(string, expressionNode *);

    //This overides the superclass' virtual method
    void printTo(ostream &) override;

    //destructor
    ~assignmentNode() override;
};

//implimentation of the compound class 
class compoundNode : public statementNode
{
public:
    //This is the array of statments in a vector
    vector<statementNode *> statements; 

    //constructor 
    compoundNode();

    //This inserts the statment into the array
    void setStatementNode(statementNode *);

    //destructor 
    ~compoundNode() override;

    //helps print the content of the statment
    void printTo(ostream &) override;
};

//implementation of the ifNode class

class ifNode : public statementNode
{
public:
    //pointer fo expression
    expressionNode *expression = NULL;
    //pointer for the thenstatment
    statementNode *thenStatement = NULL;
    //pointer for the elseStatment
    statementNode *elseStatement = NULL; 

    //contructor 
    ifNode(expressionNode *, statementNode *);

    //if elseStatment exist
    void elsestatement(statementNode *);

    //print if condition met
    void printTo(ostream &) override;

    //Destructor
    ~ifNode() override;
};

//implementation of whileNode class
class whileNode : public statementNode
{
public:
    //pointer to expression
    expressionNode *expression = NULL; 
    //pointer to the loopBody
    statementNode *loopBody = NULL;    

    //constructor
    whileNode(expressionNode *, statementNode *);

    void printTo(ostream &) override;

    //Destructor 
    ~whileNode() override;
};

//implementation of the readNode class
class readNode : public statementNode
{
public:
    //pointer to the identifyier
    string *name = NULL; 

    //constructor 
    readNode(string);


    void printTo(ostream &) override;

    //destructor 
    ~readNode() override;
};

//implementation of the writeNode class
class writeNode : public statementNode
{
public:
    //pointer to identifyier of string literal
    string *name = NULL;
    //constructor
    writeNode(string);
    void printTo(ostream &) override;
    //destructor 
    ~writeNode() override;
};

//expressionNode class
class expressionNode
{
public:
    //pointer for simpleexpression
    simpleExpressionNode *simple_expression = NULL;       
    //pointer to expression_operator
    string *expression_operator = NULL;                   
    //pointer to next simpleexpression
    simpleExpressionNode *other_simple_expression = NULL; 
    expressionNode(simpleExpressionNode *);//intializing by passing simpleExpressionNode pointer
    void setExpressionOperator(int);//we are setting the expression_operator if it exists
    void setOtherSimpleExpression(simpleExpressionNode *);//setting another expression_operator if there exist another
    //destructor 
    ~expressionNode();
};

//simpleExpressionNode class
class simpleExpressionNode
{
public:
    //pointer for termNode
    TermNode *term = NULL;        
    //array of simpleexpression operator        
    vector<string *> simpleExpresionOperator; 
    //array for termNode
    vector<TermNode *> otherterm;             
    //setting it by passing the pointer to the TermNode
    simpleExpressionNode(TermNode *);
    //setting simpleExpression if it exist
    void setSimpleExpressionOperator(int);
    //setting another simpleExpressionOperator if it exist
    void setOtherTerm(TermNode *);
    //destructor 
    ~simpleExpressionNode();
};

//TermNode class
class TermNode
{
public:
    FactorNode *factor = NULL;     //holds pointer to FactorNode
    vector<string *> termOperator;    //holds array of termOperators
    vector<FactorNode *> otherFactor; //holds array of otherFactor

    //initializes with passed FactorNode pointer
    TermNode(FactorNode *);

    //set array of termoperator if there are any
    void setTermOperator(int);

    //set array of otherfactor if there are any
    void setOtherFactor(FactorNode *);

    //destructor for TermNode
    ~TermNode();
};

//FactorNode class
class FactorNode
{
public:
    string *factor = NULL;             //holds pointer to identifier/integer literal/floating-point literal
    float float_number = 0;                 //holds information about floating number
    string *factorOperator = NULL;     //holds pointer to factorOperator like NOT and -
    FactorNode *nextFactor = NULL;     //pointer to FactorNode
    expressionNode *expression = NULL; //pointer to expressionNode

    //initializes with string passed to the constructor
    FactorNode(string);

    //initializes with float number
    FactorNode(float);

    //initializes with operator and FactorNode* passed to it
    FactorNode(int, FactorNode *);

    //initializes with expressionNode* passed to it
    FactorNode(expressionNode *);

    //destructor of FactorNode
    ~FactorNode();
};

//operator "<<" overloading for every listed class
ostream &operator<<(ostream &os, statementNode &node);
ostream &operator<<(ostream &os, blockNode &node);
ostream &operator<<(ostream &os, ExprNode &node);
ostream &operator<<(ostream &os, ifNode &node);
ostream &operator<<(ostream &os, compoundNode &node);
ostream &operator<<(ostream &os, assignmentNode &node);
ostream &operator<<(ostream &os, whileNode &node);
ostream &operator<<(ostream &os, readNode &node);
ostream &operator<<(ostream &os, writeNode &node);
ostream &operator<<(ostream &os, expressionNode &node);
ostream &operator<<(ostream &os, simpleExpressionNode &node);
ostream &operator<<(ostream &os, TermNode &node);
ostream &operator<<(ostream &os, FactorNode &node);

#endif
