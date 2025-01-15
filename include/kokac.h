#pragma once
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "node.h"
#include "typingVisitor.h"


extern int yyparse();
extern FILE *yyin;
extern int yyrestart(FILE*);
extern char* yycurrentfilename;
extern std::vector<std::string> debug_tokens;
extern std::vector<NDecl*>* programBlock;
extern std::vector<std::string> programLines;

class KokaCompiler{
private:
    const std::string fileName;
    std::vector<NDecl*> MainAst;
    FILE* file;
    std::string outName;
    bool parseOnly, typeOnly;

public:
    KokaCompiler(const std::string& fileName, bool parseOnly, bool typeOnly);

    void compile();
};