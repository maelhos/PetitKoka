#include "propagVisitor.h"


propagVisitor::propagVisitor(std::vector<NDecl*>* root, std::map<std::pair<VStorage, std::string>, EffectType>& env) : root(root), env(env) {}

bool propagVisitor::unify(const Type& t1, const Type& t2)
{
    if (t1 == t2)
        return true;

    if (std::holds_alternative<TWeak*>(t1))
    {
        fullpropag(t1, t2);
        return true;
    }

    if (std::holds_alternative<TWeak*>(t2))
    {
        fullpropag(t2, t1);
        return true;
    }

    if (std::holds_alternative<TReturn*>(t1) && std::holds_alternative<TReturn*>(t2))
        return unify(std::get<TReturn*>(t1)->elt, std::get<TReturn*>(t2)->elt);

    if (std::holds_alternative<TReturn*>(t1) && std::holds_alternative<TUnit*>(t2))
    {
        fullpropag(t1, t2);
        return true;
    }
    
    if (std::holds_alternative<TReturn*>(t2) && std::holds_alternative<TUnit*>(t1))
    {
        fullpropag(t2, t1);
        return true;
    }

    if (std::holds_alternative<TReturn*>(t1))
    {
        bool u = std::get<TReturn*>(t1)->elt == t2;
        if (u) fullpropag(t1, t2);
        return u;
    }

    if (std::holds_alternative<TReturn*>(t2))
    {
        bool u = std::get<TReturn*>(t2)->elt == t1;
        if (u) fullpropag(t2, t1);
        return u;
    }

    if (std::holds_alternative<TList*>(t1) && std::holds_alternative<TList*>(t2))
    {
        TList* t1L = std::get<TList*>(t1);
        TList* t2L = std::get<TList*>(t2);

        return unify(t1L->elt, t2L->elt);
    }

    if (std::holds_alternative<TMaybe*>(t1) && std::holds_alternative<TMaybe*>(t2))
        return unify(std::get<TMaybe*>(t1)->elt, std::get<TMaybe*>(t2)->elt);

    if (std::holds_alternative<TFun*>(t1) && std::holds_alternative<TFun*>(t2))
    {
        TFun* t1L = std::get<TFun*>(t1);
        TFun* t2L = std::get<TFun*>(t2);

        if (t1L->elts.size() != t2L->elts.size()) return false;
        for (size_t i = 0; i < t1L->elts.size(); i++)
        {
            if (!unify(t1L->elts[i], t2L->elts[i]))
                return false;
        }

        bool b = !((t1L->ret->effects != t2L->ret->effects) && !(t1L->ret->isWeak || t2L->ret->isWeak));
        b &= unify(*t1L->ret, *t2L->ret);
        return b;
    }

    if (std::holds_alternative<TVariant*>(t1) && std::holds_alternative<TVariant*>(t2))
    {
        TSet& s1 = std::get<TVariant*>(t1)->elts;
        TSet& s2 = std::get<TVariant*>(t2)->elts;

        if (std::includes(s2.begin(), s2.end(), s1.begin(), s1.end())) // s1 subset of s2
        {
            fullpropag(t2, t1);
            return true;
        }
        else if (std::includes(s1.begin(), s1.end(), s2.begin(), s2.end())) // s2 subset of s1
        {
            fullpropag(t1, t2);
            return true;
        }
        return false;
    }

    if (std::holds_alternative<TVariant*>(t1))
    {
        std::optional<BasicType> bt2 = getBasic(t2);
        if (!bt2.has_value()) return false;
        if (std::get<TVariant*>(t1)->elts.count(bt2.value()))
        {
            fullpropag(t1, t2);
            return true;
        }
        return false;
    }

    if (std::holds_alternative<TVariant*>(t2))
    {
        std::optional<BasicType> bt1 = getBasic(t1);
        if (!bt1.has_value()) return false;

        if (std::get<TVariant*>(t2)->elts.count(bt1.value()))
        {
            fullpropag(t2, t1);
            return true;
        }
        return false;
    }

    return false;
}


void propagVisitor::fullpropag(const Type& from, const Type& to)
{
    // we also update the current "partial type" of the function being typed
    subst(env[current_decl], from, to);
    visit(root, from, to);
}

void propagVisitor::visit(std::vector<NDecl*>* node, const Type& from, const Type& to)
{
    for (auto &&decl : *node)
    {
        visit(decl->body, from, to);
        subst(decl->t, from, to);
    }
}

void propagVisitor::visit(NFunBody* node, const Type& from, const Type& to)
{
    for (auto &&param : *node->params)
        visit(param, from, to);

    visit(node->bodyExpr, from, to);

    if (node->retType)
        visit(node->retType, from, to);
    
    subst(node->t, from, to);
}

void propagVisitor::visit(NParam* node, const Type& from, const Type& to)
{
    visit(node->type, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NBasicType* node, const Type& from, const Type& to) {}
void propagVisitor::visit(NTemplateType* node, const Type& from, const Type& to) {}
void propagVisitor::visit(NReturnType* node, const Type& from, const Type& to) {}
void propagVisitor::visit(NFunType* node, const Type& from, const Type& to) {}

void propagVisitor::visit(NBlock* node, const Type& from, const Type& to)
{
    if (node->retExpr.has_value())
    {
        for (NStmt& stmt: *node->stmts)
            visit(stmt, from, to);
        visit(node->retExpr.value(), from, to);
    }
    subst(node->t, from, to);
}

void propagVisitor::visit(NBexprInfix* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NBexprBinOP* node, const Type& from, const Type& to)
{
    visit(node->left, from, to);
    visit(node->right, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NBexprAssign* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NBexprIf* node, const Type& from, const Type& to)
{
    visit(node->condition.value(), from, to);
    visit(node->thenExpr.value(), from, to);
    if (node->elseExpr.has_value())
        visit(node->elseExpr.value(), from, to);
    
    subst(node->t, from, to);
}

void propagVisitor::visit(NBexprLambda* node, const Type& from, const Type& to)
{
    visit(node->body, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NBexprReturn* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NBAtom* node, const Type& from, const Type& to)
{
    visit(node->atom, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NStmtBexpr* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
}

void propagVisitor::visit(NStmtVal* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
}

void propagVisitor::visit(NStmtVar* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomTrue* node, const Type& from, const Type& to)
{
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomFalse* node, const Type& from, const Type& to)
{
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomInt* node, const Type& from, const Type& to)
{
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomStr* node, const Type& from, const Type& to)
{
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomNil* node, const Type& from, const Type& to)
{
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomIdent* node, const Type& from, const Type& to)
{
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomExpr* node, const Type& from, const Type& to)
{
    visit(node->expr, from, to);
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomList* node, const Type& from, const Type& to)
{
    if (node->elts->size())
    {
        visit(node->elts->at(0), from, to);
        for (size_t i = 1; i < node->elts->size(); i++)
            visit(node->elts->at(i), from, to);
    }
    subst(node->t, from, to);
}

void propagVisitor::visit(NAtomCall* node, const Type& from, const Type& to)
{
    visit(node->fun, from, to);
    
    for (size_t i = 0; i < node->args->size(); i++)
        visit(node->args->at(i), from, to);

    subst(node->t, from, to);
}
