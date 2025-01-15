#include "typingVisitor.h"
#include <cassert>

using check = std::pair<EffectType, YYLTYPE>;
std::vector<std::vector<check>> toLateCheck;

typingVisitor::typingVisitor(std::vector<NDecl*>* root) : root(root), env{}, propag(root, env), effecto(root, env)
{
    
    env[std::make_pair(VStorage::Vfun, "while")] = 
        EffectType(
        new TFun(std::vector<Type>{new TFun(std::vector<Type>{}, new EffectType(new TBool())), new TFun(std::vector<Type>{}, new EffectType(new TUnit()))}, 
            new EffectType(new TUnit(), {Effect::EDiv})));

    env[std::make_pair(VStorage::Vfun, "for")] = 
        EffectType(
        new TFun(std::vector<Type>{new TInt(), new TInt(), new TFun(std::vector<Type>{new TInt()}, new EffectType(new TUnit()))}, 
            new EffectType(new TUnit())));

    env[std::make_pair(VStorage::Vfun, "println")] = 
        EffectType(
        new TFun(std::vector<Type>{new TVariant{new TUnit(), new TBool(), new TInt(), new TString()}}, 
            new EffectType(new TUnit(), {Effect::EConsole})));

    env[std::make_pair(VStorage::Vfun, "repeat")] = 
        EffectType(
        new TFun(std::vector<Type>{new TInt(), new TFun(std::vector<Type>{}, new EffectType(new TUnit()))}, 
            new EffectType(new TUnit())));

    Type tau = new TWeak();

    env[std::make_pair(VStorage::Vfun, "head")] = 
        EffectType(new TFun(std::vector<Type>{new TList(tau)}, new EffectType(new TMaybe(tau))));

    env[std::make_pair(VStorage::Vfun, "tail")] = 
        EffectType(new TFun(std::vector<Type>{new TList(tau)}, new EffectType(new TList(tau))));

    env[std::make_pair(VStorage::Vfun, "default")] = 
        EffectType(new TFun(std::vector<Type>{new TMaybe(tau), tau}, new EffectType(tau)));
}

EffectType typingVisitor::visit(std::vector<NDecl*>* node)
{
    for (auto &&decl : *node)
    {
        auto id = make_pair(VStorage::Vfun, *decl->name);
        propag.current_decl = id;
        if (env.count(id))
            typingError("Function \"" + *decl->name + "\" already defined", decl->loc);

        env[id] = makeWeakFunction(decl->body->params->size());
        toLateCheck.push_back(std::vector<check>{});

        EffectType t = visit(decl->body);
        EffectType ret_t = *std::get<TFun*>(*t)->ret;

        std::vector<check> toCheck = toLateCheck[toLateCheck.size() - 1];
        for (auto &&e : toCheck)
        {
            if (!propag.unify(e.first, ret_t))
                typingError("Return statement expect same type as function return type meaning : \"" + toString(ret_t) + "\" and not \"" + toString(e.first) + "\"", e.second);
        }

        // check for consistency with infered effect
        if (!effecto.unify(ret_t, env[id]))
            typingError("Effect uncompatible (is function passed as a lambda without necessary effects ?) : \"" + toString(ret_t) + "\" and not \"" + toString(env[id]) + "\"", decl->loc);

        toLateCheck.pop_back();
        env[id] = t; // "correct the type"
        decl->t = t;
    }
    auto main_id = std::make_pair(VStorage::Vfun, "main");
    if (!env.count(main_id))
        typingError("Function main not defined", YYLTYPE{1, 1, 1, 1});

    TFun* tmain = std::get<TFun*>(*env[main_id]);
    if (tmain->elts.size())
        typingError("Function main should not take any arguments", YYLTYPE{1, 1, 1, 1});

    return EffectType(new TUnit()); // arbitrary decision...
}

EffectType typingVisitor::visit(NFunBody* node)
{
    // to allow for shadowing
    typingVisitor tv(*this);
    std::vector<Type> params;

    for (auto &&param : *node->params)
    {
        Type t = *tv.visit(param);
        params.push_back(t);

        //if (std::holds_alternative<TFun*>(t))
         //   std::get<TFun*>(t)->ret->isWeak = false; // function type are absolute meaning you HAVE to specify desired effect for function argument
    }
    
    EffectType* infered_t = new EffectType(tv.visit(node->bodyExpr));

    node->t = EffectType(new TFun(params, infered_t));
    node->t.addEffects(infered_t->effects);

    std::cout << "DEBUG funbody :" << toString(node->t) << std::endl;

    if (node->retType)
    {
        EffectType specified_type = tv.visit(node->retType);

        std::set<Effect> sepecifiedEffects{};
        for (std::string* s : *node->retType->effects)
            sepecifiedEffects.emplace(effectFromString(*s, node->retType->loc));

        if (!infered_t->isSubst(sepecifiedEffects))
            typingError("Specified effects are missing at least one necessary effect", node->loc);

        if (!propag.unify(*infered_t, specified_type))
            typingError("Specified type does not match infered one", node->loc);
    }

    return node->t;
}

EffectType typingVisitor::visit(NParam* node)
{
    auto id = make_pair(VStorage::Vvar, *node->name);
    if (env.count(id))
        typingError("Parameter \"" + *node->name + "\" already defined", node->loc);
    
    EffectType t = visit(node->type);
    env[id] = t;
    node->t = t;
    return node->t;
}

EffectType typingVisitor::visit(NBasicType* node)
{
    Type t;
    std::string tname = *node->name;
    if (tname == "unit") t = new TUnit();
    else if (tname == "bool") t = new TBool();
    else if (tname == "int") t = new TInt();
    else if (tname == "string") t = new TString();
    else typingError("Unknown basic type : \"" + tname + "\"", node->loc);

    node->t = t;
    return t;
}

EffectType typingVisitor::visit(NTemplateType* node)
{
    EffectType t_temp = visit(node->templat);
    std::string tname = *node->name;
    if (tname == "list")       node->t = EffectType(new TList(*t_temp));
    else if (tname == "maybe") node->t = EffectType(new TMaybe(*t_temp));
    else typingError("Unknown template type : \"" + tname + "\"", node->loc);

    return node->t;
}

EffectType typingVisitor::visit(NReturnType* node)
{
    std::set<Effect> sepecifiedEffects{};
    for (std::string* s : *node->effects)
        sepecifiedEffects.emplace(effectFromString(*s, node->loc));
    node->t = visit(node->type);
    node->t.addEffects(sepecifiedEffects);
    node->t.isWeak = false; // return type is absolute cant be weak
    return node->t;
}

EffectType typingVisitor::visit(NFunType* node)
{
    std::vector<Type> elts;
    ESet effects{};
    for (NType& a : *node->argsType)
    {
        EffectType et = visit(a);
        elts.push_back(*et);
        effects = setUni(effects, et.effects);
    }
        
    if (elts.size() == 1 && std::holds_alternative<TUnit*>(elts[0]))
        elts.clear();
    EffectType et = visit(node->retType);
    if (!et.isWeak && (et.effects.size() == 0))
        et.effects.emplace(Effect::ETotal);
        
    EffectType* ret = new EffectType(*et, et.effects, et.isWeak, et.weak_id);


    node->t = EffectType(new TFun(elts, ret));
    return node->t;
}

EffectType typingVisitor::visit(NBlock* node)
{
    if (node->retExpr.has_value())
    {
        typingVisitor tv(*this);
        std::set<Effect> eff{};
        for (NStmt& stmt: *node->stmts)
        {
            EffectType te = tv.visit(stmt);
            eff = setUni(eff, te.effects);
        }
        EffectType t = tv.visit(node->retExpr.value());

        node->t = t;
        node->t.addEffects(eff);
    }
    else node->t = EffectType(new TUnit());

    return node->t;
}

EffectType typingVisitor::visit(NBexprInfix* node)
{
    EffectType t = visit(node->expr);
    if (node->op == yytokentype::TTILDE)
    {
        if (!propag.unify_conv(t, new TInt()))
            typingError("Unary operator \"~\" expects type \"int\" not \"" + toString(t) + "\"", node->loc);
    }
    else if (node->op == yytokentype::TEXCL)
    {
        if (!propag.unify_conv(t, new TBool()))
            typingError("Unary operator \"!\" expects type \"bool\" not \"" + toString(t) + "\"", node->loc);
    }
    else typingError("Unsupported unary operator token : " + std::to_string(node->op), node->loc);

    node->t = t;
    return node->t;
}

EffectType typingVisitor::visit(NBexprBinOP* node)
{
    EffectType tl = visit(node->left);
    EffectType tr = visit(node->right);

    if (node->op == yytokentype::TADD || node->op == yytokentype::TSUB 
        || node->op == yytokentype::TMUL || node->op == yytokentype::TDIV || node->op == yytokentype::TMOD)
    {
        bool isUni = propag.unify(tr, tl);
        if (!isUni || !propag.unify_conv(tr, new TInt()))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects types \"int\" and \"int\" not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);
        node->t = EffectType(new TInt());
    }
    else if (node->op == yytokentype::TCLE || node->op == yytokentype::TCGE 
        || node->op == yytokentype::TCLT || node->op == yytokentype::TCGT)
    {
        bool isUni = propag.unify(tr, tl);
        if (!isUni || !propag.unify_conv(tr, new TInt()))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects types \"int\" and \"int\" not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);
        
        node->t = EffectType(new TBool());
    }
    else if (node->op == yytokentype::TCEQ || node->op == yytokentype::TCNE)
    {
        if (!propag.unify(tr, tl))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects same types and not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);
        
        if (!(propag.unify_conv(tr, new TInt()) || propag.unify_conv(tr, new TBool()) || propag.unify_conv(tr, new TString())))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects types to be \"int\", \"bool\" or \"string\" and not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);

        node->t = EffectType(new TBool());
    }
    else if (node->op == yytokentype::TINC)
    {
        if (!propag.unify(tr, tl))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects same types and not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);

        if (!(propag.unify_conv(tr, new TString()) || std::holds_alternative<TList*>(*tr)))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects types \"string\" or \"list\" not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);

        node->t = tr;
    }
    else if (node->op == yytokentype::TAND || node->op == yytokentype::TOR)
    {
        bool isUni = propag.unify(tr, tl);
        if (!isUni || !propag.unify_conv(tr, new TBool()))
            typingError("Binary operator tok : " + std::to_string(node->op) + " expects types \"bool\" and \"bool\" not \"" + toString(tl) + "\" and \"" + toString(tr) + "\"", node->loc);

        node->t = EffectType(new TBool());
    }
    else typingError("Unsuported inary operator tok : " + std::to_string(node->op), node->loc);

    ESet effects = setUni(tl.effects, tr.effects);
    node->t.addEffects(effects);
    return node->t;
}

EffectType typingVisitor::visit(NBexprAssign* node)
{
    EffectType t = visit(node->expr);

    auto id_var = std::make_pair(VStorage::Vvar, *node->name);

    if (!env.count(id_var))
        typingError("Variable  \"" + *node->name + "\" is undefined", node->loc);

    if (!propag.unify(env[id_var], t))
        typingError("Can't assign variablr \"" + *node->name + "\" of type : \"" + toString(env[id_var]) + "\" to expression of type : \"" + toString(t) + "\"", node->loc);


    node->t = EffectType(new TUnit());
    node->t.addEffects(t.effects);
    return node->t;
}

EffectType typingVisitor::visit(NBexprIf* node)
{
    EffectType tcond = visit(node->condition.value());
    if (!propag.unify_conv(tcond, new TBool()))
        typingError("If expression expect \"bool\" condition and not : \"" + toString(tcond) + "\"", node->loc);
    
    EffectType tthen = visit(node->thenExpr.value());
    EffectType telse;
    if (node->elseExpr.has_value()) telse = visit(node->elseExpr.value());
    else telse = EffectType(new TUnit());

    node->t = tthen;

    std::cout << "debug : " << toString(tthen) << " and " << toString(telse) << std::endl;
    if (!propag.unify(tthen, telse))
        typingError("If expression expects both then and else type to be the same, not \"" + toString(tthen) + "\" and \"" + toString(telse) + "\"", node->loc);

    ESet effects = setUni(tthen.effects, telse.effects, tcond.effects);
    node->t.addEffects(effects);
    return node->t;
}

EffectType typingVisitor::visit(NBexprLambda* node)
{
    toLateCheck.push_back(std::vector<check>{});
    node->t = visit(node->body);

    EffectType ret_t = *std::get<TFun*>(*node->t)->ret;

    std::vector<check> toCheck = toLateCheck[toLateCheck.size() - 1];
    for (auto &&e : toCheck)
    {
        if (!propag.unify(e.first, ret_t))
            typingError("Return statement expect same type as lambda return type meaning : \"" + toString(ret_t) + "\" and not \"" + toString(e.first) + "\"", e.second);
    }

    toLateCheck.pop_back();

    // lambdas "embed" their code and thus the effects of their code which sholdnt be propagated
    // we "move" the effects to the effect of return
    ESet saved_effects = node->t.effects;
    node->t.effects.clear();
    std::get<TFun*>(*node->t)->ret->addEffects(saved_effects);

    return node->t;
}

EffectType typingVisitor::visit(NBexprReturn* node)
{
    EffectType et = visit(node->expr);
    toLateCheck[toLateCheck.size() - 1].push_back(std::make_pair(et, node->loc));
    node->t = EffectType(new TReturn(*et));
    node->t.addEffects(et.effects);
    return node->t;
}

EffectType typingVisitor::visit(NBAtom* node)
{
    node->t = visit(node->atom);
    return node->t;
}

EffectType typingVisitor::visit(NStmtBexpr* node)
{
    node->t = visit(node->expr);
    return node->t;
}

EffectType typingVisitor::visit(NStmtVal* node)
{
    EffectType t = visit(node->expr);
    auto id_val = make_pair(VStorage::Vval, *node->name);
    if (env.count(id_val))
    {
        typingWarning("Val declaration shadows previous definition", node->loc);
        env.erase(id_val);
    }

    // in koka a var decl can shadow a val decl and vice versa without error... weird
    auto id_var = make_pair(VStorage::Vvar, *node->name);
    if (env.count(id_var))
    {
        typingWarning("Val declaration shadows previous definition", node->loc);
        env.erase(id_var);
    }

    env[id_val] = t;
    node->t = t;
    return node->t;
}

EffectType typingVisitor::visit(NStmtVar* node)
{
    EffectType t = visit(node->expr);
    auto id_val = make_pair(VStorage::Vval, *node->name);
    if (env.count(id_val))
    {
        typingWarning("Var declaration shadows previous definition", node->loc);
        env.erase(id_val);
    }

    // in koka a var decl can shadow a val decl and vice versa without error... weird
    auto id_var = make_pair(VStorage::Vvar, *node->name);
    if (env.count(id_var))
    {
        typingWarning("Var declaration shadows previous definition", node->loc);
        env.erase(id_var);
    }

    env[id_var] = t;
    node->t = t;
    return node->t;
}

EffectType typingVisitor::visit(NAtomTrue* node)
{
    node->t = EffectType(new TBool());
    return node->t;
}

EffectType typingVisitor::visit(NAtomFalse* node)
{
    node->t = EffectType(new TBool());
    return node->t;
}

EffectType typingVisitor::visit(NAtomInt* node)
{
    node->t = EffectType(new TInt());
    return node->t;
}

EffectType typingVisitor::visit(NAtomStr* node)
{
    node->t = EffectType(new TString());
    return node->t;
}

EffectType typingVisitor::visit(NAtomNil* node)
{
    node->t = EffectType(new TUnit());
    return node->t;
}

EffectType typingVisitor::visit(NAtomIdent* node)
{
    auto id_val = make_pair(VStorage::Vval, *node->val);
    auto id_var = make_pair(VStorage::Vvar, *node->val);
    auto id_fun = make_pair(VStorage::Vfun, *node->val);


    if (env.count(id_val))
        node->t = env[id_val]; 
    else if (env.count(id_var))
        node->t = env[id_var];
    else if (env.count(id_fun))
    {
        if (propag.current_decl.second == *node->val) // add div to main decl
        {
            std::cout << "OH " << toString(env[id_fun]) << " " << env[id_fun].effects.size() << std::endl;
            assert(env[id_fun].isWeak);
            env[id_fun].addEffects({Effect::EDiv});
        }

        node->t = copy(env[id_fun]); // copy to avoid modifying env later on for functions, we deal with recursive in the function definition by "correcting" the infered type afterward
    }
    else
        typingError("Undefined variable/identifier \"" + *node->val + "\"", node->loc);

    return node->t;
}

EffectType typingVisitor::visit(NAtomExpr* node)
{
    node->t = visit(node->expr);
    return node->t;
}

EffectType typingVisitor::visit(NAtomList* node)
{
    ESet effects{};
    if (node->elts->size())
    {
        EffectType t = visit(node->elts->at(0));
        effects = setUni(effects, t.effects);

        for (size_t i = 1; i < node->elts->size(); i++)
        {
            EffectType nt = visit(node->elts->at(i));
            effects = setUni(effects, nt.effects);
            if (!propag.unify(nt, t))
                typingError("List initializer has in-homogenious types, first element has type \"" + toString(t) + "\"" + "while element in position " + std::to_string(i+1)  + " is ok type \"" + toString(nt) + "\"", node->loc);
        }
        node->t = EffectType(new TList(*t));
    }
    else
        node->t = EffectType(new TList(new TWeak()));
    node->t.addEffects(effects);
    return node->t;
}

EffectType typingVisitor::visit(NAtomCall* node)
{
    ESet effects{};
    EffectType ct = visit(node->fun);

    if (!std::holds_alternative<TFun*>(*ct))
        typingError("Expression is not callable \"" + toString(node->fun) + "\"", node->loc);
    
    TFun* ctf = std::get<TFun*>(*ct);
    effects = setUni(effects, ct.effects);
    
    if (ctf->elts.size() != node->args->size())
        typingError("Function \"" + toString(node->fun) + "\" requires " + std::to_string(ctf->elts.size()) + " argument while " + std::to_string(node->args->size()) + " were provided", node->loc);
    
    for (size_t i = 0; i < node->args->size(); i++)
    {
        EffectType te = visit(node->args->at(i));
        effects = setUni(effects, te.effects);

        if (!propag.unify(te, ctf->elts[i]))
            typingError("Function \"" + toString(node->fun) + "\" expect argument " + std::to_string(i + 1) + " to be of type \"" + toString(ctf->elts[i]) + "\" while the provided one was of type : \"" + toString(te) + "\"" , node->loc);

        // handle the case of function argument in which we have to check return effects
        if (std::holds_alternative<TFun*>(*te))
        {
            EffectType* atf = std::get<TFun*>(*te)->ret;
            
            if (!effecto.unify(*atf, *std::get<TFun*>(ctf->elts[i])->ret))
                typingError("Function \"" + toString(node->fun) + "\" expect effects return types as " + std::to_string(i + 1) + " to be of type \"" + toString(ctf->elts[i]) + "\" while the provided one was of type : \"" + toString(te) + "\"" , node->loc);

            atf = std::get<TFun*>(*te)->ret;

            std::cout << "DEBUG arg ret type :" << toString(*atf) << " || " << toString(*std::get<TFun*>(ctf->elts[i])->ret) << std::endl;
        }
    }
    
    node->t = *ctf->ret;
    node->t.addEffects(effects);
    return node->t;
}

