#include "funciones.h"
#include "ordenar.h"


void ordenarPaisCreditoSeleccion(Pais *vec, size_t *cePais)
{
    Pais *auxI, *auxJ, *menor, reemplazo;
    size_t i, j;

    auxI = vec; 
    for(i=0; i < (*cePais)-1; i++)
    {
        menor = auxI; 
        auxJ = auxI + 1; 

        
        for(j = i+1; j < *cePais; j++)
        {
            if(auxJ->total_credito > menor->total_credito)
            {
                menor = auxJ;
            }
            auxJ++; 
        }

        
        if(menor != auxI)
        {
            reemplazo = *auxI;
            *auxI = *menor;
            *menor = reemplazo;
        }
        
        auxI++; 
    }
}
void ordenarResumenPaisDebito(Pais *vec, size_t *cePais)
{
    Pais *aux, reemplazo;
    size_t i,j;

    for(i=0;i< (*cePais)-1; i++)
    {
        aux = vec;
        for(j=0;j< (*cePais)-i-1; j++)
        {
            if(aux->total_debito < (aux+1)->total_debito)
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

void ordenarSaldoTrimestralInsercion(SaldoTrimestral *vecTrimestre, size_t *ceTrimestre)
{
    SaldoTrimestral *auxI, *auxJ, *izq, elemAIns;
    size_t i, j;

    auxI = vecTrimestre + 1; 

    for(i=1; i < *ceTrimestre; i++)
    {
        elemAIns = *auxI; 
        
        auxJ = auxI;       
        izq = auxI - 1;    
        j = i;

        
        while(j > 0 && strcmp(izq->paisDesc, elemAIns.paisDesc) > 0)
        {
            *auxJ = *izq; 
            
            
            auxJ--; 
            izq--;
            j--;
        }
        
        *auxJ = elemAIns; 
        
        auxI++; 
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

void ordenarParticipacion(participacionContinente *vecParticipacionContinente, size_t *ceParticipacion)
{
    participacionContinente *aux, reemplazo;
    size_t i,j;

    for(i=0;i< (*ceParticipacion)-1; i++)
    {
        aux = vecParticipacionContinente;
        for(j=0;j< (*ceParticipacion)-i-1; j++)
        {
            if(strcmp(aux->continente, (aux+1)->continente) > 0)
            {
                reemplazo = *(aux+1);
                *(aux+1) = *aux;
                *aux = reemplazo;
            }
            aux++;
        }
    }

}

void ordenarPromedioTrimestral(PromedioTrimestralPais *vecPromedio, size_t *cePromedio)
{
    PromedioTrimestralPais *aux, reemplazo;
    size_t i,j;

    for(i=0; i< *cePromedio -1; i++)
    {
        aux = vecPromedio;
        for(j=0 ; j< *cePromedio-i-1 ; j++)
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




