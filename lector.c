#include <stdio.h>
#include <string.h>

#define ARCHIVO "/home/maxim/Descargas/ejemplo.txt"

// revisa que la linea empiece con la palabra (ej. "if" seguido de espacio o '(')
int empieza(char *l, char *palabra) {
    int n = strlen(palabra);
    return strncmp(l, palabra, n) == 0 && (l[n] == ' ' || l[n] == '(');
}

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
        int len = strlen(l);
        char ultimo = l[len - 1];
        int comillas = 0, abre = 0, cierra = 0;

        for (int i = 0; i < len; i++) {       // contar simbolos
            if (l[i] == '"') comillas++;
            if (l[i] == '(') abre++;
            if (l[i] == ')') cierra++;
            if (l[i] == '{') llaves++;
            if (l[i] == '}') llaves--;
        }

        if (strncmp(l, "#include", 8) == 0) {
            if ((strchr(l, '<') && strchr(l, '>')) || comillas == 2)
                printf("Linea %d: OK, include bien\n", num);
            else {
                printf("Linea %d: ERROR, el include debe ser <x.h> o \"x.h\"\n", num);
                errores++;
            }
        }
        // ===== NUEVO (paso 5): revisar printf =====
        else if (empieza(l, "printf")) {
            if (l[6] != '(') {
                printf("Linea %d: ERROR, falta '(' despues de printf\n", num);
                errores++;
            } else if (comillas == 0 || comillas % 2 != 0) {
                printf("Linea %d: ERROR, faltan comillas en el printf\n", num);
                errores++;
            } else if (abre != cierra) {
                printf("Linea %d: ERROR, parentesis sin cerrar en el printf\n", num);
                errores++;
            } else if (ultimo != ';') {
                printf("Linea %d: ERROR, falta ';' en el printf\n", num);
                errores++;
            } else
                printf("Linea %d: OK, printf bien\n", num);
        }
    }
    fclose(f);

    return 0;
}