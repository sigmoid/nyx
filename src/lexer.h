#pragma once

#include "lexer.h"
#include <vector>
#include <string>

#define TOK_IDENT          'I'
#define TOK_NUMBER         'n'
#define TOK_CONST          'C'
#define TOK_VAR            'V'
#define TOK_PROCEDURE      'P'
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
#define TOK_COMMA          ','
#define TOK_SEMICOLON      ';'
#define TOK_ASSIGN         ':'
#define TOK_HASH           '#'
#define TOK_LESSTHAN       '<'
#define TOK_GREATERTHAN    '>'
#define TOK_PLUS           '+'
#define TOK_MINUS          '-'
#define TOK_MULTIPLY       '*'
#define TOK_DIVIDE         '/'
#define TOK_LPAREN         '('
#define TOK_RPAREN         ')'

class Lexer{
    public:
        std::vector<char> LexInput(std::ifstream& fileStream);
};
