#include "funciones.h"
#define largoLinea 256

Transferencia* cargarTransferencias(Transferencia *vec, size_t *ce, size_t *capacidad)
{
    char linea[largoLinea];
    char *token;
    Transferencia *temp = vec;
    FILE *arch = fopen("transferencias_personales_clean.csv", "r");

    if (arch == NULL)
    {
        printf("\nError al abrir el archivo.");
        return temp;
    }

    fgets(linea, sizeof(linea), arch);

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (*ce == *capacidad)
        {
            *capacidad *= 2;
            temp = (Transferencia *)realloc(temp, (*capacidad) * sizeof(Transferencia));

            if (temp == NULL) {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                break;
            }
            vec = temp + *ce;
        }

        // 1. ANIO
        token = strtok(linea, ";");
        if (token != NULL)
        {
            vec->anio = atoi(token);
        }

        // 2. TRIMESTRE
        token = strtok(NULL, ";");
        if (token != NULL)
        {
           vec->trimestre = atoi(token);
        }

        // 3. PAIS_COD
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vec->paisCod, token);
        }

        // 4. PAIS_DESC
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vec->paisDesc, token);
        }

        // 5. OPERACION
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            vec->operacion = token[0];
        }

        // 6. MONTO
        token = strtok(NULL, "\r\n");
        if (token != NULL)
        {
            vec->monto = atof(token);
        }

        vec++;
        (*ce)++;
    }

    fclose(arch);
    return temp; // Retornamos la dirección final (sea la original o la nueva del realloc)
}

Paises_continente* cargarPaises(Paises_continente *vec, size_t *ce, size_t *capacidad)
{
    char linea[largoLinea];
    char *token;
    Paises_continente *temp = vec;
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
             temp = (Paises_continente *)realloc(temp, (*capacidad) * sizeof(Paises_continente));

            if (temp == NULL)
            {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                break;
            }
            vec = temp + *ce; // Actualizamos el puntero simple local
        }

        // 1. paisCod
        token = strtok(linea, ";");
        if (token != NULL)
        {
            strcpy(vec->paisCod, token);
        }

        // 2. paisDesc
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vec->paisDesc, token);
        }

        // 3. continente
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vec->continente, token);
        }

        vec++;
        (*ce)++;
    }
    fclose(arch);
    return temp;
}

Pais *lecturaAgrupamientoPais(Pais *vecResumenPais,Transferencia *vecTransferencia ,size_t *ceTransferencias, size_t *cePais, size_t *capacidadPais)
{
    int i, j,encontrado=0, k;
    Pais *aux = vecResumenPais; // para poder volver al principio del puntero

    for(i=0; i< *ceTransferencias; i++)
    {
        encontrado=0;
        vecResumenPais=aux;
        for(j=0;j< *cePais ; j++)
        {
            if(strcmp(vecResumenPais->paisCod, vecTransferencia->paisCod)==0)
            {
                encontrado=1;
                vecResumenPais->cantRegistros += 1;

                if(vecTransferencia->operacion == 'C')
                {
                    vecResumenPais->total_credito += vecTransferencia->monto;
                }
                if (vecTransferencia->operacion == 'D')
                {
                    vecResumenPais->total_debito += vecTransferencia->monto;
                }
                break;
            }

            vecResumenPais++;
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
                    vecResumenPais=aux;
                    k=0;
                    while(k< *cePais)
                    {
                        vecResumenPais++;
                        k++;
                    }

                }
                strcpy(vecResumenPais->paisCod, vecTransferencia->paisCod);
                strcpy(vecResumenPais->paisDesc,vecTransferencia->paisDesc);

                vecResumenPais->cantRegistros = 1;
                vecResumenPais->total_credito = 0.0;
                vecResumenPais->total_debito = 0.0;

                if(vecTransferencia->operacion == 'C')
                {
                    vecResumenPais->total_credito = vecTransferencia->monto;
                }
                if (vecTransferencia->operacion == 'D')
                {
                    vecResumenPais->total_debito = vecTransferencia->monto;
                }
                *cePais +=1;
            }
        vecTransferencia++;
    }
    return aux;
}

Continente *ResumenContinentes(Continente *vecRefContinente, size_t *ceContinentes, Pais *vecPaises, size_t *cePais, Paises_continente *vecPaisesCont, size_t *cePaisesCont, size_t *capacidadContinentes)
{
    size_t i,j,k;
    int creado=0;
    Continente *auxContinente = vecRefContinente;
    Paises_continente *auxPaisesCont = vecPaisesCont;

    for(i=0;i< *cePais ; i++)
    {
        vecPaisesCont = auxPaisesCont;
        for(j=0; j< *cePaisesCont ; j++)
        {
            if(strcmp(vecPaises->paisCod, vecPaisesCont->paisCod)==0)
            {
                vecRefContinente = auxContinente;
                for(k=0;k< *ceContinentes;k++)
                {
                    if(strcmp(vecRefContinente->continente,vecPaisesCont->continente)==0)
                    {
                        creado =1;
                        vecRefContinente->cantRegistros += vecPaises->cantRegistros;
                        vecRefContinente->total_credito += vecPaises->total_credito;
                        vecRefContinente->total_debito  += vecPaises->total_debito;

                    }
                    vecRefContinente++;
                }

                if(creado == 0)
                {
                        if(*ceContinentes == *capacidadContinentes)
                        {
                            *capacidadContinentes *=2;
                            auxContinente = (Continente *)realloc(auxContinente, (*capacidadContinentes)* sizeof(Continente));
                            if(auxContinente == NULL)
                            {
                                printf("\nError al redimensionar vecRefContinente");
                                break;
                            }
                            vecRefContinente=auxContinente;
                            k=0;
                            while(k< *ceContinentes)
                            {
                                vecRefContinente++;
                                k++;
                            }
                        }
                    strcpy(vecRefContinente->continente,vecPaisesCont->continente);
                    vecRefContinente->cantRegistros =0;
                    vecRefContinente->total_credito =0;
                    vecRefContinente->total_debito  =0;

                    vecRefContinente->cantRegistros += vecPaises->cantRegistros;
                    vecRefContinente->total_credito += vecPaises->total_credito;
                    vecRefContinente->total_debito  += vecPaises->total_debito;
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
    size_t i,j;
    int creado=0, anio;
    float saldo=0;

    printf ("\nIngrese anio para calcular saldos trimestrales(2015 a 2026):\n");
    scanf ("%d", &anio);
    getchar();
    while(anio >= 2027 || 2014 >=anio)
    {
        printf ("\nIngrese anio nuevamente para calcular saldos trimestrales(2015 a 2026):\n");
        scanf ("%d", &anio);
        getchar();
    }

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

                vecTrimestre = aux + *(ceTrimestre);



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
AnualAnio *totalAnual (AnualAnio *vecAnual, size_t *ceAnual, size_t *capacidadAnual, Transferencia *vecTransferencia, size_t *ceTransferencia)
{
    size_t i,j;
    int creado=0;
    AnualAnio *temp=vecAnual;
    for(i=0;i< *ceTransferencia; i++)
    {
        vecAnual= temp;
        for(j=0; j< *ceAnual ; j++)
        {
            if(vecAnual->anio == vecTransferencia->anio)
            {
                creado=1;

                if(vecTransferencia->operacion == 'C')
                vecAnual->credito += vecTransferencia->monto;
                else
                vecAnual->debito +=vecTransferencia->monto;


                vecAnual->saldo = vecAnual->credito - vecAnual->debito;


            }


            vecAnual++;
        }

        if (creado==0)
            {
                if(*ceAnual== *capacidadAnual)
                {
                    *capacidadAnual *= 2;
                    temp = (AnualAnio *)realloc(temp, (*capacidadAnual) * sizeof(AnualAnio));
                    if(vecAnual == NULL)
                    {
                        printf("\nError al redimensionar el vector anual.");
                        return temp;
                    }

                    vecAnual = temp + *(ceAnual);


                }
                vecAnual->anio = vecTransferencia->anio;
                vecAnual->credito =0;
                vecAnual->debito =0;
                vecAnual->saldo = 0;
                vecAnual->var_pct_saldo = 0;


                if(vecTransferencia->operacion == 'C')
                vecAnual->credito += vecTransferencia->monto;
                else
                vecAnual->debito +=vecTransferencia->monto;



                *ceAnual+=1;
            }

        creado = 0;
        vecTransferencia++;
    }




    return temp;
}

AnualAnio *calculoVariacionAnual (AnualAnio *vecAnual, size_t *ceAnual)
{
    size_t i;
    AnualAnio *retorno = vecAnual;

    for(i=0;i< *ceAnual; i++)
    {
        if(i > 0)  // para evitar el primer anio
        {
            vecAnual->var_pct_saldo = ((vecAnual->saldo - (vecAnual-1)->saldo)/ (vecAnual-1)->saldo) *100;
        }
        vecAnual++;
    }

    return retorno;
}


