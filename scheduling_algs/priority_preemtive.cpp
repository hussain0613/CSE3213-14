// Implementetion of Preemptive Priority Process Scheduling Algorithm

#include<bits/stdc++.h>

using namespace std;

class ProcessControlBlock{
    public:
    ProcessControlBlock(){}
    ProcessControlBlock(int pid, int a_t, int cpu_t, int p){
        ProcessControlBlock();
        this->pid = pid;
        this->arrival_time = a_t;
        this->cpu_time = cpu_t;
        this->priority = p;

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
    freopen("input", "r", stdin);
    int n, i, j, current_time, q = 1, temp_at, temp_cput, temp_priority;
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
    
    cout << current_time;

    while(!ready_q.empty()){
        // loading
        current_task = tasks.at(ready_q.top());
        ready_q.pop();
        bool preempt = false;

        if(current_task.remaining_time == current_task.cpu_time){
            tasks.at(current_task.pid).start_time = current_time;
            tasks.at(current_task.pid).response_time = current_time - current_task.arrival_time;
        }
        
        // running and checking for new incoming tasks
        while(i+1 < n && current_task.remaining_time > 0){ // i+1<n na dileo hoito, just i+1==n hoile ar ebhabe na kore direct kora jay tai.. ekhane iteration komanor jonno
            // running
            ++current_time;
            --current_task.remaining_time;

            // queueing new incomming tasks
            for(j = i+1; j < n; ++j){
                if(tasks.at(sorted_pids.at(j)).arrival_time <= current_time){
                    ready_q.push(sorted_pids.at(j));
                    if(tasks.at(sorted_pids.at(j)).priority < current_task.priority) 
                        preempt = true;
                }
                else 
                    break;
            }
            i = --j;
            if(preempt) break;
        }
        
        // running without checking for new incoming tasks
        if(!preempt){
            current_time += current_task.remaining_time; // jodi remaining time 0 hoy taile to 0 e, no change.
            current_task.remaining_time = 0;
        }

        // building gantt chart
        cout << " P" << current_task.pid << " " << current_time;

        // unloading
        tasks.at(current_task.pid).remaining_time = current_task.remaining_time;

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
    if(tasks.at(pid1).arrival_time == tasks.at(pid2).arrival_time) 
        return tasks.at(pid1).priority < tasks.at(pid2).priority;
    else
        return tasks.at(pid1).arrival_time < tasks.at(pid2).arrival_time;
}

bool Comparator_priority::operator()(int pid1, int pid2){
    return tasks.at(pid1).priority > tasks.at(pid2).priority;
}

