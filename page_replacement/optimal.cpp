#include<bits/stdc++.h>
using namespace std;

bool less_then(pair<int, int> first, pair<int, int> second)
{
    return first.second < second.second;
}


int main()
{
    freopen("input.txt", "r", stdin);

    int p, n, m, pfc = 0;
    cin >> p >> n;
    
    vector<int> refs(n);

    for(int i = 0; i < n; ++i){
        cin >> refs[i];
    }

    cin >> m;

    map<int, int> frames;

    for(int i = 0; i < n; ++i){
        if(frames.find(refs[i]) == frames.end()){
            if(frames.size() >= m){
                map<int, int>::iterator farthest = max_element(frames.begin(), frames.end(), less_then);
                frames.erase(farthest->first);
            }
            ++pfc;
        }
        
        int j = i + 1;
        for(; j < n; ++j){
            if(refs[i] == refs[j]) break;
        }
        frames[refs[i]] = j==n? INT_MAX : j;
    }

    cout << "Number of page fault using Optimal Page replacement Algorithm: " << pfc << endl;
    cout <<  "Page Fault Rage: " << round(pfc * 100.0 / n) << "%\n";
 
    return 0;
}