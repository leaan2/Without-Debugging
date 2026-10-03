#include "archivos.h"

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
    fprintf(arch,"%-32s | %-10s | %-10s | %-10s | %-10s\n", "PAIS", "TRIM 1", "TRIM 2", "TRIM 3", "TRIM 4");
    fprintf(arch,"----------------------------------------------------------------------------------------\n");

    for(i=0 ; i<*cantidadTrimeste; i++)
    {
        fprintf(arch,"%-32s | %-10.2f | %-10.2f | %-10.2f | %-10.2f\n",
               vecTrimestre->paisDesc,
               vecTrimestre->t1,
               vecTrimestre->t2,
               vecTrimestre->t3,
               vecTrimestre->t4);

       vecTrimestre++;
    }
    fprintf(arch,"----------------------------------------------------------------------------------------");

    return 1;
}