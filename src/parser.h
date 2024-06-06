#pragma once
#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>

class Parser
{

public:
    Parser(std::vector<char> tokens);
    void Parse();

private:
    void Expect(char tokenType);
    void Next();
    char GetCurrentToken();

    // Grammar Rules
    void Block();
    void Statement();
    void IfStatement();
    void WhileLoop();
    void FunctionCall();
    void Assign();
    void Expression();
    void Condition();
    void ParamList();
    void Term();
    void Factor();

    std::vector<char>::iterator _CurrentTokenItr;
    std::vector<char> _Tokens;

};