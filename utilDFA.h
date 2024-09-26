#include<bits/stdc++.h>
using namespace std;
class DFA{
    vector<unordered_map<char,int>>m;
    vector<pair<char,unordered_map<char,char>>>dfa_trans;
    map<set<int>,char>states;
    char intitState, finalState;
    string re;
    public:
    DFA(vector<vector<int>>v,string re)
    {
        this->re = re;
        for(int i=0;i<v.size();i++)
        {
            unordered_map<char,int>temp;
            for(int j=0;j<4;j++)
            {
                if(j==0)temp['a'] = v[i][j];
                if(j==1)temp['b'] = v[i][j];
                if(j==2)temp['$'] = v[i][j];
                if(j==3)temp['#'] = v[i][j];
            }
            m.push_back(temp);
        }
    }

    set<int> closure(int src)
    {
        set<int>s;
        queue<int>q;
        s.insert(src);
        q.push(src);

        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            if(m[x]['$']!=-1){q.push(m[x]['$']);s.insert(m[x]['$']);} 
            if(m[x]['#']!=-1){q.push(m[x]['#']);s.insert(m[x]['#']);}    
        }
        return s;
    }

    set<int>transition(set<int>clos,char ch)
    {
        set<int>ans;
        for(auto x:clos)
        {
            if(m[x][ch]!=-1)ans.insert(m[x][ch]);
        }
        for(auto x:ans)
        {
            set<int>temp = closure(x);
            for(auto xx:temp)ans.insert(xx);
        }
        return ans;
    }
    
    void make_dfa(int src = 0)
    {
        queue<set<int>>q;
        set<set<int>>ss;
        set<int>clos = closure(src);
        ss.insert(clos);
        q.push(clos);
        
        char st = 'A';
        states[clos] = st; 
        intitState = st;
        while(!q.empty())
        {
            set<int>x = q.front();
            set<int>trans_a = transition(x,'a');
            set<int>trans_b = transition(x,'b');
            unordered_map<char,char>curr_trans;
            if(!trans_a.empty() && ss.find(trans_a)==ss.end()){ss.insert(trans_a);q.push(trans_a);st++;states[trans_a]=st;};
            if(!trans_a.empty()){curr_trans['a']=states[trans_a];}
            if(!trans_b.empty() && ss.find(trans_b)==ss.end()){ss.insert(trans_b);q.push(trans_b);st++;states[trans_b]=st;};
            if(!trans_b.empty()){curr_trans['b']=states[trans_b];}
            q.pop();
            dfa_trans.push_back({states[x],curr_trans});
        }
        finalState = st;
    }
    void print_DFA()
    {
        make_dfa();
        cout<<"*******************************START**************************************\n";
        cout<<"Solving for Regular Expression: "<<re<<"\n";
        cout<<"*************************************************************************\n";
        cout<<"Initial and Final states\n";
        cout<<"initial state : "<<intitState<<"\n";
        cout<<"final state : "<<finalState<<"\n";
        cout<<"*************************************************************************\n";
        int idx = 1;
        cout<<"Priniting Transitions of DFA\n";
        for(auto x:dfa_trans)
        {
            char from = x.first;
            char to_a = x.second['a'];
            char to_b = x.second['b'];
    
            if(to_a)cout<<idx++<<". Transition from state "<<from<<" to "<<to_a<<" on symbol 'a'\n";
            if(to_b)cout<<idx++<<". Transition from state "<<from<<" to "<<to_b<<" on symbol 'b'\n";
        }
        cout<<"*************************************************************************\n";
        cout<<"Subsets and their respective state names\n";
        for(auto i:states)
        {
            cout<<"{";
            for(auto x:i.first)cout<<x<<", ";cout<<"\b\b} : ";
            cout<<i.second<<"\n";
        }
        cout<<"********************************END**************************************\n";
    }
};