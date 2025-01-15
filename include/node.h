#pragma once
#include <vector>
#include <string>
#include <optional>
#include "type.h"
#include "effect.h"
#include "error.h"
// Base Node

#define variantToString(v) std::visit([](auto* n) { return n->operator std::string(); }, v)

// Debug print
template <typename ...Ts>
std::string vecToString(std::vector<std::variant<Ts...>>* lst)
{   
    if (!lst) return "()";
    
    std::string ret = "(";
    long s = lst->size();
    for (long i = 0; i < s; i++)
    {
        ret += variantToString(lst->at(i));
        if (i != s - 1) ret += ", ";
    }
    return ret + ")";
}

// Debug print
template <typename T>
std::string vecToString(std::vector<T>* lst)
{   
    if (!lst) return "()";
    
    std::string ret = "(";
    long s = lst->size();
    for (long i = 0; i < s; i++)
    {
        ret += lst->at(i)->operator std::string();
        if (i != s - 1) ret += ", ";
    }
    return ret + ")";
}

///////////////
//   Basic   //
///////////////

// Forward declarations
//base
class NFunBody;
class NParam;

// type
class NBasicType;
class NTemplateType;
class NReturnType;
class NFunType;
using NType = std::variant<NBasicType*, NTemplateType*, NReturnType*, NFunType*>;

// expr/bexpr
class NBlock;
class NBexprInfix;
class NBexprBinOP;
class NBexprAssign;
class NBexprIf;
class NBexprLambda;
class NBexprReturn;
class NBAtom;
using NExpr = std::variant<NBAtom*, NBlock*, NBexprInfix*, NBexprBinOP*, NBexprAssign*, NBexprIf*, NBexprLambda*, NBexprReturn*>;

// stmt
class NStmtBexpr;
class NStmtVal;
class NStmtVar;
using NStmt = std::variant<NStmtBexpr*, NStmtVal*, NStmtVar*>;

// atom
class NAtomTrue;
class NAtomFalse;
class NAtomInt;
class NAtomStr;
class NAtomIdent;
class NAtomNil;
class NAtomCall;
class NAtomExpr;
class NAtomList;
using NAtom = std::variant<NAtomTrue*, NAtomFalse*, NAtomInt*, NAtomStr*, NAtomIdent*, NAtomNil*, NAtomCall*, NAtomExpr*, NAtomList*>;

class NDecl {
public:
    YYLTYPE loc;
    EffectType t;
    
    std::string* name;
    NFunBody* body;
    NDecl(YYLTYPE loc, std::string* name, NFunBody* body) : loc(loc), name(name), body(body) { }

    operator std::string() const;
};

class NFunBody {
public:
    YYLTYPE loc;
    EffectType t;

    std::vector<NParam*>* params;
    NExpr bodyExpr;
    NReturnType* retType;
    NFunBody(YYLTYPE loc, std::vector<NParam*>* params, NExpr bodyExpr, NReturnType* retType) 
        : loc(loc), params(params), bodyExpr(bodyExpr), retType(retType) { }
    NFunBody(YYLTYPE loc, std::vector<NParam*>* params, NExpr bodyExpr) 
        : loc(loc), params(params), bodyExpr(bodyExpr), retType(nullptr) { }

    operator std::string() const;
};

class NParam {
public:
    YYLTYPE loc;
    EffectType t;

    std::string* name;
    NType type;
    NParam(YYLTYPE loc, std::string* name, NType type) : loc(loc), name(name), type(type) { }

    operator std::string() const;
};

///////////////
//   Types   //
///////////////

class NBasicType {
public:
    YYLTYPE loc;
    EffectType t;

    std::string* name;
    NBasicType(YYLTYPE loc, std::string* name) : loc(loc), name(name) { }

    operator std::string() const;
};

class NTemplateType {
public:
    YYLTYPE loc;
    EffectType t;

    std::string* name;
    NType templat; // templat is reserved in C++ :(
    NTemplateType(YYLTYPE loc, std::string* name, NType templat) : loc(loc), name(name), templat(templat) { }

    operator std::string() const;
};

class NReturnType {
public:
    YYLTYPE loc;
    EffectType t;

    std::vector<std::string*>* effects;
    NType type;

    NReturnType(YYLTYPE loc, NType type) : loc(loc), type(type), effects(new std::vector<std::string*>()) { }
    NReturnType(YYLTYPE loc, NType type, std::vector<std::string*>* effects) : loc(loc), type(type), effects(effects) { }
    
    operator std::string() const;
};

class NFunType {
public:
    YYLTYPE loc;
    EffectType t;

    std::vector<NType>* argsType;
    NReturnType* retType;
    NFunType(YYLTYPE loc, std::vector<NType>* argsType, NReturnType* retType) : loc(loc), argsType(argsType), retType(retType) { }

    operator std::string() const;
};

///////////////
//   Expr    //
///////////////

class NBlock {
public:
    YYLTYPE loc;
    EffectType t;
    
    std::vector<NStmt>* stmts;
    std::optional<NExpr> retExpr;
    NBlock(YYLTYPE loc, std::vector<NStmt>* stmts, NExpr retExpr) : loc(loc), stmts(stmts), retExpr(retExpr) { }
    NBlock(YYLTYPE loc) : loc(loc), stmts{}, retExpr{std::nullopt} { }
    operator std::string() const;};

class NBAtom {
public:
    YYLTYPE loc;
    EffectType t;
    
    NAtom atom;
    NBAtom(YYLTYPE loc, NAtom atom) :  loc(loc), atom(atom) { }
    operator std::string() const;
};

class NStmtBexpr {
public:
    YYLTYPE loc;
    EffectType t;
  
    NExpr expr;
    NStmtBexpr(YYLTYPE loc, NExpr expr) : loc(loc), expr(expr) { }

    operator std::string() const;
};

class NStmtVal {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::string* name;
    NExpr expr;
    NStmtVal(YYLTYPE loc, std::string* name, NExpr expr) : loc(loc), name(name), expr(expr) { }

    operator std::string() const;
};

class NStmtVar {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::string* name;
    NExpr expr;
    NStmtVar(YYLTYPE loc, std::string* name, NExpr expr) : loc(loc), name(name), expr(expr) { }

    operator std::string() const;
};

///////////////
//   Bexpr   //
///////////////

class NBexprInfix {
public:
    YYLTYPE loc;
    EffectType t;
  
    int op;
    NExpr expr;
    NBexprInfix(YYLTYPE loc, int op, NExpr expr) : loc(loc), op(op), expr(expr) { }

    operator std::string() const;
};

class NBexprBinOP {
public:
    YYLTYPE loc;
    EffectType t;
  
    NExpr left;
    int op;
    NExpr right;
    NBexprBinOP(YYLTYPE loc, NExpr left, int op, NExpr right) : loc(loc), left(left), op(op), right(right) { }

    operator std::string() const;
};

class NBexprAssign {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::string* name;
    NExpr expr;
    NBexprAssign(YYLTYPE loc, std::string* name, NExpr expr) : loc(loc), name(name), expr(expr) { }

    operator std::string() const;
};

class NBexprIf {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::optional<NExpr> condition;
    std::optional<NExpr> thenExpr;
    std::optional<NExpr> elseExpr;

    NBexprIf(YYLTYPE loc, NExpr condition, NExpr thenExpr, NExpr elseExpr) 
        : loc(loc), condition(condition), thenExpr(thenExpr), elseExpr(elseExpr) { }
    NBexprIf(YYLTYPE loc, std::optional<NExpr> condition, std::optional<NExpr> thenExpr, std::optional<NExpr> elseExpr) 
        : loc(loc), condition(condition), thenExpr(thenExpr), elseExpr(elseExpr) { }
    NBexprIf(YYLTYPE loc, NExpr condition, NExpr thenExpr) 
        : loc(loc), condition(condition), thenExpr(thenExpr), elseExpr{std::nullopt} { }

    operator std::string() const;
};

class NBexprLambda {
public:
    YYLTYPE loc;
    EffectType t;
  
    NFunBody* body;

    NBexprLambda(YYLTYPE loc, NFunBody* body) : loc(loc), body(body) { }

    operator std::string() const;
};

class NBexprReturn {
public:
    YYLTYPE loc;
    EffectType t;
  
    NExpr expr;

    NBexprReturn(YYLTYPE loc, NExpr expr) : loc(loc), expr(expr) { }

    operator std::string() const;
};

///////////////
//   Atom    //
///////////////

class NAtomTrue {
public:
    YYLTYPE loc;
    EffectType t;
  
    NAtomTrue(YYLTYPE loc) : loc(loc) { }

    operator std::string() const;
};

class NAtomFalse {
public:
    YYLTYPE loc;
    EffectType t;
  
    NAtomFalse(YYLTYPE loc) : loc(loc) { }

    operator std::string() const;
};

class NAtomInt {
public:
    YYLTYPE loc;
    EffectType t;
  
    long val;
    NAtomInt(YYLTYPE loc, long val) : loc(loc), val(val) { }

    operator std::string() const;
};

class NAtomStr {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::string* val;
    NAtomStr(YYLTYPE loc, std::string* val) : loc(loc), val(val) { }

    operator std::string() const;
};

class NAtomIdent {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::string* val;
    NAtomIdent(YYLTYPE loc, std::string* val) : loc(loc), val(val) { }

    operator std::string() const;
};

class NAtomNil {
public:
    YYLTYPE loc;
    EffectType t;
  
    NAtomNil(YYLTYPE loc) : loc(loc) { }

    operator std::string() const;
};

class NAtomCall {
public:
    YYLTYPE loc;
    EffectType t;
  
    NAtom fun;
    std::vector<NExpr>* args;
    NAtomCall(YYLTYPE loc, NAtom fun, std::vector<NExpr>* args) : loc(loc), fun(fun), args(args) { }

    operator std::string() const;
};

class NAtomExpr {
public:
    YYLTYPE loc;
    EffectType t;
  
    NExpr expr;
    NAtomExpr(YYLTYPE loc, NExpr expr) : loc(loc), expr(expr) { }

    operator std::string() const;
};

class NAtomList {
public:
    YYLTYPE loc;
    EffectType t;
  
    std::vector<NExpr>* elts;
    NAtomList(YYLTYPE loc, std::vector<NExpr>* elts) : loc(loc), elts(elts) { }

    operator std::string() const;
};