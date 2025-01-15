#include "error.h"

std::string locToString(const YYLTYPE& loc)
{
    return "";
    std::stringstream r;
    r << " " << std::string(yycurrentfilename) << ":" << loc.first_line;

    r << ":" << loc.first_column;
    if (loc.first_column != loc.last_column)
        r << "-" << loc.last_column;
    r << " ";
    return r.str();
}

void typingError(const std::string& msg, const YYLTYPE& loc) 
{ 
    std::cout << "Typing error in File \"" << std::string(yycurrentfilename) << "\", line " << loc.first_line;
    if (loc.first_line != loc.last_line)
        std::cout << "-" << loc.last_line;
    std::cout << ", characters " << loc.first_column << "-" << loc.last_column << ":" << std::endl;

    std::cout << "     | " << msg << std::endl;
    if (loc.first_line - 1 < programLines.size())
        std::cout << "     | " << programLines[loc.first_line - 1] << std::endl;
    else 
        std::cout << "     | " << ";" << std::endl; // only reason for that would be an inserted ; at the end of an empty line

    std::cout << "     | " << std::string(loc.first_column - 1, ' ') <<  std::string(std::max(loc.last_column - loc.first_column, 1), '^') << std::endl;

    exit(1);
}

void typingError(const std::string& msg) 
{ 
    std::cout << "Typing error in File \"" << std::string(yycurrentfilename) << "\"" << std::endl;
    std::cout << "     | " << msg << std::endl;
    exit(1);
}

void typingWarning(const std::string& msg, const YYLTYPE& loc) 
{ 
    std::cout << "Typing warning in File \"" << std::string(yycurrentfilename) << "\", line " << loc.first_line;
    if (loc.first_line != loc.last_line)
        std::cout << "-" << loc.last_line;
    std::cout << ", characters " << loc.first_column << "-" << loc.last_column << ":" << std::endl;

    std::cout << "     | " << msg << std::endl;
    if (loc.first_line - 1 < programLines.size())
        std::cout << "     | " << programLines[loc.first_line - 1] << std::endl;
    else 
        std::cout << "     | " << ";" << std::endl; // only reason for that would be an inserted ; at the end of an empty line

    std::cout << "     | " << std::string(loc.first_column - 1, ' ') <<  std::string(std::max(loc.last_column - loc.first_column, 1), '^') << std::endl;
}
