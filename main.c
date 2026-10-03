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

    SaldoTrimestral *vecTrimestre;
    size_t capacidadTrimestre = 10, cantidadTrimestre =0;

    vec = (Transferencia *)malloc(capacidadTransferencias * sizeof(Transferencia));

    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));

    vecResumenPais =(Pais *)malloc(capacidadResumenPais * sizeof(Pais));

    vecContinentes = (Continente *)malloc (capacidadContinentes * sizeof(Continente));

    vecTrimestre = (SaldoTrimestral *)malloc (capacidadTrimestre * sizeof(SaldoTrimestral));

    if(vec == NULL || vecPaises == NULL || vecResumenPais == NULL || vecContinentes == NULL || vecTrimestre == NULL)
    {
        printf("Error al reservar memoria.\n");
        return SIN_MEM;
    }
    // CARGA DE ARCHIVOS .CSV
    vec = cargarTransferencias(vec, &cantidadTransferencias, &capacidadTransferencias);
    vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises);

    //PUNTO 1
    vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadTransferencias, &capacidadResumenPais);
    ordenarResumenPais(vecResumenPais, &cantidadResumenPais);
    mostrarResumenPais(vecResumenPais, &cantidadResumenPais);

    // PUNTO 2
    printf("\n ----- Continentes ----- \n\n\n");
    vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes);
    ordenarContinente(vecContinentes, &cantidadContinentes);
    mostrarContinentesGuardados(vecContinentes, &cantidadContinentes);

    vecTrimestre = calculoTrimestre(vecTrimestre, &cantidadTrimestre, &capacidadTrimestre, vec, &cantidadTransferencias);
    mostrarSaldoTrimestral(vecTrimestre, &cantidadTrimestre);
    archivoTxtSaldo(vecTrimestre, &cantidadTrimestre);


    free(vec);
    free(vecPaises);
    free(vecResumenPais);
    free(vecContinentes);
    free(vecTrimestre);
    return 0;
}
