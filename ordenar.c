#include "funciones.h"
#include "ordenar.h"


void ordenarSeleccionPaisCredito(Pais *vec, size_t *cePais)
{
    Pais *auxI, *auxJ, *menor, reemplazo;
    size_t i, j;

    auxI = vec; // Arrancamos en el inicio del vector
    for(i=0; i < (*cePais)-1; i++)
    {
        menor = auxI; 
        auxJ = auxI + 1; // auxJ empieza un lugar a la derecha de auxI

        // Buscamos el más chico en lo que queda del vector
        for(j = i+1; j < *cePais; j++)
        {
            if(auxJ->total_credito > menor->total_credito)
            {
                menor = auxJ;
            }
            auxJ++; // Avanzamos el puntero explorador
        }

        // Intercambiamos si encontramos uno menor
        if(menor != auxI)
        {
            reemplazo = *auxI;
            *auxI = *menor;
            *menor = reemplazo;
        }
        
        auxI++; // Avanzamos al siguiente hueco a ordenar
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

    auxI = vecTrimestre + 1; // Arrancamos evaluando desde la segunda posición

    for(i=1; i < *ceTrimestre; i++)
    {
        elemAIns = *auxI; // Sacamos el valor a insertar
        
        auxJ = auxI;       // El hueco arranca donde sacamos el elemento
        izq = auxI - 1;    // Miramos el elemento inmediatamente a su izquierda
        j = i;

        // Mientras no lleguemos al inicio y el país de la izquierda sea mayor alfabéticamente...
        while(j > 0 && strcmp(izq->paisDesc, elemAIns.paisDesc) > 0)
        {
            *auxJ = *izq; // Movemos el de la izquierda hacia la derecha
            
            // Retrocedemos ambos punteros
            auxJ--; 
            izq--;
            j--;
        }
        
        *auxJ = elemAIns; // Colocamos el elemento en el hueco final
        
        auxI++; // Avanzamos al siguiente elemento a procesar
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




