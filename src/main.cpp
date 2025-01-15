#include <iostream>
#include <vector>
#include <string>
#include "kokac.h"

extern int yydebug;
//#define YYERROR_VERBOSE 1
//#define YYDEBUG 1

int main(int argc, char* argv[]){   
    //yydebug = 1;

    std::vector<std::string> args(argv + 1, argv + argc);
    std::vector<std::string> files{};

    bool parseOnly = false;
    bool typeOnly = false;

    for (auto &&arg : args)
    {
        if (arg[0] == '-')
        {
            if (arg == "--parse-only")
                parseOnly = true;
            else if (arg == "--type-only")
                typeOnly = true;  
            else
            {
                std::cerr << "Unrecognized option : " << arg << std::endl;
                exit(2);
            }
        }
        else
            files.push_back(arg);
    }

    if (parseOnly && typeOnly)
    {
        std::cerr << "option \"--type-only\" is incompatible with \"--parse-only\"" << std::endl;
        exit(2);
    }

    if (files.size() == 0)
    {
        std::cerr << std::string(argv[0]) << ": fatal error: no input files" << std::endl << "compilation terminated." << std::endl;
        return 2;
    }

    for (auto &&file : files)
    {
        KokaCompiler kokac(file, parseOnly, typeOnly);
        kokac.compile();
    }

    return 0;
}