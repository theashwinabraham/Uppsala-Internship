#include <bits/stdc++.h>
using namespace std;
using ull = uint64_t;

struct Language {
    Language *app[2];
    Language* pref;
    bool valid;
    bool in_int; // if a node is not in_int, no child of it is in_int

    Language(Language *pref = nullptr): valid(true), pref(pref), in_int(false)
    {
        app[0] = app[1] = nullptr;
    }

    void append(bool bit, Language* ptr, bool preserve = true)
    {
        app[bit] = ptr;
        if(ptr != nullptr) ptr->pref = this;
        valid = preserve;
    }
};

Language *make_complete(ull l)
{
    Language *ll = new Language;
    if(l > 0)
    {
        ll->append(0, make_complete(l - 1));
        ll->append(1, make_complete(l - 1));
    }
    return ll;
}

Language *integral(Language *lang, ull k, ull l)
{
    if(lang == nullptr || !(lang->valid)) return nullptr;
    Language *complete_tree = make_complete(l);
    
}