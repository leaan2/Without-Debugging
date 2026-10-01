#include "funciones.h"

int main()
{
    Transferencia *vec;
    Paises_continente *vecPaises;
    size_t capacidadTransferencias = 10, cantidadTransferencias=0;
    size_t capacidadPaises = 10, cantidadPaises=0;
    vec = (Transferencia *)malloc(capacidadTransferencias * sizeof(Transferencia));
    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));
    if(vec == NULL || vecPaises == NULL)
    {
        printf("Error al reservar memoria.\n");
        return SIN_MEM;
    }

    vec = cargarTransferencias(vec, &cantidadTransferencias, &capacidadTransferencias);
    //mostrarTransferencias(vec, &cantidadTransferencias);
    vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises);
    mostrarPaises(vecPaises, &cantidadPaises);
    free(vec);
    free (vecPaises);
    return 0;
}
