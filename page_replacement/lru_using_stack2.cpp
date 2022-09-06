#include<bits/stdc++.h>
using namespace std;

class Stack{
    private:
    list<int> container;
    
    public:
    // common stack methods

    void push(int val){
        container.push_front(val);
    }

    void pop(){
        container.pop_front();
    }

    int top(){
        return container.front();
    }
    
    int size(){
        return container.size();
    }

    // special methods specifically for this problem

    void pop_bottom(){
        container.pop_back();
    }

    bool move_element_to_top(int val){
        list<int>:: iterator itr;
        if( (itr = find(container.begin(), container.end(), val)) != container.end()){
            if(itr != container.begin()){
                container.erase(itr);
                container.push_front(*itr);
            }
            return true;
        }
        return false;
    }
};


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

    Stack frames;
    
    for(int i = 0; i < n; ++i){
        if(frames.size() < m){
            frames.push(refs[i]);
            ++pfc;
        }
        else if(!frames.move_element_to_top(refs[i])){
            frames.pop_bottom();
            frames.push(refs[i]);
            ++pfc;
        }
    }

    cout << "Number of page fault using Least Recently Used Page replacement Algorithm: " << pfc << endl;
    cout <<  "Page Fault Rage: " << round(pfc * 100.0 / n) << "%\n";
 
    return 0;
}