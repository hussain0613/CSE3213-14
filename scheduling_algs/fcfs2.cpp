#include<bits/stdc++.h>

using namespace std;

class Process{
    public:
    int process_number, arrival_time, cpu_time, waiting_time, turnaround_time;

    Process(){}
    Process(int pn, int at, int cpt){
        this->process_number = pn;
        this->arrival_time = at;
        this->cpu_time = cpt;
    }

    bool operator<(Process other){
        return this->arrival_time < other.arrival_time;
    }
};

bool sort_by_serial_comparator(Process a, Process b){
    return a.process_number < b.process_number;
}

vector<Process> processes;

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
    }

    sort(processes.begin(), processes.end());

    current_process = processes.at(0);
    int current_time = current_process.arrival_time;
    cout << current_time << " ";
    for(i = 0; i < n; ++i){
        current_process = processes.at(i);
        processes.at(i).waiting_time = current_time - current_process.arrival_time;
        
        cout << "P" << current_process.process_number << " ";
        current_time += current_process.cpu_time;
        cout << current_time << " ";
        
        processes.at(i).turnaround_time = current_time - current_process.arrival_time;
    }
    cout << endl;

    sort(processes.begin(), processes.end(), sort_by_serial_comparator);
    double avg_wt = 0.0, avg_tat = 0.0;
    for(i = 0; i < n; ++i){
        cout << "P" << processes.at(i).process_number << ": " << processes.at(i).waiting_time << " " << processes.at(i).turnaround_time << endl;
        avg_wt += processes.at(i).waiting_time;
        avg_tat += processes.at(i).turnaround_time;
    }

    avg_wt /= n;
    avg_tat /= n;
    cout << "Average: " << avg_wt << " " << avg_tat;

    return 0;
}
