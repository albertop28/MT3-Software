#include <stdio.h>
#include <string.h>

#define max_name_leght 20

// Define a structure to track the status of each employee
typedef struct {
    char name[max_name_leght];
    int inside; // 0 = outside, 1 = inside
} Employee;

// Function to find an employee in the array
int findEmployee(Employee employees[], int count, const char* name) {
    int i = 0;
	for (i; i < count; i++) {
        if (strcmp(employees[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int logLength, i = 0;
    scanf("%d", &logLength);

    Employee employees[logLength];
    int employeeCount = 0;

    char action[5];
    char name[max_name_leght]; 

    for (i; i < logLength; i++) {
        scanf("%s %s", action, name);

        // Find the employee in the array
        int index = findEmployee(employees, employeeCount, name);
        if (index == -1) { // If the employee is not found, add them to the array
            strcpy(employees[employeeCount].name, name);
            employees[employeeCount].inside = 0; // Assume they are outside at the start
            index = employeeCount;
            employeeCount++;
        }

        if (strcmp(action, "entry") == 0) {
            if (employees[index].inside == 1) {
                printf("%s entered (ANOMALY)\n", name);
            } else {
                printf("%s entered\n", name);
            }
            employees[index].inside = 1; // Mark as inside
        } else if (strcmp(action, "exit") == 0) {
            if (employees[index].inside == 0) {
                printf("%s exited (ANOMALY)\n", name);
            } else {
                printf("%s exited\n", name);
            }
            employees[index].inside = 0; // Mark as outside
        }
    }

    return 0;
}
