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

    while (fgets(linea, sizeof(linea), f)) {
        num++;
        linea[strcspn(linea, "\r\n")] = '\0';

        char *l = linea;                      // quitar espacios del inicio
        while (*l == ' ' || *l == '\t') l++;
        if (*l == '\0' || strncmp(l, "//", 2) == 0 || strncmp(l, "/*", 2) == 0) continue;
        printf("Linea %d: %s\n", num, l);   // temporal (se borra en el paso 4)
    }
    fclose(f);

    return 0;
}