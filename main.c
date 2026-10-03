#include "funciones.h"

int main()
{
    Transferencia *vec;
    size_t capacidadTransferencias = 10, cantidadTransferencias=0;


    Paises_continente *vecPaises;
    size_t capacidadPaises = 10, cantidadPaises=0;

    Pais *vecResumenPais;
    size_t capacidadResumenPais =10, cantidadResumenPais=0;

    Continente *vecContinentes;
    size_t capacidadContinentes = 10, cantidadContinentes=0;


    vec = (Transferencia *)malloc(capacidadTransferencias * sizeof(Transferencia));

    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));

    vecResumenPais =(Pais *)malloc(capacidadResumenPais * sizeof(Pais));

    vecContinentes = (Continente *)malloc (capacidadContinentes * sizeof(Continente));

    if(vec == NULL || vecPaises == NULL || vecResumenPais == NULL || vecContinentes== NULL)
    {
        printf("Error al reservar memoria.\n");
        return SIN_MEM;
    }

    vec = cargarTransferencias(vec, &cantidadTransferencias, &capacidadTransferencias);

    vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises);

    vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadTransferencias, &capacidadResumenPais);
    //ordenarResumenPais(vecResumenPais, &cantidadResumenPais);
    //mostrarResumenPais(vecResumenPais, &cantidadResumenPais);

    vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes);
    mostrarContinentesGuardados(vecContinentes, &cantidadContinentes);

    free(vec);
    free (vecPaises);
    free(vecResumenPais);
    free(vecContinentes);
    return 0;
}
