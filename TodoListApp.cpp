
//A basic todo list app should allow users to:
// Add tasks: Allow users to input task descriptions.
// View tasks: Display the list of tasks.
// Mark tasks as complete: Toggle the completion status of a task.
// Delete tasks: Remove completed or unwanted tasks.
// Save and load tasks: Persist the todo list for future use.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Task {
    string description;
    bool isCompleted;
};

vector<Task> tasks;

void addTask() {
    string description;
    cout << "Enter task description: ";
    getline(cin, description);
    tasks.push_back({description, false});
    cout << "Task added successfully.\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
    } else {
        cout << "Tasks:\n";
        for (int i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].description;
            if (tasks[i].isCompleted) {
                cout << " (Completed)";
            }
            cout << endl;
        }
    }
}

void markTaskCompleted(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].isCompleted = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task index.\n";
    }
}

void deleteTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
        cout << "Task deleted.\n";
    } else {
        cout << "Invalid task index.\n";
    }
}

void saveTasksToFile(string filename) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const Task& task : tasks) {
            outfile << task.description << endl;
            outfile << task.isCompleted << endl;
        }
        outfile.close();
        cout << "Tasks saved to file.\n";
    } else {
        cout << "Error saving tasks to file.\n";
    }
}

void loadTasksFromFile(string filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            Task task;
            task.description = line;
            getline(infile, line);
            task.isCompleted = (line == "true");
            tasks.push_back(task);
        }
        infile.close();
        cout << "Tasks loaded from file.\n";
    } else {
        cout << "Error loading tasks from file.\n";
    }
}

int main() {
    loadTasksFromFile("tasks.txt");

    while (true) {
        cout << "\nTodo List App\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Save Tasks\n";
        cout << "6. Load Tasks\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3: {
                int index;
                cout << "Enter task index to mark as completed: ";
                cin >> index;
                markTaskCompleted(index - 1);
                break;
            }
            case 4: {
                int index;
                cout << "Enter task index to delete: ";
                cin >> index;
                deleteTask(index - 1);
                break;
            }
            case 5:
                saveTasksToFile("tasks.txt");
                break;
            case 6:
                loadTasksFromFile("tasks.txt");
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}