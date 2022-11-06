//*****************************************************************************
// purpose: Project Part 3 (parser_tree_nodes.h)
// version: Spring 2021
// Name: Rojal Bishwokarma
// Net-ID- rb2298@msstate.edu
//*****************************************************************************


#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"
#include <map>

using namespace std;
extern map<string, int> symbolTable;
// forward declarations of classes and functions
//
class programNode;
class blockNode;
class statementNode;
class assignmentNode;
class compoundNode;
class readNode;
class writeNode;
class ifNode;
class whileNode;
class expressionNode;
class nestedExprNode;
class simpleExpressionNode;
class termNode;
class factorNode;
class intLitNode;
class floatLitNode;
class identNode;
class nestedFactorNode;

//*########################################################################################################################################################*//

//Implementation of all the classes and the operator overloading and the distructor

class factorNode
{
public:
    virtual void printTo(ostream &os) = 0;
    virtual ~factorNode() {}
    virtual int interpret() = 0;
};
ostream &operator<<(ostream &os, factorNode &node)
{
    node.printTo(os);
    os << " )";
    return os;
}

//------------------------------------------------------------------------------------------------------------------------

class intLitNode : public factorNode
{
public:
    int intLiteral = 0;

    intLitNode(int value)
    {
        intLiteral = value;
    }

    void printTo(ostream &os)
    {
        os << "factor( " << intLiteral;
    }
    ~intLitNode();
    int interpret();
};

intLitNode::~intLitNode()
{
    cout << "Deleting a factorNode" << endl;
}

int intLitNode::interpret()
{
    return intLiteral;
}

//---------------------------------------------------------------------------------------------------------------------

class floatLitNode : public factorNode
{
public:
    float floatLiteral = 0.0;

    floatLitNode(float value)
    {
        floatLiteral = value;
    }

    void printTo(ostream &os)
    {
        os << "factor( " << floatLiteral;
    }
    ~floatLitNode();
    int interpret();
};

floatLitNode::~floatLitNode()
{
    cout << "Deleting a factorNode" << endl;
}

int floatLitNode::interpret()
{
    return floatLiteral;
}

//-------------------------------------------------------------------------------------------------------------------------------------------

class identNode : public factorNode
{
public:
    string *id = NULL;

    identNode(string name)
    {
        id = new string(name);
    }

    void printTo(ostream &os)
    {
        os << "factor( " << *id;
    }
    ~identNode();
    int interpret();
};

identNode::~identNode()
{
    cout << "Deleting a factorNode" << endl;
    delete id;
    id = NULL;
}

int identNode::interpret()
{
    return symbolTable[*id];
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

class nestedFactorNode : public factorNode
{
public:
    int operand = 0;
    factorNode *factorPtr = NULL;

    nestedFactorNode(int op, factorNode *fa)
    {
        this->operand = op;
        factorPtr = fa;
    }
    void printTo(ostream &os)
    {
        os << "factor( ";
        if (operand == TOK_NOT)
            os << "NOT ";
        else
            os << "- ";

        os << *factorPtr;
    }
    ~nestedFactorNode();
    int interpret();
};

nestedFactorNode::~nestedFactorNode()
{
    cout << "Deleting a factorNode" << endl;

    delete factorPtr;
    factorPtr = NULL;
}

int nestedFactorNode::interpret()
{
    if (operand == TOK_NOT)
        return !factorPtr->interpret();
    else
        return -1 * factorPtr->interpret();
}

//------------------------------------------------------------------------------------------------------------------------------------------------

class termNode
{
public:
    factorNode *factorPtr = NULL;

    termNode(factorNode *pFact)
    {
        factorPtr = pFact;
    }
    vector<int> restFactorOps;
    vector<factorNode *> restFactors;
    ~termNode();
    int interpret();
};

ostream &operator<<(ostream &os, termNode &node)
{
    os << "term( ";
    os << *(node.factorPtr);

    int length = node.restFactorOps.size();
    for (int i = 0; i < length; ++i)
    {
        int op = node.restFactorOps[i];
        if (op == TOK_MULTIPLY)
            os << " * ";
        else if (op == TOK_DIVIDE)
            os << " / ";
        else
            os << " AND ";
        os << *(node.restFactors[i]);
    }

    os << " )";
    return os;
}

termNode::~termNode()
{
    cout << "Deleting a termNode" << endl;
    delete factorPtr;
    factorPtr = NULL;

    int length = restFactorOps.size();
    for (int i = 0; i < length; ++i)
    {
        delete restFactors[i];
        restFactors[i] = NULL;
    }
}

int termNode::interpret()
{
    int result = 0;
    result = factorPtr->interpret();
    int length = restFactorOps.size();
    for (int i = 0; i < length; ++i)
    {
        int opCode = restFactorOps[i];
        if (opCode == TOK_MULTIPLY)
            result *= restFactors[i]->interpret();
        else if (opCode == TOK_DIVIDE)
            result /= restFactors[i]->interpret();
        else if (opCode == TOK_AND)
            result = result && restFactors[i]->interpret();
    }
    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

class simpleExpressionNode
{
public:
    termNode *termPtr = NULL;

    simpleExpressionNode(termNode *pTerm)
    {
        termPtr = pTerm;
    }

    vector<int> restTermOps;
    vector<termNode *> restTerms;
    ~simpleExpressionNode();
    int interpret();
};

ostream &operator<<(ostream &os, simpleExpressionNode &node)
{
    os << "simple_expression( ";
    os << *(node.termPtr);

    int length = node.restTermOps.size();
    for (int i = 0; i < length; ++i)
    {
        int op = node.restTermOps[i];
        if (op == TOK_PLUS)
            os << " + ";
        else if (op == TOK_MINUS)
            os << " - ";
        else
            os << " 0R ";
        os << *(node.restTerms[i]);
    }
    os << " )";
    return os;
}

simpleExpressionNode::~simpleExpressionNode()
{
    cout << "Deleting a simpleExpressionNode" << endl;
    delete termPtr;
    termPtr = NULL;

    int length = restTermOps.size();
    for (int i = 0; i < length; ++i)
    {
        delete restTerms[i];
        restTerms[i] = NULL;
    }
}

int simpleExpressionNode::interpret()
{
    int result = 0;
    result = termPtr->interpret();
    int length = restTermOps.size();
    for (int i = 0; i < length; ++i)
    {
        int opCode = restTermOps[i];
        if (opCode == TOK_PLUS)
            result += restTerms[i]->interpret();
        else if (opCode == TOK_MINUS)
            result -= restTerms[i]->interpret();
        else if (opCode == TOK_OR)
            result = result || restTerms[i]->interpret();
    }
    return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

class expressionNode
{
public:
    simpleExpressionNode *simpleExpression1Ptr = NULL;
    simpleExpressionNode *simpleExpression2Ptr = NULL;
    int operand;

    expressionNode(simpleExpressionNode *pSimp1)
    {
        simpleExpression1Ptr = pSimp1;
    }

    expressionNode(simpleExpressionNode *pSimp1, int opCode, simpleExpressionNode *pSimp2)
    {
        simpleExpression1Ptr = pSimp1;
        operand = opCode;
        simpleExpression2Ptr = pSimp2;
    }
    ~expressionNode();
    int interpret();
};

ostream &operator<<(ostream &os, expressionNode &node)
{
    os << *(node.simpleExpression1Ptr);

    if (node.operand == TOK_EQUALTO)
        os << " = ";
    else if (node.operand == TOK_LESSTHAN)
        os << " < ";
    else if (node.operand == TOK_GREATERTHAN)
        os << " > ";
    else if (node.operand == TOK_NOTEQUALTO)
        os << " <> ";

    if (node.simpleExpression2Ptr != NULL)
        os << *(node.simpleExpression2Ptr);
    return os;
}

expressionNode::~expressionNode()
{
    cout << "Deleting an expressionNode" << endl;
    delete simpleExpression1Ptr;
    simpleExpression1Ptr = NULL;
    delete simpleExpression2Ptr;
    simpleExpression2Ptr = NULL;
}

int expressionNode::interpret()
{
    int result;
    result = simpleExpression1Ptr->interpret();

    if (operand == TOK_EQUALTO)
    {
        if (result == simpleExpression2Ptr->interpret())
            result = 1;
        else
            result = 0;
    }
    else if (operand == TOK_LESSTHAN)
    {
        if (result < simpleExpression2Ptr->interpret())
        {
            result = 1;
        }
        else
            result = 0;
    }
    else if (operand == TOK_GREATERTHAN)
    {
        if (result > simpleExpression2Ptr->interpret())
            result = 1;
        else
            result = 0;
    }
    else if (operand == TOK_NOTEQUALTO)
    {
        if (result != simpleExpression2Ptr->interpret())
            result = 1;
        else
            result = 0;
    }
    return result;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

class nestedExprNode : public factorNode
{
public:
    expressionNode *expressionPtr = NULL;

    nestedExprNode(expressionNode *ex)
    {
        expressionPtr = ex;
    }
    void printTo(ostream &os)
    {
        os << "nested_expression( expression( " << *expressionPtr;
        os << " )";
    }
    ~nestedExprNode();
    int interpret();
};

nestedExprNode::~nestedExprNode()
{
    cout << "Deleting a factorNode" << endl;

    delete expressionPtr;
    expressionPtr = NULL;
}

int nestedExprNode::interpret()
{
    return expressionPtr->interpret();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

class statementNode
{
public:
    virtual void printTo(ostream &os) = 0;
    virtual ~statementNode() {}
    virtual int interpret() = 0;
};

ostream &operator<<(ostream &os, statementNode &node)
{
    node.printTo(os);
    return os;
}

class assignmentNode : public statementNode
{
public:
    string *name = NULL;
    expressionNode *expressionPtr = NULL;

    assignmentNode(string id, expressionNode *expr)
    {
        name = new string(id);
        expressionPtr = expr;
    }

    void printTo(ostream &os)
    {
        os << "Assignment " << *name << " := expression( ";
        os << *expressionPtr << " )" << endl;
    }
    ~assignmentNode();
    int interpret();
};

//--------------------------------------------------------------------------------------------------------------------------------------------------

assignmentNode::~assignmentNode()
{
    cout << "Deleting an assignmentNode" << endl;
    delete name;
    name = NULL;
    delete expressionPtr;
    expressionPtr = NULL;
}
int assignmentNode::interpret()
{
    return symbolTable[*name] = expressionPtr->interpret();
}

class readNode : public statementNode
{
public:
    string *name = NULL;

    readNode(string id)
    {
        this->name = new string(id);
    }
    void printTo(ostream &os)
    {
        os << "Read Value " << *name << endl;
    }
    ~readNode();
    int interpret();
};

readNode::~readNode()
{
    cout << "Deleting a readNode" << endl;
    delete name;
    name = NULL;
}

int readNode::interpret()
{
    int inputNumber;
    cin >> inputNumber;
    symbolTable[*name] = inputNumber;
    return inputNumber;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

class writeNode : public statementNode
{
public:
    string *name = NULL;
    int tokenNumber = 0;

    writeNode(string id, int tokenNum)
    {
        name = new string(id);
        tokenNumber = tokenNum;
    }
    void printTo(ostream &os)
    {
        if (tokenNumber == TOK_STRINGLIT)
            os << "Write String " << *name << endl;
        else
            os << "Write Value " << *name << endl;
    }
    ~writeNode();
    int interpret();
};

writeNode::~writeNode()
{
    cout << "Deleting a writeNode" << endl;
    delete name;
    name = NULL;
}

int writeNode::interpret()
{
    if (this->tokenNumber == TOK_IDENT)
    {
        cout << symbolTable.at(*name) << endl;
    }
    else
    {
        string consoleOut = *name;
        consoleOut.erase(consoleOut.begin());
        consoleOut.pop_back();
        cout << consoleOut << endl;
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

class ifNode : public statementNode
{
public:
    expressionNode *expressionPtr = NULL;
    statementNode *thenStatementPtr = NULL;
    statementNode *elseStatementPtr = NULL;

    ifNode(expressionNode *expr, statementNode *thenState)
    {
        expressionPtr = expr;
        thenStatementPtr = thenState;
    }
    ifNode(expressionNode *expr, statementNode *thenState, statementNode *elseState)
    {
        expressionPtr = expr;
        thenStatementPtr = thenState;
        elseStatementPtr = elseState;
    }
    void printTo(ostream &os)
    {
        os << "If expression( ";
        os << *expressionPtr << " )" << endl;

        os << "%%%%%%%% True Statement %%%%%%%%" << endl;
        os << *thenStatementPtr;
        os << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";

        if (elseStatementPtr != NULL)
        {
            os << "%%%%%%%% False Statement %%%%%%%%" << endl;
            os << *elseStatementPtr;
            os << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
        }
    }
    ~ifNode();
    int interpret();
};

ifNode::~ifNode()
{
    cout << "Deleting an ifNode" << endl;
    delete expressionPtr;
    expressionPtr = NULL;
    delete thenStatementPtr;
    thenStatementPtr = NULL;
    if (elseStatementPtr != NULL)
    {
        delete elseStatementPtr;
        elseStatementPtr = NULL;
    }
}
int ifNode::interpret()
{
    int result = expressionPtr->interpret();
    if (result != 0)
        return thenStatementPtr->interpret();
    if (elseStatementPtr != NULL)
        return elseStatementPtr->interpret();
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------

class whileNode : public statementNode
{
public:
    expressionNode *expressionPtr = NULL;
    statementNode *loopBody = NULL;

    whileNode(expressionNode *expr, statementNode *loopB)
    {
        expressionPtr = expr;
        loopBody = loopB;
    }
    void printTo(ostream &os)
    {
        os << "While expression( ";
        os << *expressionPtr << " )" << endl;

        os << "%%%%%%%% Loop Body %%%%%%%%" << endl;
        os << *loopBody;

        os << "%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    }
    ~whileNode();
    int interpret();
};

whileNode::~whileNode()
{
    cout << "Deleting a whileNode" << endl;
    delete expressionPtr;
    expressionPtr = NULL;
    delete loopBody;
    loopBody = NULL;
}

int whileNode::interpret()
{
    while (expressionPtr->interpret())
    {
        loopBody->interpret();
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

class compoundNode : public statementNode
{
public:
    statementNode *statementPtr = NULL;

    compoundNode(statementNode *mystate)
    {
        statementPtr = mystate;
    }
    vector<statementNode *> restStatements;
    void printTo(ostream &os)
    {
        os << "Begin Compound Statement" << endl;
        os << *statementPtr;
        int length = restStatements.size();
        for (int i = 0; i < length; ++i)
        {
            statementNode *sts = restStatements[i];
            os << *sts;
        }
        os << "End Compound Statement" << endl;
    }
    ~compoundNode();
    int interpret();
};

ostream &operator<<(ostream &os, compoundNode &node)
{
    node.printTo(os);
    return os;
}

compoundNode::~compoundNode()
{
    cout << "Deleting a compoundNode" << endl;
    delete statementPtr;
    statementPtr = NULL;
    int length = restStatements.size();
    for (int i = 0; i < length; ++i)
    {
        delete restStatements[i];
        restStatements[i] = NULL;
    }
}

int compoundNode::interpret()
{
    statementPtr->interpret();
    int length = restStatements.size();
    for (int i = 0; i < length; ++i)
    {
        restStatements[i]->interpret();
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------

class blockNode
{
public:
    compoundNode *compoundStatement = NULL;

    blockNode(compoundNode *compoundPtr)
    {
        this->compoundStatement = compoundPtr;
    }
    ~blockNode();
    int interpret();
};

ostream &operator<<(ostream &os, blockNode &node)
{
    os << *(node.compoundStatement);
    return os;
}

blockNode::~blockNode()
{
    cout << "Deleting a blockNode" << endl;
    delete compoundStatement;
    compoundStatement = NULL;
}

int blockNode::interpret()
{
    return compoundStatement->interpret();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

class programNode
{
public:
    string *name = NULL;
    blockNode *block = NULL;

    programNode(string id, blockNode *blk)
    {
        name = new string(id);
        block = blk;
    }
    ~programNode();
    int interpret();
};

ostream &operator<<(ostream &os, programNode &node)
{
    os << "Program Name " << *(node.name) << endl;
    os << *(node.block) << endl;
    return os;
}

programNode::~programNode()
{
    cout << "Deleting a programNode" << endl;
    delete name;
    name = NULL;
    delete block;
    block = NULL;
}

int programNode::interpret()
{
    return block->interpret();
}

//######################################################################################################################################################//

//All the operator overload functions:
ostream &operator<<(ostream &os, programNode &node);
ostream &operator<<(ostream &os, blockNode &node);
ostream &operator<<(ostream &os, statementNode &node);
ostream &operator<<(ostream &os, compoundNode &node);
ostream &operator<<(ostream &os, expressionNode &node);
ostream &operator<<(ostream &os, simpleExpressionNode &node);
ostream &operator<<(ostream &os, termNode &node);
ostream &operator<<(ostream &os, factorNode &node);

//########################################################################################################################################################//
/*
This will return string representing integer token value for example 2000 will be " + " 
and useful for printing math and logical operators.
*/
string token_to_string(int Token1)
{
    if (Token1 == TOK_PLUS)
    {
        return " + ";
    }
    else if (Token1 == TOK_MINUS)
    {
        return " - ";
    }
    else if (Token1 == TOK_MULTIPLY)
    {
        return " * ";
    }
    else if (Token1 == TOK_DIVIDE)
    {
        return " / ";
    }
    else if (Token1 == TOK_ASSIGN)
    {
        return " := ";
    }
    else if (Token1 == TOK_EQUALTO)
    {
        return " = ";
    }
    else if (Token1 == TOK_LESSTHAN)
    {
        return " < ";
    }
    else if (Token1 == TOK_GREATERTHAN)
    {
        return " > ";
    }
    else if (Token1 == TOK_NOTEQUALTO)
    {
        return " <> ";
    }
    else if (Token1 == TOK_MOD)
    {
        return " MOD ";
    }
    else if (Token1 == TOK_NOT)
    {
        return " NOT ";
    }
    else if (Token1 == TOK_OR)
    {
        return " OR ";
    }
    else if (Token1 == TOK_OR)
    {
        return " OR ";
    }
    else if (Token1 == TOK_AND)
    {
        return " AND ";
    }
    else
    {
        return " UNKNOWN TOKEN";
    }
}

#endif