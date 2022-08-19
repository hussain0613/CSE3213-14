// CSE3214 Online 08

#include<bits/stdc++.h>
using namespace std;

//*
int index_of(int val, vector<int> vec){
    int i = 0;
    for(; i < vec.size(); ++i){
        if(vec[i] == val) break;
    }
    if(i == vec.size()) return -1;
    else return i;
}
//*/
//*
int get_victim_index(vector<int> frames,  vector<int> refs, int current_ref){
    int farthest = 0;
    int vic_index = 0;
    for(int potential_vic = 0; potential_vic < frames.size(); ++potential_vic){
        int nearest_next_ref_of_pot_vic = current_ref + 1;
        for(; nearest_next_ref_of_pot_vic < refs.size(); ++nearest_next_ref_of_pot_vic){
            if(refs[nearest_next_ref_of_pot_vic] == frames[potential_vic]) break;
        }
        if(nearest_next_ref_of_pot_vic == refs.size()){
            farthest = nearest_next_ref_of_pot_vic;
            vic_index = potential_vic;
            break;
        }
        else if(nearest_next_ref_of_pot_vic > farthest){
            farthest = nearest_next_ref_of_pot_vic;
            vic_index = potential_vic;
        }
    }
    return vic_index;
}
//*/

int main()
{
    freopen("input.txt", "r", stdin);

    int p, n, m, pfc = 0;

    cin >> p >> n;

    vector<int> refs, frames, non_faulty;

    for(int i = 0; i < n; ++i){
        int temp;
        cin >> temp;
        refs.push_back(temp);
    }
    cin >> m;

    for(int i = 0; i < n; ++i){
        // cout << "Req: " << refs[i];
        if(frames.size() < m){
            // cout << " fault ";
            frames.push_back(refs[i]);
            ++pfc;
        }
        else if(index_of(refs[i], frames) == -1){
            // cout << " fault2 ";
            ++pfc;
            int victim_index = get_victim_index(frames, refs, i);
            // cout << "victim index in frames: " << victim_index << " victim: " << frames[victim_index];
            frames[victim_index] = refs[i];
        }
        else{
            non_faulty.push_back(refs[i]);
        }
        // cout << endl;
    }

    printf("Number of page fault using Optimal Page replacement Algorithm: %d\n", pfc);
    printf("Page fault Rate: %.0f%\n", (pfc*100.0)/n);
    printf("Pages without fault: ");

    for(int i = 0; i < non_faulty.size(); ++i){
        cout << non_faulty[i] << " ";
    }
    cout << endl;

    return 0;
}
