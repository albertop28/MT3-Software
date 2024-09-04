#ifndef OBJECTS_H
#define OBJECTS_H

#define MAX_NAME_LEN 20

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int status;
} employee;

// Función para obtener un empleado por id
employee* get_object_by_id(int id);

#endif
