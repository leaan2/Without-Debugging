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

    PromedioTrimestralPais *vecPromedioPais;
    size_t capacidadPromedioPais = 10, cantidadPromedioPais = 0;


    PromedioTrimestralContinente *vecContinentePromedioTrimestral;
    size_t capacidadContinentePromedio = 10, cantidadContinentePromedio =0;

    int opcion, archivoBaseLarga=0;

    vec = (TransferenciaPersonal *)malloc(capacidadTransferencias * sizeof(TransferenciaPersonal));

    vecPaises = (Paises_continente *)malloc(capacidadPaises * sizeof(Paises_continente));

    vecResumenPais =(Pais *)malloc(capacidadResumenPais * sizeof(Pais));

    vecContinentes = (Continente *)malloc (capacidadContinentes * sizeof(Continente));

    vecTrimestre = (SaldoTrimestral *)malloc (capacidadTrimestre * sizeof(SaldoTrimestral));

    vecAnual = (AnualAnio *)malloc (capacidadAnual * sizeof(AnualAnio));

    vecParticipacionContinente = (participacionContinente *)malloc(capacidadParticipacion * sizeof(participacionContinente));

    vecPromedioPais = (PromedioTrimestralPais *)malloc(capacidadPromedioPais * sizeof(PromedioTrimestralPais));

    vecContinentePromedioTrimestral = (PromedioTrimestralContinente *)malloc (capacidadContinentePromedio * sizeof(PromedioTrimestralContinente));

    if(!vec || !vecPaises || !vecResumenPais  || !vecContinentes || !vecTrimestre  || !vecAnual || !vecParticipacionContinente || !vecPromedioPais || !vecContinentePromedioTrimestral)
    {
        printf("Error al reservar memoria.\n");
        return SIN_MEM;
    }
    // CARGA DE ARCHIVOS .CSV
    vec = cargarTransferencias(vec, &cantidadTransferencias, &capacidadTransferencias);
    vecPaises= cargarPaises(vecPaises, &cantidadPaises, &capacidadPaises);

    do{
        opcion = mostrarMenu();
        switch(opcion) {
            case 1:
            //PUNTO 1
            vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais);
            ordenarResumenPaisCredito(vecResumenPais, &cantidadResumenPais);
            mostrarResumenPais(vecResumenPais, &cantidadResumenPais);
            break;

            case 2:
            // PUNTO 2
            printf("\n ----- Continentes ----- \n\n\n");
            vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes);
            ordenarContinente(vecContinentes, &cantidadContinentes);
            mostrarContinentesGuardados(vecContinentes, &cantidadContinentes);
            capacidadParticipacion = capacidadContinentes;
            cantidadParticipacion = cantidadContinentes;
            break;

            case 3:
            // PUNTO 3
            vecTrimestre = calculoTrimestre(vecTrimestre, &cantidadTrimestre, &capacidadTrimestre, vec, &cantidadTransferencias);
            ordenarSaldoTrimestral(vecTrimestre, &cantidadTrimestre);
            mostrarSaldoTrimestral(vecTrimestre, &cantidadTrimestre);
            archivoTxtSaldo(vecTrimestre, &cantidadTrimestre);
            break;

            case 4:
            // PUNTO 4
            vecAnual = totalAnual(vecAnual, &cantidadAnual, &capacidadAnual, vec, &cantidadTransferencias);
            ordenarAnualAnio (vecAnual, &cantidadAnual);
            vecAnual = calculoVariacionAnual(vecAnual, &cantidadAnual);
            printf("\n\nANUAL POR ANIO");
            mostrarAnualAnio(vecAnual, &cantidadAnual);
            break;

            case 5:
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
            break;

            case 6:
            // PUNTO 6
            if(cantidadContinentes == 0)
            {
                vecResumenPais = lecturaAgrupamientoPais(vecResumenPais, vec, &cantidadTransferencias, &cantidadResumenPais, &capacidadResumenPais);
                vecContinentes = ResumenContinentes(vecContinentes, &cantidadContinentes, vecResumenPais, &cantidadResumenPais, vecPaises, &cantidadPaises, &capacidadContinentes);
                ordenarContinente(vecContinentes, &cantidadContinentes);
                capacidadParticipacion = capacidadContinentes;
                cantidadParticipacion = cantidadContinentes;
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
            break;

            case 7:
            // punto 7
            archivoBaseLarga =vecBaseLarga(vec, &cantidadTransferencias, vecPaises, &cantidadPaises);
            break;

            case 8:
            if(!archivoBaseLarga)
            {
                archivoBaseLarga = vecBaseLarga(vec, &cantidadTransferencias, vecPaises, &cantidadPaises);
            }
            //punto 8
            vecPromedioPais = cargaPromedio(vecPromedioPais, &cantidadPromedioPais, &capacidadPromedioPais);
            vecPromedioPais = calculoPromedio(vecPromedioPais, &cantidadPromedioPais, &capacidadPromedioPais);
            ordenarPromedioTrimestral(vecPromedioPais, &cantidadPromedioPais);
            mostrarPromedioTrimestral(vecPromedioPais, &cantidadPromedioPais);
            case 9:
            // punto 9
            if(!archivoBaseLarga)
            {
                archivoBaseLarga = vecBaseLarga(vec, &cantidadTransferencias, vecPaises, &cantidadPaises);
            }
            vecContinentePromedioTrimestral = cargaPromedioContinente(vecContinentePromedioTrimestral, &cantidadContinentePromedio, &capacidadContinentePromedio);
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

    }while(opcion != 10);


    free(vec);
    free(vecPaises);
    free(vecResumenPais);
    free(vecContinentes);
    free(vecTrimestre);
    free(vecAnual);
    free(vecParticipacionContinente);
    free(vecPromedioPais);
    free(vecContinentePromedioTrimestral);
    return 0;
}
