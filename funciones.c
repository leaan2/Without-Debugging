#include "funciones.h"

Transferencia* cargarTransferencias(Transferencia *vec, size_t *ce, size_t *capacidad)
{
    char linea[256];
    char *token;
    Transferencia *temp;
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
            temp = (Transferencia *)realloc(vec, (*capacidad) * sizeof(Transferencia));

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

Pais *lecturaAgrupamientoPais(Pais *vec,Transferencia *vecTransferencia ,size_t *ce, size_t *cePais,size_t *capacidad, size_t *capacidadPais)
{
    int i, j,encontrado=0, k;
    Pais *aux = vec; // para poder volver al principio del puntero

   for(i=0; i< *ce; i++)
   {
        encontrado=0;
        vec=aux;
        for(j=0;j< *cePais ; j++)
        {
            if(strcmp(vec->paisCod, vecTransferencia->paisCod)==0)
            {
                encontrado=1;
                vec->cantRegistros += 1;

                if(vecTransferencia->operacion == 'C') {
                    vec->total_credito += vecTransferencia->monto;
                }
                if (vecTransferencia->operacion == 'D') {
                    vec->total_debito += vecTransferencia->monto;
                }
                break;
            }

            vec++;
        }
        if(encontrado==0)
            {
                if(*cePais == *capacidadPais)
                {
                    *capacidadPais *=2;
                    aux = (Pais *)realloc(aux, (*capacidadPais)* sizeof(Pais));
                    if(aux == NULL)
                    {
                        printf("\nError al redimensionar vecPais");
                        break;
                    }
                    vec=aux;
                    k=0;
                    while(k< *cePais)
                    {
                        vec++;
                        k++;
                    }

                }
                strcpy(vec->paisCod, vecTransferencia->paisCod);
                strcpy(vec->paisDesc,vecTransferencia->paisDesc);

                vec->cantRegistros = 1;
                vec->total_credito = 0.0;
                vec->total_debito = 0.0;

                if(vecTransferencia->operacion == 'C') {
                    vec->total_credito = vecTransferencia->monto;
                }
                if (vecTransferencia->operacion == 'D') {
                    vec->total_debito = vecTransferencia->monto;
                }
                *cePais +=1;
            }



        vecTransferencia++;
   }




    return aux;
}
void ordenarResumenPais(Pais *vec, size_t *cePais)
{
    Pais *aux, reemplazo;
    size_t i,j;

    for(i=0;i< (*cePais)-1; i++)
    {
        aux = vec;
        for(j=0;j< (*cePais)-i-1; j++)
        {
            if(aux->total_credito < (aux+1)->total_credito)
            {
                reemplazo = *(aux+1);
                *(aux+1) = *aux;
                *aux = reemplazo;
            }
            aux++;
        }
    }

}

void mostrarResumenPais(Pais *vec, size_t* cePais)
{
    printf("\n--- LISTA DE PAISES GUARDADOS (%zu) ---\n", *cePais);

    // Encabezado de la tabla para que se lea claro
    printf("%-5s | %-25s | %-10s | %-15s | %-15s\n", "COD", "NOMBRE DEL PAIS", "REGISTROS", "CREDITO", "DEBITO");
    printf("--------------------------------------------------------------------------------------\n");

    for(size_t i = 0; i < *cePais; i++)
    {
        // %-5s: string alineado a la izquierda ocupando 5 espacios
        // %-10d: número entero alineado a la izquierda ocupando 10 espacios
        // %.2f: número flotante (double/float) mostrando solo 2 decimales
        printf("%-5s | %-25s | %-10d | %-15.2f | %-15.2f\n",
               vec->paisCod,
               vec->paisDesc,
               vec->cantRegistros,
               vec->total_credito,
               vec->total_debito);

        // Avanzamos el puntero al siguiente país
        vec++;
    }
    printf("--------------------------------------------------------------------------------------\n");
}

Continente *ResumenContinentes(Continente *vecContinente, size_t *ceContinentes, Pais *vecPaises, size_t *cePais, Paises_continente *vecPaisesCont, size_t *cePaisesCont, size_t *capacidadContinentes)
{
    size_t i,j,k;
    int creado=0;
    Continente *auxContinente = vecContinente;
    Paises_continente *auxPais = vecPaisesCont;

    for(i=0;i< *cePais ; i++)
    {
        vecPaisesCont = auxPais;
        for(j=0; j< *cePaisesCont ; j++)
        {
            if(strcmp(vecPaises->paisCod, vecPaisesCont->paisCod)==0)
            {
                vecContinente = auxContinente;
                for(k=0;k< *ceContinentes;k++)
                {
                    if(strcmp(vecContinente->continente,vecPaisesCont->continente)==0)
                    {
                        creado =1;
                        vecContinente->cantRegistros += vecPaises->cantRegistros;
                        vecContinente->total_credito += vecPaises->total_credito;
                        vecContinente->total_debito  += vecPaises->total_debito;

                    }
                    vecContinente++;
                }

                if(creado == 0)
                {
                        if(*ceContinentes == *capacidadContinentes)
                        {
                            *capacidadContinentes *=2;
                        auxContinente = (Continente *)realloc(auxContinente, (*capacidadContinentes)* sizeof(Continente));
                        if(auxContinente == NULL)
                        {
                            printf("\nError al redimensionar vecContinente");
                            break;
                        }
                        vecContinente=auxContinente;
                        k=0;
                        while(k< *ceContinentes)
                        {
                            vecContinente++;
                            k++;
                        }

                    }
                    strcpy(vecContinente->continente,vecPaisesCont->continente);
                    vecContinente->cantRegistros =0;
                    vecContinente->total_credito =0;
                    vecContinente->total_debito  =0;


                    vecContinente->cantRegistros += vecPaises->cantRegistros;
                    vecContinente->total_credito += vecPaises->total_credito;
                    vecContinente->total_debito  += vecPaises->total_debito;
                    *ceContinentes += 1;
                }
                creado =0;
            }
            vecPaisesCont++;
        }
        vecPaises++;

    }

    return auxContinente;
}
void ordenarContinente(Continente *vecContinente, size_t *ceContinente)
{
    Continente *aux, reemplazo;
    size_t i,j;

    for(i=0;i< (*ceContinente)-1; i++)
    {
        aux = vecContinente;
        for(j=0;j< (*ceContinente)-i-1; j++)
        {
            if(aux->total_credito < (aux+1)->total_credito)
            {
                reemplazo = *(aux+1);
                *(aux+1) = *aux;
                *aux = reemplazo;
            }
            aux++;
        }
    }

}

void mostrarContinentesGuardados(Continente *vecContinente, size_t *ceContinentes)
{
    printf("\n--- LISTA DE CONTINENTES GUARDADOS (%zu) ---\n", *ceContinentes);

    // Encabezado alineado
    printf("%-20s | %-10s | %-15s | %-15s\n", "CONTINENTE", "REGISTROS", "CREDITO", "DEBITO");
    printf("-------------------------------------------------------------------------\n");

    for(size_t i = 0; i < *ceContinentes; i++)
    {
        printf("%-20s | %-10d | %-15.2f | %-15.2f\n",
               vecContinente->continente,
               vecContinente->cantRegistros,
               vecContinente->total_credito,
               vecContinente->total_debito);

        vecContinente++;
    }
    printf("-------------------------------------------------------------------------\n");
}

SaldoTrimestral *calculoTrimestre (SaldoTrimestral *vecTrimestre, size_t *ceTrimestre, size_t *capacidadTrimestre, Transferencia*vecTransferencia, size_t *ceTransferencia)
{
    SaldoTrimestral *aux = vecTrimestre;
    size_t i,j,k;
    int creado=0, anio = 0;
    float saldo=0;

    printf ("\nIngrese anio para calcular saldos trimestrales:\n");
    scanf ("%d", &anio);
    getchar ();

    for(i = 0 ; i < *ceTransferencia ; i++)
    {

        creado = 0;
        vecTrimestre=aux;
        saldo = 0;
        for(j=0 ; j< *ceTrimestre ; j++)
        {
            if((strcmp(vecTrimestre->paisDesc,vecTransferencia->paisDesc) == 0) && vecTransferencia->anio == anio)
            {
                creado =1;
                if(vecTransferencia->operacion == 'C' || vecTransferencia->operacion == 'c')
                {
                    saldo += vecTransferencia->monto;
                }
                if(vecTransferencia->operacion == 'D' || vecTransferencia->operacion == 'd')
                {
                    saldo -= vecTransferencia->monto;
                }

                switch(vecTransferencia->trimestre)
                {
                    case 1:
                    vecTrimestre->t1 += saldo;
                    break;

                    case 2:
                    vecTrimestre->t2 += saldo;
                    break;

                    case 3:
                    vecTrimestre->t3 += saldo;
                    break;

                    case 4:
                    vecTrimestre->t4 += saldo;
                    break;
                }


            }
            vecTrimestre++;
        }
        if(creado == 0 && vecTransferencia->anio == anio)
        {
            if(*ceTrimestre == *capacidadTrimestre)
            {
                *capacidadTrimestre *=2;
                aux = (SaldoTrimestral *) realloc(aux, *capacidadTrimestre * sizeof(SaldoTrimestral));
                if(aux == NULL)
                {
                    return vecTrimestre;
                }

                vecTrimestre = aux;

                for(k=0 ; k < *ceTrimestre ; k++)
                {
                    vecTrimestre++;
                }

            }
            strcpy(vecTrimestre->paisDesc, vecTransferencia->paisDesc);
            vecTrimestre->t1 = 0;
            vecTrimestre->t2 = 0;
            vecTrimestre->t3 = 0;
            vecTrimestre->t4 = 0;
            *ceTrimestre +=1;

            if(vecTransferencia->operacion == 'C' || vecTransferencia->operacion == 'c')
                {
                    saldo += vecTransferencia->monto;
                }
                if(vecTransferencia->operacion == 'D' || vecTransferencia->operacion == 'd')
                {
                    saldo -= vecTransferencia->monto;
                }

            switch(vecTransferencia->trimestre)
                {
                    case 1:
                    vecTrimestre->t1 += saldo;
                    break;

                    case 2:
                    vecTrimestre->t2 += saldo;
                    break;

                    case 3:
                    vecTrimestre->t3 += saldo;
                    break;

                    case 4:
                    vecTrimestre->t4 += saldo;
                    break;
                }

        }


        vecTransferencia++;
    }

    return aux;
}

void mostrarSaldoTrimestral(SaldoTrimestral *vec, size_t *ce)
{
    printf("\n--- SALDO TRIMESTRAL POR PAIS (%zu) ---\n", *ce);

    // Encabezado de columnas
    printf("%-25s | %-12s | %-12s | %-12s | %-12s\n", "PAIS", "TRIM 1", "TRIM 2", "TRIM 3", "TRIM 4");
    printf("----------------------------------------------------------------------------------------\n");

    for(size_t i = 0; i < *ce; i++)
    {
        printf("%-25s | %-12.2f | %-12.2f | %-12.2f | %-12.2f\n",
               vec->paisDesc,
               vec->t1,
               vec->t2,
               vec->t3,
               vec->t4);

        // Avanzamos el puntero al siguiente elemento
        vec++;
    }
    printf("----------------------------------------------------------------------------------------\n");
}

int archivoTxtSaldo (SaldoTrimestral *vecTrimestre, size_t *cantidadTrimeste)
{
    size_t i;
    FILE *arch = fopen("SaldoTrimestral.txt", "wt");

    if(arch == NULL)
    {
        printf("\nError archivo txt.");
        return SIN_MEM;
    }

    fprintf(arch, "--- SALDO TRIMESTRAL POR PAIS (%zu) ---\n", *cantidadTrimeste);
    fprintf(arch,"----------------------------------------------------------------------------------------\n");
    fprintf(arch,"%-25s | %-12s | %-12s | %-12s | %-12s\n", "PAIS", "TRIM 1", "TRIM 2", "TRIM 3", "TRIM 4");
    fprintf(arch,"----------------------------------------------------------------------------------------\n");

    for(i=0 ; i<*cantidadTrimeste; i++)
    {
        fprintf(arch,"%-25s | %-12.2f | %-12.2f | %-12.2f | %-12.2f\n",
               vecTrimestre->paisDesc,
               vecTrimestre->t1,
               vecTrimestre->t2,
               vecTrimestre->t3,
               vecTrimestre->t4);

       vecTrimestre++;        
    }
    fprintf(arch,"----------------------------------------------------------------------------------------");
}



