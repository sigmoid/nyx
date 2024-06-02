#include "lexer.h"
#include "argument_parser.h"
#include "logger.h"
#include <iostream>
#include <string>
#include <fstream>

ProgramArguments ParseArguments(int argc, char **argv)
{
    ProgramArguments res;

    if(argc == 1)
    {
        std::cerr << "Please enter a filename..." << std::endl;
        return res;
    }

    res.filename = std::string(argv[1]);

    ArgumentParser argumentParser;
    res.flags = argumentParser.ParseCommandLineArguments(argc, argv);
    
    return res;
}

int main(int argc, char **argv) {

    auto args = ParseArguments(argc, argv);

    std::ifstream inputFile(args.filename);

    if(args.flags.count("-h") || args.flags.count("-help"))
    {
        std::cout << "Nyx Compiler version 0.0 commands" << std::endl;
        std::cout << "\"-h\" \"-help\" - display a list of available commands" << std::endl;
        std::cout << "\"-dt\" - creates a token dump file" << std::endl;
    }

    bool shouldDumpTokens = args.flags.count("-dt");

    Lexer lex;
    
    auto tokens = lex.LexInput(inputFile);

    if(shouldDumpTokens)
        Logger::LogTokens(tokens, std::cout);

    return 0;
}