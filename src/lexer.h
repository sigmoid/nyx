#pragma once

#include "lexer.h"
#include <vector>
#include <string>

#define TOK_IDENT          'I'
#define TOK_NUMBER         'n'
#define TOK_CONST          'C'
#define TOK_VAR            'V'
#define TOK_VOID           'v'
#define TOK_CALL           'c'
#define TOK_BEGIN          'B'
#define TOK_END            'E'
#define TOK_IF             'i'
#define TOK_THEN           'T'
#define TOK_WHILE          'W'
#define TOK_DO             'D'
#define TOK_ODD            'O'
#define TOK_DOT            '.'
#define TOK_EQUAL          '='
#define TOK_DOUBLEEQUAL    'd'
#define TOK_COMMA          ','
#define TOK_SEMICOLON      ';'
#define TOK_ASSIGN         ':'
#define TOK_HASH           '#'
#define TOK_LESSTHAN       '<'
#define TOK_LESSTHANEQ     'l'
#define TOK_GREATERTHAN    '>'
#define TOK_GREATERTHANEQ  'g'
#define TOK_PLUS           '+'
#define TOK_MINUS          '-'
#define TOK_MULTIPLY       '*'
#define TOK_DIVIDE         '/'
#define TOK_LPAREN         '('
#define TOK_RPAREN         ')'
#define TOK_LCURLY         '{'
#define TOK_RCURLY         '}'
#define TOK_MAIN           'M'
#define TOK_TYPE           't'

class Token {
    public:
    char Value;
    int LineNumber;
    int Position;
};

class Lexer{
    public:
        std::vector<Token> LexInput(std::ifstream& fileStream);
};
