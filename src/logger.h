#include "lexer.h"
#include <iostream>
#include <vector>

class Logger{
    public:
        static void LogTokens(std::vector<Token>& tokens, std::ostream& output);
};