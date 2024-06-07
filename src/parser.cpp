#include "parser.h"

Parser::Parser(std::vector<Token> tokens)
{
    _Tokens = tokens;
    _CurrentTokenItr = _Tokens.begin();
}

void Parser::Parse()
{
    Expect(TOK_MAIN);
    Block();
}

void Parser::Expect(char tokenType)
{    
    if(GetCurrentToken().Value != tokenType)
        throw std::runtime_error("Invalid token: " + std::string(1,GetCurrentToken().Value) + " expected " + std::string(1,tokenType) + " Line: " + std::to_string(GetCurrentToken().LineNumber) + " Pos: " + std::to_string(GetCurrentToken().Position));
    
    Next();
}
void Parser::Next()
{
    _CurrentTokenItr++;
}

Token Parser::GetCurrentToken()
{
    if(_CurrentTokenItr != _Tokens.end())
    {
        return *_CurrentTokenItr;
    }
}

void Parser::Block()
{
    Expect(TOK_LCURLY);
    while(GetCurrentToken().Value != TOK_RCURLY)
    {
        Statement();
    }
    Expect(TOK_RCURLY);  
}

void Parser::Statement()
{
    if(GetCurrentToken().Value == TOK_TYPE)
    {
        Declare();
    }
    if(GetCurrentToken().Value == TOK_IDENT)
    {
        Expect(TOK_IDENT);
        if(GetCurrentToken().Value == TOK_ASSIGN)
        {
            Assign();
        }
        else if(GetCurrentToken().Value == TOK_LPAREN)
        {        
            FunctionCall();
        }
    }
    else if(GetCurrentToken().Value == TOK_IF)
    {
        IfStatement();
    }
    else if(GetCurrentToken().Value == TOK_WHILE)
    {
        WhileLoop();
    }
}


void Parser::IfStatement()
{
    Expect(TOK_IF);
    Expect(TOK_LPAREN);
    Condition();
    Expect(TOK_RPAREN);
    Block();
}

void Parser::WhileLoop()
{
    Expect(TOK_WHILE);
    Expect(TOK_LPAREN);
    Condition();
    Expect(TOK_RPAREN);
    Block();
}

void Parser::FunctionCall()
{
    Expect(TOK_LPAREN);
    ParamList();
    Expect(TOK_RPAREN);
    Expect(TOK_SEMICOLON);
}

void Parser::Declare()
{
    Expect(TOK_TYPE);
    Expect(TOK_IDENT);
    Expect(TOK_ASSIGN);
    Expression();
    Expect(TOK_SEMICOLON);
}

void Parser::Assign()
{
    Expect(TOK_ASSIGN);
    if(GetCurrentToken().Value == TOK_IDENT)
    {
        Expression();
    }
    else
    {
        Expression();
    }
    Expect(TOK_SEMICOLON);
}

void Parser::Expression()
{
    if(GetCurrentToken().Value == TOK_MINUS)
    {
        Next();
    }

    Term();

    while(GetCurrentToken().Value == TOK_MINUS || GetCurrentToken().Value == TOK_PLUS)
    {
        Next();
        Term();
    }
}

void Parser::Condition()
{
    Expression();
    
    if(GetCurrentToken().Value == TOK_DOUBLEEQUAL
        || GetCurrentToken().Value == TOK_GREATERTHANEQ
        || GetCurrentToken().Value == TOK_LESSTHANEQ
        || GetCurrentToken().Value == TOK_LESSTHAN
        || GetCurrentToken().Value == TOK_GREATERTHAN)
    {
        Next();
        Expression();
        return;
    }

    throw std::runtime_error("Expected a comparison operator, got " + std::string(1,GetCurrentToken().Value) + " Line: " + std::to_string(GetCurrentToken().LineNumber) + " Pos " + std::to_string(GetCurrentToken().Position));
}

void Parser::ParamList()
{
    Expect(TOK_IDENT);
    while(GetCurrentToken().Value == TOK_COMMA)
    {
        Expect(TOK_IDENT);
    }
}

void Parser::Term()
{
    Factor();

    while(GetCurrentToken().Value == TOK_MULTIPLY 
    || GetCurrentToken().Value == TOK_DIVIDE)
    {
        Next();
        Factor();
    }
}

void Parser::Factor()
{
    if(GetCurrentToken().Value == TOK_IDENT
    || GetCurrentToken().Value == TOK_NUMBER)
    {
        Next();
    }
    else if(GetCurrentToken().Value == TOK_LPAREN)
    {
        Expect(TOK_LPAREN);
        Expression();
        Expect(TOK_RPAREN);
    }
}
