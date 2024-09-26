#include "utilDFA.h"
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s = "(a+b)*abb";
    vector<vector<int>>v = {
    //{on taking symbol 'a', on taking symbol 'b', on taking epsilon1($), on taking epsillon2(#)}
        {-1,-1,1,7},
        {-1,-1,2,4},
        {3,-1,-1,-1},
        {-1,-1,6,-1},
        {-1,5,-1,-1},
        {-1,-1,6,-1},
        {-1,-1,1,7},
        {8,-1,-1,-1},
        {-1,9,-1,-1},
        {-1,10,-1,-1},
        {-1,-1,-1,-1}
    };
    DFA df1(v,s);
    df1.print_DFA();

    return 0;
}