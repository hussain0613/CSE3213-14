#include<bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input3.txt", "r", stdin);

    int no_proc, no_res;
    cin >> no_proc >> no_res;

    vector<int> 
        capacity(no_res, 0),
        available(no_res, 0);
    
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

    // for(int i = 0; i < no_proc; ++i){
    //     for(int j = 0; j < no_res; ++j){
    //         cout << need[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for(int j = 0; j < no_res; ++j){
    //     cout << available[j] << " ";
    // }
    // cout << "\n";
    
    bool work_done = true;
    while(work_done){
        work_done = false;
        
        for(int i = 0; i < no_proc; ++i){
            if(is_done[i]) continue;
            
            int j = 0;
            for(; j < no_res; ++j){
                if(need[i][j] > available[j]) break;
            }
            
            if(j == no_res){
                is_done[i] = true;
                work_done = true;
                cout << "P" << i+1 << " ";

                for(j = 0; j < no_res; ++j){
                    available[j] += allocation[i][j];
                }
            }
        }
    }
    cout << endl;

    return 0;
}
