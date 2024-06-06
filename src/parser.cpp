#include "parser.h"

Parser::Parser(std::vector<char> tokens)
{
    std::cout << tokens.size() << tokens[0] << std::endl;
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
    if(GetCurrentToken() != tokenType)
        throw std::runtime_error("Invalid token: " + std::string(1,GetCurrentToken()) + " expected " + std::string(1,tokenType));
    
    Next();
}
void Parser::Next()
{
    if(_CurrentTokenItr + 1 >= _Tokens.end())
        throw std::runtime_error("Attempted to read token past end of lexed code");
    
    _CurrentTokenItr++;
}

char Parser::GetCurrentToken()
{
    if(_CurrentTokenItr != _Tokens.end())
        return *_CurrentTokenItr;

    throw std::runtime_error("Attempt to access out of bounds object");
}

void Parser::Block()
{
    Expect(TOK_LCURLY);
    Statement();
    Expect(TOK_RCURLY);   
}

void Parser::Statement()
{
    if(GetCurrentToken() == TOK_IDENT)
    {
        Next();

        if(GetCurrentToken() == TOK_ASSIGN)
        {
            Assign();
        }
        else if(GetCurrentToken() == TOK_LPAREN)
        {
            FunctionCall();
        }
    }
    else if(GetCurrentToken() == TOK_IF)
    {
        IfStatement();
    }
    else if(GetCurrentToken() == TOK_WHILE)
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
}

void Parser::WhileLoop()
{
    Expect(TOK_WHILE);
    Expect(TOK_LCURLY);
    Condition();
    Expect(TOK_RPAREN);
    Block();
}

void Parser::FunctionCall()
{
    Expect(TOK_IDENT);
    Expect(TOK_LPAREN);
    ParamList();
    Expect(TOK_RPAREN);
    Expect(TOK_SEMICOLON);
}

void Parser::Assign()
{
    Expect(TOK_ASSIGN);
    Expression();
}

void Parser::Expression()
{
    if(GetCurrentToken() == TOK_MINUS)
    {
        Next();
    }

    Term();

    while(GetCurrentToken() == TOK_MINUS || GetCurrentToken() == TOK_PLUS)
    {
        Next();
        Term();
    }
}

void Parser::Condition()
{
    Expression();
    
    if(GetCurrentToken() == TOK_DOUBLEEQUAL
        || GetCurrentToken() == TOK_GREATERTHANEQ
        || GetCurrentToken() == TOK_LESSTHANEQ
        || GetCurrentToken() == TOK_LESSTHAN
        || GetCurrentToken() == TOK_GREATERTHAN)
    {
        Next();
        Expression();
    }

    throw std::runtime_error("Expected a comparison operator, got " + std::string(1,GetCurrentToken()));
}

void Parser::ParamList()
{
    Expect(TOK_IDENT);
    while(GetCurrentToken() == TOK_COMMA)
    {
        Expect(TOK_IDENT);
    }
}

void Parser::Term()
{
    Factor();

    while(GetCurrentToken() == TOK_MULTIPLY 
    || GetCurrentToken() == TOK_DIVIDE)
    {
        Next();
        Factor();
    }
}

void Parser::Factor()
{
    if(GetCurrentToken() == TOK_IDENT
    || GetCurrentToken() == TOK_NUMBER)
    {
        Next();
    }
    else if(GetCurrentToken() == TOK_LPAREN)
    {
        Expect(TOK_LPAREN);
        Expression();
        Expect(TOK_RPAREN);
    }
}
