#include "kokac.h"


KokaCompiler::KokaCompiler(const std::string& fileName, bool parseOnly, bool typeOnly) 
    : fileName(fileName), MainAst{}, outName{}, parseOnly(parseOnly), typeOnly(typeOnly)
{
    file = fopen(fileName.c_str(), "r");
    if (!file){
        std::cerr << "No such file or can't open file \"" << fileName << "\"" << std::endl;
        exit(2);
    }

    char * line = NULL;
    size_t len = 0;
    long read;
    // read all the file to emit errors later
    while ((read = getline(&line, &len, file)) != -1) 
    {
        while (line[read - 1] == '\n') read--;
        programLines.push_back(std::string(line, read));
    }
    fseek(file, 0, SEEK_SET);

    long flen = fileName.length();
    std::string ext;
    if (flen < 6) goto BAD_EXT;

    ext = fileName.substr(flen - 5, 5);
    if (ext != ".koka")
    {
        BAD_EXT:;
        std::cerr << "File : \"" << fileName << "\" does not have extension \".koka\"" << std::endl;
        exit(2);
    }
    outName = fileName.substr(0, flen - 5).append(".s");
}

void KokaCompiler::compile()
{
    // 1. Parsing
    yycurrentfilename = (char*)fileName.c_str();
    yyrestart(file);
    yyparse();

    // 1.5. Debug Token output
    //std::cout << "\nDebug tokens : ";
    //for (auto &&debug_token : debug_tokens)
    //    std::cout << debug_token << " ";
    //std::cout << std::endl;
    
    // 2. Ast building (or retrieving rather)
    MainAst = *programBlock;

    if (parseOnly)
    {
        std::cout << "\nAST :  \n" << vecToString(programBlock) << std::endl;
        return;
    }
    
    // 3. Typing
    typingVisitor typeWriter(programBlock);
    typeWriter.visit(programBlock);
    std::cout << "\nAST :  \n" << vecToString(programBlock) << std::endl;

    if (typeOnly) return;

    // 4. Generating llvm IR
    // std::error_code errCode;
    // llvm::raw_fd_ostream outLL(outName, errCode);
    // GMLLVM leuleuveumeu(MainAst);
    // std::unique_ptr<llvm::Module> module(std::move(leuleuveumeu.assemble()));
    // module->print(outLL, nullptr);
}