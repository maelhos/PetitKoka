#include "effect.h"
#include <cassert>

std::string effectToString(const Effect& s)
{
    if (s == Effect::EConsole) return "console";
    else if (s == Effect::EDiv) return "div";
    else if (s == Effect::ETotal) return "total";


    std::cout << "Internal error : effect " << long(s) << " does not have a string representation" << std::endl;
    exit(2);

    return "ohno";
}


Effect effectFromString(const std::string& s, const YYLTYPE& loc)
{
    if (s == "div") return Effect::EDiv;
    else if (s == "console") return Effect::EConsole;

    typingError("Unknown effect : \"" + s + "\"", loc);

    return Effect::EDiv; // just to please the compiler... typing error interupts the program
}

EffectType::EffectType() : elt{}, effects{}, isWeak(true), weak_id(weak_eff_ctr++) { }
EffectType::EffectType(Type elt) : elt(elt), effects{}, isWeak(true), weak_id(weak_eff_ctr++) { }
EffectType::EffectType(Type elt, ESet effects) : elt(elt), effects(effects), isWeak(false), weak_id(-1)  { }
EffectType::EffectType(Type elt, ESet effects, bool isWeak, long id) : elt(elt), effects(effects), isWeak(isWeak), weak_id(id)  { }


EffectType::operator std::string() const
{
    std::string ret = toString(elt) + " : <";
    if (isWeak) return ret + "weak_eff_" + std::to_string(weak_id) + ">";

    bool nfst = false;
    for (auto&& elt : effects) 
    {
        if (nfst) ret += ", ";
        else nfst = true;
        ret += effectToString(elt);
    }
    return ret + ">"; 
}

void EffectType::addEffects(const ESet& s)
    { effects = setUni(effects, s); /*if (s.size()) isWeak = false; */ }


bool EffectType::isSubst(const EffectType& et) const
    { return isSubset(effects, et.effects); }

bool EffectType::isSubst(const ESet& et) const
    { return isSubset(effects, et); }

EffectType wrap(Type t) { return EffectType(t); }
ESet setUni() { return ESet{}; }

void __substEffect(Type& T1, const EffectType& from, const EffectType& to)
{
    if (std::holds_alternative<TList*>(T1))
        __substEffect(std::get<TList*>(T1)->elt, from, to);

    if (std::holds_alternative<TMaybe*>(T1))
        __substEffect(std::get<TMaybe*>(T1)->elt, from, to);

    if (std::holds_alternative<TFun*>(T1))
    {
        TFun* f = std::get<TFun*>(T1);
        for (auto&& e: f->elts)
            __substEffect(e, from, to);
        substEffect(*f->ret, from, to);
    }
}

void substEffect(EffectType& T1, const EffectType& from, const EffectType& to)
{
    if (!from.isWeak) return; // we only support this case

    if (T1.weak_id == from.weak_id) T1 = EffectType(*T1, to.effects, to.isWeak, to.weak_id);

    if (std::holds_alternative<TList*>(*T1))
        __substEffect(std::get<TList*>(*T1)->elt, from, to);

    if (std::holds_alternative<TMaybe*>(*T1))
        __substEffect(std::get<TMaybe*>(*T1)->elt, from, to);

    if (std::holds_alternative<TFun*>(*T1))
    {
        TFun* f = std::get<TFun*>(*T1);
        for (auto&& e: f->elts)
            __substEffect(e, from, to);
        substEffect(*f->ret, from, to);
    }
}
