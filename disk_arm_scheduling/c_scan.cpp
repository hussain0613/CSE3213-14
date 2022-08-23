#include<bits/stdc++.h>
using namespace std;

int fcfs(int current_head_pos, vector<int> reqs, int start, int end, int total_mov){
    for(int i = start; i < end; ++i){
        total_mov += abs(reqs[i] - current_head_pos);
        current_head_pos = reqs[i];
        cout << current_head_pos;
        if(i < end - 1) cout << " -> ";
    }

    return total_mov;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int n = 0, head_count, current_head_pos, total_mov = 0, divider = 0;
    vector<int> reqs;

    cin >> head_count;

    char ch = '\0';
    while(ch != '\n'){
        int temp;
        cin >> temp;
        reqs.push_back(temp);
        ch = getchar();
    }
    cin >> current_head_pos;

    n = reqs.size();

    sort(reqs.begin(), reqs.end());

    for(int i = 0; i < n; ++i){
        if(reqs[i] > current_head_pos){
            divider = i;
            break;
        }
    }
    
    cout << "Cylinder Serving Order: ";
    cout << current_head_pos;
    if(n>0) cout << " -> ";

    total_mov += fcfs(current_head_pos, reqs, divider, reqs.size(), total_mov);
    if(divider > 0) cout << " -> ";
    total_mov += fcfs(current_head_pos, reqs, 0, divider, total_mov);
    cout << endl;

    cout << "Total Cylinder movement: " << total_mov << endl;

    return 0;
}