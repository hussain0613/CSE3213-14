/*
example 1:
input:
4 
3
3 2 2
1 0 0
6 1 3
5 1 1
3 1 4
2 1 1
4 2 2
0 0 2
9 3 6
output:
The System is currently in safe state and < P2 P1 P3 P4 > is the safe sequence
*/
/*
Example 2:
input:
2
2
4 4
3 3
3 4
2 3
output:
The System is currently in unsafe mode.
*/

#include<bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input3.txt", "r", stdin);

    int no_proc, no_res;
    cin >> no_proc >> no_res;

    vector<int> 
        capacity(no_res, 0),
        available(no_res, 0),
        safe_sequence;
    
    vector<vector<int> > 
        allocation(no_proc, vector<int>(no_res, 0)), 
        max_need(no_proc, vector<int>(no_res, 0)),
        need(no_proc, vector<int>(no_res, 0));
    
    vector<bool> is_done(no_proc, false);
    
    for(int i = 0; i < no_proc; ++i){
        for(int j = 0; j < no_res; ++j){
            cin >> max_need[i][j];
        }
        for(int j = 0; j < no_res; ++j){
            cin >> allocation[i][j];
            
            available[j] -= allocation[i][j];
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }
    for(int j = 0; j < no_res; ++j){
        cin >> capacity[j];
        available[j] += capacity[j];
    }

    for(int i = 0; i < no_proc; ++i){
        if(is_done[i]) continue;
        
        int j = 0;
        for(; j < no_res; ++j){
            if(need[i][j] > available[j]) break;
        }
        
        if(j == no_res){
            
            for(j = 0; j < no_res; ++j){
                available[j] += allocation[i][j];
            }
            is_done[i] = true;
            safe_sequence.push_back(i+1);
            i = -1;
        }
    }
    if(safe_sequence.size() == no_proc){
        cout << "The System is currently in safe state and < ";
        for(int i = 0; i < safe_sequence.size(); ++i){
            printf("P%d ", safe_sequence[i]);
        }
        cout << "> is the safe sequence" << endl;
    }
    else{
        cout << "The System is currently in unsafe mode.\n";
    }
    

    return 0;
}
