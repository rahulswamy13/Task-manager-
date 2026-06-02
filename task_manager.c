#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Task {
    char title[100];
    int done;
};

struct Task tasks[MAX];
int count = 0;

// Load tasks from file
void loadTasks() {
    FILE *fp = fopen("tasks.txt", "r");
    if (fp == NULL) return;

    count = 0;
    while (fscanf(fp, " %[^
] %d", tasks[count].title, &tasks[count].done) != EOF) {
        count++;
    }
    fclose(fp);
}

// Save tasks to file
void saveTasks() {
    FILE *fp = fopen("tasks.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d\n", tasks[i].title, tasks[i].done);
    }
    fclose(fp);
}

// Add task
void addTask() {
    printf("Enter task: ");
    getchar();
    fgets(tasks[count].title, 100, stdin);
    tasks[count].title[strcspn(tasks[count].title, "\n")] = 0;

    tasks[count].done = 0;
    count++;

    saveTasks();
    printf("Task added!\n");
}

// View tasks
void viewTasks() {
    if (count == 0) {
        printf("No tasks found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d. %s [%s]\n", i + 1, tasks[i].title,
               tasks[i].done ? "Done" : "Pending");
    }
}

// Mark task as done
void markDone() {
    int index;
    viewTasks();

    printf("Enter task number: ");
    scanf("%d", &index);

    if (index < 1 || index > count) {
        printf("Invalid choice.\n");
        return;
    }

    tasks[index - 1].done = 1;
    saveTasks();
    printf("Task marked as done!\n");
}

// Delete task
void deleteTask() {
    int index;
    viewTasks();

    printf("Enter task number: ");
    scanf("%d", &index);

    if (index < 1 || index > count) {
        printf("Invalid choice.\n");
        return;
    }

    for (int i = index - 1; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    count--;
    saveTasks();
    printf("Task deleted!\n");
}

// Main function
int main() {
    int choice;
    loadTasks();

    while (1) {
        printf("\n==== Task Manager ====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task Done\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markDone(); break;
            case 4: deleteTask(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}
