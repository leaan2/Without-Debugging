#include "funciones.h"
#define largoLinea 256

Transferencia* cargarTransferencias(Transferencia *vec, size_t *ce, size_t *capacidad)
{
    char linea[largoLinea];
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
        if (*ce == *capacidad)
        {
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
        if (token != NULL)
        {
            (vec + *ce)->anio = atoi(token);
        }

        // 2. TRIMESTRE
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            (vec + *ce)->trimestre = atoi(token);
        }

        // 3. PAIS_COD
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy((vec + *ce)->paisCod, token);
        }

        // 4. PAIS_DESC
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy((vec + *ce)->paisDesc, token);
        }

        // 5. OPERACION
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            (vec + *ce)->operacion = token[0];
        }

        // 6. MONTO
        token = strtok(NULL, "\r\n");
        if (token != NULL)
        {
            (vec + *ce)->monto = atof(token);
        }

        (*ce)++;
    }

    fclose(arch);
    return vec; // Retornamos la dirección final (sea la original o la nueva del realloc)
}

Paises_continente* cargarPaises(Paises_continente *vec, size_t *ce, size_t *capacidad)
{
    char linea[largoLinea];
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

            if (temp == NULL)
            {
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

                if(vecTransferencia->operacion == 'C')
                {
                    vec->total_credito += vecTransferencia->monto;
                }
                if (vecTransferencia->operacion == 'D')
                {
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

                if(vecTransferencia->operacion == 'C')
                {
                    vec->total_credito = vecTransferencia->monto;
                }
                if (vecTransferencia->operacion == 'D')
                {
                    vec->total_debito = vecTransferencia->monto;
                }
                *cePais +=1;
            }
        vecTransferencia++;
    }
    return aux;
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
