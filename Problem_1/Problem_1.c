#include <stdio.h>
#include <string.h>
#include "objects.h"

/*Requirements:
-Input lecture between with first number 1-1000
    - output Format: 'Entry - name', 'Exit - name'
-Each name need to have max 20 characters
-Remember the IN or OUT status of each employer
-Detect anomalies 'IN  then IN again' or 'OUT and OUT again'
*/
#define max_employees 1000

int main(){
    int id_employee, INOUT_employee;
    char* name;
    // printf("SoStruct : %zu\n", sizeof(struct employee));
    while(1){
        printf("Provide the employee ID and whether it's an entry or exit (1 for entry or 0 for exit), separated by a space\n");
        scanf("%i %i", &id_employee, &INOUT_employee);
        if (id_employee <= max_employees){
            employee* obj = get_object_by_id(id_employee);
            if (obj) {
                // Actualizar el estado del empleado
                if (INOUT_employee == 1) {
                    if (obj->status == 1) {
                        printf("%s entered (ANOMALY)\n", obj->name);
                    } else {
                        obj->status = 1; // Actualiza el estado a 'entrada'
                        printf("%s entered\n", obj->name);
                    }
                } else if (INOUT_employee == 0) {
                    if (obj->status == 0) {
                        printf("%s exited (ANOMALY)\n", obj->name);
                    } else {
                        obj->status = 0; // Actualiza el estado a 'salida'
                        printf("%s exited\n", obj->name);
                    }
                } else {
                    printf("invalid IN/OUT code\n");
                }
            } else {
                printf("invalid employee ID code\n");
            }
        } 
        else {
            printf("invalid employee ID code\n");
        }
    }
    // printf("Press enter to exit...");
    // getchar();
    // getchar();

    // compile with console code: gcc -o my_program Problem_1.c objects.c 
}
