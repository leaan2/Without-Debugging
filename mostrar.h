#ifndef MOSTRAR_H_INCLUDED
#define MOSTRAR_H_INCLUDED

#include "funciones.h"

void mostrarSaldoTrimestral(SaldoTrimestral *, size_t *);
void mostrarContinentesGuardados(Continente *, size_t *);
void mostrarResumenPais(Pais *vec, size_t* cePais);
void mostrarPaises(Paises_continente *, size_t* );
void mostrarTransferencias(TransferenciaPersonal *, size_t* );
void mostrarAnualAnio(AnualAnio *, size_t *);
void mostrarListadoPaises(Pais *, size_t* , char* );
void mostrarPromedioTrimestral(PromedioTrimestral *, size_t *);

#endif // MOSTRAR_H_INCLUDED
