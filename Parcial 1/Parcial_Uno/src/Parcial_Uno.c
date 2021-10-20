/*
 ============================================================================
 Name        : Parcial_Uno.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMTIP 4
#define TAMCOL 5
#define TAMSERV 4
#define TAMBICI 1000
#define TAMTRA 1000
#define VACIO 0
#define OCUPADO 1

typedef struct
{
	int dia;
	int mes;
	int anio;
}eFecha;

typedef struct
{
	int id;
	char descripcion[20];
}eTipo;

typedef struct
{
	int id;
	char nombreColor[20];
}eColor;

typedef struct
{
	int id;
	char marca[20];
	int idTipo;
	int idColor;
	char material;
	int isEmpty;
}eBicicleta;

typedef struct
{
	int id;
	char descripcion[20];
	int precio;
}eServicio;

typedef struct
{
	int id;
	int idBicicleta;
	int idServicio;
	int fecha;
	int isEmpty;
}eTrabajo;


int inicializarBicicletas(eBicicleta* listaBicicletas, int tam);
int buscarLibre(eBicicleta* listaBicicletas, int tam);
int listarTipos(eTipo* listaTipos, int tamTipo);
int cargarTipo(eTipo* listaTipos, int tam, int id, char nombreTipo[]);
int listarColores(eColor* listaColores, int tamColor);
int cargarColor(eColor* listaColores, int tam, int id, char nombreColor[]);
int listarServicios(eServicio* listaServicios, int tamServicio);
int validarEntero(int* datoValidar, int minimo, int maximo);
int altaBicicleta(eBicicleta* listaBicicletas, int tam, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor, int* idSiguiente);
void mostrarBicicleta(eBicicleta miBicicleta, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor);
int mostrarBicicletas(eBicicleta* listaBicicletas, int tamBici, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor);
int modificarBicicleta(eBicicleta* listaBicicletas, int tamBici, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor);
int bajaBicicleta(eBicicleta* listaBicicletas, int tam, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor);
int inicializarTrabajos(eTrabajo* listaTrabajos, int tam);
int buscarTrabajoLibre(eTrabajo* listaTrabajos, int tam);
int altaTrabajo(eTrabajo* listaTrabajos, int tamTrabajo, eBicicleta* listaBicicletas, int tamBici, eServicio* listaServicios, int tamServicio, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor, int* idSiguiente);
void mostrarTrabajo(eTrabajo miTrabajo,eBicicleta* listaBicicletas, int tamBici, eServicio* listaServicios, int tamServicio, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor);
int mostrarTrabajos(eTrabajo* listaTrabajos, int tamTrabajo, eBicicleta* listaBicicletas, int tamBici, eServicio* listaServicios, int tamServicio, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor);

int main(void)
{
	setbuf(stdout, NULL);
    int opcion;

    eBicicleta listaBicicletas[TAMBICI];
    eTrabajo listaTrabajos[TAMTRA];
    inicializarBicicletas(listaBicicletas, TAMBICI);
    inicializarTrabajos(listaTrabajos, TAMTRA);

    int idSiguienteB = 1;
    int idSiguienteT = 1;
    int flagAlta = 0;
    int i;

    eTipo listaTipos[TAMTIP] =
    {
        {1000, "Rutera"},
        {1001, "Carrera"},
        {1002, "Mountain"},
        {1003, "BMX"}
    };
    eColor listaColores[TAMCOL] =
    {
        {5000, "Gris"},
        {5002, "Blanco"},
        {5003, "Azul"},
        {5001, "Negro"},
        {5004, "Rojo"}
    };
    eServicio listaServicios[TAMSERV] =
    {
        {20000, "Limpieza",30},
        {20001, "Parche",400},
        {20002, "Centrado",500},
        {20003, "Cadena",450}
    };


    do
    {
		system("cls");
		printf("\n*************MENU*************\n\n");
		printf("1- ALTA BICICLETA\n");
		printf("2- MODIFICAR BICICLETA\n");
		printf("3- BAJA BICICLETA\n");
		printf("4- LISTAR BICICLETAS\n");
		printf("5- LISTAR TIPOS\n");
		printf("6- LISTAR COLORES\n");
		printf("7- LISTAR SERVICIOS\n");
		printf("8- ALTA TRABAJO\n");
		printf("9- LISTAR TRABAJOS\n");
		printf("10- SALIR\n\n");
		scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
        	if(altaBicicleta(listaBicicletas, TAMBICI, listaTipos, TAMTIP, listaColores, TAMCOL, &idSiguienteB))
        	{
        		flagAlta = 1;
        		printf("Bicicleta dada de alta con exito.\n");
        		system("pause");
        	}
        	else
        	{
        		printf("Hubo un error al dar de alta la bicicleta.\n");
        	}
        break;

        case 2:
        	if(flagAlta)
        	{
        		modificarBicicleta(listaBicicletas, TAMBICI, listaTipos, TAMTIP, listaColores, TAMCOL);
        	}
        	else
        	{
        		printf("No hay bicicletas en el sistema.\n");
        		system("pause");
        	}
        break;

        case 3:
        	if(flagAlta)
        	{
        		if(bajaBicicleta(listaBicicletas, TAMBICI, listaTipos, TAMTIP, listaColores, TAMCOL))
				{
					printf("Bicicleta dada de baja con exito.\n");
					flagAlta = 0;

					for(i=0;i<TAMBICI;i++)
					{
						if(listaBicicletas[i].isEmpty == OCUPADO)
						{
							flagAlta = 1;
							break;
						}
					}
					system("pause");
				}
        	}
        	else
        	{
        		printf("No hay bicicletas en el sistema.\n");
        		system("pause");
        	}
        break;

        case 4:
        	if(flagAlta)
        	{
        		mostrarBicicletas(listaBicicletas, TAMBICI, listaTipos, TAMTIP, listaColores, TAMCOL);
        	}
        	else
        	{
        		printf("No hay bicicletas en el sistema.\n");
        		system("pause");
        	}
        break;

        case 5:
        	listarTipos(listaTipos, TAMTIP);
        	system("pause");
        break;

        case 6:
        	listarColores(listaColores, TAMCOL);
        	system("pause");
        break;

        case 7:
        	listarServicios(listaServicios, TAMSERV);
        	system("pause");
        break;

        case 8:
        	if(flagAlta)
        	{
        		if(altaTrabajo(listaTrabajos, TAMTRA, listaBicicletas, TAMBICI, listaServicios, TAMSERV, listaTipos, TAMTIP, listaColores, TAMCOL, &idSiguienteT))
        		{
					printf("Trabajo dado de alta con exito.\n");
					system("pause");
        		}
        	}
        	else
        	{
        		printf("No hay bicicletas en el sistema.\n");
        		system("pause");
        	}
		break;

        case 9:

        break;

        case 10:
        	printf("Ha salido con exito.\n");
        break;

        default:
            printf("Error, ingrese una opcion valida.");
            system("pause");
        break;
        }
    }
    while(opcion != 10);


	return EXIT_SUCCESS;
}

int inicializarBicicletas(eBicicleta* listaBicicletas, int tam)
{
    int ret = 0;
    int i;

    if(listaBicicletas != NULL && tam > 0)
    {
        for(i=0; i<tam; i++)
        {
        	listaBicicletas[i].isEmpty = VACIO;
        }
        ret = 1;
    }
    return ret;
}

int buscarLibre(eBicicleta* listaBicicletas, int tam)
{
    int index = -1;
    int i;

    if(listaBicicletas != NULL && tam > 0)
    {
        for(i=0; i<tam; i++)
        {
            if(listaBicicletas[i].isEmpty == VACIO)
            {
            	index = i;
                break;
            }
        }
    }
    return index;
}

int listarTipos(eTipo* listaTipos, int tamTipo)
{
    int ret = 0;
    int i;

    if(listaTipos != NULL && tamTipo > 0)
    {
        printf("\n************ TIPOS ************\n");
        for(i=0; i<tamTipo; i++)
        {
            printf("%d  %10s\n", listaTipos[i].id, listaTipos[i].descripcion);
        }

        ret = 1;
    }

    return ret;
}

int cargarTipo(eTipo* listaTipos, int tam, int id, char nombreTipo[])
{
	int ret = 0;
	int i;

	if(listaTipos != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			if(listaTipos[i].id == id)
			{
				strcpy(nombreTipo, listaTipos[i].descripcion);
				break;
			}
		}

		ret = 1;
	}

	return ret;
}

int listarColores(eColor* listaColores, int tamColor)
{
    int ret = 0;
    int i;

    if(listaColores != NULL && tamColor > 0)
    {
        printf("\n************ COLORES ************\n");
        for(i=0; i<tamColor; i++)
        {
            printf("%d  %10s\n", listaColores[i].id, listaColores[i].nombreColor);
        }

        ret = 1;
    }

    return ret;
}

int cargarColor(eColor* listaColores, int tam, int id, char nombreColor[])
{
	int ret = 0;
	int i;

	if(listaColores != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			if(listaColores[i].id == id)
			{
				strcpy(nombreColor, listaColores[i].nombreColor);
				break;
			}
		}

		ret = 1;
	}

	return ret;
}

int listarServicios(eServicio* listaServicios, int tamServicio)
{
    int ret = 0;
    int i;

    if(listaServicios != NULL && tamServicio > 0)
    {
        printf("\n************ SERVICIOS ************\n");
        for(i=0; i<tamServicio; i++)
        {
            printf("%d  %10s  %d\n", listaServicios[i].id, listaServicios[i].descripcion, listaServicios[i].precio);
        }

        ret = 1;
    }

    return ret;
}
int cargarServicios(eServicio* listaServicios, int tam, int id, char nombreServicio[])
{
	int ret = 0;
	int i;

	if(listaServicios != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			if(listaServicios[i].id == id)
			{
				strcpy(nombreServicio, listaServicios[i].descripcion);
				break;
			}
		}

		ret = 1;
	}

	return ret;
}

int validarEntero(int* datoValidar, int minimo, int maximo)
{
	int validacion = 0;

	fflush(stdin);
	if((scanf("%d", datoValidar)))
	{
		if(*datoValidar >= minimo && *datoValidar <= maximo)
		{
			validacion = 1;
		}
		else
		{
			do
			{
				printf("Error, ingrese un valor valido: ");
				fflush(stdin);
				if(scanf("%d", datoValidar))
				{
					if(*datoValidar >= minimo && *datoValidar <= maximo)
					{
						validacion = 1;
					}
				}
				else
				{
					validacion = 0;
				}
			}while(validacion == 0);
		}
	}
	else
	{
		do
		{
			printf("Error, ingrese un valor valido: ");
			fflush(stdin);
			if(scanf("%d", datoValidar))
			{
				if(*datoValidar >= minimo && *datoValidar <= maximo)
				{
					validacion = 1;
				}
			}
			else
			{
				validacion = 0;
			}

		}while(validacion == 0);
	}

	return validacion;
}

int validarCaracter(char* datoValidar, char primeraOpcion, char segundaOpcion)
{
	int validacion = 0;

	fflush(stdin);
	if((scanf("%c", datoValidar)))
	{
		if(*datoValidar == primeraOpcion || *datoValidar == segundaOpcion)
		{
			validacion = 1;
		}
		else
		{
			do
			{
				printf("Error, ingrese un caracter valido: ");
				fflush(stdin);
				if(scanf("%c", datoValidar))
				{
					if(*datoValidar == primeraOpcion || *datoValidar == segundaOpcion)
					{
						validacion = 1;
					}
				}
				else
				{
					validacion = 0;
				}
			}while(validacion == 0);
		}
	}
	else
	{
		do
		{
			printf("Error, ingrese un caracter valido: ");
			fflush(stdin);
			if(scanf("%c", datoValidar))
			{
				if(*datoValidar == primeraOpcion || *datoValidar == segundaOpcion)
				{
					validacion = 1;
				}
			}
			else
			{
				validacion = 0;
			}

		}while(validacion == 0);
	}

	return validacion;

}
int altaBicicleta(eBicicleta* listaBicicletas, int tam, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor, int* idSiguiente)
{
	int ret = 0;
	int index;
	int tamChar;
	int i;
	char marca[20];
	int validacionMarca = 0;
	int tipo;
	int color;
	char material;

	if(listaBicicletas != NULL && tam > 0)
	{
		index = buscarLibre(listaBicicletas, tam);

		if(index != -1)
		{
			//ID//
			printf("La bicicleta a ingresar tendra el id: %d\n", *idSiguiente);
			listaBicicletas[index].id = *idSiguiente;
			(*idSiguiente)++;

			//MARCA//
			do
			{
				printf("Ingrese marca: ");
				scanf("%s", marca);
				tamChar = strlen(marca);

				for(i=0;i<tamChar;i++)
				{
					if(!((marca[i] >= 65 && marca[i] <= 90) || (marca[i] >= 97 && marca[i] <= 122)))
					{
						printf("Error, ingrese una marca valido\n");
						validacionMarca = 0;
						break;
					}

					validacionMarca = 1;
				}
			}while(validacionMarca == 0);

			if(validacionMarca == 1)
			{
				strcpy(listaBicicletas[index].marca, marca);
			}

			//TIPO//
			listarTipos(listaTipos, tamTipo);
			printf("Ingrese el id del tipo: ");
			fflush(stdin);
			if(validarEntero(&tipo, 1000, 1003))
			{
				listaBicicletas[index].idTipo = tipo;
			}

			//COLOR//
			listarColores(listaColores, tamColor);
			printf("Ingrese el id del color: ");
			fflush(stdin);
			if(validarEntero(&color, 5000, 5004))
			{
				listaBicicletas[index].idColor = color;
			}

			//MATERIAL//
			printf("Ingrese el material: ");
			fflush(stdin);
			if(validarCaracter(&material, 'a', 'c'))
			{
				listaBicicletas[index].material = material;
			}

			listaBicicletas[index].isEmpty = OCUPADO;

			ret = 1;
		}

	}
	return ret;
}

int buscarBicicletaPorId(eBicicleta* listaBicicletas, int tam, int id)
{
	int index = -1;
	int i;

	for(i=0; i<tam; i++)
	{
		if(listaBicicletas[i].isEmpty == OCUPADO)
		{
			if(listaBicicletas[i].id == id)
			{
				index = id;
				break;
			}
		}
		else
		{
			index = -1;
		}
	}

	return index;
}

void mostrarBicicleta(eBicicleta miBicicleta, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor)
{
	char tipo[20];
	char color[20];
    cargarTipo(listaTipos,tamTipo,miBicicleta.idTipo, tipo);
    cargarColor(listaColores,tamColor,miBicicleta.idColor, color);
    printf("%d\t %s\t %s\t %s\t %c\n", miBicicleta.id, miBicicleta.marca ,tipo, color, miBicicleta.material);
}

int mostrarBicicletas(eBicicleta* listaBicicletas, int tamBici, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor)
{
	int ret = 0;
	int i;

	if(listaBicicletas != NULL && tamBici > 0)
	{
		printf("ID\t  MARCA\t TIPO\t COLOR\t MATERIAL\n");
		for(i=0;i<tamBici;i++)
		{
			if(listaBicicletas[i].isEmpty == OCUPADO)
			{
				mostrarBicicleta(listaBicicletas[i], listaTipos, tamTipo, listaColores, tamColor);
			}
		}
	}

	return ret;
}

int modificarBicicleta(eBicicleta* listaBicicletas, int tamBici, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor)
{
	int ret = 0;
	int opcion;
	int index;
	int idIngresado;
	int tipo;
	char material;

	mostrarBicicletas(listaBicicletas, tamBici, listaTipos, tamTipo, listaColores, tamColor);

	printf("Ingrese el ID que quiere modificar: ");
	fflush(stdin);
	validarEntero(&idIngresado, 1, 1000);

	index = buscarBicicletaPorId(listaBicicletas, tamBici, idIngresado);

	if(index == idIngresado)
	{
		do
		{
		system("cls");
		printf("\n************* MENU MODIFICACIONES *************\n\n");
		printf("1- MODIFICAR TIPO\n");
		printf("2- MODIFICAR MATERIAL\n");
		printf("3- SALIR\n");
		scanf("%d", &opcion);

		switch(opcion)
		{
			case 1:
				listarTipos(listaTipos, tamTipo);
				printf("Ingrese el id del nuevo tipo: ");
				fflush(stdin);
				if(validarEntero(&tipo, 1000, 1003))
				{
					printf("Tipo modificado con exito\n");
					system("pause");
					listaBicicletas[index].idTipo = tipo;
				}
			break;

			case 2:
				printf("Ingrese el nuevo material: ");
				fflush(stdin);
				if(validarCaracter(&material, 'a', 'c'))
				{
					printf("Material modificado con exito\n");
					system("pause");
					listaBicicletas[index].material = material;
				}
			break;

			case 3:
				printf("Ha salido con exito.\n");
			break;

			default:
				printf("Error, ingrese una opcion valida\n");
			break;
		}

		}while(opcion != 3);
	}
	else
	{
		printf("Error, el id ingresado no pertenece a ninguna bicicleta.\n");
		system("pause");
	}


	return ret;
}

int bajaBicicleta(eBicicleta* listaBicicletas, int tam, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor)
{
	int ret = 0;
	int idIngresado;
	int indice;

	if(listaBicicletas != NULL && tam > 0)
	{

		mostrarBicicletas(listaBicicletas, tam, listaTipos, tamTipo, listaColores, tamColor);

		printf("Ingrese el ID de la bici a dar de baja: ");
		fflush(stdin);
		if(validarEntero(&idIngresado, 1, 1000))
		{
			indice = buscarBicicletaPorId(listaBicicletas, tam, idIngresado);

			if(indice != -1)
			{
				listaBicicletas[indice].isEmpty = VACIO;
				ret = 1;
			}
			else
			{
				printf("Error, no hay ninguna bicicleta con el ID ingresado.\n");
			}
		}
	}
	return ret;
}

int inicializarTrabajos(eTrabajo* listaTrabajos, int tam)
{
    int ret = 0;
    int i;

    if(listaTrabajos != NULL && tam > 0)
    {
        for(i=0; i<tam; i++)
        {
        	listaTrabajos[i].isEmpty = VACIO;
        }
        ret = 1;
    }
    return ret;
}

int buscarTrabajoLibre(eTrabajo* listaTrabajos, int tam)
{
    int index = -1;
    int i;

    if(listaTrabajos != NULL && tam > 0)
    {
        for(i=0; i<tam; i++)
        {
            if(listaTrabajos[i].isEmpty == VACIO)
            {
            	index = i;
                break;
            }
        }
    }
    return index;
}

int altaTrabajo(eTrabajo* listaTrabajos, int tamTrabajo, eBicicleta* listaBicicletas, int tamBici, eServicio* listaServicios, int tamServicio, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor, int* idSiguiente)
{
	int ret = 0;
	int indexTrabajo;
	int idBicicleta;
	int idServicio;
	int indexBici;

	if(listaTrabajos != NULL && tamTrabajo > 0)
	{
		indexTrabajo = buscarTrabajoLibre(listaTrabajos, tamTrabajo);

		if(indexTrabajo != -1)
		{
			printf("El trabajo a ingresar tendra el id: %d\n", *idSiguiente);
			listaTrabajos[indexTrabajo].id = *idSiguiente;
			(*idSiguiente)++;

			mostrarBicicletas(listaBicicletas, tamBici, listaTipos, tamTipo, listaColores, tamColor);

			printf("Ingrese el ID de la bicicleta: ");
			fflush(stdin);
			validarEntero(&idBicicleta, 1, 1000);

			indexBici = buscarBicicletaPorId(listaBicicletas, tamBici, idBicicleta);

			if(indexBici == idBicicleta)
			{
				listarServicios(listaServicios, tamServicio);

				printf("Ingrese el ID del servicio: ");
				fflush(stdin);
				validarEntero(&idServicio, 20000, 20003);

				ret = 1;
			}
			else
			{
				printf("No hay ninguna bicicleta con el id ingresado.\n");
				system("pause");
			}
		}
		else
		{
			printf("Lista de trabajos llena.\n");
			system("pause");
		}
	}


	return ret;
}

void mostrarTrabajo(eTrabajo miTrabajo, eBicicleta* listaBicicletas, int tamBici, eServicio* listaServicios, int tamServicio, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor)
{
	char servicio[20];
    cargarServicio(listaColores,tamColor,miTrabajo.idServicio, servicio);
    mostrarBicicleta(listaBicicletas, listaTipos, tamTipo, listaColores, tamColor);
    printf("%d\t %s\n", miTrabajo.id, servicio);
}
int mostrarTrabajos(eTrabajo* listaTrabajos, int tamTrabajo, eBicicleta* listaBicicletas, int tamBici, eServicio* listaServicios, int tamServicio, eTipo* listaTipos, int tamTipo, eColor* listaColores, int tamColor)
{
	int ret = 0;
	int i;

	if(listaTrabajos != NULL && tamBici > 0)
	{
		printf("ID\t  MARCA\t TIPO\t COLOR\t MATERIAL\n");
		for(i=0;i<tamBici;i++)
		{
			if(listaTrabajos[i].isEmpty == OCUPADO)
			{
				mostrarTrabajo(listaTrabajos[i], listaTipos, tamTipo, listaColores, tamColor);
			}
		}
	}

	return ret;
}
