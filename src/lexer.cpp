#include "lexer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cwctype>

char LexIdentifier(std::string line, int lineNum, int& i)
{
    std::string innerText;

    while (std::isalnum(line[i]) || line[i] == '_')
    {
        innerText += line[i];
		++i;
    }
	
	if (innerText == "const")
		return TOK_CONST;
	else if (innerText == "var")
		return TOK_VAR;
	else if (innerText == "void")
		return TOK_VOID;
	else if (innerText == "call")
		return TOK_CALL;
	else if (innerText == "begin")
		return TOK_BEGIN;
	else if (innerText == "end")
		return TOK_END;
	else if (innerText == "if")
		return TOK_IF;
	else if (innerText == "then")
		return TOK_THEN;
	else if (innerText == "while")
		return TOK_WHILE;
	else if (innerText == "do")
		return TOK_DO;
	else if (innerText == "odd")
		return TOK_ODD;
    else if(innerText == "main")
        return TOK_MAIN;
    else if(innerText == "int")
        return TOK_TYPE;
        
	return TOK_IDENT;
}

char LexNumber(std::string line, int lineNum, int& i)
{
    bool isDecimal = false;
    bool isFloat = false;

    std::string innerText;    

    while(i < line.length() && !std::iswspace(line[i]))
    {
        if(!std::isdigit(line[i]) && line[i] != 'f' && line[i] != '.')
        {
            break;
        }
        if(line[i] != ' ' && isFloat)
        {
            throw std::runtime_error("Error parsing number literal: Line-" + std::to_string(lineNum) + " Col-" + std::to_string(i));
        }
        if(line[i] == '.')
        {
            if(isDecimal == false)
               isDecimal = true;
            else
                throw std::runtime_error("Error parsing number literal: Line-" + std::to_string(lineNum) + " Col-" + std::to_string(i));
        }
        if(line[i] == 'f')
        {
            if(isFloat == false)
                isFloat = true;
            else
                throw std::runtime_error("Error parsing number literal: Line-" + std::to_string(lineNum) + " Col-" + std::to_string(i));
        }

        innerText += line[i];

        i++;
    }

    return TOK_NUMBER;
}

std::vector<Token> Lexer::LexInput(std::ifstream& fileStream)
{
    std::vector<Token> res;

    int lineNum = 0;
    std::string line;
    while (std::getline(fileStream, line)) {
        int i = 0;
        while(i < line.length())
        {
            char currentTokenVal;
            char currentChar = line[i];

            if(currentChar == ' ' || currentChar == '\n' || currentChar == '\t')
            {
                i++;
                continue;
            }
            if(currentChar == '/')
            {
                // comment
                if(i+1 <= line.length() && line[i+1] == '/')
                {
                    break;
                }
                
                i++;
                currentTokenVal = currentChar;
            }
            else if(std::isalpha(currentChar) || currentChar == '_')
            {
                currentTokenVal = LexIdentifier(line, lineNum, i);
            }
            else if(std::isdigit(currentChar))
            {
                currentTokenVal = LexNumber(line, lineNum, i);
            }
            else if(currentChar == ':')
            {
                if(i+1 >= line.length() || line[i+1] != '=')
                    throw std::runtime_error("Invalid assignment operator");
                
                i += 2;
                currentTokenVal = TOK_ASSIGN;
            }
            else if(currentChar == '=')
            {
                if(i + 1 < line.length() && line[i+1] == '=')
                    currentTokenVal = TOK_DOUBLEEQUAL;
                else
                    currentTokenVal = TOK_EQUAL;

                i++;
            }
            else if(currentChar == '<')
            {
                if(i + 1 < line.length() && line[i+1] == '=')
                    currentTokenVal = TOK_LESSTHANEQ;
                else
                    currentTokenVal = TOK_LESSTHAN;
                i++;
            }
            else if(currentChar == '>')
            {
                if(i + 1 < line.length() && line[i+1] == '=')
                    currentTokenVal = TOK_GREATERTHANEQ;
                else
                    currentTokenVal = TOK_GREATERTHAN;
                
                i++;
            }
            else if(currentChar == '.' ||
             currentChar == ',' ||
             currentChar == ';' ||
             currentChar == '#' ||
             currentChar == '+' ||
             currentChar == '-' ||
             currentChar == '*' ||
             currentChar == '(' ||
             currentChar == ')' ||
             currentChar == '{' ||
             currentChar == '}' )
            {
                currentTokenVal = currentChar;
                i++;
            }
            else
            {
                throw std::runtime_error("Unrecognized Token \"" + std::string(1, currentChar) + "\"");
            }

            Token currentToken;
            currentToken.Value = currentTokenVal;
            currentToken.LineNumber = lineNum + 1;
            currentToken.Position = i;
            res.push_back(currentToken);
        }
        lineNum++;
    }

    return res;
}