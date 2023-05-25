#include <bits/stdc++.h>
using namespace std;

// A lattice will be used as the data structure
// We will not make the entire lattice at the beginning
struct LatticeNode {
    list<bool> word;
    vector<LatticeNode *> ins_0;
    vector<LatticeNode *> ins_1;
    bool in_answer;

    LatticeNode(): word(), ins_0(1, nullptr), ins_1(1, nullptr), in_answer(true) {}
    LatticeNode(const list<bool> &w, bool ans = false): word(w), ins_0(word.size() + 1, nullptr), ins_1(word.size() + 1, nullptr), in_answer(ans)
    {}
    LatticeNode(list<bool> w, int loc, bool element, bool ans = false)
    {
        w.insert(w.begin() + loc, element);
        
    }
};

void integral(const vector<unordered_set<list<bool> > > &lang, int l, int k)
{
    // lang.size() must be k
    // lang[i] is the set of words of length i
    // We will grow a lattice to represent the integral set
    if(lang[0].empty()) /* HANDLE */ assert(false);
    LatticeNode* lattice = new LatticeNode();
    for(int size = 1; size < l; ++size)
    {
        
    }
}