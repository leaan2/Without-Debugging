#include "funciones.h"
#include "ordenar.h"


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

void ordenarSaldoTrimestral(SaldoTrimestral *vecTrimestre, size_t *ceTrimestre)
{
    SaldoTrimestral *aux, reemplazo;
    size_t i,j;

    for(i=0; i< *ceTrimestre -1; i++)
    {
        aux = vecTrimestre;
        for(j=0 ; j< *ceTrimestre-i-1 ; j++)
        {
            if(strcmp(aux->paisDesc, (aux+1)->paisDesc)>0)
             {
                reemplazo = *(aux+1);
                *(aux+1) = *aux;
                *aux = reemplazo;
             }
             aux++;
        }

    }

}
void ordenarAnualAnio (AnualAnio *vecAnual, size_t *ceAnual)
{
   AnualAnio *aux, reemplazo;
    size_t i,j;

    for(i=0; i< *ceAnual -1; i++)
    {
        aux = vecAnual;
        for(j=0 ; j< *ceAnual-i-1 ; j++)
        {
            if(aux->anio > (aux+1)->anio)
             {
                reemplazo = *(aux+1);
                *(aux+1) = *aux;
                *aux = reemplazo;
             }
             aux++;
        }

    }
}






