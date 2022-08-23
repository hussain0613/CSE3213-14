#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int n = 0, head_count, current_head_pos, total_mov = 0;
    vector<int> reqs;
    vector<bool> visited;

    cin >> head_count;

    char ch = '\0';
    while(ch != '\n'){
        int temp;
        cin >> temp;
        reqs.push_back(temp);
        ch = getchar();
        visited.push_back(false);
    }
    cin >> current_head_pos;

    n = reqs.size();

    cout << "Cylinder Serving Order: ";
    
    bool complete = false;
    while(!complete){
        complete = true;
        int min_dist = INT_MAX;
        int next_head_index = -1;

        cout << current_head_pos;
        
        for(int i = 0; i < n; ++i){
            if(!visited[i]){
                complete = false;
                int dist = abs(current_head_pos - reqs[i]);
                if(dist < min_dist){
                    min_dist = dist;
                    next_head_index = i;
                }
            }
        }
        if(next_head_index > -1){
            visited[next_head_index] = true;
            current_head_pos = reqs[next_head_index];
            total_mov += min_dist;
        }
        if(!complete) cout << " -> ";
    }
    cout << endl;

    cout << "Total Cylinder movement: " << total_mov << endl;

    return 0;
}