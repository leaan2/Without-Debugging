#include "funciones.h"
#include "mostrar.h"

void mostrarTransferencias(Transferencia *vec, size_t* ce)
{
    printf("\n--- Registros cargados: %zu ---\n", *ce);

    
    for (size_t i = 0; i < *ce; i++)
    {
        printf("Anio: %d | Trim: %d | Pais: %s (%s) | Operacion: %c | Monto: %.2f\n", vec->anio, vec->trimestre, vec->paisCod, vec->paisDesc, vec->operacion, vec->monto);
        vec++;
    }
    printf("--------------------------------\n");
}

void mostrarPaises(Paises_continente *vec, size_t* ce)
{
    printf("\n--- Registros cargados: %zu ---\n", *ce);

    
    for (size_t i = 0; i < *ce; i++)
    {
        printf("Pais: %s (%s) |Continente: %s\n", vec->paisCod, vec->paisDesc, vec->continente);
        vec++;
    }
    printf("--------------------------------\n");
}



void mostrarResumenPais(Pais *vec, size_t* cePais)
{
    printf("\n--- LISTA DE PAISES GUARDADOS (%zu) ---\n", *cePais);

    
    printf("%-5s | %-25s | %-10s | %-15s | %-15s\n", "COD", "NOMBRE DEL PAIS", "REGISTROS", "CREDITO", "DEBITO");
    printf("--------------------------------------------------------------------------------------\n");

    for(size_t i = 0; i < *cePais; i++)
    {
        
        printf("%-5s | %-25s | %-10d | %-15.2f | %-15.2f\n", vec->paisCod, vec->paisDesc, vec->cantRegistros, vec->total_credito, vec->total_debito);

        
        vec++;
    }
    printf("--------------------------------------------------------------------------------------\n");
}

void mostrarContinentesGuardados(Continente *vecContinente, size_t *ceContinentes)
{
    printf("\n--- LISTA DE CONTINENTES GUARDADOS (%zu) ---\n", *ceContinentes);

    // Encabezado alineado
    printf("%-20s | %-10s | %-15s | %-15s\n", "CONTINENTE", "REGISTROS", "CREDITO", "DEBITO");
    printf("-------------------------------------------------------------------------\n");

    for(size_t i = 0; i < *ceContinentes; i++)
    {
        printf("%-20s | %-10d | %-15.2f | %-15.2f\n", vecContinente->continente, vecContinente->cantRegistros, vecContinente->total_credito, vecContinente->total_debito);

        vecContinente++;
    }
    printf("-------------------------------------------------------------------------\n");
}

void mostrarSaldoTrimestral(SaldoTrimestral *vec, size_t *ce)
{
    printf("\n--- SALDO TRIMESTRAL POR PAIS (%zu) ---\n", *ce);

    
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

        
        vec++;
    }
    printf("----------------------------------------------------------------------------------------\n");
}


void mostrarAnualAnio(AnualAnio *vecAnual, size_t *ceAnual)
{
    printf("\n--- RESUMEN ANUAL DE OPERACIONES (%zu) ---\n", *ceAnual);
    
    
    printf("%-10s | %-15s | %-15s | %-15s | %-12s\n", "ANIO", "C", "D", "SALDO", "VAR_PCT_SALDO");
    printf("------------------------------------------------------------------------------------\n");

    for(size_t i = 0; i < *ceAnual; i++)
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
