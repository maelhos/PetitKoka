#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include "type.h"
#include "node.h"
#include "error.h"
#include "effect.h"
#include "parser.hpp"

enum class VStorage 
{
    Vvar,
    Vval, 
    Vfun
};

class effectVisitor
{
    std::vector<NDecl*>* root;
    std::map<std::pair<VStorage, std::string>, EffectType>& env;
public:
    std::pair<VStorage, std::string> current_decl;
    effectVisitor(std::vector<NDecl*>* root, std::map<std::pair<VStorage, std::string>, EffectType>& env);
    ~effectVisitor() { }

    void visit(std::vector<NDecl*>* node, const EffectType& from, const EffectType& to);
    void visit(NFunBody* node, const EffectType& from, const EffectType& to);
    void visit(NParam* node, const EffectType& from, const EffectType& to);
    void visit(NBasicType* node, const EffectType& from, const EffectType& to);
    void visit(NTemplateType* node, const EffectType& from, const EffectType& to);
    void visit(NReturnType* node, const EffectType& from, const EffectType& to);
    void visit(NFunType* node, const EffectType& from, const EffectType& to);

    void visit(NBlock* node, const EffectType& from, const EffectType& to);
    void visit(NBexprInfix* node, const EffectType& from, const EffectType& to);
    void visit(NBexprBinOP* node, const EffectType& from, const EffectType& to);
    void visit(NBexprAssign* node, const EffectType& from, const EffectType& to);
    void visit(NBexprIf* node, const EffectType& from, const EffectType& to);
    void visit(NBexprLambda* node, const EffectType& from, const EffectType& to);
    void visit(NBexprReturn* node, const EffectType& from, const EffectType& to);
    void visit(NBAtom* node, const EffectType& from, const EffectType& to);
    
    void visit(NStmtBexpr* node, const EffectType& from, const EffectType& to);
    void visit(NStmtVal* node, const EffectType& from, const EffectType& to);
    void visit(NStmtVar* node, const EffectType& from, const EffectType& to);

    void visit(NAtomTrue* node, const EffectType& from, const EffectType& to);
    void visit(NAtomFalse* node, const EffectType& from, const EffectType& to);
    void visit(NAtomInt* node, const EffectType& from, const EffectType& to);
    void visit(NAtomStr* node, const EffectType& from, const EffectType& to);
    void visit(NAtomIdent* node, const EffectType& from, const EffectType& to);
    void visit(NAtomNil* node, const EffectType& from, const EffectType& to);
    void visit(NAtomCall* node, const EffectType& from, const EffectType& to);
    void visit(NAtomExpr* node, const EffectType& from, const EffectType& to);
    void visit(NAtomList* node, const EffectType& from, const EffectType& to);

    // variants
    template <typename ...Ts>
    inline void visit(std::variant<Ts...> node, const EffectType& from, const EffectType& to)
    {
        std::visit([&](auto* n) { visit(n, from, to); }, node);
    }

    void fullpropag(const EffectType& from, const EffectType& to);
    bool unify(const EffectType& t1, const EffectType& t2);

};