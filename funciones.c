#include "funciones.h"
#define largoLinea 256

TransferenciaPersonal* cargarTransferencias(TransferenciaPersonal *vec, size_t *ce, size_t *capacidad, int *estado)
{
    char linea[largoLinea];
    char *token;
    TransferenciaPersonal *aux = vec;
    TransferenciaPersonal *temp = vec;
    FILE *arch = fopen("transferencias_personales_clean.csv", "r");

    if (arch == NULL)
    {
        printf("\nError al abrir el archivo transferencias_personales_clean.csv.");
        *estado = ERROR_ARCHIVO;
        return aux;
    }

    fgets(linea, sizeof(linea), arch);

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (*ce == *capacidad)
        {
            *capacidad *= 2;
            temp = (TransferenciaPersonal *)realloc(aux, (*capacidad) * sizeof(TransferenciaPersonal));

            if (temp == NULL) {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                *estado = SIN_MEM;
                break;
            }
            aux = temp;
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
            vec->operacion = *token;
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
    return aux;
}

Paises_continente* cargarPaises(Paises_continente *vec, size_t *ce, size_t *capacidad, int *estado)
{
    char linea[largoLinea];
    char *token;
    Paises_continente *aux = vec;
    Paises_continente *temp = vec;
    FILE *arch = fopen("paises_continentes.csv", "r");

    if (arch == NULL)
    {
        printf("\nError al abrir el archivo paises_continentes.csv.");
        *estado = ERROR_ARCHIVO;
        return vec;
    }

    fgets(linea, sizeof(linea), arch);

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (*ce == *capacidad)
        {
            *capacidad *= 2;
             temp = (Paises_continente *)realloc(aux, (*capacidad) * sizeof(Paises_continente));

            if (temp == NULL)
            {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                *estado = SIN_MEM;
                break;
            }
            aux = temp;
            vec = temp + *ce;
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
        token = strtok(NULL, ";\r\n");
        if (token != NULL)
        {
            strcpy(vec->continente, token);
        }

        vec++;
        (*ce)++;
    }
    fclose(arch);
    return aux;
}

Pais *lecturaAgrupamientoPais(Pais *vecResumenPais,TransferenciaPersonal *vecTransferencia ,size_t *ceTransferencias, size_t *cePais, size_t *capacidadPais, int *estado)
{
    int encontrado=0;
    size_t i,j;
    Pais *aux = vecResumenPais;
    Pais *temp = vecResumenPais;

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
                    temp = (Pais *)realloc(aux, (*capacidadPais)* sizeof(Pais));
                    if(temp == NULL)
                    {
                        printf("\nError al redimensionar vecPais");
                        *estado = SIN_MEM;
                        break;
                    }
                    aux = temp;
                }
                vecResumenPais = aux + *cePais;
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

Continente *ResumenContinentes(Continente *vecRefContinente, size_t *ceContinentes, Pais *vecPaises, size_t *cePais, Paises_continente *vecPaisesCont, size_t *cePaisesCont, size_t *capacidadContinentes, int *estado)
{
    size_t i,j,k;
    int creado=0;
    Continente *auxContinente = vecRefContinente;
    Continente *tempContinente = vecRefContinente;
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
                        break;
                    }
                    vecRefContinente++;
                }

                if(creado == 0)
                {
                        if(*ceContinentes == *capacidadContinentes)
                        {
                            *capacidadContinentes *=2;
                            tempContinente = (Continente *)realloc(auxContinente, (*capacidadContinentes)* sizeof(Continente));
                            if(tempContinente == NULL)
                            {
                                printf("\nError al redimensionar vecRefContinente");
                                *estado = SIN_MEM;
                                return auxContinente;
                            }
                            auxContinente = tempContinente;
                        }
                    vecRefContinente = auxContinente + *ceContinentes;
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

SaldoTrimestral *calculoTrimestre (SaldoTrimestral *vecTrimestre, size_t *ceTrimestre, size_t *capacidadTrimestre, TransferenciaPersonal*vecTransferencia, size_t *ceTransferencia, int anio, int *estado)
{
    SaldoTrimestral *aux = vecTrimestre;
    SaldoTrimestral *temp = vecTrimestre;
    size_t i,j;
    int creado=0;
    float saldo=0;



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
                break;
            }
            vecTrimestre++;
        }
        if(creado == 0 && vecTransferencia->anio == anio)
        {
            if(*ceTrimestre == *capacidadTrimestre)
            {
                *capacidadTrimestre *=2;
                temp = (SaldoTrimestral *) realloc(aux, *capacidadTrimestre * sizeof(SaldoTrimestral));
                if(temp == NULL)
                {
                    *estado = SIN_MEM;
                    return aux;
                }
                aux = temp;

            }
            vecTrimestre = aux + *(ceTrimestre);
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
AnualAnio *totalAnual (AnualAnio *vecAnual, size_t *ceAnual, size_t *capacidadAnual, TransferenciaPersonal *vecTransferencia, size_t *ceTransferencia, int *estado)
{
    size_t i,j;
    int creado=0;
    AnualAnio *aux = vecAnual;
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

                break;
            }


            vecAnual++;
        }

        if (creado==0)
            {
                if(*ceAnual== *capacidadAnual)
                {
                    *capacidadAnual *= 2;
                    temp = (AnualAnio *)realloc(aux, (*capacidadAnual) * sizeof(AnualAnio));
                    if(temp == NULL)
                    {
                        printf("\nError al redimensionar el vector anual.");
                        *estado = SIN_MEM;
                        return aux;
                    }
                    aux = temp;
                }
                vecAnual = aux + *(ceAnual);
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




    return aux;
}

AnualAnio *calculoVariacionAnual (AnualAnio *vecAnual, size_t *ceAnual)
{
    size_t i;
    AnualAnio *retorno = vecAnual;

    for(i=0;i< *ceAnual; i++)
    {
        if(i > 0 && (vecAnual-1)->saldo != 0)  // para evitar el primer anio
        {
            vecAnual->var_pct_saldo = ((vecAnual->saldo - (vecAnual-1)->saldo)/ (vecAnual-1)->saldo) *100;
        }
        vecAnual++;
    }

    return retorno;
}

participacionContinente* porcentajeContinente (participacionContinente *vecParticipacionContinente, size_t *ceParticipacion, size_t *capacidadParticipacion, Continente* vecContinente, int *estado)
{
    participacionContinente* aux= vecParticipacionContinente;
    participacionContinente* temp = vecParticipacionContinente;
    float sumaCredito=0, sumaDebito=0;
    size_t i;
    if(*ceParticipacion > *capacidadParticipacion)
    {
        *capacidadParticipacion = *ceParticipacion;
        temp = (participacionContinente *)realloc(aux, *capacidadParticipacion * sizeof(participacionContinente));
        if(!temp)
        {
            printf("\nError al redimensionar. ");
            *estado = SIN_MEM;
            return aux;
        }
        aux = temp;
    }
    vecParticipacionContinente = aux;

    for(i =0 ; i < *ceParticipacion;i++)
    {

        strcpy(vecParticipacionContinente->continente, vecContinente->continente);

        vecParticipacionContinente->total_credito=0;
        vecParticipacionContinente->total_credito+= vecContinente->total_credito;

        vecParticipacionContinente->total_debito=0;
        vecParticipacionContinente->total_debito+= vecContinente->total_debito;

        sumaCredito+= vecContinente->total_credito;
        sumaDebito+= vecContinente->total_debito;

        vecContinente++;
        vecParticipacionContinente++;
    }
    vecParticipacionContinente= aux;



    for(i =*ceParticipacion; i > 0;i--)
    {
        if (sumaCredito > 0)
        {
            vecParticipacionContinente->total_credito = (vecParticipacionContinente->total_credito / sumaCredito) * 100;
        }

        if (sumaDebito > 0)
        {
            vecParticipacionContinente->total_debito = (vecParticipacionContinente->total_debito / sumaDebito) * 100;
        }

        vecParticipacionContinente++;
    }



    return aux;
}

int vecBaseLarga (TransferenciaPersonal *vecPersonal, size_t *cePersonal, Paises_continente *vecPaises, size_t *cePaises, int *estado)
{
    int creado =0;
    TransferenciaBaseLarga* auxBaseLarga;
    TransferenciaBaseLarga* tempBaseLarga;
    size_t ceTransBaseLarga=0, capacidadTransBaseLarga=10;
    size_t i,j,k;
    TransferenciaBaseLarga* vecTransBaseLarga =(TransferenciaBaseLarga *)malloc(capacidadTransBaseLarga * sizeof(TransferenciaBaseLarga));
    if(!vecTransBaseLarga)
    {
        printf("\nError al reservar memoria para transferencia base larga");
        *estado = SIN_MEM;
        return SIN_MEM;
    }
    auxBaseLarga = vecTransBaseLarga;
    tempBaseLarga = vecTransBaseLarga;
    Paises_continente* auxPaises = vecPaises;
    FILE *arch = fopen("transferencias_base_larga.csv", "wt");
    if(!arch)
    {
        printf("\nError al abrir archivo del punto 7");
        free(vecTransBaseLarga);
        *estado = ERROR_ARCHIVO;
        return SIN_MEM;
    }

    for(i=0; i < *cePersonal ; i++)
    {
        vecPaises= auxPaises;
        for(j=0; j< *cePaises; j++)
        {
            vecTransBaseLarga= auxBaseLarga;
            if(strcmp(vecPersonal->paisCod, vecPaises->paisCod)==0)
            {

                for(k=0; k < ceTransBaseLarga; k++)
                {
                    if(strcmp(vecTransBaseLarga->paisCod, vecPaises->paisCod)==0 && vecTransBaseLarga->anio == vecPersonal->anio && vecTransBaseLarga->trimestre == vecPersonal->trimestre && vecTransBaseLarga->operacion == vecPersonal->operacion)
                    {
                        creado =1;
                        vecTransBaseLarga->monto += vecPersonal->monto;
                        break;
                    }
                    vecTransBaseLarga++;
                }


                if(creado==0)
                {
                    if(capacidadTransBaseLarga == ceTransBaseLarga)
                    {
                        capacidadTransBaseLarga *=2;
                        tempBaseLarga = (TransferenciaBaseLarga *) realloc(auxBaseLarga, capacidadTransBaseLarga * sizeof(TransferenciaBaseLarga));
                        if(!tempBaseLarga)
                        {
                            printf("\nError al reservar memoria nuevamente para transferencia base larga");
                            fclose(arch);
                            free(auxBaseLarga);
                            *estado = SIN_MEM;
                            return SIN_MEM;
                        }
                        auxBaseLarga = tempBaseLarga;

                    }
                    vecTransBaseLarga = auxBaseLarga + ceTransBaseLarga;

                    vecTransBaseLarga->anio = vecPersonal->anio;
                    vecTransBaseLarga->trimestre = vecPersonal->trimestre;
                    strcpy(vecTransBaseLarga->paisCod, vecPersonal->paisCod);
                    strcpy(vecTransBaseLarga->paisDesc, vecPersonal->paisDesc);
                    strcpy(vecTransBaseLarga->continente, vecPaises->continente);
                    vecTransBaseLarga->operacion = vecPersonal->operacion;

                    vecTransBaseLarga->monto = 0;
                    vecTransBaseLarga->monto += vecPersonal->monto;

                    ceTransBaseLarga++;
                }
                creado =0;
            }
            vecPaises++;
        }
        vecPersonal++;
    }

    vecTransBaseLarga = auxBaseLarga;
    fprintf(arch, "ANIO;TRIMESTRE;PAIS_COD;PAIS_DESC;CONTINENTE;OPERACION;MONTO\n");
    for(i=0 ; i< ceTransBaseLarga; i++)
    {
         fprintf(arch, "%d;%d;%s;%s;%s;%c;%.2f\n",
                vecTransBaseLarga->anio,
                vecTransBaseLarga->trimestre,
                vecTransBaseLarga->paisCod,
                vecTransBaseLarga->paisDesc,
                vecTransBaseLarga->continente,
                vecTransBaseLarga->operacion,
                vecTransBaseLarga->monto);

        vecTransBaseLarga++;
    }


    vecTransBaseLarga = auxBaseLarga;
    free(vecTransBaseLarga);
    fclose(arch);
    return TODO_OK;
}


PromedioTrimestralPais* cargaPromedio(PromedioTrimestralPais *vecPromedio, size_t *cePromedio, size_t *capacidadPromedio, int *estado) {
    TransferenciaBaseLarga *vecBaseLarga, *auxBaseLarga, *tempBaseLarga;
    size_t ceBaseLarga = 0, capacidadBaseLarga = 10, i, j;
    FILE *arch = fopen("transferencias_base_larga.csv", "r");
    char linea[largoLinea];
    char *token;
    PromedioTrimestralPais *auxPromedio = vecPromedio;
    PromedioTrimestralPais *tempPromedio = vecPromedio;
    int creado = 0;

    vecBaseLarga = (TransferenciaBaseLarga*)malloc(capacidadBaseLarga * sizeof(TransferenciaBaseLarga));
    auxBaseLarga = vecBaseLarga;
    tempBaseLarga = vecBaseLarga;

    if(!vecBaseLarga){
        *estado = SIN_MEM;
        return NULL;
    }

    if (arch == NULL)
    {
        free(vecBaseLarga);
        *estado = ERROR_ARCHIVO;
        return NULL;
    }

    fgets(linea, sizeof(linea), arch);

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (ceBaseLarga == capacidadBaseLarga)
        {
            capacidadBaseLarga *= 2;
            tempBaseLarga = (TransferenciaBaseLarga *)realloc(auxBaseLarga, capacidadBaseLarga * sizeof(TransferenciaBaseLarga));

            if (tempBaseLarga == NULL) {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                fclose(arch);
                free(auxBaseLarga);
                *estado = SIN_MEM;
                return NULL;
            }
            auxBaseLarga = tempBaseLarga;
            vecBaseLarga = tempBaseLarga + ceBaseLarga;
        }

        // 1. ANIO
        token = strtok(linea, ";");
        if (token != NULL)
        {
            vecBaseLarga->anio = atoi(token);
        }

        // 2. TRIMESTRE
        token = strtok(NULL, ";");
        if (token != NULL)
        {
           vecBaseLarga->trimestre = atoi(token);
        }

        // 3. PAIS_COD
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vecBaseLarga->paisCod, token);
        }

        // 4. PAIS_DESC
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vecBaseLarga->paisDesc, token);
        }

        // 5. CONTINENTE
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vecBaseLarga->continente, token);
        }

        // 6. OPERACION
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            vecBaseLarga->operacion = *token;
        }

        // 7. MONTO
        token = strtok(NULL, "\r\n");
        if (token != NULL)
        {
            vecBaseLarga->monto = atof(token);
        }

        vecBaseLarga++;
        ceBaseLarga++;

    }

    vecBaseLarga = tempBaseLarga;

    for(i = 0; i < ceBaseLarga; i++){

        vecPromedio = auxPromedio;
        creado = 0;

        for(j = 0; j < *cePromedio; j++){
            if(strcmp(vecPromedio->paisCod, vecBaseLarga->paisCod) == 0 && vecPromedio->operacion == vecBaseLarga->operacion){
                vecPromedio->suma_monto += vecBaseLarga->monto;

                if(vecBaseLarga->monto > 0)
                vecPromedio->cant_trimestres++;

                creado = 1;
                break;
            }
            vecPromedio++;
        }
        if(!creado){

            if(*cePromedio == *capacidadPromedio)
            {
                *capacidadPromedio *= 2;
                tempPromedio = (PromedioTrimestralPais *)realloc(auxPromedio, *capacidadPromedio * sizeof(PromedioTrimestralPais));

                if (tempPromedio == NULL) 
                {
                    printf("\nError: memoria insuficiente al redimensionar.\n");
                    fclose(arch);
                    free(auxBaseLarga);
                    *estado = SIN_MEM;
                    return auxPromedio;
                }
                auxPromedio = tempPromedio;
            }
            vecPromedio = auxPromedio + *cePromedio;
            strcpy(vecPromedio->paisCod, vecBaseLarga->paisCod);
            strcpy(vecPromedio->paisDesc, vecBaseLarga->paisDesc);
            vecPromedio->operacion = vecBaseLarga->operacion;
            vecPromedio->suma_monto = vecBaseLarga->monto;
            vecPromedio->cant_trimestres = (vecBaseLarga->monto > 0.0f) ? 1 : 0;
            (*cePromedio)++;
        }
        vecBaseLarga++;
    }

    fclose(arch);
    free(tempBaseLarga);
    return auxPromedio;
}

PromedioTrimestralPais* calculoPromedio(PromedioTrimestralPais *vecPromedio, size_t *cePromedio)
{
    PromedioTrimestralPais *tempPromedio = vecPromedio;
    size_t i;
    for(i = 0; i < *cePromedio; i++)
    {
        if(vecPromedio->cant_trimestres > 0)
        {
            vecPromedio->promedio = vecPromedio->suma_monto / vecPromedio->cant_trimestres;
        }
        else
        {
            vecPromedio->promedio = 0.0;
        }
        vecPromedio++;
    }

    return tempPromedio;
}

PromedioTrimestralContinente* cargaPromedioContinente(PromedioTrimestralContinente* vecTrimestralContinente, size_t *ceContinenteTrimestral, size_t *capacidadContinenteTrimestral, int *estado)
{
    TransferenciaBaseLarga *vecBaseLarga, *auxBaseLarga ,*tempBaseLarga;
    size_t ceBaseLarga = 0, capacidadBaseLarga = 10, i, j;
    FILE *arch = fopen("transferencias_base_larga.csv", "r");
    char linea[largoLinea];
    char *token;
    int creado = 0;
    PromedioTrimestralContinente *auxTrimestralContinente= vecTrimestralContinente;
    PromedioTrimestralContinente *tempTrimestralContinente = vecTrimestralContinente;

    vecBaseLarga = (TransferenciaBaseLarga*)malloc(capacidadBaseLarga * sizeof(TransferenciaBaseLarga));
    tempBaseLarga = vecBaseLarga;
    auxBaseLarga = vecBaseLarga;
    if(!vecBaseLarga){
        *estado = SIN_MEM;
        return NULL;
    }

    if (arch == NULL)
    {
        free(vecBaseLarga);
        *estado = ERROR_ARCHIVO;
        return NULL;
    }

    fgets(linea, sizeof(linea), arch);

    while (fgets(linea, sizeof(linea), arch) != NULL)
    {
        if (ceBaseLarga == capacidadBaseLarga)
        {
            capacidadBaseLarga *= 2;
            tempBaseLarga = (TransferenciaBaseLarga *)realloc(auxBaseLarga, capacidadBaseLarga * sizeof(TransferenciaBaseLarga));

            if (tempBaseLarga == NULL) {
                printf("\nError: memoria insuficiente al redimensionar.\n");
                fclose(arch);
                free(auxBaseLarga);
                *estado = SIN_MEM;
                return vecTrimestralContinente;
            }
            auxBaseLarga = tempBaseLarga;
            vecBaseLarga = auxBaseLarga + ceBaseLarga;
        }

        // 1. ANIO
        token = strtok(linea, ";");
        if (token != NULL)
        {
            vecBaseLarga->anio = atoi(token);
        }

        // 2. TRIMESTRE
        token = strtok(NULL, ";");
        if (token != NULL)
        {
           vecBaseLarga->trimestre = atoi(token);
        }

        // 3. PAIS_COD
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vecBaseLarga->paisCod, token);
        }

        // 4. PAIS_DESC
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vecBaseLarga->paisDesc, token);
        }

        // 5. CONTINENTE
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(vecBaseLarga->continente, token);
        }

        // 6. OPERACION
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            vecBaseLarga->operacion = *token;
        }

        // 7. MONTO
        token = strtok(NULL, "\r\n");
        if (token != NULL)
        {
            vecBaseLarga->monto = atof(token);
        }

        vecBaseLarga++;
        ceBaseLarga++;

    }

    vecBaseLarga = tempBaseLarga;

    for(i=0; i< ceBaseLarga ; i++)
    {
        creado = 0;
        vecTrimestralContinente = auxTrimestralContinente;

        for(j=0; j< *ceContinenteTrimestral; j++)
        {
            if(strcmp(vecBaseLarga->continente, vecTrimestralContinente->continente)==0 && vecTrimestralContinente->operacion == vecBaseLarga->operacion && vecTrimestralContinente->anio == vecBaseLarga->anio)
            {
                creado = 1;
                vecTrimestralContinente->suma_monto += vecBaseLarga->monto;
                if(vecBaseLarga-> monto > 0)
                vecTrimestralContinente->cant_trimestres +=1;
                break;
            }

            vecTrimestralContinente++;
        }

        if (creado==0 )
        {
            if(*ceContinenteTrimestral == *capacidadContinenteTrimestral){
                *capacidadContinenteTrimestral *= 2;
                tempTrimestralContinente = (PromedioTrimestralContinente *)realloc(auxTrimestralContinente, *capacidadContinenteTrimestral * sizeof(PromedioTrimestralContinente));

                if (tempTrimestralContinente == NULL) {
                    printf("\nError: memoria insuficiente al redimensionar.\n");
                    *estado = SIN_MEM;
                    fclose(arch);
                    free(auxBaseLarga);
                    return auxTrimestralContinente;
                }
                auxTrimestralContinente = tempTrimestralContinente;
                
            }
            vecTrimestralContinente = auxTrimestralContinente + *ceContinenteTrimestral;
            strcpy(vecTrimestralContinente->continente, vecBaseLarga->continente);
            vecTrimestralContinente-> anio = vecBaseLarga->anio;
            vecTrimestralContinente->operacion = vecBaseLarga->operacion;


            vecTrimestralContinente->promedio=0;
            vecTrimestralContinente->suma_monto = vecBaseLarga->monto;

            vecTrimestralContinente->cant_trimestres = (vecBaseLarga->monto > 0.0f) ? 1 : 0;

            (*ceContinenteTrimestral)++;
        }

        vecBaseLarga++;
    }



    free(tempBaseLarga);
    fclose(arch);
    return auxTrimestralContinente;
}
PromedioTrimestralContinente* calculoPromedioContinente(PromedioTrimestralContinente* vecTrimestralContinente, size_t *ce)
{
    size_t i;
    PromedioTrimestralContinente *aux = vecTrimestralContinente;
    for(i=0;i< *ce; i++)
    {
        if(vecTrimestralContinente->cant_trimestres > 0)
        {
            vecTrimestralContinente->promedio = vecTrimestralContinente->suma_monto / vecTrimestralContinente->cant_trimestres;
        }
        else
        {
            vecTrimestralContinente->promedio = 0.0;
        }
        vecTrimestralContinente++;
    }

    return aux;
}

