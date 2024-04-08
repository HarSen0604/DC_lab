#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

int num_processes;
bool visited[MAX_PROCESSES];
bool rec_stack[MAX_PROCESSES];

bool isCycleUtil(int wait_for_graph[][MAX_PROCESSES], int i) {
    if (rec_stack[i]) {
        return true;
    }
    if (visited[i]) {
        return false;
    }

    visited[i] = true;
    rec_stack[i] = true;

    for (int j = 0; j < num_processes; j++) {
        if (wait_for_graph[i][j]) {
            if (isCycleUtil(wait_for_graph, j))
                return true;
        }
    }
    rec_stack[i] = false; // Remove the process from recursion stack
    return false;
}

bool detectCycle(int wait_for_graph[][MAX_PROCESSES]) {
    for (int i = 0; i < num_processes; i++) {
        visited[i] = false;
        rec_stack[i] = false;
    }

    for (int i = 0; i < num_processes; i++) {
        if (!visited[i] && isCycleUtil(wait_for_graph, i))
            return true;
    }
    return false;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int wait_for_graph[MAX_PROCESSES][MAX_PROCESSES] = {0};

    // Input processes that are holding resources
    printf("\n--------\nEnter the processes that are holding resources (Enter -1 to stop):\n");
    int process, resource;
    while (true) {
        printf("\nFrom process: ");
        scanf("%d", &process);
        if (process == -1) break;
        printf("To process: ");
        scanf("%d", &resource);
        wait_for_graph[process][resource] = 1; // Mark the edge in the wait-for graph
    }

    // Check for deadlock in the wait-for graph
    if (detectCycle(wait_for_graph))
        printf("Deadlock detected!\n");
    else
        printf("No deadlock detected.\n");

    return 0;
}
