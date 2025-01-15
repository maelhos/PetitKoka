#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdio>

extern char* yycurrentfilename;
extern std::vector<std::string> programLines;

// we declare this here to avoid cycle inclusions
typedef struct YYLTYPE YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};

std::string locToString(const YYLTYPE& loc);
void typingError(const std::string& msg);
void typingError(const std::string& msg, const YYLTYPE& loc);
void typingWarning(const std::string& msg, const YYLTYPE& loc);
