%{
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <set>
#include <cctype>

#include "node.h"
#include "parser.hpp"

#define TAB_SIZE 2
#define SAVE_TOKEN yylval.str = new std::string(yytext, yyleng);

char* yycurrentfilename;
std::vector<std::string> programLines;

// We do token localisation by hand because of our dirty home made lookahead...
int column = 1;
int column_sub = 0; // to take into account inserted chars
int old_column = 1;
int last_token = -1;
int next_token = -1;

int current_line_indent = 0;
int look_ahead = 0;
int is_eof = 0;
std::stack<int> indent_stack;
std::vector<std::string> debug_tokens{};


const std::set<int> end_continuations {TADD, TSUB, TMUL, TDIV, TMOD, TINC, TCLT, TCLE, TCGT, TCGE, TCEQ, TCNE, TAND, TOR, TLPAREN, TLBRACE, TCOMMA};

const std::set<int> begin_continuations {TADD, TSUB, TMUL, TDIV, TMOD, TINC, TCLT, TCLE, TCGT, TCGE, TCEQ, TCNE, TAND, TOR, TTHEN, TELSE, TELIF, TRPAREN, TRBRACE, TCOMMA, TRARROW, TLBRACE, TEQUAL, TDOT, TCOLONEQ};

#define HANDLE_COLUMN if (!look_ahead) { if (column_sub) { column_sub--; } else { old_column = column; column += yyleng; }}

#define RESET_COLUMN column = 1
#define CURRENT_INDENT (indent_stack.empty() ? 0 : indent_stack.top())
#define IS_CONTINUATION_END(t) (end_continuations.count(t) > 0) 
#define IS_CONTINUATION_START(t) (begin_continuations.count(t) > 0) 

#define HANDLE_LOC ; yylloc.first_line = yylineno; yylloc.last_line = yylineno; yylloc.first_column = old_column; yylloc.last_column = column;

// the "#t" is a macro syntax to get the constant string equal to the macro-resolved identifier name, it's very handy to debug tokens and get the actual token name and not some int
#define RETURN(t) if (look_ahead) { next_token = t; yyless(0); BEGIN(indent); } else {debug_tokens.push_back(#t); last_token = t; HANDLE_LOC; return (yylval.token = t); }

// for comments and ignored tokens
#define HANDLE_LOOK_AHEAD if (look_ahead) { yyless(0); }

// return no lval to avoid token overwriting (basically we because we use a union, if we modify yylval.token we overwrite yylval.string...)
#define RETURN_NO_LVAL(t) if (look_ahead) { next_token = t; yyless(0); BEGIN(indent); } else {debug_tokens.push_back(#t); last_token = t; HANDLE_LOC; return t; }

void yyerror(char const *msg) 
{ 
    std::cout << "File \"" << std::string(yycurrentfilename) << "\", line " << yylineno << ", characters " << old_column << "-" << column << ":" << std::endl;
    
    std::string msg_str{};
    if (msg && *msg) msg_str = std::string(msg);
    else msg_str = std::string("Syntax error");

    std::cout << "     | " << msg_str <<" on token \"" << std::string(yytext) << "\"" << std::endl;
    if (yylineno - 1 < programLines.size())
        std::cout << "     | " << programLines[yylineno - 1] << std::endl;
    else 
        std::cout << "     | " << ";" << std::endl; // only reason for that would be an inserted ; at the end of an empty line

    std::cout << "     | " << std::string(old_column - 1, ' ') <<  std::string(yyleng, '^') << std::endl;

    /* DEBUG */
    std::cout << "Debug tokens : ";
    for (auto &&debug_token : debug_tokens)
        std::cout << debug_token << " ";
    std::cout << std::endl;

    exit(1);
}

void check_ident(const std::string& id)
{
    bool cond = true;
    for (int i = 1; i < id.size(); i++)
    {
        if (id[i] == '-')
        {
            cond &= std::isalpha(id[i - 1]) || std::isdigit(id[i - 1]);
            cond &= (i == id.size() - 1) || std::isalpha(id[i + 1]);
        }
    }
    if (!cond)
        yyerror("Malformed identifier");
}

#define CHECK_IDENT check_ident(*yylval.str)

%}

%option warn
%option nodefault
%option yylineno
%option noyywrap

%x indent
%s normal


IDENT    [a-z_][a-zA-Z0-9_\-]*\'*

/*
This may not be the best way but here is how I deal with it (and I purposly didn't look at the koka repo to do it on my own :)

- either we start with [a-z_] and then DASH which is a non 2 second position not last position well surrounded "-"
- either we have a second position "-" that is non terminal meaning we start with [a-z]\-[a-zA-Z]
- either we have some well formed beggining and terminal dash matched by ({ALPHA}\-)?
- either the bothersome case where the dash is second character and the last character represented by SINGLE_LOWER_AND_DASH

TODO: fix handling a-b-c
*/


NUMERIC  \-?(([1-9][0-9]*)|0)
STRING   \"([^\"\\\n]|(\\n)|(\\t)|(\\\\)|(\\\"))*\"

%%

<indent>[ ]                         { HANDLE_COLUMN; current_line_indent++; }
<indent>\t                          { HANDLE_COLUMN; current_line_indent += TAB_SIZE; }
<indent>\n                          { RESET_COLUMN; current_line_indent = 0; }
<indent>.                           {
                                        yyless(0);
                                        // look ahead by hand... bit dirty but bison doesn't support token lookahead afaik
                                        if (look_ahead == 0)
                                            look_ahead = 1;
                                        else
                                        {
                                            look_ahead = 0;

                                            //std::cout << std::endl << "DEBUG next token : " << next_token << std::endl;
                                            //std::cout << "DEBUG last token : " << last_token << std::endl << std::endl;
                                            if (current_line_indent > CURRENT_INDENT)
                                            {
                                                if (!IS_CONTINUATION_END(last_token) && !IS_CONTINUATION_START(next_token))
                                                {
                                                    column_sub++;
                                                    unput('{');
                                                    indent_stack.push(current_line_indent);
                                                }
                                                else if (last_token == TLBRACE)
                                                    indent_stack.push(current_line_indent);
                                            }
                                            else
                                            {
                                                // because we cant emit tokens we have to "unput" chars on the lexing input in the "opposite" order
                                                std::stack<char> emit_stack;
                                                while (current_line_indent < CURRENT_INDENT)
                                                {
                                                    indent_stack.pop();
                                                    if (next_token != TRBRACE)
                                                    {
                                                        emit_stack.push('}');
                                                        last_token = TRBRACE;
                                                    }
                                                }
                                                if (current_line_indent > CURRENT_INDENT)
                                                    yyerror("Broken indentation"); 
                                                
                                                if (!IS_CONTINUATION_END(last_token) && !IS_CONTINUATION_START(next_token))
                                                    emit_stack.push(';');

                                                while (!emit_stack.empty())
                                                {
                                                    column_sub++;
                                                    unput(emit_stack.top());
                                                    emit_stack.pop();
                                                }
                                            }
                                        }
                                        BEGIN(normal);
                                    }
<indent><<EOF>>                     {
                                        std::stack<char> emit_stack;
                                        while (0 < CURRENT_INDENT)
                                        {
                                            indent_stack.pop();
                                            if (next_token != TRBRACE)
                                            {
                                                emit_stack.push('}');
                                                last_token = TRBRACE;
                                            }
                                        }
                                        
                                        // for EOF we can always emit a semicolon and avoid infinite loop
                                        if (!is_eof)
                                        {
                                            is_eof = 1;
                                            emit_stack.push(';');

                                            while (!emit_stack.empty())
                                            {
                                                column_sub++;
                                                unput(emit_stack.top());
                                                emit_stack.pop();
                                            }
                                        }
                                        else yyterminate();
                                    }
<normal>\n                          { RESET_COLUMN; current_line_indent = 0; BEGIN(indent); }


<normal>[ \t]                       HANDLE_COLUMN;
<normal>"//".*                      HANDLE_COLUMN;
<normal>\/\*.*\*\/                  HANDLE_COLUMN;

<normal>"if"                        HANDLE_COLUMN; RETURN(TIF)
<normal>"else"                      HANDLE_COLUMN; RETURN(TELSE)
<normal>"elif"                      HANDLE_COLUMN; RETURN(TELIF)
<normal>"fn"                        HANDLE_COLUMN; RETURN(TFN)
<normal>"fun"                       HANDLE_COLUMN; RETURN(TFUN)
<normal>"return"                    HANDLE_COLUMN; RETURN(TRETURN)
<normal>"then"                      HANDLE_COLUMN; RETURN(TTHEN)
<normal>"val"                       HANDLE_COLUMN; RETURN(TVAL)
<normal>"var"                       HANDLE_COLUMN; RETURN(TVAR)

<normal>"True"                      HANDLE_COLUMN; RETURN(TTRUE)
<normal>"False"                     HANDLE_COLUMN; RETURN(TFALSE)

<normal>{IDENT}                     SAVE_TOKEN; CHECK_IDENT; HANDLE_COLUMN; RETURN_NO_LVAL(TIDENTIFIER)
<normal>{NUMERIC}                   SAVE_TOKEN; HANDLE_COLUMN; RETURN_NO_LVAL(TINTEGER)
<normal>{STRING}                    SAVE_TOKEN; HANDLE_COLUMN; RETURN_NO_LVAL(TSTRING)

<normal>"+"                         HANDLE_COLUMN; RETURN(TADD)
<normal>"-"                         HANDLE_COLUMN; RETURN(TSUB)
<normal>"*"                         HANDLE_COLUMN; RETURN(TMUL)
<normal>"/"                         HANDLE_COLUMN; RETURN(TDIV)
<normal>"%"                         HANDLE_COLUMN; RETURN(TMOD)

<normal>"++"                        HANDLE_COLUMN; RETURN(TINC)
<normal>"<"                         HANDLE_COLUMN; RETURN(TCLT)
<normal>"<="                        HANDLE_COLUMN; RETURN(TCLE)
<normal>">"                         HANDLE_COLUMN; RETURN(TCGT)
<normal>">="                        HANDLE_COLUMN; RETURN(TCGE)
<normal>"=="                        HANDLE_COLUMN; RETURN(TCEQ)
<normal>"!="                        HANDLE_COLUMN; RETURN(TCNE)

<normal>"&&"                        HANDLE_COLUMN; RETURN(TAND)
<normal>"||"                        HANDLE_COLUMN; RETURN(TOR)

<normal>")"                         HANDLE_COLUMN; RETURN(TRPAREN)
<normal>"["                         HANDLE_COLUMN; RETURN(TLBRACK)
<normal>"]"                         HANDLE_COLUMN; RETURN(TRBRACK)
<normal>"}"                         HANDLE_COLUMN; RETURN(TRBRACE)
<normal>","                         HANDLE_COLUMN; RETURN(TCOMMA)
<normal>"->"                        HANDLE_COLUMN; RETURN(TRARROW)
<normal>"{"                         HANDLE_COLUMN; RETURN(TLBRACE)

<normal>"="                         HANDLE_COLUMN; RETURN(TEQUAL)
<normal>"."                         HANDLE_COLUMN; RETURN(TDOT)
<normal>":="                        HANDLE_COLUMN; RETURN(TCOLONEQ)
<normal>":"                         HANDLE_COLUMN; RETURN(TCOLON)

<normal>"("                         HANDLE_COLUMN; RETURN(TLPAREN)
<normal>";"                         HANDLE_COLUMN; RETURN(TSEMICOLON)

<normal>"~"                         HANDLE_COLUMN; RETURN(TTILDE)
<normal>"!"                         HANDLE_COLUMN; RETURN(TEXCL)
<normal>.                           { yyerror("Unknown symbol"); }   
<normal><<EOF>>                     { BEGIN(indent); }
(.|\n)                              { yyless(0); BEGIN(indent); }   

%%