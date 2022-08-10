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
class Comparator_cpu_time{
    public:
    bool operator()(int a, int b);
};
bool comparator_arrival_time(int a, int b);

vector<Process> processes;
vector<int> sorted_pids;
priority_queue<int, vector<int>, Comparator_cpu_time> ready_q;

int main()
{
    freopen("input.txt", "r", stdin);

    int n, i, at, cput, current_pid;
    Process current_process;

    cin >> n;
    for(i = 0; i < n; ++i){
        cin >> at >> cput;
        current_process = Process(i, at, cput);
        processes.push_back(current_process);
        sorted_pids.push_back(i);
    }
    sort(sorted_pids.begin(), sorted_pids.end(), comparator_arrival_time);

    i = 0;
    current_pid = sorted_pids.at(0);
    current_process = processes.at(current_pid);
    int current_time = current_process.arrival_time;
    
    cout << current_time << " ";
    ready_q.push(current_pid);
    while(!ready_q.empty()){
        current_pid = ready_q.top();
        current_process = processes.at(current_pid);
        ready_q.pop();
        
        processes.at(current_pid).waiting_time = current_time - current_process.arrival_time;
        
        cout << "P" << current_process.process_id << " ";
        current_time += current_process.cpu_time;
        cout << current_time << " ";
        
        processes.at(current_pid).turnaround_time = current_time - current_process.arrival_time;
        for(++i; i < n && processes.at(sorted_pids.at(i)).arrival_time <= current_time; ++i){
            ready_q.push(sorted_pids.at(i));
        }
    }
    cout << endl;

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

bool Comparator_cpu_time::operator()(int a, int b){
    return processes.at(a).cpu_time > processes.at(b).cpu_time;
}


bool comparator_arrival_time(int a, int b){
    return processes.at(a).arrival_time < processes.at(b).arrival_time;
};

