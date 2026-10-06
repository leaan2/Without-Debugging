 #include "funciones.h"
 #include "mostrar.h"
 #include "ordenar.h"
 #include "archivos.h"

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

    AnualAnio *vecAnual;
    size_t capacidadAnual = 10, cantidadAnual = 0;

    vec = (Transferencia *)malloc(capacidadTransferencias * sizeof(Transferencia));

    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));

    vecResumenPais =(Pais *)malloc(capacidadResumenPais * sizeof(Pais));

    vecContinentes = (Continente *)malloc (capacidadContinentes * sizeof(Continente));

    vecTrimestre = (SaldoTrimestral *)malloc (capacidadTrimestre * sizeof(SaldoTrimestral));

    vecAnual = (AnualAnio *)malloc (capacidadAnual * sizeof(AnualAnio));
    if(vec == NULL || vecPaises == NULL || vecResumenPais == NULL || vecContinentes == NULL || vecTrimestre == NULL || vecAnual == NULL)
    {
        printf("Error al reservar memoria.\n");
        return SIN_MEM;
    }
    // CARGA DE ARCHIVOS .CSV
    vec = cargarTransferencias(vec, &cantidadTransferencias, &capacidadTransferencias);
    vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises);

    //PUNTO 1
    vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais);
    ordenarResumenPais(vecResumenPais, &cantidadResumenPais);
    mostrarResumenPais(vecResumenPais, &cantidadResumenPais);

    // PUNTO 2
    printf("\n ----- Continentes ----- \n\n\n");
    vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes);
    ordenarContinente(vecContinentes, &cantidadContinentes);
    mostrarContinentesGuardados(vecContinentes, &cantidadContinentes);

    // PUNTO 3 
    vecTrimestre = calculoTrimestre(vecTrimestre, &cantidadTrimestre, &capacidadTrimestre, vec, &cantidadTransferencias);
    ordenarSaldoTrimestral(vecTrimestre, &cantidadTrimestre);
    mostrarSaldoTrimestral(vecTrimestre, &cantidadTrimestre);
    archivoTxtSaldo(vecTrimestre, &cantidadTrimestre);


    // PUNTO 4 
    vecAnual = totalAnual(vecAnual, &cantidadAnual, &capacidadAnual, vec, &cantidadTransferencias);
    ordenarAnualAnio (vecAnual, &cantidadAnual);
    vecAnual = calculoVariacionAnual(vecAnual, &cantidadAnual);
    printf("\n\nANUAL POR ANIO");
    mostrarAnualAnio(vecAnual, &cantidadAnual);

    free(vec);
    free(vecPaises);
    free(vecResumenPais);
    free(vecContinentes);
    free(vecTrimestre);
    free(vecAnual);
    return 0;
}
