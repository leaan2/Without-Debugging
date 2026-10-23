 #include "funciones.h"
 #include "mostrar.h"
 #include "ordenar.h"
 #include "archivos.h"

int main()
{
    TransferenciaPersonal *vecTransferencia;
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
    int leerArchivo = -1;

    PromedioTrimestralPais *vecPromedioPais;
    size_t capacidadPromedioPais = 10, cantidadPromedioPais = 0;


    PromedioTrimestralContinente *vecContinentePromedioTrimestral;
    size_t capacidadContinentePromedio = 10, cantidadContinentePromedio =0;

    int opcion=0, archivoBaseLarga=0, anio;
    int estado = TODO_OK;

    vecTransferencia = (TransferenciaPersonal *)malloc(capacidadTransferencias * sizeof(TransferenciaPersonal));

    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));

    vecResumenPais =(Pais *)malloc(capacidadResumenPais * sizeof(Pais));

    vecContinentes = (Continente *)malloc (capacidadContinentes * sizeof(Continente));

    vecTrimestre = (SaldoTrimestral *)malloc (capacidadTrimestre * sizeof(SaldoTrimestral));

    vecAnual = (AnualAnio *)malloc (capacidadAnual * sizeof(AnualAnio));

    vecParticipacionContinente = (participacionContinente *)malloc(capacidadParticipacion * sizeof(participacionContinente));

    vecPromedioPais = (PromedioTrimestralPais *)malloc(capacidadPromedioPais * sizeof(PromedioTrimestralPais));

    vecContinentePromedioTrimestral = (PromedioTrimestralContinente *)malloc (capacidadContinentePromedio * sizeof(PromedioTrimestralContinente));

    if(!vecTransferencia || !vecPaises || !vecResumenPais  || !vecContinentes || !vecTrimestre  || !vecAnual || !vecParticipacionContinente || !vecPromedioPais || !vecContinentePromedioTrimestral)
    {
        printf("Error al reservar memoria.\n");
        estado = SIN_MEM;
    }

    if(estado == TODO_OK) {
        // CARGA DE ARCHIVOS .CSV
        vecTransferencia = cargarTransferencias(vecTransferencia, &cantidadTransferencias, &capacidadTransferencias, &estado);
        vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises, &estado);

        if(cantidadTransferencias == 0 || cantidadPaises == 0) {
            printf("No se pudieron cargar los archivos.\n");
            estado = ERROR_ARCHIVO;
        }
    }

    while(estado == TODO_OK && opcion != 10) {
        opcion = mostrarMenu();
        switch(opcion) {
            case 1:
            //PUNTO 1
            cantidadResumenPais=0;
            vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vecTransferencia, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais, &estado);
            if(estado == TODO_OK)
            {
                ordenarPaisCreditoSeleccion(vecResumenPais, &cantidadResumenPais);
                mostrarResumenPais(vecResumenPais, &cantidadResumenPais);
            }
            break;

            case 2:
            // PUNTO 2
            if(cantidadResumenPais == 0)
            {
                vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vecTransferencia, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais, &estado);
            }
            printf("\n ----- Continentes ----- \n\n\n");
            cantidadContinentes=0;
            vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes, &estado);
            if(estado == TODO_OK)
            {
                ordenarContinente(vecContinentes, &cantidadContinentes);
                mostrarContinentesGuardados(vecContinentes, &cantidadContinentes);
            }

            break;

            case 3:
            // PUNTO 3
            printf ("\nIngrese anio para calcular saldos trimestrales(2015 a 2026):\n");
            scanf ("%d", &anio);
            getchar();
            while(anio >= 2027 || 2014 >=anio)
            {
                printf ("\nIngrese anio nuevamente para calcular saldos trimestrales(2015 a 2026):\n");
                scanf ("%d", &anio);
                getchar();
            }
            cantidadTrimestre=0;
            vecTrimestre = calculoTrimestre(vecTrimestre, &cantidadTrimestre, &capacidadTrimestre, vecTransferencia, &cantidadTransferencias, anio, &estado);
            if(estado == TODO_OK)
            {
                ordenarSaldoTrimestralInsercion(vecTrimestre, &cantidadTrimestre);
                mostrarSaldoTrimestral(vecTrimestre, &cantidadTrimestre);
                archivoTxtSaldo(vecTrimestre, &cantidadTrimestre);
            }

            break;

            case 4:
            // PUNTO 4
            cantidadAnual=0;
            vecAnual = totalAnual(vecAnual, &cantidadAnual, &capacidadAnual, vecTransferencia, &cantidadTransferencias, &estado);
            if(estado == TODO_OK)
            {
                ordenarAnualAnio (vecAnual, &cantidadAnual);
                vecAnual = calculoVariacionAnual(vecAnual, &cantidadAnual);
                printf("\n\nANUAL POR ANIO");
                mostrarAnualAnio(vecAnual, &cantidadAnual);
            }

            break;

            case 5:
            // PUNTO 5
            cantidadPaisesAListar = 0;
            if(cantidadResumenPais == 0)
            {
                vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vecTransferencia, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais, &estado);
            }
            printf("\nIndique la cantidad de paises a listar (mayor a 0, menor o igual a %zu): ", cantidadResumenPais);
            scanf("%zu", &cantidadPaisesAListar);
            while(getchar() != '\n');
            while (cantidadPaisesAListar <=0 || cantidadPaisesAListar > cantidadResumenPais)
            {
                printf("\nIndique nuevamente la cantidad de paises a listar (mayor a 0, menor o igual a %zu): ", cantidadResumenPais);
                scanf("%zu", &cantidadPaisesAListar);
                while(getchar() != '\n');
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

            if (estado == TODO_OK)
            {
                if(Operacion == 'C')
                {
                    printf("\nOrdenando paises por credito \n\n");
                    ordenarPaisCreditoSeleccion(vecResumenPais, &cantidadResumenPais);
                    mostrarListadoPaises(vecResumenPais,&cantidadPaisesAListar, &Operacion);
                }
                else
                {
                    printf("\nOrdenando paises por debito \n\n");
                    ordenarResumenPaisDebito(vecResumenPais, &cantidadResumenPais);
                    mostrarListadoPaises(vecResumenPais,&cantidadPaisesAListar, &Operacion);
                }
            }
            break;

            case 6:
            // PUNTO 6
            leerArchivo = -1;
            if(cantidadContinentes == 0)
            {
                vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vecTransferencia, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais, &estado);
                vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes, &estado);

                if (estado == TODO_OK)
                ordenarContinente(vecContinentes, &cantidadContinentes);
            }
            capacidadParticipacion = capacidadContinentes;
            cantidadParticipacion = cantidadContinentes;
            vecParticipacionContinente = porcentajeContinente(vecParticipacionContinente, &cantidadParticipacion,&capacidadParticipacion, vecContinentes, &estado);
            if (estado == TODO_OK)
            {
                ordenarParticipacion(vecParticipacionContinente, &cantidadParticipacion);
                archivoParticipacion(vecParticipacionContinente, &cantidadParticipacion);

                printf("\nIndique si quiere leer el archivo partipacion continentes (1 para SI, 0 para NO): \n");
                while(leerArchivo != 0 && leerArchivo !=1)
                {
                    do
                    {
                        scanf("%d", &leerArchivo);
                        while (getchar() != '\n');
                        if (leerArchivo != 0 && leerArchivo != 1)
                        {
                            printf("\nIndique nuevamente si quiere leer el archivo partipacion continentes (1 para SI, 0 para NO): \n");
                        }
                    }
                    while (leerArchivo != 0 && leerArchivo != 1);
                }
                if (leerArchivo == 1)
                {
                    mostrarParticipacionContinente();
                }
            }
            break;

            case 7:
            // punto 7
            printf("\nGenerando archivo Transferencias_base_larga.csv\n");
            if (estado == TODO_OK)
            {
                archivoBaseLarga = vecBaseLarga(vecTransferencia, &cantidadTransferencias, vecPaises, &cantidadPaises, &estado);
            }
            break;

            case 8:
            if(!archivoBaseLarga)
            {
                archivoBaseLarga = vecBaseLarga(vecTransferencia, &cantidadTransferencias, vecPaises, &cantidadPaises, &estado);
            }
            //punto 8
            cantidadPromedioPais=0;
            vecPromedioPais = cargaPromedio(vecPromedioPais, &cantidadPromedioPais, &capacidadPromedioPais, &estado);
            if (estado == TODO_OK)
            {
                vecPromedioPais = calculoPromedio(vecPromedioPais, &cantidadPromedioPais);
                ordenarPromedioTrimestral(vecPromedioPais, &cantidadPromedioPais);
                mostrarPromedioTrimestral(vecPromedioPais, &cantidadPromedioPais);
            }
            break;

            case 9:
            // punto 9
            if(!archivoBaseLarga)
            {
                archivoBaseLarga = vecBaseLarga(vecTransferencia, &cantidadTransferencias, vecPaises, &cantidadPaises, &estado);
            }
            if(estado != TODO_OK)
            {
                printf("\nError al generar el archivo base larga.\n");
                break;
            }
            cantidadContinentePromedio=0;
            vecContinentePromedioTrimestral = cargaPromedioContinente(vecContinentePromedioTrimestral, &cantidadContinentePromedio, &capacidadContinentePromedio, &estado);
            if(estado != TODO_OK)
            {
                printf("\nError al cargar el promedio por continente y anio.\n");
                break;
            }
            vecContinentePromedioTrimestral = calculoPromedioContinente(vecContinentePromedioTrimestral , &cantidadContinentePromedio);
            mostrarPromedioContinente(vecContinentePromedioTrimestral,  &cantidadContinentePromedio);
            break;

            case 10:
            printf("\nSaliendo del programa...\n");
            break;

            default:
            printf("\nOpcion invalida. Intente nuevamente.\n");
            break;
        }
    }

    free(vecTransferencia);
    free(vecPaises);
    free(vecResumenPais);
    free(vecContinentes);
    free(vecTrimestre);
    free(vecAnual);
    free(vecParticipacionContinente);
    free(vecPromedioPais);
    free(vecContinentePromedioTrimestral);
    return estado;
}
