#include<bits/stdc++.h>

using namespace std;

class Process{
    public:
    int process_id, arrival_time, cpu_time, waiting_time, turnaround_time;

    Process(){}
    Process(int pid, int at, int cpt){
        this->process_id = pid;
        this->arrival_time = at;
        this->cpu_time = cpt;
    }
};
bool operator<(const Process &a, const Process &b){
    return a.cpu_time > b.cpu_time;
}

bool sort_by_serial_comparator(Process a, Process b){
    return a.process_id < b.process_id;
}
bool sort_by_arrival_comparator(Process a, Process b){
    return a.arrival_time < b.arrival_time;
}

vector<Process> processes, sorted_processes;
priority_queue<Process, vector<Process>> ready_q;

int main()
{
    freopen("input.txt", "r", stdin);

    int n, i, at, cput;
    Process current_process;

    cin >> n;
    for(i = 0; i < n; ++i){
        cin >> at >> cput;
        current_process = Process(i, at, cput);
        processes.push_back(current_process);
        sorted_processes.push_back(current_process);
    }
    sort(sorted_processes.begin(), sorted_processes.end(), sort_by_arrival_comparator);

    i = 0;
    current_process = sorted_processes.at(i);
    int current_time = current_process.arrival_time;
    cout << current_time << " ";
    ready_q.push(current_process);
    while(!ready_q.empty()){
        current_process = ready_q.top();
        ready_q.pop();
        processes.at(current_process.process_id).waiting_time = current_time - current_process.arrival_time;
        
        cout << "P" << current_process.process_id << " ";
        current_time += current_process.cpu_time;
        cout << current_time << " ";
        
        processes.at(current_process.process_id).turnaround_time = current_time - current_process.arrival_time;
        for(++i; i < n && sorted_processes.at(i).arrival_time <= current_time; ++i){
            ready_q.push(sorted_processes.at(i));
        }
    }
    cout << endl;

    sort(processes.begin(), processes.end(), sort_by_serial_comparator);
    double avg_wt = 0.0, avg_tat = 0.0;
    for(i = 0; i < n; ++i){
        cout << "P" << processes.at(i).process_id << ": " << processes.at(i).waiting_time << " " << processes.at(i).turnaround_time << endl;
        avg_wt += processes.at(i).waiting_time;
        avg_tat += processes.at(i).turnaround_time;
    }

    avg_wt /= n;
    avg_tat /= n;
    cout << "Average: " << avg_wt << " " << avg_tat;

    return 0;
}
