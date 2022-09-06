#include<bits/stdc++.h>
using namespace std;


int main()
{
    freopen("input2.txt", "r", stdin);


    int i, j;
    int n, nb, pb, nab; // #blocks, #blocks_in_a_file/next_block#, previous_block#, #available_blocks
    char op = 'o', fn; // filename
    
    cin >> n;
    nab = n;
    
    unordered_map<char, int> directory_table;
    vector<int> next_blocks(n, -2); // -2 not allocated, -1 end of file

    while(op != '0'){
        cin >> op >> fn;
        if(op == 'C'){
            cin >> nb;
            if(nb > nab){
                cout << "File " << fn << " could not be created(not enough free blocks)\n";
                continue;
            }
            nab -= nb;
            pb = -1;
            for(j = 0; j < n && nb; ++j){
                if(next_blocks[j] == -2){
                    if(pb == -1){
                        directory_table.insert(make_pair(fn, j));
                    }else{
                    next_blocks[pb] = j;  
                    }

                    pb = j;
                    --nb;
                }
            }
            next_blocks[pb] = -1;
            cout << "File " << fn << " created\n";
        }
        else if(op == 'D'){
            if(directory_table.find(fn) != directory_table.end()){
                nb = directory_table[fn];
                directory_table.erase(fn);
                while(nb != -1){
                    ++nab;
                    pb = nb;
                    nb = next_blocks[nb];
                    next_blocks[pb] = -2;
                }
                cout << "File " << fn << " Deleted\n";
            }
            else{
                cout << "Could not Delete File(File " << fn << " not Found)\n";
            }
        }
        else if(op == 'R'){
            if(directory_table.find(fn) != directory_table.end()){
                nb = directory_table[fn];
                cout << "File " << fn << " Found in blocks: ";
                while(true){
                    cout << nb;
                    nb = next_blocks[nb];
                    if(nb == -1) break;
                    else cout << ", ";
                }
                cout << "\b\b\n";
            }
            else{
                cout << "Could not Read File(File " << fn << " not Found)\n";
            }
        }
    }

    return 0;
}

