// main.c
#include <stdio.h>
#include "objects.h"

int main() {
    int id;
    printf("Introduce el ID del objeto: ");
    scanf("%d", &id);

    Object* obj = get_object_by_id(id);
    if (obj) {
        printf("Objeto encontrado: ID=%d, Nombre=%s\n", obj->id, obj->name);
    } else {
        printf("No se encontró un objeto con ID=%d\n", id);
    }

	printf("Presiona Enter para salir...");
    getchar(); // Limpiar el buffer de entrada
    getchar(); // Esperar por una entrada del usuario

    return 0;
}
