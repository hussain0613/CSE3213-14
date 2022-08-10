// Implementetion of Round Robin Process Scheduling Algorithm

#include<bits/stdc++.h>

using namespace std;

class ProcessControlBlock{
    public:
    ProcessControlBlock(){}
    ProcessControlBlock(int pid, int a_t, int cpu_t){
        ProcessControlBlock();
        this->pid = pid;
        this->arrival_time = a_t;
        this->cpu_time = cpu_t;
        
        this->waiting_time = 0;
        this->turnaround_time = 0;
        this->turnaround_time = 0;

        this->start_time = 0;
        this->end_time = 0;

        this->remaining_time = cpu_t;
    }

    int pid;
    int arrival_time, cpu_time, waiting_time, turnaround_time, response_time;
    int start_time, end_time;
    int remaining_time;
};

bool comparator_arrival_time(int pid1, int pid2);


vector<ProcessControlBlock> tasks;

int main()
{
    freopen("input3.txt", "r", stdin);
    int n, i, j, current_time, q, temp_at, temp_cput;
    vector<int> sorted_pids;
    ProcessControlBlock current_task;
    queue<int> ready_q;

    cin >> n >> q;
    for(i = 0; i < n; ++i){
        cin >> temp_at >> temp_cput;
        ProcessControlBlock temp_task = ProcessControlBlock(i, temp_at, temp_cput);
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
        current_task = tasks.at(ready_q.front());
        ready_q.pop();
        int q2 = min(current_task.remaining_time, q);

        if(current_task.remaining_time == current_task.cpu_time){
            
            tasks.at(current_task.pid).start_time = current_time;
            tasks.at(current_task.pid).response_time = current_time - current_task.arrival_time;
        }
        
        // running
        current_time += q2;
        current_task.remaining_time -= q2;
        tasks.at(current_task.pid).remaining_time = current_task.remaining_time;

        // queueing new incoming processes
        for(j = i+1; j < n; ++j){
            if(tasks.at(sorted_pids.at(j)).arrival_time <= current_time) 
                ready_q.push(sorted_pids.at(j));
            else 
                break;
        }
        i = --j;

        // building gantt chart
        cout << " P" << current_task.pid << " " << current_time;

        // unloading/context switching
        if(current_task.remaining_time == 0){
            tasks.at(current_task.pid).turnaround_time = current_time - current_task.arrival_time;
            tasks.at(current_task.pid).waiting_time = tasks.at(current_task.pid).turnaround_time - current_task.cpu_time;
            tasks.at(current_task.pid).end_time = current_time;
        }else ready_q.push(current_task.pid);
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
    return tasks.at(pid1).arrival_time < tasks.at(pid2).arrival_time;
}
