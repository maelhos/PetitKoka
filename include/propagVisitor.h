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
#include "effectVisitor.h"

class propagVisitor
{
    std::vector<NDecl*>* root;
    std::map<std::pair<VStorage, std::string>, EffectType>& env;
public:
    std::pair<VStorage, std::string> current_decl;
    propagVisitor(std::vector<NDecl*>* root, std::map<std::pair<VStorage, std::string>, EffectType>& env);
    ~propagVisitor() { }

    void visit(std::vector<NDecl*>* node, const Type& from, const Type& to);
    void visit(NFunBody* node, const Type& from, const Type& to);
    void visit(NParam* node, const Type& from, const Type& to);
    void visit(NBasicType* node, const Type& from, const Type& to);
    void visit(NTemplateType* node, const Type& from, const Type& to);
    void visit(NReturnType* node, const Type& from, const Type& to);
    void visit(NFunType* node, const Type& from, const Type& to);

    void visit(NBlock* node, const Type& from, const Type& to);
    void visit(NBexprInfix* node, const Type& from, const Type& to);
    void visit(NBexprBinOP* node, const Type& from, const Type& to);
    void visit(NBexprAssign* node, const Type& from, const Type& to);
    void visit(NBexprIf* node, const Type& from, const Type& to);
    void visit(NBexprLambda* node, const Type& from, const Type& to);
    void visit(NBexprReturn* node, const Type& from, const Type& to);
    void visit(NBAtom* node, const Type& from, const Type& to);
    
    void visit(NStmtBexpr* node, const Type& from, const Type& to);
    void visit(NStmtVal* node, const Type& from, const Type& to);
    void visit(NStmtVar* node, const Type& from, const Type& to);

    void visit(NAtomTrue* node, const Type& from, const Type& to);
    void visit(NAtomFalse* node, const Type& from, const Type& to);
    void visit(NAtomInt* node, const Type& from, const Type& to);
    void visit(NAtomStr* node, const Type& from, const Type& to);
    void visit(NAtomIdent* node, const Type& from, const Type& to);
    void visit(NAtomNil* node, const Type& from, const Type& to);
    void visit(NAtomCall* node, const Type& from, const Type& to);
    void visit(NAtomExpr* node, const Type& from, const Type& to);
    void visit(NAtomList* node, const Type& from, const Type& to);

    // variants
    template <typename ...Ts>
    inline void visit(std::variant<Ts...> node, const Type& from, const Type& to)
    {
        std::visit([&](auto* n) { visit(n, from, to); }, node);
    }

    void fullpropag(const Type& from, const Type& to);
    bool unify(const Type& t1, const Type& t2);

    inline bool unify(const EffectType& t1, const EffectType& t2)
        { return unify(*t1, *t2); }

    inline bool unify_conv(Type& t1, Type t2)
        { return unify(t1, t2); }

    inline bool unify_conv(EffectType& t1, Type t2)
        { return unify(*t1, t2); }
};