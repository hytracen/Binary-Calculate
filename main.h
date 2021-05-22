//
// Created by Yoyotao on 2021/3/29.
//

#ifndef WEEK03_MAIN_H
#define WEEK03_MAIN_H

#include "BinaryTree.h"
#include <bits/stdc++.h>

enum TOKEN
{
    VOID,           // invalid token
    NUMBER,         // any float or int
    VARIABLE,       // c, s, t, or l
    OPERATOR,       // +, -, *, /, ^
    LPAREN,         // (
    RPAREN          // )
};

class Token
{
public:
    TOKEN m_type;       // what type of token is it?
    float m_number;     // if number, what number is it?
    int m_variable;     // if a variable, which variable?
    int m_operator;     // if an operator, which operator?
};

void Scan( const char* p_string, std::queue<Token>& p_queue );
float ReadFloat( const char* p_string, int& p_index );
void PrintBinaryTree( BinaryTree<Token>* Root);

BinaryTree<Token>* ExcExpression(std::queue<Token>& Expression);
BinaryTree<Token>* ExcItem(std::queue<Token>& Expression);
BinaryTree<Token>* ExcFactor(std::queue<Token>& Expression);


#endif //WEEK03_MAIN_H
