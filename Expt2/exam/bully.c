#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 1024

int processes[MAX_PROCESSES], num_processes, coordinator;

void display_processes() {
    printf("\nProcesses-->");
    for (int i = 1; i <= num_processes; i++)
        printf("\t %d", i);
    printf("\nAlive-->");
    for (int i = 1; i <= num_processes; i++)
        printf("\t %d", processes[i]);
    printf("\nCoordinator is: %d", coordinator);
}

void crash_process() {
    int crash_id, generator_id, new_coordinator = 0;
    printf("\nEnter Process no. to Crash: ");
    scanf("%d", &crash_id);
    if (processes[crash_id] == 1) {
        processes[crash_id] = 0;
    } else {
        printf("\nProcess is already dead!!");
        return;
    }
    do {
        printf("\nEnter election generator id: ");
        scanf("%d", &generator_id);
    } while (generator_id == coordinator || generator_id == crash_id);

    if (crash_id == coordinator) {
        for (int i = generator_id + 1; i <= num_processes; i++) {
            printf("\nMessage sent from %d to %d", generator_id, i);
            if (processes[i]) {
                new_coordinator = i;
                printf("\nResponse sent from %d to %d", i, generator_id);
            }
        }
        if (new_coordinator == 0) {
            new_coordinator = generator_id;
        }
        coordinator = new_coordinator;
    }
    display_processes();
}

void activate_process() {
    int activate_id, new_coordinator;
    printf("\nEnter Process no. to Activate: ");
    scanf("%d", &activate_id);
    if (processes[activate_id] == 0) {
        processes[activate_id] = 1;
    } else {
        printf("\nProcess is already alive!!");
        return;
    }
    if (activate_id == num_processes) {
        coordinator = num_processes;
        display_processes();
        return;
    }
    new_coordinator = 0;
    for (int i = activate_id + 1; i <= num_processes; i++) {
        printf("\nMessage sent from %d to %d", activate_id, i);
        if (processes[i]) {
            new_coordinator = i;
            printf("\nResponse sent from %d to %d", i, activate_id);
        }
    }
    if (new_coordinator == 0) {
        new_coordinator = activate_id;
    }
    coordinator = new_coordinator;
    display_processes();
}

int main() {
    printf("\nEnter number of processes: ");
    scanf("%d", &num_processes);

    for (int i = 1; i <= num_processes; i++) {
        printf("\nEnter Process %d is Alive or not (0/1): ", i);
        scanf("%d", &processes[i]);
        if (processes[i]) {
            coordinator = i;
        }
    }
    display_processes();
    printf("\nBULLY ALGORITHM\n");
    while (true) {
        int choice;
        printf("\n1. Crash\n2. Activate\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                crash_process();
                break;
            case 2:
                activate_process();
                break;
            case 3:
                display_processes();
                break;
            case 4:
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}
