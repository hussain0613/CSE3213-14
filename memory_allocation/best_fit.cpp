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
        int fit_hole = -1;
        int diff = INT_MAX;

        for(int j = 0; j < m; ++j){
            int temp_diff = holes[j] - requests[i];
            if(0 <= temp_diff && temp_diff < diff){
                diff = temp_diff;
                fit_hole = j;
            }
        }
        
        if(fit_hole < 0) break;

        --unallocated_count;
        holes[fit_hole] -= requests[i];

        for(int j = 0; j < m; ++j){
            memory[j][i] = holes[j];
        }
    }

    cout << "Best Fit\n\n";

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