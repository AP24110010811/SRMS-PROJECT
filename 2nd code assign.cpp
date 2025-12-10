#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int burstTime;
    struct Process* next;
} Process;

Process* head = NULL;

Process* createProcess(int pid, int burstTime) {
    Process* newP = (Process*)malloc(sizeof(Process));
    newP->pid = pid;
    newP->burstTime = burstTime;
    newP->next = NULL;
    return newP;
}

void addProcess(int pid, int burstTime) {
    Process* newP = createProcess(pid, burstTime);

    if (head == NULL) {
        head = newP;
        newP->next = newP;
    } else {
        Process* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = newP;
        newP->next = head;
    }
}

void roundRobin(int quantum) {
    if (head == NULL) return;

    Process* current = head;
    Process* prev = NULL;

    while (current->next != current) { 
        printf("Processing P%d\n", current->pid);

        if (current->burstTime > quantum) {
            current->burstTime -= quantum;
            printf("  Time used: %d, Remaining: %d\n",
                   quantum, current->burstTime);

            prev = current;
            current = current->next;
        } else {
            printf("  P%d completed!\n", current->pid);

            if (current == head)
                head = head->next;

            prev->next = current->next;
            free(current);
            current = prev->next;
        }
    }

   
    printf("Processing P%d (final)\n", current->pid);
    printf("  P%d completed!\n", current->pid);
    free(current);
}

void display() {
    if (head == NULL) {
        printf("No processes.\n");
        return;
    }

    Process* temp = head;
    printf("Processes:\n");
    do {
        printf("  P%d (BT=%d)\n", temp->pid, temp->burstTime);
        temp = temp->next;
    } while (temp != head);
}

int main() {
    addProcess(1, 10);
    addProcess(2, 5);
    addProcess(3, 15);
    addProcess(4, 7);

    printf("Initial queue:\n");
    display();

    int quantum = 5;
    printf("\nRunning Round Robin (Quantum = %d)\n\n", quantum);

    roundRobin(5);

    return 0;
}
