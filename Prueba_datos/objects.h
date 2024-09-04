// objects.h
#ifndef OBJECTS_H
#define OBJECTS_H

#define MAX_NAME_LEN 100

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int status;
    // Otros atributos
} Object;

// Función para obtener un objeto por id
Object* get_object_by_id(int id);

#endif // OBJECTS_H
