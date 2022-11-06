//*****************************************************************************
// purpose:  node.h for the lab 3
//
//  author: rb2298
//*****************************************************************************

#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <string>

using namespace std;

// Abstract class. Base class for StringNode, IntegerNode, and FloatNode
//
// Do NOT change this class
class DataNode {
public:
    virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
    virtual ~DataNode(); // labeling the destructor as virtual allows 
	                     // the subclass destructors to be called
};

// Uses double dispatch to call the overloaded method printTo in the 
// DataNodes: StringNode, IntegerNode, and FloatNode
//
// Do NOT change this method
ostream& operator<<(ostream& os, DataNode& fn) {
	os << "Data: ";
	fn.printTo(os);
	return os;
}

// Do NOT change this method
DataNode::~DataNode() {}


class StringNode : public DataNode {
public:
    string* mystring = nullptr;

    // Add constructor, destructor, and printTo methods
    StringNode(string stringValue) //constructor
        
    {
        mystring = new string(stringValue); 
    }
    void printTo(ostream &os) override 
    {

        cout << "(string: " << *mystring << ") "; // for printing

    }
    ~StringNode()//destructor
    {
        cout <<"Deleting DataNode:StringNode:"<<*mystring << endl; 
        free(mystring);

    }

};



class IntegerNode : public DataNode {
public:
    int myinteger = 0;

    // Add constructor, destructor, and printTo methods

    IntegerNode(int intValue)
    {
        myinteger = intValue; //this is the constructor
    }

    void printTo(ostream &os) override 
    {
        cout << "(integer: " << myinteger << ") "; //this is for the print


    }
    ~IntegerNode()
    {
        cout<<"Deleting DataNode:IntegerNode:"<<myinteger<<endl; //this is the distructor
        
    }
};



class FloatNode : public DataNode {
public:
    float myfloat = 0.0;

    // Add constructor, destructor, and printTo methods

    FloatNode(float floatValue)
    {
        myfloat = floatValue; // This is the constructer

    }
    void printTo(ostream &os) override //This is for printing

    {
        cout<< "(float: "<<myfloat<<") "; 

    }


    ~FloatNode()


    {
        cout <<"Deleting DataNode:FloatNode:"<<myfloat<< endl; //destructor


    }
};



#endif /* NODES_H */
