#include <stdio.h>
#include <string.h>
#define ARCHIVO "/home/maxim/Descargas/ejemplo.txt"

int main() {
    char nombre[200] = ARCHIVO, linea[256], fn[256];
    int num = 0, llaves = 0, errores = 0;

    FILE *f = fopen(nombre, "r");
    if (f == NULL) {
        printf("No se pudo abrir el archivo: %s\n", nombre);
        return 1;
    }

    fclose(f);
    return 0;
}
