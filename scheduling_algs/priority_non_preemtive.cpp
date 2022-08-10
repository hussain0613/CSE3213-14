// Implementetion of Non-Preemptive Priority Process Scheduling Algorithm

#include<bits/stdc++.h>

using namespace std;

class ProcessControlBlock{
    public:
    ProcessControlBlock(){}
    ProcessControlBlock(int pid, int a_t, int cpu_t, int p){
        this->pid = pid;
        this->arrival_time = a_t;
        this->cpu_time = cpu_t;
        this->priority = p;

        this->waiting_time = 0;
        this->turnaround_time = 0;
        this->turnaround_time = 0;

        this->start_time = 0;
        this->end_time = 0;
    }

    int pid;
    int arrival_time, cpu_time, waiting_time, turnaround_time, response_time;
    int start_time, end_time;
    //int current_running_time; will be necessary for preemptive algorithms
    int priority;
};

bool comparator_arrival_time(int pid1, int pid2);
class Comparator_priority{
    public:
    bool operator()(int pid1, int pid2);
};

vector<ProcessControlBlock> tasks;

int main()
{
    freopen("input2.txt", "r", stdin);
    int n, i, j, current_time, q, temp_at, temp_cput, temp_priority;
    vector<int> sorted_pids;
    ProcessControlBlock current_task;
    priority_queue<int, vector<int>, Comparator_priority> ready_q;

    cin >> n;
    for(i = 0; i < n; ++i){
        cin >> temp_at >> temp_cput >> temp_priority;
        ProcessControlBlock temp_task = ProcessControlBlock(i, temp_at, temp_cput, temp_priority);
        tasks.push_back(temp_task);
        sorted_pids.push_back(i);
    }

    sort(sorted_pids.begin(), sorted_pids.end(), comparator_arrival_time);

    i = 0;
    ready_q.push(sorted_pids.at(i));
    current_time = tasks.at(sorted_pids.at(i)).arrival_time;
    
    cout << "Gantt Chart:\n";
    cout << current_time;

    while(!ready_q.empty()){
        // loading
        current_task = tasks.at(ready_q.top());
        ready_q.pop();

        current_task.start_time = current_time;
        current_task.response_time = current_time - current_task.arrival_time;
        
        // running
        current_time += current_task.cpu_time;

        // queueing new incoming processes
        for(j = i + 1; j < n; ++j){
            if(tasks.at(sorted_pids.at(j)).arrival_time <= current_time) ready_q.push(sorted_pids.at(j)); // priority preemptive e < hobe instead of <=
            else break;
        }
        i = --j;

        // building gantt chart
        cout << " P" << current_task.pid << " " << current_time;

        // unloading
        tasks.at(current_task.pid).turnaround_time = current_time - current_task.arrival_time;
        tasks.at(current_task.pid).waiting_time = tasks.at(current_task.pid).turnaround_time - current_task.cpu_time;
        tasks.at(current_task.pid).end_time = current_time;
    }
    cout << endl;

    // printing wating time and turnaround time table and calculating averages
    printf("\nProcess \t Waiting Time \t Turnaround Time\n");
    double avg_wt, avg_tat;
    for(i = 0; i < n; ++i){
        temp_at = tasks.at(i).waiting_time;
        temp_cput = tasks.at(i).turnaround_time;
        printf("P%d \t %d \t %d\n", i, temp_at, temp_cput);

        avg_wt += temp_at;
        avg_tat += temp_cput;
    }

    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage Waiting Time: %lf\n", avg_wt);
    printf("Average Turnaround Time: %lf\n", avg_tat);


    return 0;
}


bool comparator_arrival_time(int pid1, int pid2){
    if(tasks.at(pid1).arrival_time == tasks.at(pid2).arrival_time) 
        return tasks.at(pid1).priority < tasks.at(pid2).priority;
    else
        return tasks.at(pid1).arrival_time < tasks.at(pid2).arrival_time;
}

bool Comparator_priority::operator()(int pid1, int pid2){
    return tasks.at(pid1).priority > tasks.at(pid2).priority;
}

