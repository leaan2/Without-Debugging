 #include "funciones.h"
 #include "mostrar.h"
 #include "ordenar.h"
 #include "archivos.h"

int main()
{
    TransferenciaPersonal *vec;
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

    size_t cantidadPaisesAListar = 0;
    char Operacion;

    participacionContinente* vecParticipacionContinente;
    size_t cantidadParticipacion =0, capacidadParticipacion=10;
    int leerArchivo =0;

    PromedioTrimestral *vecPromedio;
    size_t capacidadPromedio = 10, cantidadPromedio = 0;



    vec = (TransferenciaPersonal *)malloc(capacidadTransferencias * sizeof(TransferenciaPersonal));

    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));

    vecResumenPais =(Pais *)malloc(capacidadResumenPais * sizeof(Pais));

    vecContinentes = (Continente *)malloc (capacidadContinentes * sizeof(Continente));

    vecTrimestre = (SaldoTrimestral *)malloc (capacidadTrimestre * sizeof(SaldoTrimestral));

    vecAnual = (AnualAnio *)malloc (capacidadAnual * sizeof(AnualAnio));

    vecPromedio = (PromedioTrimestral *)malloc(capacidadPromedio * sizeof(PromedioTrimestral));

  
    if(!vec  || !vecPaises || !vecResumenPais  || !vecContinentes || !vecTrimestre  || !vecAnual || !vecPromedio)
    {
        printf("Error al reservar memoria.\n");
        return SIN_MEM;
    }
    // CARGA DE ARCHIVOS .CSV
    vec = cargarTransferencias(vec, &cantidadTransferencias, &capacidadTransferencias);
    vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises);

    //PUNTO 1
    vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais);
    ordenarResumenPaisCredito(vecResumenPais, &cantidadResumenPais);
    mostrarResumenPais(vecResumenPais, &cantidadResumenPais);

    // PUNTO 2
    printf("\n ----- Continentes ----- \n\n\n");
    vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes);
    ordenarContinente(vecContinentes, &cantidadContinentes);
    mostrarContinentesGuardados(vecContinentes, &cantidadContinentes);
    capacidadParticipacion = capacidadContinentes;
    cantidadParticipacion = cantidadContinentes;

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


    // PUNTO 5
    // vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais);
    // por si no se ingresa al punto 3 en el menu
    printf("\nIndique la cantidad de paises a listar (mayor a 0, menor o igual a %zu): ", cantidadResumenPais);
    scanf("%zu", &cantidadPaisesAListar);
    while (cantidadPaisesAListar <=0 || cantidadPaisesAListar > cantidadResumenPais)
    {
        printf("\nIndique nuevamente la cantidad de paises a listar (mayor a 0, menor o igual a %zu): ", cantidadResumenPais);
        scanf("%zu", &cantidadPaisesAListar);
    }
    printf("\nIngrese tipo de operacion ('C' para Credito, 'D' para Debito): ");
    scanf(" %c", &Operacion);
    Operacion = toupper(Operacion);
    while(Operacion != 'C' && Operacion != 'D')
    {
        printf("\nIngrese nuevamente tipo de operacion ('C' para Credito, 'D' para Debito): ");
        scanf(" %c", &Operacion);
        Operacion = toupper(Operacion);
    }

    if(Operacion == 'C')
    {
        printf("\nOrdenando paises por credito \n\n");
        ordenarResumenPaisCredito(vecResumenPais, &cantidadResumenPais);
        mostrarListadoPaises(vecResumenPais,&cantidadPaisesAListar, &Operacion);
    }
    else
    {
        printf("\nOrdenando paises por debito \n\n");
        ordenarResumenPaisDebito(vecResumenPais, &cantidadResumenPais);
        mostrarListadoPaises(vecResumenPais,&cantidadPaisesAListar, &Operacion);
    }



    // PUNTO 6

    vecParticipacionContinente = (participacionContinente *)malloc(capacidadParticipacion * sizeof(participacionContinente));
    if(!vecParticipacionContinente)
    {
        return SIN_MEM;
    }

    vecParticipacionContinente = porcentajeContinente(vecParticipacionContinente, &cantidadParticipacion, vecContinentes);
    ordenarParticipacion(vecParticipacionContinente, &cantidadParticipacion);
    archivoParticipacion(vecParticipacionContinente, &cantidadParticipacion);
    printf("\nIndique si quiere leer el archivo partipacion continentes (1 para SI, 0 para NO): \n");
    scanf("%d", &leerArchivo);
    while(leerArchivo != 0 && leerArchivo !=1)
    {
        printf("\nIndique nuevamente si quiere leer el archivo partipacion continentes (1 para SI, 0 para NO): \n");
        scanf("%d", &leerArchivo);
    }
    if (leerArchivo == 1)
    {
        mostrarParticipacionContinente();
    }


    // punto 7
    vecBaseLarga(vec, &cantidadTransferencias, vecPaises, &cantidadPaises);
    
    //punto 8
    vecPromedio = calculoPromedio(vecPromedio, &cantidadPromedio, &capacidadPromedio);
    mostrarPromedioTrimestral(vecPromedio, &cantidadPromedio);

    






    free(vec);
    free(vecPaises);
    free(vecResumenPais);
    free(vecContinentes);
    free(vecTrimestre);
    free(vecAnual);
    free(vecPromedio);
    return 0;
}
