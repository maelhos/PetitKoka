#include "effectVisitor.h"


effectVisitor::effectVisitor(std::vector<NDecl*>* root, std::map<std::pair<VStorage, std::string>, EffectType>& env) : root(root), env(env) {}

bool effectVisitor::unify(const EffectType& t1, const EffectType& t2)
{
    if (t1.effects == t2.effects && ((!t1.isWeak && !t2.isWeak) || t1.weak_id == t2.weak_id)  )
        return true;

    if (t1.isWeak)
    {
        fullpropag(t1, t2);
        return true;
    }

    if (t2.isWeak)
    {
        fullpropag(t2, t1);
        return true;
    }

    return false;
}


void effectVisitor::fullpropag(const EffectType& from, const EffectType& to)
{
    // we also update the current "partial EffectType" of the function being EffectTyped
    substEffect(env[current_decl], from, to);
    visit(root, from, to);
}

void effectVisitor::visit(std::vector<NDecl*>* node, const EffectType& from, const EffectType& to)
{
    for (auto &&decl : *node)
    {
        visit(decl->body, from, to);
        substEffect(decl->t, from, to);
    }
}

void effectVisitor::visit(NFunBody* node, const EffectType& from, const EffectType& to)
{
    for (auto &&param : *node->params)
        visit(param, from, to);

    visit(node->bodyExpr, from, to);

    if (node->retType)
        visit(node->retType, from, to);
    
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NParam* node, const EffectType& from, const EffectType& to)
{
    visit(node->type, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBasicType* node, const EffectType& from, const EffectType& to) {}
void effectVisitor::visit(NTemplateType* node, const EffectType& from, const EffectType& to) {}
void effectVisitor::visit(NReturnType* node, const EffectType& from, const EffectType& to) {}
void effectVisitor::visit(NFunType* node, const EffectType& from, const EffectType& to) {}

void effectVisitor::visit(NBlock* node, const EffectType& from, const EffectType& to)
{
    if (node->retExpr.has_value())
    {
        for (NStmt& stmt: *node->stmts)
            visit(stmt, from, to);
        visit(node->retExpr.value(), from, to);
    }
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBexprInfix* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBexprBinOP* node, const EffectType& from, const EffectType& to)
{
    visit(node->left, from, to);
    visit(node->right, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBexprAssign* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBexprIf* node, const EffectType& from, const EffectType& to)
{
    visit(node->condition.value(), from, to);
    visit(node->thenExpr.value(), from, to);
    if (node->elseExpr.has_value())
        visit(node->elseExpr.value(), from, to);
    
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBexprLambda* node, const EffectType& from, const EffectType& to)
{
    visit(node->body, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBexprReturn* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NBAtom* node, const EffectType& from, const EffectType& to)
{
    visit(node->atom, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NStmtBexpr* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
}

void effectVisitor::visit(NStmtVal* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
}

void effectVisitor::visit(NStmtVar* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomTrue* node, const EffectType& from, const EffectType& to)
{
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomFalse* node, const EffectType& from, const EffectType& to)
{
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomInt* node, const EffectType& from, const EffectType& to)
{
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomStr* node, const EffectType& from, const EffectType& to)
{
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomNil* node, const EffectType& from, const EffectType& to)
{
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomIdent* node, const EffectType& from, const EffectType& to)
{
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomExpr* node, const EffectType& from, const EffectType& to)
{
    visit(node->expr, from, to);
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomList* node, const EffectType& from, const EffectType& to)
{
    if (node->elts->size())
    {
        visit(node->elts->at(0), from, to);
        for (size_t i = 1; i < node->elts->size(); i++)
            visit(node->elts->at(i), from, to);
    }
    substEffect(node->t, from, to);
}

void effectVisitor::visit(NAtomCall* node, const EffectType& from, const EffectType& to)
{
    visit(node->fun, from, to);
    
    for (size_t i = 0; i < node->args->size(); i++)
        visit(node->args->at(i), from, to);

    substEffect(node->t, from, to);
}
