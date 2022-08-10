#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int m, n, unallocated_count;
    cin >> m >> n;

    unallocated_count = n;
    vector<int> holes(m), requests(n);
    vector<vector<int> > memory(m, vector<int>(n, 0));

    for(int i = 0; i < m; ++i){
        cin >> holes[i];
    }
    for(int i = 0; i < n; ++i){
        cin >> requests[i];
    }

    for(int i = 0; i < n; ++i){
        int j = 0;
        for(; j < m; ++j){
            if(requests[i] <= holes[j]){
                holes[j] -= requests[i];
                break;
            }
        }
        
        if(j == m) break;
        
        --unallocated_count;
        for(int j = 0; j < m; ++j){
            memory[j][i] = holes[j];
        }
    }

    cout << "First Fit\n\n";

    for(int i = 0; i < n; ++i){
        cout << requests[i] << " \t ";
    }
    cout << endl;
    
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cout << memory[i][j] << " \t ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "External Fragmentation: " << ( unallocated_count? accumulate(holes.begin(), holes.end(), 0): 0) << endl;

    return 0;
}