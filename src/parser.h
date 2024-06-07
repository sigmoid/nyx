#pragma once
#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>

class Parser
{

public:
    Parser(std::vector<Token> tokens);
    void Parse();

private:
    void Expect(char tokenType);
    void Next();
    Token GetCurrentToken();

    // Grammar Rules
    void Block();
    void Statement();
    void IfStatement();
    void WhileLoop();
    void FunctionCall();
    void Declare();
    void Assign();
    void Expression();
    void Condition();
    void ParamList();
    void Term();
    void Factor();

    std::vector<Token>::iterator _CurrentTokenItr;
    std::vector<Token> _Tokens;

};