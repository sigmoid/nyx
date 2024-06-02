#include "lexer.h"
#include <iostream>
#include <vector>

class Logger{
    public:
        static void LogTokens(std::vector<char>& tokens, std::ostream& output);
};