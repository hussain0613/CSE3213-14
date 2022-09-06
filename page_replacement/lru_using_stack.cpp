#include<bits/stdc++.h>
using namespace std;

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

    list<int> frames_stack;
    list<int>::iterator itr;
    
    for(int i = 0; i < n; ++i){
        if(frames_stack.size() < m){
            frames_stack.push_front(refs[i]); // pushing to the top of stack 
            ++pfc;
        }
        else if( (itr = find(frames_stack.begin(), frames_stack.end(), refs[i])) != frames_stack.end()){ // finding the reference page in stack
            if(itr != frames_stack.begin()){
                frames_stack.erase(itr); // taking the reference page from the middle or end of the stack
                frames_stack.push_front(*itr); // and it pushing to the top of stack 
            }
        }else{
            frames_stack.pop_back(); // removing the bottom of the stack
            frames_stack.push_front(refs[i]); // pushing the new request to the top of the stack
            ++pfc;
        }

    }

    cout << "Number of page fault using Least Recently Used Page replacement Algorithm: " << pfc << endl;
    cout <<  "Page Fault Rage: " << round(pfc * 100.0 / n) << "%\n";
 
    return 0;
}