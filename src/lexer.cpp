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

    if(!std::iswspace(line[i]) && !line[i] == '\0')
    {
        std::cerr << "Error parsing identifier: line: " + std::to_string(lineNum) + " col: " + std::to_string(i);
    }
	
	if (innerText == "const")
		return TOK_CONST;
	else if (innerText == "var")
		return TOK_VAR;
	else if (innerText == "procedure")
		return TOK_PROCEDURE;
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

std::vector<char> Lexer::LexInput(std::ifstream& fileStream)
{
    std::vector<char> res;

    int lineNum = 0;
    std::string line;
    while (std::getline(fileStream, line)) {
        int i = 0;
        while(i < line.length())
        {
            char currentToken;
            char currentChar = line[i];

            if(currentChar == ' ' || currentChar == '\n' || currentChar == '\t')
            {
                i++;
                continue;
            }
            if(currentChar == '/')
            {
                // comment
                if(i+1 >= line.length() && line[i+1] != '/')
                {
                    break;
                }
                
                i++;
                currentToken = currentChar;
            }
            else if(std::isalpha(currentChar) || currentChar == '_')
            {
                currentToken = LexIdentifier(line, lineNum, i);
            }
            else if(std::isdigit(currentChar))
            {
                currentToken = LexNumber(line, lineNum, i);
            }
            else if(currentChar == ':')
            {
                if(i+1 >= line.length() || line[i+1] != '=')
                    throw std::runtime_error("Invalid assignment operator");
                
                i += 2;
                currentToken = TOK_ASSIGN;
            }
            else if(currentChar == '.' ||
             currentChar == '=' ||
             currentChar == ',' ||
             currentChar == ';' ||
             currentChar == '#' ||
             currentChar == '<' ||
             currentChar == '>' ||
             currentChar == '+' ||
             currentChar == '-' ||
             currentChar == '*' ||
             currentChar == '(' ||
             currentChar == ')')
            {
                currentToken = currentChar;
                i++;
            }
            else
            {
                throw std::runtime_error("Unrecognized Token \"" + std::string(1, currentChar) + "\"");
            }

            res.push_back(currentToken);
        }
        lineNum++;
    }

    return res;
}