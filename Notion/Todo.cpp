#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    int taskId;
    string taskName;
    int dueDate;
    unordered_set<string> tags;
    bool finish;

    Task(int id, string name, int due, vector<string>& tagList)
        : taskId(id), taskName(name), dueDate(due), finish(false) {
        tags.insert(tagList.begin(), tagList.end());
    }
};

struct CompareTask {
    bool operator()(const Task* a, const Task* b) const {
        if (a->dueDate == b->dueDate)
            return a->taskId < b->taskId;  // tie breaker
        return a->dueDate < b->dueDate;
    }
};

class TodoList {
private:
    int idCounter;
    unordered_map<int, set<Task*, CompareTask>> tasks;

public:
    TodoList() {
        idCounter = 1;
    }

    int addTask(int userId, string taskDescription, int dueDate, vector<string> tags) {
        Task* task = new Task(idCounter++, taskDescription, dueDate, tags);
        tasks[userId].insert(task);
        return task->taskId;
    }

    vector<string> getAllTasks(int userId) {
        vector<string> ans;
        if (tasks.find(userId) == tasks.end())
            return ans;

        for (auto task : tasks[userId]) {
            if (!task->finish)
                ans.push_back(task->taskName);
        }
        return ans;
    }

    vector<string> getTasksForTag(int userId, string tag) {
        vector<string> ans;
        if (tasks.find(userId) == tasks.end())
            return ans;

        for (auto task : tasks[userId]) {
            if (!task->finish && task->tags.count(tag))
                ans.push_back(task->taskName);
        }
        return ans;
    }

    void completeTask(int userId, int taskId) {
        if (tasks.find(userId) == tasks.end())
            return;

        for (auto task : tasks[userId]) {
            if (task->taskId == taskId) {
                task->finish = true;
                break;
            }
        }
    }
};