#include "funciones.h"
#include "mostrar.h"

void mostrarTransferencias(TransferenciaPersonal *vec, size_t* ce)
{
    size_t i = 0;
    printf("\n--- Registros cargados: %zu ---\n", *ce);


    for (i = 0; i < *ce; i++)
    {
        printf("Anio: %d | Trim: %d | Pais: %s (%s) | Operacion: %c | Monto: %.2f\n", vec->anio, vec->trimestre, vec->paisCod, vec->paisDesc, vec->operacion, vec->monto);
        vec++;
    }
    printf("--------------------------------\n");
}

void mostrarPaises(Paises_continente *vec, size_t* ce)
{
    size_t i = 0;
    printf("\n--- Registros cargados: %zu ---\n", *ce);


    for (i = 0; i < *ce; i++)
    {
        printf("Pais: %s (%s) |Continente: %s\n", vec->paisCod, vec->paisDesc, vec->continente);
        vec++;
    }
    printf("--------------------------------\n");
}



void mostrarResumenPais(Pais *vec, size_t* cePais)
{
    size_t i = 0;
    printf("\n--- LISTA DE PAISES GUARDADOS (%zu) ---\n", *cePais);


    printf("%-5s | %-45s | %-10s | %-15s | %-15s\n", "COD", "NOMBRE DEL PAIS", "REGISTROS", "CREDITO", "DEBITO");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < *cePais; i++)
    {

        printf("%-5s | %-45s | %-10d | %-15.2f | %-15.2f\n", vec->paisCod, vec->paisDesc, vec->cantRegistros, vec->total_credito, vec->total_debito);


        vec++;
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}

void mostrarContinentesGuardados(Continente *vecContinente, size_t *ceContinentes)
{
    size_t i = 0;
    printf("\n--- LISTA DE CONTINENTES GUARDADOS (%zu) ---\n", *ceContinentes);


    printf("%-20s | %-10s | %-15s | %-15s\n", "CONTINENTE", "REGISTROS", "CREDITO", "DEBITO");
    printf("-------------------------------------------------------------------------\n");

    for(i = 0; i < *ceContinentes; i++)
    {
        printf("%-20s | %-10d | %-15.2f | %-15.2f\n", vecContinente->continente, vecContinente->cantRegistros, vecContinente->total_credito, vecContinente->total_debito);

        vecContinente++;
    }
    printf("-------------------------------------------------------------------------\n");
}

void mostrarSaldoTrimestral(SaldoTrimestral *vec, size_t *ce)
{
    size_t i = 0;
    printf("\n--- SALDO TRIMESTRAL POR PAIS (%zu) ---\n", *ce);


    printf("%-45s | %-12s | %-12s | %-12s | %-12s\n", "PAIS", "TRIM 1", "TRIM 2", "TRIM 3", "TRIM 4");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < *ce; i++)
    {
        printf("%-45s | %-12.2f | %-12.2f | %-12.2f | %-12.2f\n",
               vec->paisDesc,
               vec->t1,
               vec->t2,
               vec->t3,
               vec->t4);


        vec++;
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}


void mostrarAnualAnio(AnualAnio *vecAnual, size_t *ceAnual)
{
    size_t i = 0;
    printf("\n--- RESUMEN ANUAL DE OPERACIONES (%zu) ---\n", *ceAnual);


    printf("%-10s | %-15s | %-15s | %-15s | %-12s\n", "ANIO", "C", "D", "SALDO", "VAR_PCT_SALDO");
    printf("------------------------------------------------------------------------------------\n");
    printf("%-10d | %-15.2f | %-15.2f | %-15.2f | %-12s%%\n",
               vecAnual->anio,
               vecAnual->credito,
               vecAnual->debito,
               vecAnual->saldo,
               "-");
    vecAnual++;
    for(i = 1; i < *ceAnual; i++)
    {
        printf("%-10d | %-15.2f | %-15.2f | %-15.2f | %-12.2f%%\n",
               vecAnual->anio,
               vecAnual->credito,
               vecAnual->debito,
               vecAnual->saldo,
               vecAnual->var_pct_saldo);


        vecAnual++;
    }
    printf("------------------------------------------------------------------------------------\n");
}

void mostrarListadoPaises(Pais *vec, size_t* cePais, char* Operacion)
{
    size_t i = 0;
    printf("\n--- LISTA DE PAISES GUARDADOS (%zu) ---\n", *cePais);

    if(*Operacion == 'C')
    {
        printf("%-10s | %-5s | %-25s | %-10s | %-15s\n", "RANKING", "COD", "NOMBRE DEL PAIS", "REGISTROS", "CREDITO");
        printf("--------------------------------------------------------------------------------------\n");
        for(i = 0; i < *cePais; i++)
        {

            printf("%-10zu | %-5s | %-25s | %-10d | %-15.2f\n", i + 1, vec->paisCod, vec->paisDesc, vec->cantRegistros, vec->total_credito);


            vec++;
        }
        printf("--------------------------------------------------------------------------------------\n");

    }
    else
    {
        printf("%-10s | %-5s | %-25s | %-10s | %-15s\n", "RANKING", "COD", "NOMBRE DEL PAIS", "REGISTROS", "DEBITO");
        printf("--------------------------------------------------------------------------------------\n");
        for(i = 0; i < *cePais; i++)
        {

            printf("%-10zu | %-5s | %-25s | %-10d | %-15.2f\n", i + 1, vec->paisCod, vec->paisDesc, vec->cantRegistros, vec->total_debito);


            vec++;
        }
        printf("--------------------------------------------------------------------------------------\n");

    }

}


void mostrarPromedioTrimestral(PromedioTrimestralPais *vecPromedio, size_t *cePromedio)
{
    size_t i = 0;
    printf("\n--- PROMEDIO TRIMESTRAL POR PAIS (%zu) ---\n", *cePromedio);

    printf(" %-45s | %-15s |%-15s |%-10s | %-15s\n", "NOMBRE DEL PAIS", "OPERACIÓN","SUMA MONTO" ,"CANT TRIM", "PROMEDIO");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < *cePromedio; i++)
    {
        printf("%-45s | %-15c | %-15.2f |%-10d | %-15.2f\n",
               vecPromedio->paisDesc,
               vecPromedio->operacion,
               vecPromedio->suma_monto,
               vecPromedio->cant_trimestres,
               vecPromedio->promedio);

        vecPromedio++;
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}
void mostrarPromedioContinente(PromedioTrimestralContinente *vec, size_t *ce)
{\
    size_t i = 0;
    printf("\n--- PROMEDIOS POR CONTINENTE Y ANIO (%zu registros) ---\n", *ce);


    printf("%-6s | %-15s | %-4s | %-12s | %-9s | %-12s\n",
           "ANIO", "CONTINENTE", "OP", "SUMA MONTO", "CANT TRIM", "PROMEDIO");
    printf("----------------------------------------------------------------------------\n");

    for(i = 0; i < *ce; i++)
    {
        printf("%-6d | %-15s | %-4c | %-12.2f | %-9d | %-12.2f\n",
               vec->anio,
               vec->continente,
               vec->operacion,
               vec->suma_monto,
               vec->cant_trimestres,
               vec->promedio);

        vec++;
    }
    printf("----------------------------------------------------------------------------\n");
}

int mostrarMenu(){

    int opcion;

    printf("\n--- MENU ---\n");
    printf("1. Agrupamiento por pais\n");
    printf("2. Agrupamiento por continente\n");
    printf("3. Saldo trimestral por pais\n");
    printf("4. Resumen anual por anio\n");
    printf("5. Listado de paises por operacion\n");
    printf("6. Porcentaje de participacion por continente\n");
    printf("7. Generar archivo base larga\n");
    printf("8. Promedio trimestral por pais\n");
    printf("9. Promedio trimestral por continente y anio\n");
    printf("10. Salir\n");
    printf("Seleccione una opcion: ");

    do
    {
        scanf("%d", &opcion);
        getchar ();
        if (opcion < 1 || opcion > 10)
        {
            printf ("\nOpcion invalida. Seleccione una opcion correcta:\n");
        }
    }
    while (opcion < 1 || opcion > 10);
    return opcion;
}
