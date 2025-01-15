#pragma once
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <variant>
#include <set>
#include <algorithm>
#include <optional>
#include "error.h"

class EffectType; // required to use if for FunType  as effect.h requires type.h

class TUnit;
class TWeak;
class TReturn;
class TBool;
class TInt;
class TString;
class TList;
class TMaybe;
class TFun;
class TVariant;

using Type = std::variant<TUnit*, TWeak*, TBool*, TInt*, TString*, TList*, TMaybe*, TFun*, TVariant*, TReturn*>;
using BasicType = std::variant<TUnit*, TBool*, TInt*, TString*>;

// TODO: make this some horrible modern c++ to handle this genericly
inline std::optional<BasicType> getBasic(const Type& t)
{
    if (std::holds_alternative<TUnit*>(t)) return std::get<TUnit*>(t);
    if (std::holds_alternative<TBool*>(t)) return std::get<TBool*>(t);
    if (std::holds_alternative<TInt*>(t)) return std::get<TInt*>(t);
    if (std::holds_alternative<TString*>(t)) return std::get<TString*>(t);

    return std::nullopt;
}


class TUnit {
public:
    TUnit() { }
    operator std::string() const;
};

static int id_ctr = 1;
class TWeak {
public:
    long id;

    TWeak() : id(id_ctr++) { }
    TWeak(long id) : id(id) { }
    operator std::string() const;
};

static int ret_ctr = 1;
class TReturn {
public:
    Type elt;
    long id;

    TReturn(Type elt) : elt(elt), id(ret_ctr++) { }
    TReturn(Type elt, long id) : elt(elt), id(id) { }
    operator std::string() const;
};

class TBool {
public:
    TBool() { }
    operator std::string() const;
};

class TInt {
public:
    TInt() { }
    operator std::string() const;
};

class TString {
public:
    TString() { }
    operator std::string() const;
};

class TList {
public:;
    Type elt;

    TList(Type elt) : elt(elt) { }
    operator std::string() const;
};

class TMaybe {
public:
    Type elt;

    TMaybe(Type elt) : elt(elt) { }
    operator std::string() const;
};

class TFun {
public:
    std::vector<Type> elts;
    EffectType* ret;

    TFun(std::vector<Type> elts, EffectType* ret) : elts(elts), ret(ret) { }
    operator std::string() const;
};

struct cmp {
    bool operator() (BasicType a, BasicType b) const 
    {
        return a.index() < b.index(); 
    }
};

using TSet = std::set<BasicType, cmp>;

static int va_ctr = 1;
class TVariant {
public: 
    TSet elts;
    int id;

    // we implement somewhat ad-hoc polymorphism for basic types
    // for learning purposes
    TVariant(std::initializer_list<BasicType> list) : elts(list), id(va_ctr++) { }
    TVariant(TSet list, int id) : elts(list), id(id) { }
    operator std::string() const;
};

bool operator==(const Type& lhs, const Type& rhs);
bool operator!=(const Type& lhs, const Type& rhs);

Type copy(const Type&);

Type makeWeakFunction(int n);
void subst(Type& T1, const Type& from, const Type& to);

template <typename T>
inline std::string toString(const T& v) 
    { return std::visit([](auto* n) { return n->operator std::string(); }, v); }

