#include "node.h"
#include <assert.h>

template <>
std::string vecToString(std::vector<std::string*>* lst)
{
    if (!lst) return "()";
    
    std::string ret = "(";
    long s = lst->size();
    for (long i = 0; i < s; i++)
    {
        ret += *lst->at(i);
        if (i != s - 1) ret += ", ";
    }
    return ret + ")";
}

NDecl::operator std::string() const
{
    return "Decl" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ", body: " + body->operator std::string() + ")";
}

NFunBody::operator std::string() const
{
    std::string ret = "FunBody" + locToString(loc) + "TYPE : " + toString(t) + "(params: ";
    ret += vecToString(params);
    ret += ", ret type: " + (retType ? retType->operator std::string(): "()") + ", body: " + variantToString(bodyExpr) + ")";
    return ret;
}



NParam::operator std::string() const
{
    return "Param" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ", type: " + variantToString(type) + ")";
}

NBasicType::operator std::string() const
{
    return "BasicType" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ")";
}

NTemplateType::operator std::string() const
{
    return "TemplateType" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ", template: " + variantToString(templat) + ")";
}

NBAtom::operator std::string() const
{
    return "Atom" + locToString(loc) + "TYPE : " + toString(t) + "(atom: " + variantToString(atom) + ")";
}

NReturnType::operator std::string() const
{
    std::string ret = "ReturnType" + locToString(loc) + "TYPE : " + toString(t) + "(type: " + variantToString(type) + ", effects: ";
    return ret + vecToString(effects) + ")";
}

NFunType::operator std::string() const
{
    std::string ret = "FunType" + locToString(loc) + "TYPE : " + toString(t) + "(argstype: " + vecToString(argsType);
    return ret + ", returntype: " + retType->operator std::string() + ")";
}

NBlock::operator std::string() const
{
    std::string ret = "Block" + locToString(loc) + "TYPE : " + toString(t) + "(stmts: " + vecToString(stmts);
    return ret + ", returnexpr: " + (retExpr.has_value() ? variantToString(retExpr.value()) : std::string("()")) + ")";
}

NStmtBexpr::operator std::string() const
{
    return "StmtBexpr" + locToString(loc) + "TYPE : " + toString(t) + "(expr: " + variantToString(expr) + ")";
}

NStmtVal::operator std::string() const
{
    return "StmtVal" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ", expr: " + variantToString(expr) + ")";
}

NStmtVar::operator std::string() const
{
    return "StmtVar" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ", expr: " + variantToString(expr) + ")";
}

NBexprInfix::operator std::string() const
{
    return "BexprInfix" + locToString(loc) + "TYPE : " + toString(t) + "(op: " + std::to_string(op) + ", expr: " + variantToString(expr) + ")";
}

NBexprBinOP::operator std::string() const
{
    return "BexprBinOP" + locToString(loc) + "TYPE : " + toString(t) + "(left: " + variantToString(left) + ", op: " + std::to_string(op) + ", right: " + variantToString(right) + ")";
}


NBexprAssign::operator std::string() const
{
    return "BexprAssign" + locToString(loc) + "TYPE : " + toString(t) + "(name: " + *name + ", expr: " + variantToString(expr) + ")";
}

NBexprIf::operator std::string() const
{
    std::string ret = "";
    if (elseExpr.has_value())
        ret += ", elseExpr: " + variantToString(elseExpr.value());

    return "BexprIf" + locToString(loc) + "TYPE : " + toString(t) + "(condition: " + variantToString(condition.value())  + ", thenExpr: " + variantToString(thenExpr.value()) + ret + ")";
}

NBexprLambda::operator std::string() const
{
    return "BexprLambda" + locToString(loc) + "TYPE : " + toString(t) + "(body: " + body->operator std::string() + ")";
}


NBexprReturn::operator std::string() const
{
    return "BexprReturn" + locToString(loc) + "TYPE : " + toString(t) + "(expr: " + variantToString(expr) + ")";
}

NAtomTrue::operator std::string() const
{
    return "True";
}

NAtomFalse::operator std::string() const
{
    return "False";
}

NAtomInt::operator std::string() const
{
    return std::to_string(val);
}

NAtomStr::operator std::string() const
{
    return "\"" + *val + "\"";
}

NAtomIdent::operator std::string() const
{
    return "AtomIdent" + locToString(loc) + "TYPE : " + toString(t) + "(" + *val + ")";
}

NAtomNil::operator std::string() const
{
    return "AtomNil" + locToString(loc) + "TYPE : " + toString(t) + "()";
}

NAtomCall::operator std::string() const
{
    return "AtomCall" + locToString(loc) + "TYPE : " + toString(t) + "(fun: " + variantToString(fun) + ", args: " + vecToString(args) + ")";
}

NAtomExpr::operator std::string() const
{
    return "AtomExpr" + locToString(loc) + "TYPE : " + toString(t) + "(expr: " + variantToString(expr) + ")";
}

NAtomList::operator std::string() const
{
    return "AtomList" + locToString(loc) + "TYPE : " + toString(t) + "(elts: " + vecToString(elts) + ")";
}