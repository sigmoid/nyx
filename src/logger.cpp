#include "logger.h"

void Logger::LogTokens(std::vector<Token>& tokens, std::ostream& output)
{
    for(const auto& token : tokens)
    {
        output << token.Value << " ";
    }
}