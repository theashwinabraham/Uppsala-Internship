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


set<vector<bool> > integral(const set<vector<bool> > &lang, ll k, ll l)
{
    set<vector<bool> > ret_set;
    auto c = vector<bool>();
    ret_set.insert(c);
    for(ll size = 1; size <= l; ++size)
    {
        c = vector<bool>(size, 0);
        do{
        // cout << "Now on: ";
        // for(bool b: c)
        // {
        //     cout << b;
        // }
        // cout << endl;
        bool broken = false;
        // cout << "BRUH" << endl;
        for(const auto& v: alpha(c.begin(), c.end(), k))
        {
            if(!lang.count(v))
            {
                // cout << "Not Accepted because of ";
                // for(bool b: v)
                // {
                //     cout << b;
                // }
                // cout << endl;
                broken = true;
                break;
            }
            sks_memo.clear();
        }
        if(!broken)
        {
            // cout << "Accepted" << endl;
            ret_set.insert(c);
        }
        c = increment(c);
        } while(c != vector<bool>(size, 0));
    }
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
    return 0;
}