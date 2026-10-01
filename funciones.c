#include "funciones.h"

Transferencia* cargarTransferencias(Transferencia *vec, size_t *ce, size_t *capacidad)
{
    char linea[256];
    char *token;
    FILE *arch = fopen("transferencias_personales_clean.csv", "r");

    if (arch == NULL)
    {
        printf("\nError al abrir el archivo.");
        return vec; // Retornamos el puntero original sin cambios si falla
    }

    fgets(linea, sizeof(linea), arch);

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (*ce == *capacidad) {
            *capacidad *= 2;
            Transferencia *temp = (Transferencia *)realloc(vec, (*capacidad) * sizeof(Transferencia));

            if (temp == NULL) {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                break;
            }
            vec = temp; // Actualizamos el puntero simple local
        }

        // 1. ANIO
        token = strtok(linea, ";");
        if (token != NULL) {
            (vec + *ce)->anio = atoi(token);
        }

        // 2. TRIMESTRE
        token = strtok(NULL, ";");
        if (token != NULL) {
            (vec + *ce)->trimestre = atoi(token);
        }

        // 3. PAIS_COD
        token = strtok(NULL, ";");
        if (token != NULL) {
            strcpy((vec + *ce)->paisCod, token);
        }

        // 4. PAIS_DESC
        token = strtok(NULL, ";");
        if (token != NULL) {
            strcpy((vec + *ce)->paisDesc, token);
        }

        // 5. OPERACION
        token = strtok(NULL, ";");
        if (token != NULL) {
            (vec + *ce)->operacion = token[0];
        }

        // 6. MONTO
        token = strtok(NULL, "\r\n");
        if (token != NULL) {
            (vec + *ce)->monto = atof(token);
        }

        (*ce)++;
    }

    fclose(arch);
    return vec; // Retornamos la dirección final (sea la original o la nueva del realloc)
}
   void mostrarTransferencias(Transferencia *vec, size_t* ce)
{
    printf("\n--- Registros cargados: %zu ---\n", *ce);

    // Recorremos el vector desde el índice 0 hasta la cantidad de elementos (ce)
    for (size_t i = 0; i < *ce; i++)
    {
        printf("Anio: %d | Trim: %d | Pais: %s (%s) | Operacion: %c | Monto: %.2f\n",
               vec->anio,
               vec->trimestre,
              vec->paisCod,
               vec->paisDesc,
               vec->operacion,
              vec->monto);

        vec++;
    }
    printf("--------------------------------\n");
}
Paises_continente* cargarPaises(Paises_continente *vec, size_t *ce, size_t *capacidad)
{
    char linea[256];
    char *token;
    FILE *arch = fopen("paises_continentes.csv", "r");

    if (arch == NULL)
    {
        printf("\nError al abrir el archivo.");
        return vec; // Retornamos el puntero original sin cambios si falla
    }

    fgets(linea, sizeof(linea), arch); // leemos la primer linea que son pais_cod, pais_desc y continente

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (*ce == *capacidad)
        {
            *capacidad *= 2;
            Paises_continente *temp = (Paises_continente *)realloc(vec, (*capacidad) * sizeof(Paises_continente));

            if (temp == NULL) {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                break;
            }
            vec = temp; // Actualizamos el puntero simple local
        }

        // 1. paisCod
        token = strtok(linea, ";");
        if (token != NULL)
        {
            strcpy((vec + *ce)->paisCod, token);
        }

        // 2. paisDesc
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy((vec + *ce)->paisDesc, token);
        }

        // 3. continente
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy((vec + *ce)->continente, token);
        }


        (*ce)++;
    }
    fclose(arch);
    return vec;
}

void mostrarPaises(Paises_continente *vec, size_t* ce)
{
    printf("\n--- Registros cargados: %zu ---\n", *ce);

    // Recorremos el vector desde el índice 0 hasta la cantidad de elementos (ce)
    for (size_t i = 0; i < *ce; i++)
    {
        printf("Pais: %s (%s) |Continente: %s\n",
               vec->paisCod, vec->paisDesc, vec->continente);

        vec++;
    }
    printf("--------------------------------\n");
}





