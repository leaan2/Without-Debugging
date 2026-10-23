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
    fprintf(arch,"%-45s | %-10s | %-10s | %-10s | %-10s\n", "PAIS", "TRIM 1", "TRIM 2", "TRIM 3", "TRIM 4");
    fprintf(arch,"----------------------------------------------------------------------------------------\n");

    for(i=0 ; i<*cantidadTrimeste; i++)
    {
        fprintf(arch,"%-45s | %-10.2f | %-10.2f | %-10.2f | %-10.2f\n",
               vecTrimestre->paisDesc,
               vecTrimestre->t1,
               vecTrimestre->t2,
               vecTrimestre->t3,
               vecTrimestre->t4);

       vecTrimestre++;
    }
    fprintf(arch,"----------------------------------------------------------------------------------------");

    fclose(arch);
    return 1;
}

int archivoParticipacion(participacionContinente* vecParticipacionContinente, size_t* ceParticipacion)
{
    FILE *arch = fopen("participacion_continentes.dat", "wb");
    size_t i;
    if(arch == NULL)
    {
        printf("\nError archivo dat.");
        return SIN_MEM;
    }

    for(i=0 ; i<*ceParticipacion; i++)
    {
        fwrite(vecParticipacionContinente, sizeof(participacionContinente), 1, arch);
        vecParticipacionContinente++;
    }

    fclose(arch);
    return 1;
}

int mostrarParticipacionContinente()
{
    FILE *arch = fopen("participacion_continentes.dat", "rb");
    participacionContinente *continenteLeido = (participacionContinente *)malloc(sizeof(participacionContinente));

    if (!continenteLeido)
    {
        return SIN_MEM;
    }

    if (arch == NULL)
    {
        printf("\nNo se encontro el archivo binario.\n");
        free(continenteLeido);
        return SIN_MEM;
    }

    printf("\n--- PARTICIPACION PORCENTUAL POR CONTINENTE ---\n");
    printf("%-20s | %-10s | %-10s\n", "CONTINENTE", "C", "D");
    printf("-------------------------------------------------\n");

    while (fread(continenteLeido, sizeof(participacionContinente), 1, arch) == 1)
    {

        printf("%-20s | %-10.2f | %-10.2f\n",
               continenteLeido->continente,
               continenteLeido->total_credito,
               continenteLeido->total_debito);
    }

    printf("-------------------------------------------------\n");

    fclose(arch);
    free(continenteLeido);
    return 1;
}
