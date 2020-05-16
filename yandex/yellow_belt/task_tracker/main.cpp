#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks.at(person);
    }
    
    void AddNewTask(const string& person) {
        tasks[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        auto result = make_tuple<TasksInfo, TasksInfo>({}, {});
        if (tasks.count(person) == 0) return result;
        TasksInfo& current_tasks = tasks.at(person);

        TasksInfo& updated_tasks = get<0>(result);
        TasksInfo& untouched_tasks = get<1>(result);
        int status_count = static_cast<int>(TaskStatus::DONE) + 1;
        int updated_task_count = 0;
        for (int i = 0; i < status_count; i++) {
            TaskStatus current_status = static_cast<TaskStatus>(i);
            if (i == (status_count - 1)) task_count = 0;
            if (updated_task_count > 0) updated_tasks[current_status] = updated_task_count;

            int current_task_count = current_tasks[current_status];
            current_tasks[current_status] = updated_task_count;
            updated_task_count = min(current_task_count, task_count);
            task_count -= updated_task_count;

            int untouched_task_count = current_task_count - updated_task_count;
            if (untouched_task_count > 0) {
                if (i != (status_count - 1)) untouched_tasks[current_status] = untouched_task_count;
                current_tasks[current_status] += untouched_task_count;
            }

            if (current_tasks[current_status] == 0) {
                current_tasks.erase(current_status);
            }
        }
        return result;
    }

private:
    map<string, TasksInfo> tasks;
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    
    TasksInfo updated_tasks, untouched_tasks;
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}