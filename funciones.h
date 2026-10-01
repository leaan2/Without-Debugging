#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIN_MEM -1

typedef struct
{
    int anio;
    int trimestre;
    char paisCod[4];
    char paisDesc[50];
    char operacion;
    float monto;
} Transferencia;

typedef struct
{
    char paisCod[4];
    char paisDesc[50];
    char continente[50];
}Paises_continente;


typedef struct
{
    char paisCod[4];
    char paisDesc[50];
    int cantRegistros;
    float total_credito;
    float total_debito;
}Pais;


Transferencia* cargarTransferencias(Transferencia *, size_t *, size_t *);
void mostrarTransferencias(Transferencia *, size_t* );
Paises_continente* cargarPaises(Paises_continente *, size_t *, size_t *);
void mostrarPaises(Paises_continente *, size_t* );
#endif // FUNCIONES_H_INCLUDED
