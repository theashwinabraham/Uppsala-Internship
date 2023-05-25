#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;

map<tuple<vector<bool>::iterator, vector<bool>::iterator, ll>, const set<vector<bool> >*> sks_memo;
const set<vector<bool > > & size_k_substrs(const vector<bool>::iterator start, const vector<bool>::iterator end, ll size)
{
    auto it = sks_memo.find(tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, size));
    if(it != sks_memo.end())
    {
        return *(it->second);
    }

    set<vector<bool > > *ret_set = new set<vector<bool> >;
    if(size == 0)
    {
        ret_set->insert(vector<bool>());
        sks_memo[tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, size)] = ret_set;
        return *sks_memo[tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, size)];
        // return *ret_set;
    }
    for(vector<bool>::iterator i = start; i < end; ++i)
    {
        set<vector<bool> > alph = size_k_substrs(start, i, size - 1);
        for(vector<bool> v: alph)
        {
            v.push_back(*i);
            ret_set->insert(v);
        }
    }
    sks_memo[tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, size)] = ret_set;
    return *sks_memo[tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, size)];
    // return *ret_set;
}

set<vector<bool> > alpha(const vector<bool>::iterator start, const vector<bool>::iterator end, ll k)
{
    // static map<tuple<vector<bool>::iterator, vector<bool>::iterator, ll>, const set<vector<bool> >*> memo;
    // auto it = memo.find(tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, k));
    // if(it != memo.end())
    // {
    //     // cout << "Memo find alpha for ";
    //     // for(auto iit = start; iit != end; ++iit) cout << *iit;
    //     // cout << " is" << endl;
    //     // for(const auto& vb: *(it->second))
    //     // {
    //     //     for(bool b: vb)
    //     //     {
    //     //         cout << b;
    //     //     }
    //     //     cout << endl;
    //     // }
    //     return *(it->second);
    // }

    set<vector<bool> > ret_set;
    for(int size = 0; size <= k; ++size)
    {
        auto sks = size_k_substrs(start, end, size);
        for(const auto &x: sks)
        {
            ret_set.insert(x);
        }
    }
    // memo[tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, k)] = ret_set;
    // cout << "Alpha for ";
    // for(auto it = start; it != end; ++it) cout << *it;
    // cout << " is" << endl;
    // for(const auto& vb: *ret_set)
    // {
    //     for(bool b: vb)
    //     {
    //         cout << b;
    //     }
    //     cout << endl;
    // }
    // return *memo[tuple<vector<bool>::iterator, vector<bool>::iterator, ll>(start, end, k)];
    return ret_set;
}

vector<bool> increment(vector<bool> num)
{
    ll i = 0;
    for(; i < num.size(); ++i)
    {
        if(num[i]) num[i] = 0;
        else
        {
            num[i] = 1;
            break;
        }
    }
    return num;
}
/* increment is bad */

// struct LatticeNode {
//     static map<vector<bool>, LatticeNode *> memo;
//     // static set<vector<bool> > processed;
//     vector<bool> v;
//     vector<LatticeNode *> ins0;
//     vector<LatticeNode *> ins1;
//     bool valid;
//     // bool done;

//     LatticeNode(): ins0(1, nullptr), ins1(1, nullptr), valid(true)
//     {
//         memo[v] = this;
//     }

//     LatticeNode(const vector<bool> &w): v(w), ins0(w.size() + 1, nullptr), ins1(w.size() + 1, nullptr), valid(true)
//     {
//         memo[v] = this;
//     }

//     void add_child(ull loc, bool ins)
//     {
//         vector<bool> nb = v;
//         nb.insert(nb.begin() + loc, ins);
//         // if(processed.count(nb)) return;
//         auto it = memo.find(nb);
//         if(it != memo.end())
//         {
//             if(ins) ins1[loc] = it->second;
//             else ins0[loc] = it->second;
//         }
//         else
//         {
//             if(ins) ins1[loc] = new LatticeNode(nb);
//             else ins0[loc] = new LatticeNode(nb);
//         }
//     }

//     void add_children()
//     {
//         for(ll i = 0; i <= v.size(); ++i)
//         {
//             add_child(i, 0);
//             add_child(i, 1);
//         }
//     }
// };

// map<vector<bool>, LatticeNode *> LatticeNode::memo;
/* This was worse */
// struct Trie;
// map<Trie *, vector<bool> > witness;

struct Trie {
    vector<bool> str;
    Trie *child[2];
    Trie *parent;
    bool valid;
    set<Trie *> prop_subwords;
    
    Trie(): valid(true), parent(nullptr)
    {
        child[0] = child[1] = nullptr;
    }

    Trie(Trie *parent, bool ins): valid(parent->valid), parent(parent), str(parent->str), prop_subwords(parent->prop_subwords)
    {
        child[0] = child[1] = nullptr;
        str.push_back(ins);
        // if(!valid) witness[this] = witness[parent];
        for(Trie *ptr: parent->prop_subwords)
        {
            if(! ptr->valid)
            {
                valid = false;
                // witness[this] = witness[ptr];
            }
            if(ptr->child[ins] == nullptr)
            {
                ptr->child[ins] = new Trie(ptr, ins);
            }
            if(! ptr->child[ins]->valid)
            {
                valid = false;
                // witness[this] = witness[parent];
            }
            prop_subwords.insert(ptr->child[ins]);
        }
    }
};

// Trie *root;
set<vector<bool> > integral(const set<vector<bool> > &lang, ll k, ll l)
{
    set<vector<bool> > ret_set;
    queue<Trie *> bfs;
    bfs.push(new Trie);
    // root = bfs.front();
    while(!bfs.empty())
    {
        Trie *t = bfs.front();
        if(t->str.size() > l) break;
        for(const auto &v: alpha((t->str).begin(), (t->str).end(), k))
        {
            if(!lang.count(v))
            {
                // witness[t] = v;
                t->valid = false;
                break;
            }
            sks_memo.clear();
        }
        if(t->valid)
        {
            ret_set.insert(t->str);
            t->child[0] = new Trie(t, 0);
            t->child[1] = new Trie(t, 1);
            if(t->child[0]->valid) bfs.push(t->child[0]);
            if(t->child[1]->valid) bfs.push(t->child[1]);
        }
        bfs.pop();
    }
    // queue<LatticeNode*> bfsqueue;
    // set<vector<bool> > added;
    // bfsqueue.push(new LatticeNode);
    // added.insert(vector<bool>());
    // while(!bfsqueue.empty())
    // {
    //     LatticeNode *lat = bfsqueue.front();
    //     if((lat->v).size() > l) break;
    //     for(const auto& v: alpha((lat->v).begin(), (lat->v).end(), k))
    //     {
    //         if(!lang.count(v))
    //         {
    //             lat->valid = false;
    //             break;
    //         }
    //     }
    //     if(lat->valid)
    //     {
    //         ret_set.insert(lat->v);
    //         lat->add_children();
    //         for(LatticeNode *ptr : lat->ins0)
    //         {
    //             if(!added.count(ptr->v)) bfsqueue.push(ptr);
    //         }
    //         for(LatticeNode *ptr: lat->ins1)
    //         {
    //             if(!added.count(ptr->v)) bfsqueue.push(ptr);
    //         }
    //     }
    //     added.insert(lat->v);
    //     bfsqueue.pop();
    // }
    // auto c = vector<bool>();
    // ret_set.insert(c);
    // for(ll size = 1; size <= l; ++size)
    // {
    //     c = vector<bool>(size, 0);
    //     do{
    //     // cout << "Now on: ";
    //     // for(bool b: c)
    //     // {
    //     //     cout << b;
    //     // }
    //     // cout << endl;
    //     bool broken = false;
    //     // cout << "BRUH" << endl;
    //     for(const auto& v: alpha(c.begin(), c.end(), k))
    //     {
    //         if(!lang.count(v))
    //         {
    //             // cout << "Not Accepted because of ";
    //             // for(bool b: v)
    //             // {
    //             //     cout << b;
    //             // }
    //             // cout << endl;
    //             broken = true;
    //             break;
    //         }
    //     }
    //     if(!broken)
    //     {
    //         // cout << "Accepted" << endl;
    //         ret_set.insert(c);
    //     }
    //     c = increment(c);
    //     } while(c != vector<bool>(size, 0));
    // }

    return ret_set;
}

int main(int argc, char **argv)
{
    if(argc != 2 && argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <value of l> <optional: debug>" << endl;
        exit(-1);
    }
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    set<vector<bool> > language;
    language.insert(vector<bool>());
    string s;
    while(cin >> s)
    {
        // cout << "Input taken: " << s << endl;
        vector<bool> b = vector<bool>();
        for(ll i = 0; i < s.size(); ++i)
        {
            b.push_back(s[i] == '1');
        }
        language.insert(b);
    }
    // cout << "Language is: ";
    // for(const auto& vb: language)
    // {
    //     for(bool b: vb)
    //     {
    //         cout << b;
    //     }
    //     cout << endl;
    // }
    ll l = stoi(argv[1]);
    auto t = chrono::steady_clock::now();
    set<vector<bool> > integ = integral(language, l - 1, l);
    cout << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - t).count() << " ms\n";
    cout << "Size: " << integ.size() << endl;

    if(argc == 3)
    {
        // cout << "Set is: " << endl;
        for(const auto& v: integ)
        {
            for(bool b: v)
            {
                cout << b;
            }
            cout << endl;
        }
        // cout << "NUM IS " << num << endl;
    }
    // cout << "MEMO" << endl;
    // for(auto it = LatticeNode::memo.begin(); it != LatticeNode::memo.end(); ++it)
    // {
    //     for(bool b: it->first) cout << b;
    //     cout << " : ";
    //     cout << it->second;
    // }
    // auto v = witness[root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[1]];
    // if(language.count(v)) cout << "BRUHHHHHH" << endl;
    // for(bool b: v) cout << b;
    // cout << endl;
    return 0;
}
