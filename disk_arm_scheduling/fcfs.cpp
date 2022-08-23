#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int n = 0, head_count, current_head_pos, total_mov = 0;
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

    cout << "Cylinder Serving Order: ";
    cout << current_head_pos;
    if(n>0) cout << " -> ";

    for(int i = 0; i < reqs.size(); ++i){
        total_mov += abs(reqs[i] - current_head_pos);
        current_head_pos = reqs[i];
        cout << current_head_pos;
        if(i < reqs.size() - 1) cout << " -> ";
    }
    cout << endl;

    cout << "Total Cylinder movement: " << total_mov << endl;

    return 0;
}