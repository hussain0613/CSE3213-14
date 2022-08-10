#include<bits/stdc++.h>

using namespace std;

struct Priority{
    bool operator()(int a, int b);
};

bool comparator(int a, int b);

vector<pair<int, int>> process_details;
vector<int> process_numbers, waiting_times, tats;
priority_queue<int, vector<int>, Priority> ready_q;

int main()
{
    freopen("input.txt", "r", stdin);

    int n, i, at, cput;

    cin >> n;
    for(i = 0; i < n; ++i){
        cin >> at >> cput;
        process_details.push_back(make_pair(at, cput));
        process_numbers.push_back(i);
        waiting_times.push_back(0);
        tats.push_back(0);
    }

    sort(process_numbers.begin(), process_numbers.end(), comparator);

    i = 0;
    int current_process = process_numbers.at(i);
    int current_time = process_details.at(current_process).first;
    ready_q.push(current_process);
    cout << current_time << " ";
    while(!ready_q.empty()){
        current_process = ready_q.top();
        ready_q.pop();

        waiting_times.at(current_process) = current_time - process_details.at(current_process).first;
        
        cout << "P" << current_process << " ";
        current_time += process_details.at(current_process).second;
        cout << current_time << " ";
        
        tats.at(current_process) = current_time - process_details.at(current_process).first;

        // if(i+1 < n) fill_rq(i, current_time);
        for(++i; i < n && process_details.at(i).first <= current_time; ++i){
            ready_q.push(process_numbers.at(i));
        }
    }
    cout << endl;

    double avg_wt = 0.0, avg_tat = 0.0;
    for(i = 0; i < n; ++i){
        cout << "P" << i << ": " << waiting_times.at(i) << " " << tats.at(i) << endl;
        avg_wt += waiting_times.at(i);
        avg_tat += tats.at(i);
    }

    avg_wt /= waiting_times.size();
    avg_tat /= tats.size();
    cout << "Average: " << avg_wt << " " << avg_tat;

    return 0;
}

bool comparator(int a, int b)
{
    return process_details.at(a).first < process_details.at(b).first;
}

bool Priority::operator()(int a, int b){
    return process_details.at(a).second > process_details.at(b).second;
}
