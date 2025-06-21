//
// Created by galig on 14/06/2025.
//

#include "TaskManager.h"
#include "SortedList.h"

TaskManager::TaskManager() {
    for(int i = 0; i < MAX_PERSONS; i++) {
        this->people[i] = Person();
    }
    this->currentsize = 0;
    this->taskID = 0;

}
void TaskManager::assignTask(const string &personName, const Task &task) {
// if person exist:
    Task copy =Task(task);
    copy.setId(this->taskID++);
    for(int i = 0; i < this->currentsize; i++) {
        if (this->people[i].getName() == personName) {
            this->people[i].assignTask(copy);
            return;
        }
    }
    // person doesnt exist:
    if(this->currentsize < MAX_PERSONS) {
        this->people[this->currentsize] = Person(personName);
        this->people[this->currentsize].assignTask(copy);
        this->currentsize++;
        return;
    }

    if (currentsize >= MAX_PERSONS) {
        throw std::runtime_error("TaskManager is full");
    }
}

void TaskManager::completeTask(const string &personName) {
    for(int i = 0; i < this->currentsize; i++) {
        if (this->people[i].getName() == personName) {
            this->people[i].completeTask();
        }
    }
}


void TaskManager::printAllTasks() const {
    SortedList<Task> bucket;   // add them altogether

    for (int i = 0; i < currentsize; ++i) {
        for (const Task& t : people[i].getTasks()) {
            bucket.insert(t);
        }
    }
// now print the sorted list:

    for (const Task& t : bucket) {
        std::cout << t << '\n';
    }
}
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority <= 0 ) {
        return;
    }

    for (int i = 0; i < currentsize; ++i) {
        Person& person = people[i];

        SortedList<Task> updated_tasks = person.getTasks().apply([&](const Task& task) {
     if (task.getType() == type) {
         int new_priority = task.getPriority() + priority;
         if (new_priority > 100) {
             new_priority = 100;
         }
         if (new_priority != task.getPriority()) {
        Task updated_task(new_priority, task.getType(), task.getDescription());
        updated_task.setId(task.getId());
        return updated_task;
}
return task;

     }
     return task;
 });

        person.setTasks(updated_tasks);
    }
}







void TaskManager::printTasksByType(TaskType type) const {

    SortedList<Task> bucket;
    for (int i = 0; i < currentsize; ++i) {
        const SortedList<Task>& tasks = people[i].getTasks();
        for ( SortedList<Task>::ConstIterator it = tasks.begin(); it != tasks.end(); ++it) {
            if ((*it).getType() == type) {
                bucket.insert(*it);           // insert שומר על הסדר (operator>)
            }
        }
    }

    for (SortedList<Task>::ConstIterator it = bucket.begin(); it != bucket.end(); ++it) {
        std::cout << *it << '\n';
    }
}
void TaskManager::printAllEmployees() const {
    for (int i = 0; i < currentsize; ++i) {
        std::cout << people[i] << '\n';
    }
}

