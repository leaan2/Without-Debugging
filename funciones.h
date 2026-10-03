#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIN_MEM -1
#define largoPaisCod 4
#define largoPaisDesc 50
#define largoContinente 30

typedef struct
{
    int anio;
    int trimestre;
    char paisCod[largoPaisCod];
    char paisDesc[largoPaisDesc];
    char operacion;
    float monto;
} Transferencia;

typedef struct
{
    char paisCod[largoPaisCod];
    char paisDesc[largoPaisDesc];
    char continente[largoContinente];
}Paises_continente;


typedef struct
{
    char paisCod[largoPaisCod];
    char paisDesc[largoContinente];
    int cantRegistros;
    float total_credito;
    float total_debito;
}Pais;

typedef struct
{
    char continente [largoContinente];
    int cantRegistros;
    float total_credito;
    float total_debito;
}Continente;

typedef struct
{
    char paisDesc[largoPaisDesc];
    float t1;
    float t2;
    float t3;
    float t4;
}SaldoTrimestral;


Transferencia* cargarTransferencias(Transferencia *, size_t *, size_t *);
void mostrarTransferencias(Transferencia *, size_t* );

Paises_continente* cargarPaises(Paises_continente *, size_t *, size_t *);
void mostrarPaises(Paises_continente *, size_t* );

Pais *lecturaAgrupamientoPais(Pais *vec,Transferencia *vecTransferencia ,size_t *ce, size_t *cePais,size_t *capacidad, size_t *capacidadPais);
void ordenarResumenPais(Pais *vec, size_t *cePais);
void mostrarResumenPais(Pais *vec, size_t* cePais);

Continente *ResumenContinentes(Continente *, size_t *, Pais *, size_t *, Paises_continente *, size_t *, size_t *);
void ordenarContinente(Continente *, size_t *);
void mostrarContinentesGuardados(Continente *, size_t *);


SaldoTrimestral *calculoTrimestre (SaldoTrimestral *vecTrimestre, size_t *ceTrimestre, size_t *capacidadTrimestre, Transferencia*vecTransferencia, size_t *ceTransferencia);
void mostrarSaldoTrimestral(SaldoTrimestral *, size_t *);

void ordenarSaldoTrimestral(SaldoTrimestral *, size_t *);
int archivoTxtSaldo (SaldoTrimestral *, size_t *);
#endif // FUNCIONES_H_INCLUDED
