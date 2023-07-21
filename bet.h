#ifndef BET_H
#define BET_H


#include <algorithm>
#include <queue>
#include <list>
#include <utility>
#include <iostream>
#include <stack>


using namespace std;

    template <typename T>
    class BET {
        private:
            struct BinaryNode
            {
                T element; 
                BinaryNode *left; 
                BinaryNode *right; 

                BinaryNode( const T & theElement, BinaryNode *lt, BinaryNode *rt )
                : element{ theElement }, left{ lt }, right{ rt } { }

                BinaryNode( T && theElement, BinaryNode *lt, BinaryNode *rt )
                : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
            };
        
       
        public:            
            BET(); //default zero-parameter constructor. Builds an empty tree.
            BET(const list<T> & postfix); //one-parameter constructor, where parameter "postfix" is a list representing a postfix expression. The tree should be built based on the postfix expression.
            BET(const BET&); //copy constructor -- makes appropriate deep copy of the tree
            ~BET(); //destructor -- cleans up all dynamic space in the tree
            bool buildFromPostfix(const list<T> & postfix); //parameter "postfix" is a list representing a postfix expression. A tree should be built based on each postfix expression. Tokens in the postfix expression are separated by spaces. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
            BET & operator=(const BET &); //assignment operator -- makes appropriate deep copy.
            void printInfixExpression(); //Print out the infix expression. Should do this by making use of the private (recursive) version
            void printPostfixExpression(); //Print the postfix form of the expression. Use the private recursive function to help
            size_t size(); //Return the number of nodes in the tree (using the private recursive function)
            int leaves(); //Return the number of leaf nodes in the tree. (Use the private recursive function to help)
            int depth(); //return the depth of the tree.
            int breadth(); //return the breadth of the tree.
            bool empty(); //return true if the tree is empty. Return false otherwise.
        private:
        
            // all  implemented recursively except breadth()
            void printInfixExpression(BinaryNode *n); //print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
            void makeEmpty(BinaryNode* &t); //delete all nodes in the subtree pointed to by t.
            BinaryNode * clone(BinaryNode *t) const; //clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=.
            void printPostfixExpression(BinaryNode *n); //print to the standard output the corresponding postfix expression.
            size_t size(BinaryNode *t); //return the number of nodes in the subtree pointed to by t.
            int leaves (BinaryNode *t); //return the number of leaf nodes in the subtree pointed to by t.
            int depth(BinaryNode* &t); //return the depth of the subtree pointed to by t.
            int breadth(BinaryNode* &t); //return the breadth of the subtree pointed to by t. Hint: this one requires a helper function for a recursive implementation. But you do not have to have a recursive implementation.
          
            BinaryNode *root;
    };
    
    #include "bet.hpp"


#endif
