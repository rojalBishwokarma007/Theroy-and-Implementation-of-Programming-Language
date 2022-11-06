#include "parse_tree_nodes.h"

//This converts the operators to its corresponding string value
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

//********************************************************************************************************************************************************************************************

/*operator overloading to print content of ExprNode & blockNode & statementNode & compoundNode & assignmentNode & readNode & ifNode & writeNode & expressionNode
& simpleExpressionNode & TermNode & FactorNode & ExprNode & blockNode & compoundNode.......*/



//ExprNode
ostream &operator<<(ostream &OS, ExprNode &NODE)
{
    OS << "Program Name " << *(NODE.name) << endl;
    OS << *(NODE.block) << endl;
    return OS;
}

//blockNode
ostream &operator<<(ostream &OS, blockNode &NODE)
{
    OS << *(NODE.comp_Stat);
    return OS;
}

//statmentNOde 
ostream &operator<<(ostream &OS, statementNode &NODE)
{
    NODE.printTo(OS);
    return OS;
}

//compoundNode
ostream &operator<<(ostream &OS, compoundNode &NODE)
{
    NODE.printTo(OS);
    return OS;
}

//assignmentNode
ostream &operator<<(ostream &OS, assignmentNode &NODE)
{
    NODE.printTo(OS);
    return OS;
}

//readNode
ostream &operator<<(ostream &OS, readNode &NODE)
{
    NODE.printTo(OS);
    return OS;
}

//ifNode
ostream &operator<<(ostream &OS, ifNode &NODE)
{
    NODE.printTo(OS);
    return OS;
}

//writeNode
ostream &operator<<(ostream &OS, writeNode &NODE)
{
    NODE.printTo(OS);
    return OS;
}

//expressionNode
ostream &operator<<(ostream &OS, expressionNode &NODE)
{
    OS << "expression( " << *(NODE.simple_expression);

    //if there is expression operators print them
    if (NODE.expression_operator != NULL)
    {
        OS << *(NODE.expression_operator);
        OS << *(NODE.other_simple_expression);
    }
    OS << " )";
    return OS;
}

//simpleExpressionNode
ostream &operator<<(ostream &OS, simpleExpressionNode &NODE)
{
    OS << "simple_expression( " << *(NODE.term);

    //if there are simpleExpressionopertors and otherterms print them
    for (int a = 0; a < (NODE.simpleExpresionOperator).size() && NODE.simpleExpresionOperator[a] != NULL; a++)
    {
        OS << *NODE.simpleExpresionOperator[a];
        OS << *NODE.otherterm[a];
    }
    OS << " )";
    return OS;
}

//TermNode
ostream &operator<<(ostream &OS, TermNode &NODE)
{
    OS << "term( " << *(NODE.factor);

    //print termOperator and otherFactor if there are any
    for (int a = 0; a < (NODE.termOperator).size() && NODE.termOperator[a] != NULL; a++)
    {
        OS << *NODE.termOperator[a];
        OS << *NODE.otherFactor[a];
    }
    OS << " )";
    return OS;
}

//FactorNode
ostream &operator<<(ostream &OS, FactorNode &NODE)
{
    //if FactorNode has integer literal / floating point literal / identifer
    if (NODE.factor != NULL)
    {
        OS << "factor( ";
        OS << *(NODE.factor);
    }
    //if FactorNode has factor operator and factor
    else if (NODE.factorOperator != NULL)
    {
        OS << "factor( ";
        OS << *(NODE.factorOperator);
        OS << *(NODE.nextFactor);
    }

    //if FactorNode has expression
    else if(NODE.expression != NULL)
    {
        OS << "nested_expression( ";
        OS << *(NODE.expression);
    }
    else {
        OS << "factor( ";
        OS << NODE.float_number;
    }
    OS << " )";
    return OS;
}


//********************************************************************************************************************************************************************************************
//contructor of the all the nodes

//ExprNode
ExprNode::ExprNode(string identy, blockNode *block1)
{
    name = new string(identy);
    block = block1;
}

//blockNode
blockNode::blockNode(compoundNode *compoundstat1)
{
    comp_Stat = compoundstat1;
}

//compoundNode
compoundNode::compoundNode(){}

assignmentNode::assignmentNode(string identy, expressionNode *expresson1)
{

    name = new string(identy);
    expression = expresson1;
}
void assignmentNode::printTo(ostream &OS)
{
    OS << "Assignment " << *name << " := ";
    OS << *expression;
}

//ifNode
ifNode::ifNode(expressionNode *expresson1, statementNode *statmt1)
{

    expression = expresson1;
    thenStatement = statmt1;
}
void ifNode::elsestatement(statementNode *statmt1)
{
    elseStatement = statmt1;
}
void ifNode::printTo(ostream &OS)
{
    OS << "If " << *expression << endl;
    OS << "%%%%%%%% True Statement %%%%%%%%" << endl;
    OS << *thenStatement <<endl;
    OS << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";

    if (elseStatement != NULL)
	{
        OS << endl <<"%%%%%%%% False Statement %%%%%%%%" << endl;
		OS << *elseStatement <<endl;
		OS << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
	}
}


//WhileNode
whileNode::whileNode(expressionNode *expresson1, statementNode *lop)
{
    expression = expresson1;
    loopBody = lop;
}
void whileNode::printTo(ostream &OS)
{
    OS << "While " << *expression << endl;
    OS << "%%%%%%%% Loop Body %%%%%%%%" << endl;
    OS << *loopBody << endl;
    OS << "%%%%%%%%%%%%%%%%%%%%%%%%%%%";
}

//readNode
readNode::readNode(string identy)
{
    name = new string(identy);
}
void readNode::printTo(ostream &OS)
{
    OS << "Read Value " << *name;
}

//writeNode
writeNode::writeNode(string identy)
{
    name = new string(identy);
}
void writeNode::printTo(ostream &OS)
{
    //This prints different values depending upon the initial value
    if ((*name)[0] == '\'')
        OS << "Write String " << *name;
    else
        OS << "Write Value " << *name;
}

//ExpressionNode
expressionNode::expressionNode(simpleExpressionNode *simplexpression1)
{
    simple_expression = simplexpression1;
}
void expressionNode::setExpressionOperator(int Token1)
{   
    //converting Token1 to string before storing
    expression_operator = new string(token_to_string(Token1));
}
void expressionNode::setOtherSimpleExpression(simpleExpressionNode *simplexpression1)
{
    other_simple_expression = simplexpression1;
}


//SimpleExpressionNode
simpleExpressionNode::simpleExpressionNode(TermNode *term1)
{
    term = term1;
}
void simpleExpressionNode::setSimpleExpressionOperator(int Token1)
{   //converting operator to string before storing
    simpleExpresionOperator.push_back(new string(token_to_string(Token1)));
}
void simpleExpressionNode::setOtherTerm(TermNode *term1)
{
    otherterm.push_back(term1);
}


//TermNode
TermNode::TermNode(FactorNode *factor1)
{
    factor = factor1;
}
void TermNode::setTermOperator(int Token1)
{
    termOperator.push_back(new string(token_to_string(Token1)));
}
void TermNode::setOtherFactor(FactorNode *factor1)
{
    otherFactor.push_back(factor1);
}

//FactorNode
FactorNode::FactorNode(float float_num1){
    float_number = float_num1;
}
FactorNode::FactorNode(string identy)
{
    factor = new string(identy);
}
FactorNode::FactorNode(int Token1, FactorNode *factor)
{   //converting operator to string before storing
    if (Token1 == TOK_MINUS){
        factorOperator = new string("- ");
    }
    else
    factorOperator = new string(token_to_string(Token1));
    nextFactor = factor;
}
FactorNode::FactorNode(expressionNode *expresson1)
{
    expression = expresson1;
}





//********************************************************************************************************************************************************************************

//destructor for all the nodes

//block NODE
blockNode::~blockNode()
{
    cout << "Deleting a blockNode" << endl;
    delete comp_Stat;
    comp_Stat = NULL;
}

//ExprNode 
ExprNode::~ExprNode()
{
    cout << "Deleting a programNode" << endl; //test case uses the programNode instead of ExprNode 
    delete name;
    delete block;
    name = NULL;
    block = NULL;
}

//compoundNode
compoundNode::~compoundNode()
{
    cout << "Deleting a compoundNode" << endl;
    int length = statements.size();
    for (int a = 0; a < length; ++a)
    {
        //distructor
        delete statements[a];
        statements[a] = NULL;
    }
    statements.clear();
}
void compoundNode::setStatementNode(statementNode *statmt1)// This is for pusing the statmt1 into vector variable of <statementNode*> type
{
    statements.push_back(statmt1);
}
void compoundNode::printTo(ostream &OS)
{
    OS << "Begin Compound Statement" << endl;
    //we are geting the size of the statment here
    int length = statements.size(); 
    for (int a = 0; a < length; ++a)
    {
        //if not pointing then we print it
        if (statements[a] != NULL)
            OS << *(statements[a]) << endl;
    }
    OS << "End Compound Statement" ;
}


//assignmentNode
assignmentNode::~assignmentNode()
{

    cout << "Deleting an assignmentNode" << endl;
    delete name;
    delete expression;
    name = NULL;
    expression = NULL;
}

//ifNode
ifNode::~ifNode()
{

    cout << "Deleting an ifNode" << endl;
    delete expression;
    expression = NULL;
    delete thenStatement;
    thenStatement = NULL;
    delete elseStatement;
    elseStatement = NULL;
}

//whileNode
whileNode::~whileNode()
{

    cout << "Deleting a whileNode" << endl;
    delete expression;
    delete loopBody;
    expression = NULL;
    loopBody = NULL;
}

//readNode
readNode::~readNode()
{

    cout << "Deleting a readNode" << endl;
    delete name;
    name = NULL;
}

//writeNode
writeNode::~writeNode()
{

    cout << "Deleting a writeNode" << endl;
    delete name;
    name = NULL;
}

//StatmentNode
statementNode::~statementNode() {}

//expressionNode
expressionNode::~expressionNode()
{

    cout << "Deleting an expressionNode" << endl;
    delete expression_operator;
    delete simple_expression;
    delete other_simple_expression;
    simple_expression = NULL;
    expression_operator = NULL;
    other_simple_expression = NULL;
}

//simpleExpressionNode
simpleExpressionNode::~simpleExpressionNode()
{
    cout << "Deleting a simpleExpressionNode" << endl;

    delete term;
    term = NULL;
    int length = simpleExpresionOperator.size();
    for (int a = 0; a < length; ++a)
    { 
        
        //here we delete the simpleExpressionOperator
        delete simpleExpresionOperator[a];
        simpleExpresionOperator[a] = NULL;

        //here we delete otherterm
        delete (otherterm[a]);
        otherterm[a] = NULL;
    }
    
    simpleExpresionOperator.clear();  //we clear the vetor simpleExpressionOperator
    
    otherterm.clear();//we are clearing vector otherTerm
}

//TermNode
TermNode::~TermNode()
{
    cout << "Deleting a termNode" << endl; //test case uses termNode instead of TermNode 
    delete factor;
    factor = NULL;
    int length = termOperator.size();
    for (int a = 0; a < length; ++a)
    { 
        //here we delete the termOperator
        delete termOperator[a];
        termOperator[a] = NULL;

        //here we delete the otherFactor
        delete otherFactor[a];
        
        otherFactor[a] = NULL;
    }
    termOperator.clear();//here we are clearing the vector termOperator
    otherFactor.clear();//here we are clearing vector otherFactor
}

//FactorNode
FactorNode::~FactorNode()
{
    cout << "Deleting a factorNode" << endl; 
    delete factor;
    factor = NULL;
    delete factorOperator;
    factorOperator = NULL;
    delete nextFactor;
    nextFactor = NULL;
    delete expression;
    expression = NULL;
}



//***************************************************************************************************************************************************************************************
