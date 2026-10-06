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
} Paises_continente;

typedef struct
{
    char paisCod[largoPaisCod];
    char paisDesc[largoContinente];
    int cantRegistros;
    float total_credito;
    float total_debito;
} Pais;

typedef struct
{
    char continente [largoContinente];
    int cantRegistros;
    float total_credito;
    float total_debito;
} Continente;

typedef struct
{
    char paisDesc[largoPaisDesc];
    float t1;
    float t2;
    float t3;
    float t4;
} SaldoTrimestral;

typedef struct
{
    int anio;
    float credito;
    float debito;
    float saldo;
    float var_pct_saldo;
}AnualAnio;



Transferencia* cargarTransferencias(Transferencia *, size_t *, size_t *);
Paises_continente* cargarPaises(Paises_continente *, size_t *, size_t *);
Pais *lecturaAgrupamientoPais(Pais *,Transferencia * ,size_t *, size_t *, size_t *);
Continente *ResumenContinentes(Continente *, size_t *, Pais *, size_t *, Paises_continente *, size_t *, size_t *);
SaldoTrimestral *calculoTrimestre (SaldoTrimestral *, size_t *, size_t *, Transferencia*, size_t *);
AnualAnio *totalAnual (AnualAnio *, size_t *, size_t *, Transferencia *, size_t *);
AnualAnio *calculoVariacionAnual (AnualAnio *, size_t *);
#endif // FUNCIONES_H_INCLUDED
