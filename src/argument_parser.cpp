#include "argument_parser.h" 

std::map<std::string, std::string> ArgumentParser::ParseCommandLineArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> options;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            std::string key = arg;
            std::string value;
            if ((i + 1) < argc && argv[i + 1][0] != '-') {
                value = argv[++i];
            }
            options[key] = value;
        }
    }
    return options;
}