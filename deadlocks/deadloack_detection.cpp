#include<bits/stdc++.h>
#define MX 20

using namespace std;

class Node{
    public:
    char name;
    int state;
    vector<Node> ajd;
};


int main()
{
    freopen("input2.txt", "r", stdin);
    // basic graph related
    int n;
    vector<char> nodes;
    unordered_map<char, int> nodes_map;
    
    vector<int> node_is_visited, ancestors;
    stack<int> S;
    vector<vector<int>> cycles;

    cin >> n;

    vector<vector<int>> graph(n, vector<int> (n, 0));

    for(int i = 0; i < n; ++i){
        char node;
        cin >> node;

        nodes.push_back(node);
        nodes_map.insert(make_pair(node, i));
        node_is_visited.push_back(0);
        ancestors.push_back(-1);
    }

    while(!feof(stdin)){
        char from, to;
        cin >> from >> to;
        graph[nodes_map[from]][nodes_map[to]] = 1;
    }


    cout << "Nodes: \n";
    for(int i = 0; i < n; ++i){
        cout << nodes[i] << " " << i << endl;
    }

    cout << "\nThe Graph: \n";
    
    cout << "  ";
    for(int j = 0; j < n; ++j){
        cout << nodes[j] << " ";
    }
    cout << endl;
    for(int i = 0; i < n; ++i){
        cout << nodes[i] << " ";
        for(int j = 0; j < n; ++j){
            char c = graph[i][j]? '1':'-';
            cout << c << " ";
        }
        cout << endl;
    }

    cout << "\nDFS: ";
    for(int root_node = 0; root_node < n; ++root_node){
        if(node_is_visited[root_node]) continue;

        S = {};
        S.push(root_node);
        
        while(!S.empty()){
            int current_node = S.top();
            S.pop();
            node_is_visited[current_node] = 1;
            cout << nodes[current_node] << " ";
            
            for(int adj_node = 0; adj_node < n; ++adj_node){
                if(graph[current_node][adj_node] == 1){ // this line and aloung with the previous one, for j in adj(current_node)
                    
                    if(!node_is_visited[adj_node]) {
                        S.push(adj_node);
                        ancestors[adj_node] = current_node;
                    }else if(node_is_visited[adj_node]){
                        int ancestor = ancestors[current_node];
                        if(ancestor < 0) continue;

                        vector<int> cycle;
                        cycle.push_back(current_node);
                        while(ancestor >= 0 && ancestor != adj_node){
                            cycle.push_back(ancestor);
                            ancestor = ancestors[ancestor];
                        }
                        cycle.push_back(ancestor);
                        if(ancestor == adj_node) cycles.push_back(cycle);
                    }
                }
            }
        }
    }
    
    cout << "\n\nNumber of cycles detected: " << cycles.size() << endl << endl;

    for(int i = 0; i < cycles.size(); ++i){
        printf("Cycle-%d (%d): ", i+1, cycles[i].size());
        for(int j = cycles[i].size() - 1; j >= 0; --j){
            cout << nodes[cycles[i][j]] << " ";
        }
        cout << endl;
    }

    return 0;
}


