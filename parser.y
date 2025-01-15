%{
    #include <string>
    #include <vector>
    #include <assert.h>
    #include <optional>
    #include <variant>
    #include "node.h"
    #include <map>

    std::vector<NDecl*>* programBlock;
    
    extern int yylex();
    extern void yyerror(char const *msg);

    void setLastExpr(NBexprIf* expr, NExpr else_expr)
    {
        if (!expr->elseExpr.has_value())
            expr->elseExpr = else_expr;
        else
        {
            NBexprIf* nif = std::get<NBexprIf*>(expr->elseExpr.value());
            setLastExpr(nif, else_expr);
        }
    }

    std::string parseStr(std::string s){
        s = s.substr(1, s.length() - 2);
        static const std::map<std::string, std::string> specialReplace = {
            {"\\\\", "\\"},
            {"\\\"", "\""},
            {"\\n", "\n"},
            {"\\t", "\t"}
        };
        for (auto &&[first, second] : specialReplace)
            while (s.find(first) != std::string::npos)
                s.replace(s.find(first), first.length(), second);
        return s;
    }

    #define WRAP_TYPE(x) (new NType(x))
    #define WRAP_EXPR(x) (new NExpr(x))
    #define WRAP_STMT(x) (new NStmt(x))
    #define WRAP_ATOM(x) (new NAtom(x))
%}

%union {
    std::string* str;
    int token;

    std::vector<NDecl*>* decl_list;
    std::vector<NExpr>* expr_list;
    std::vector<NType>* type_list;
    std::vector<NParam*>* param_list;
    std::vector<std::string*>* ident_list;
    NDecl* decl;
    NFunBody* funbody;
    NParam* param;
    NType* type;
    NReturnType* rtype;
    NExpr* expr;
    NBlock* block;
    std::optional<NBlock*>* block_maybe;
    NExpr* bexpr;
    std::optional<NExpr>* bexpr_maybe;
    NBexprIf* bexpr_if;
    NAtom* atom;
    NAtomCall* atom_call;
    std::optional<NStmt>* stmt_maybe;
}
%locations

%token <str> TIDENTIFIER TSTRING TINTEGER

%token <token> TIF TELSE TELIF TFN TFUN TRETURN TTHEN TVAL TVAR
%token <token> TTRUE TFALSE
%token <token> TADD TSUB TMUL TDIV TMOD 
%token <token> TINC TCLT TCLE TCGT TCGE TCEQ TCNE
%token <token> TAND TOR TRPAREN TRBRACE TCOMMA TRARROW TLBRACE TLBRACK TRBRACK
%token <token> TEQUAL TDOT TCOLONEQ TCOLON TLPAREN TSEMICOLON TTILDE TEXCL

%type <decl_list> file non_empty_decl_list_semicolon
%type <decl> decl
%type <funbody> funbody
%type <param_list> non_empty_param_list_comma param_list_comma
%type <ident_list> non_empty_ident_list_comma ident_list_comma
%type <param> param
%type <rtype> annot result
%type <type> type atype
%type <type_list> type_list_comma_2_or_more
%type <atom> atom atom_sugar  atom_basic
%type <atom_call> atom_call
%type <expr> expr
%type <expr_list> non_empty_expr_list_comma expr_list_comma
%type <bexpr> bexpr bexpr_op
%type <bexpr_maybe> bexpr_maybe
%type <bexpr_if> elif_list
%type <block> block
%type <block_maybe> block_content_last block_content
%type <stmt_maybe> stmt

%start file
%locations

%left PATOM
%left TIF
%left TTHEN
%left TELIF
%left TELSE
%left TRETURN
%left TAND
%left TOR
%left TCOLONEQ TCEQ TCNE TCGT TCGE TCLT TCLE
%left TADD TSUB TINC
%left TMUL TDIV TMOD
%left TTILDE TEXCL
%left TDOT TLBRACE TRBRACE TFN

%%

file : /* blank */ {programBlock = new std::vector<NDecl*>{}; } 
     | TSEMICOLON file { $$ = $2; }
     | non_empty_decl_list_semicolon { programBlock = $1; }
     ;

semicolon_plus : TSEMICOLON
               | semicolon_plus TSEMICOLON
               ;

/*
semicolon_star : // blank 
               | semicolon_star TSEMICOLON
               ;
*/

non_empty_decl_list_semicolon : decl semicolon_plus { $$ = new std::vector<NDecl*>{$1}; }
                              | non_empty_decl_list_semicolon decl semicolon_plus { $1->push_back($2); $$ = $1; }
                              ;

decl : TFUN TIDENTIFIER funbody { $$ = new NDecl(@$, $2, $3); }
     ;
    
funbody : TLPAREN param_list_comma TRPAREN expr { $$  = new NFunBody(@$, $2, *$4); }
        | TLPAREN param_list_comma TRPAREN annot expr { $$  = new NFunBody(@$, $2, *$5, $4); }

non_empty_param_list_comma : param { $$ = new std::vector<NParam*>{$1}; }
                           | non_empty_param_list_comma TCOMMA param { $1->push_back($3); $$ = $1; }
                           ;

param_list_comma : /* blank */ { $$ = new std::vector<NParam*>{}; }
                 | non_empty_param_list_comma
                 ;

non_empty_ident_list_comma : TIDENTIFIER { $$ = new std::vector<std::string*>{$1}; }
                           | non_empty_ident_list_comma TCOMMA TIDENTIFIER { $1->push_back($3); $$ = $1; }
                           ;

ident_list_comma : /* blank */ { $$ = new std::vector<std::string*>{}; }
                 | non_empty_ident_list_comma
                 ;

param : TIDENTIFIER TCOLON type { $$ = new NParam(@$, $1, *$3); }
      ;

annot : TCOLON result { $$ = $2; }
      ;

result : type { $$ = new NReturnType(@$, *$1); }
       | TCLT ident_list_comma TCGT type { $$ = new NReturnType(@$, *$4, $2); }
       ;

/* Desambiguification :

to parse () -> result or (type) -> result one could go only with type
or first transform type to atype and then use atype := (type) and atype := ()
to solve this we simply have to make sure the proper list used in type is size 2 or more
*/

type : atype
     | atype TRARROW result { $$ = WRAP_TYPE(new NFunType(@$, new std::vector<NType>{*$1}, $3)); }
     | TLPAREN type_list_comma_2_or_more TRPAREN TRARROW result { $$ = WRAP_TYPE(new NFunType(@$, $2, $5)); }
     ;

type_list_comma_2_or_more : type TCOMMA type { $$ = new std::vector<NType>{*$1, *$3}; }
                          | type_list_comma_2_or_more TCOMMA type { $1->push_back(*$3); $$ = $1; }
                          ;

atype : TIDENTIFIER { $$ = WRAP_TYPE(new NBasicType(@$, $1)); }
      | TIDENTIFIER TCLT type TCGT { $$ = WRAP_TYPE(new NTemplateType(@$, $1, *$3)); }
      | TLPAREN type TRPAREN { $$ = $2; }
      | TLPAREN TRPAREN { $$ = WRAP_TYPE(new NBasicType(@$, new std::string("unit"))); }
      ;

atom : atom_basic
     | atom_call { $$ = WRAP_ATOM($1); }
     ;

atom_basic : TTRUE { $$ = WRAP_ATOM(new NAtomTrue(@$)); }
     | TFALSE { $$ = WRAP_ATOM(new NAtomFalse(@$)); }
     | TINTEGER { $$ = WRAP_ATOM(new NAtomInt(@$, std::stol(*$1))); }
     | TSTRING { $$ = WRAP_ATOM(new NAtomStr(@$, new std::string(parseStr(*$1)))); delete $1; }
     | TLPAREN TRPAREN { $$ = WRAP_ATOM(new NAtomNil(@$)); }
     | TIDENTIFIER { $$ = WRAP_ATOM(new NAtomIdent(@$, $1)); }
     | TLPAREN expr TRPAREN { $$ = WRAP_ATOM(new NAtomExpr(@$, *$2)); }
     | TLBRACK expr_list_comma TRBRACK { $$ = WRAP_ATOM(new NAtomList(@$, $2)); }
     | atom_sugar
     ;

atom_call : atom TLPAREN expr_list_comma TRPAREN { $$ = new NAtomCall(@$, *$1, $3); }
          | atom TDOT TIDENTIFIER { $$ = new NAtomCall(@$, new NAtomIdent(@$, $3), new std::vector<NExpr>{new NBAtom(@$, *$1)}); }
          | atom_basic TFN funbody { $$ = new NAtomCall(@$, *$1, new std::vector<NExpr>{new NBexprLambda(@$, $3)}); }
          | atom_basic block { $$ = new NAtomCall(@$, *$1, 
                new std::vector<NExpr>{new NBexprLambda(@$, new NFunBody(@$, new std::vector<NParam*>{}, $2))}); }
          ;

atom_sugar : atom_call TFN funbody { $1->args->push_back(new NBexprLambda(@$, $3)); $$ = WRAP_ATOM($1); }
           | atom_call block { $1->args->push_back(new NBexprLambda(@$, 
                new NFunBody(@$, new std::vector<NParam*>{}, $2))); $$ = WRAP_ATOM($1); }
           ;

/* Desambiguification :
To desambiguify syntactic sugar notation we just put them in their own derived symbols */

expr : block { $$ = WRAP_EXPR($1); }
     | bexpr { $$ = $1; }
     ;

non_empty_expr_list_comma : expr { $$ = new std::vector<NExpr>{*$1}; }
                          | non_empty_expr_list_comma TCOMMA expr { $1->push_back(*$3); $$ = $1; }
                          ;

expr_list_comma : /* blank */ { $$ = new std::vector<NExpr>{}; }
                 | non_empty_expr_list_comma
                 ;

bexpr : bexpr_op
      | TIF bexpr TTHEN expr elif_list { $5->condition = *$2; $5->thenExpr = *$4; $$ = WRAP_EXPR($5); }
      | TIF bexpr TTHEN expr elif_list TELSE expr { $5->condition = *$2; $5->thenExpr = *$4; setLastExpr($5, *$7); $$ = WRAP_EXPR($5); }
      | TFN funbody { $$ = WRAP_EXPR(new NBexprLambda(@$, $2)); }
      | TRETURN expr { $$ = WRAP_EXPR(new NBexprReturn(@$, *$2)); }
      | TIF bexpr TRETURN expr { $$ = WRAP_EXPR(new NBexprIf(@$, *$2, new NBexprReturn(@$, *$4))); }
      | TIDENTIFIER TCOLONEQ bexpr { $$ = WRAP_EXPR(new NBexprAssign(@$, $1, *$3)); }
      ;

bexpr_op : atom { $$ = WRAP_EXPR(new NBAtom(@$, *$1)); }   
      | TTILDE bexpr { $$ = WRAP_EXPR(new NBexprInfix(@$, $1, *$2)); }
      | TEXCL bexpr { $$ = WRAP_EXPR(new NBexprInfix(@$, $1, *$2)); }                                         %prec PATOM
      | bexpr_op TCEQ bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TCNE bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TCLE bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TCLT bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TCGE bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TCGT bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TADD bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TSUB bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TMUL bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TDIV bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TMOD bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TINC bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TAND bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      | bexpr_op TOR  bexpr_op { $$ = WRAP_EXPR(new NBexprBinOP(@$, *$1, $2, *$3)); }
      ;

elif_list : /* blank */ { $$ = new NBexprIf(@$, std::nullopt, std::nullopt, std::nullopt); }
          | elif_list TELIF bexpr TTHEN expr {$1->elseExpr = static_cast<NExpr>(new NBexprIf(@$, *$3, *$5, $1->elseExpr)); $$ = $1; }
          ;

block : TLBRACE block_content_last TRBRACE { $$ = ($2->has_value()) ? $2->value() : new NBlock(@$); }
      ;

bexpr_maybe : /* blank */ { $$ = new std::optional<NExpr>(std::nullopt); }
            | bexpr { $$ = new std::optional<NExpr>(*$1); }
            ;

block_content_last : block_content { $$ = $1; }
                   | bexpr_maybe { $$ = ($1->has_value()) ? new std::optional<NBlock*>(new NBlock(@$, new std::vector<NStmt>{}, $1->value())) : new std::optional<NBlock*>(std::nullopt); }
                   ;
                    
block_content : stmt TSEMICOLON block_content_last  
    { 
        if ($1->has_value()) 
        { 
            if ($3->has_value()) 
            {
                ($3->value()->stmts)->insert(($3->value()->stmts)->begin(), $1->value());
                $$ = $3;
            }
            else 
            {
                if (!$1->has_value() || !std::holds_alternative<NStmtBexpr*>($1->value())) // note that this specific error should not really happen... its for debugging purposes
                    yyerror("Internal parsing error : malformed block, last statement of block is not an expression");
                NStmtBexpr* nretExpr = std::get<NStmtBexpr*>($1->value());
                
                $$ = new std::optional<NBlock*>(new NBlock(@$, new std::vector<NStmt>{}, nretExpr->expr));
            } 
        } 
        else { $$ = $3; } 
    }
              ;


stmt : bexpr_maybe { $$ = ($1->has_value()) ? new std::optional<NStmt>(NStmt(new NStmtBexpr(@$, $1->value()))) : new std::optional<NStmt>(std::nullopt); }
     | TVAL TIDENTIFIER TEQUAL expr { $$ = new std::optional<NStmt>(NStmt(new NStmtVal(@$, $2, *$4))); }
     | TVAR TIDENTIFIER TCOLONEQ expr { $$ = new std::optional<NStmt>(NStmt(new NStmtVar(@$, $2, *$4))); }
     ;


%%
