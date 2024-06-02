#include <map>
#include <string>

class ArgumentParser{
    public:
        std::map<std::string, std::string> ParseCommandLineArguments(int argc, char* argv[]);
};

class ProgramArguments{
    public:
        std::string filename;
        std::map<std::string, std::string> flags;
};