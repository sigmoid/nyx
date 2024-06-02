#include "logger.h"

void Logger::LogTokens(std::vector<char>& tokens, std::ostream& output)
{
    for(const auto& token : tokens)
    {
        output << token << " ";
    }
}