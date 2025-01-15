#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <variant>
#include <set>
#include <algorithm>
#include "error.h"
#include "type.h"

enum class Effect 
{
    EDiv, 
    EConsole,
    ETotal
};

using ESet = std::set<Effect>;

Effect effectFromString(const std::string& s, const YYLTYPE& loc);
std::string effectToString(const Effect& s);

inline bool isSubset(const ESet& A, const ESet& B)
{ return std::includes(B.begin(), B.end(), A.begin(), A.end()); } 

inline ESet setInter(const ESet& A, const ESet& B)
{
    ESet intersect;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(),std::inserter(intersect, intersect.begin()));
    return intersect;
}

inline ESet __setUni(const ESet& A, const ESet& B)
{
    ESet uni;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::inserter(uni, uni.begin()));
    return uni;
}

static int weak_eff_ctr = 1;
class EffectType
{
public:
    Type elt;
    ESet effects;
    bool isWeak;
    long weak_id;

    EffectType();
    EffectType(Type elt);
    EffectType(Type elt, ESet effects);
    EffectType(Type elt, ESet effects, bool isWeak, long id);

    bool isSubst(const EffectType& et) const;
    bool isSubst(const ESet& et) const;
    inline Type operator*() const { return elt; }

    void addEffects(const ESet& s);
    operator std::string() const;
};

inline std::string toString(const EffectType& v) 
{ return v.operator std::string(); }

ESet setUni();

template<typename... Args>
ESet setUni(const ESet& et, Args... args)
    { return __setUni(et, setUni(args...)); }


EffectType wrap(Type t);

template<typename... Args>
EffectType wrap(Type t, Args... args)
    { return EffectType(t, setUni(args...)); }

// just to wrap Type, changes just the underlying type
inline void subst(EffectType& T1, const Type& from, const Type& to)
    { subst(T1.elt, from, to); }
// this affets ONLY the effect, and re-wrap the type
void substEffect(EffectType& T1, const EffectType& from, const EffectType& to);
// this is done because doing both at once is quite messy


inline EffectType copy(const EffectType& t)
    { return EffectType(copy(*t), t.effects); }