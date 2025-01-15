#include "type.h"
#include "effect.h"

Type copy(const Type& t)
{

    if (std::holds_alternative<TList*>(t))
        return new TList(copy(std::get<TList*>(t)->elt));

    if (std::holds_alternative<TMaybe*>(t))
        return new TList(copy(std::get<TMaybe*>(t)->elt));

    if (std::holds_alternative<TReturn*>(t))
    {
        TReturn* re = std::get<TReturn*>(t);
        Type nt = copy(re->elt);
        return new TReturn(nt, re->id);
    }

    if (std::holds_alternative<TVariant*>(t))
    {
        TVariant* va = std::get<TVariant*>(t);
        return new TVariant(va->elts, va->id);
    }

    if (std::holds_alternative<TFun*>(t))
    {
        TFun* tf = std::get<TFun*>(t);
        std::vector<Type> elts{};
        for (auto&& elt : tf->elts)
            elts.push_back(copy(elt));

        return new TFun(elts, new EffectType(copy(**tf->ret), tf->ret->effects, tf->ret->isWeak, tf->ret->weak_id));
    }

    if (std::holds_alternative<TWeak*>(t))
        return new TWeak(std::get<TWeak*>(t)->id);

    if (std::holds_alternative<TUnit*>(t)) return new TUnit();
    if (std::holds_alternative<TBool*>(t)) return new TBool();
    if (std::holds_alternative<TInt*>(t)) return new TInt();
    if (std::holds_alternative<TString*>(t)) return new TString();

    typingError("Internal error : copy type not found");
    return Type{};
}

bool operator==(const Type& lhs, const Type& rhs)
{
    if (lhs.index() != rhs.index()) return false;

    if (std::holds_alternative<TWeak*>(lhs))
        return std::get<TWeak*>(lhs)->id == std::get<TWeak*>(rhs)->id;

    if (std::holds_alternative<TReturn*>(lhs))
        return std::get<TReturn*>(lhs)->id == std::get<TReturn*>(rhs)->id;

    if (std::holds_alternative<TList*>(lhs))
    {
        TList* lhsL = std::get<TList*>(lhs);
        TList* rhsL = std::get<TList*>(rhs);

        return lhsL->elt == rhsL->elt;
    }

    if (std::holds_alternative<TMaybe*>(lhs))
        return std::get<TMaybe*>(lhs)->elt == std::get<TMaybe*>(rhs)->elt;

    if (std::holds_alternative<TVariant*>(lhs))
        return std::get<TVariant*>(lhs)->id == std::get<TVariant*>(rhs)->id;

    if (std::holds_alternative<TFun*>(lhs))
    {
        TFun* lhsL = std::get<TFun*>(lhs);
        TFun* rhsL = std::get<TFun*>(rhs);

        if (lhsL->elts.size() != rhsL->elts.size()) return false;
        for (size_t i = 0; i < lhsL->elts.size(); i++)
        {
            if (lhsL->elts[i] != rhsL->elts[i]) 
                return false;
        }
        if (lhsL->ret != rhsL->ret)
            return false;
    }

    return true;
}

bool operator!=(const Type& lhs, const Type& rhs)
{
    return !(lhs == rhs);
}


TUnit::operator std::string() const
{
    return "unit";
}

TBool::operator std::string() const
{
    return "bool";
}

TInt::operator std::string() const
{
    return "int";
}

TString::operator std::string() const
{
    return "string";
}

TWeak::operator std::string() const
{
    return "weak_" + std::to_string(id);
}

TList::operator std::string() const
{
    return "list<" + toString(elt) + ">";
}

TMaybe::operator std::string() const
{
    return "maybe<" + toString(elt) + ">";
}

TReturn::operator std::string() const
{
    return "return_" + std::to_string(id) + "<" + toString(elt) + ">";
}

TFun::operator std::string() const
{
    std::string ret_str{"("};
    for (size_t i = 0; i < elts.size(); i++)
    {
        ret_str += toString(elts[i]);
        if (i != elts.size() - 1) ret_str += ", ";
    }
    return ret_str + ") -> " + ret->operator std::string();
}

TVariant::operator std::string() const
{
    std::string rep("variant<");
    bool nfst = false;
    for (auto it = elts.begin(); it != elts.end(); ++it) 
    {
        if (nfst) rep += ", ";
        else nfst = true;
        rep += toString(*it);
    }

    return rep + ">";
}

Type makeWeakFunction(int n)
{
    std::vector<Type> args{};
    for (int i = 0; i < n; i++)
        args.push_back(new TWeak());
    return new TFun(args, new EffectType(new TWeak()));
}

void subst(Type& T1, const Type& from, const Type& to)
{
    if (T1 == from) T1 = to;

    if (std::holds_alternative<TList*>(T1))
        subst(std::get<TList*>(T1)->elt, from, to);

    if (std::holds_alternative<TMaybe*>(T1))
        subst(std::get<TMaybe*>(T1)->elt, from, to);

    if (std::holds_alternative<TFun*>(T1))
    {
        TFun* f = std::get<TFun*>(T1);
        for (auto&& e: f->elts)
            subst(e, from, to);
        subst(*f->ret, from, to);
    }
}