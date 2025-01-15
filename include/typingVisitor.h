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
#include "propagVisitor.h"
#include "effectVisitor.h"

class typingVisitor
{
    std::vector<NDecl*>* root;

    propagVisitor propag;
    effectVisitor effecto;
public:
    std::map<std::pair<VStorage, std::string>, EffectType> env;

    typingVisitor(std::vector<NDecl*>* root);
    ~typingVisitor() { }

    // the choice of making some of them return void and others return Type
    // is definetly not pretty but quite practical
    // it could be avoided but a pain to deal with for the variant
    EffectType visit(std::vector<NDecl*>* node);
    EffectType visit(NFunBody* node);
    EffectType visit(NParam* node);
    EffectType visit(NBasicType* node);
    EffectType visit(NTemplateType* node);
    EffectType visit(NReturnType* node);
    EffectType visit(NFunType* node);

    EffectType visit(NBlock* node);
    EffectType visit(NBexprInfix* node);
    EffectType visit(NBexprBinOP* node);
    EffectType visit(NBexprAssign* node);
    EffectType visit(NBexprIf* node);
    EffectType visit(NBexprLambda* node);
    EffectType visit(NBexprReturn* node);
    EffectType visit(NBAtom* node);
    
    EffectType visit(NStmtBexpr* node);
    EffectType visit(NStmtVal* node);
    EffectType visit(NStmtVar* node);

    EffectType visit(NAtomTrue* node);
    EffectType visit(NAtomFalse* node);
    EffectType visit(NAtomInt* node);
    EffectType visit(NAtomStr* node);
    EffectType visit(NAtomIdent* node);
    EffectType visit(NAtomNil* node);
    EffectType visit(NAtomCall* node);
    EffectType visit(NAtomExpr* node);
    EffectType visit(NAtomList* node);

    //Type handleSpeciaFun(NAtomCall* node, TSpecFun* ft);
    
    // variants
    template <typename ...Ts>
    EffectType visit(std::variant<Ts...> node)
    {
        return std::visit([&](auto* n) { return visit(n); }, node);
    }

};