/*
 ============================================================================
 Name        : proyectReciclaje.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "clientes.h"
#include "pedidos.h"
#include "plasticos.h"
#include "funciones.h"
#define TAM 200
#define TAM2 400

int main(void) {
	setbuf(stdout, NULL);
	int pValidaciones = 1; // 0 sin errores / vacio
						   // 1 cargado / procesado
						   // -1 error
	int validacionIdABM = 1;
	int validacionLocalidadABM = 1;
	int validacionDireccionABM = 1;
	int validacionKgIngresados = 1;
	int isListadoVacio;

	int opcion = 0;
	int flagCiclo = 1;
	int idCliente = 200;
	int idPedidos = 400;
	int cantidadDeClientes = 0;

	float kgIngresados;
	float totalKgPedidos = 0;

	int cantidadPedidosPendientes = 0;
	int idABM;

	int estadoComparacion;
	int estadoProceso;

	char direccionABM[50];
	char localidadABM[50];
	char busquedaLocalidad[50];

	do{
		MostrarMenu();
		puts("-------------------------------------------");
		opcion = IngresarEntero("Elija una opcion\n",10, &pValidaciones);
		if(pValidaciones != 0){
			break;
		}
		if(flagCiclo ==1){
			InicializarListaPedidos(listaPedidos,TAM2);
			InicializarListaClientes(listaClientes, TAM);
			InicializarListaPlasticos(listaPlasticos, TAM2);
			pValidaciones = 1;
			estadoComparacion = -1;
			flagCiclo = 0;
		}



	switch(opcion){
		case 1:
			for(int i = 0; i<sizeof(listaClientes);i++){
				if(listaClientes[i].isEmpty ==0){
					idCliente ++;
					listaClientes[i] = IngresarUnCliente(listaClientes, idCliente,&pValidaciones);

					if(pValidaciones != 0){
						listaClientes[i].isEmpty = 0;
						idCliente--;
					}
					break;
				}
			}

			if(pValidaciones == 0){
				puts("-------------------------------------------");
				printf("Ingresado correctamente. El id del cliente es %d\n", idCliente);
				cantidadDeClientes++;
			}else{
				puts("-------------------------------------------");
				puts("El cliente no se pudo ingresar. Intentelo nuevamente");
			}
			pValidaciones = 1;
		break;
		case 2:
			puts("-------------------------------------------");
			MostrarListadoClientes(listaClientes, TAM);
			idABM = IngresarEntero("Ingrese el id del cliente a modificar\n", 400, &validacionIdABM);
			for(int i=0; i<sizeof(listaClientes);i++){
				if(listaClientes[i].idCliente == idABM && listaClientes[i].isEmpty != 0 && validacionIdABM == 0){
					puts("-------------------------------------------");
					printf("Cliente encontrado. El id correspondiente es: %d\n", listaClientes[i].idCliente);
					puts("-------------------------------------------");
					getString(direccionABM, "Ingrese la nueva direccion del cliente\n", 50, &validacionDireccionABM);
					puts("-------------------------------------------");
					getString(localidadABM, "Ingrese la nueva localidad del cliente\n", 50, &validacionLocalidadABM);

					if(validacionDireccionABM == 0 && validacionLocalidadABM == 0 && validacionIdABM == 0){
						CargarCambios(direccionABM,localidadABM, listaClientes, i);
						pValidaciones = 0;
						listaClientes[i].isEmpty = 1;
					}
				break;
				}else{
					pValidaciones = -1;
				}
			}

			if(pValidaciones == 0){
				puts("-------------------------------------------");
					puts("El usuario se modifico correctamente");
				}else{
					puts("-------------------------------------------");
					puts("No encontramos el id del usuario que ingreso");
				}
			pValidaciones = 0;
			validacionDireccionABM = 1;
			validacionLocalidadABM = 1;
			validacionIdABM = 1;
		break;
		case 3:
			puts("-------------------------------------------");
			MostrarListadoClientes(listaClientes, TAM);
			puts("-------------------------------------------");
			idABM = IngresarEntero("Ingrese el id del usuario a eliminar\n",400, &validacionIdABM);
			for(int i=0; i<sizeof(listaClientes);i++){
				if(listaClientes[i].idCliente == idABM && listaClientes[i].isEmpty != 0 && validacionIdABM == 0){
					listaClientes[i].isEmpty = -1;
					OrdenarListaClientesPorId(listaClientes, TAM);
					puts("-------------------------------------------");
					puts("Lista de clientes actualizada:");
					MostrarListadoClientes(listaClientes, TAM);
					pValidaciones = 0;
					break;
				}
			}
			//BorrarCliente(listaClientes, TAM, &pValidaciones);
			if(pValidaciones == 0){
				puts("-------------------------------------------");
				puts("El usuario se elimino correctamente\n");
			}else{
				puts("-------------------------------------------");
				puts("No encontramos el id del usuario que ingreso");
			}
			pValidaciones = 1;
			validacionIdABM = 1;
		break;
		case 4:
			/*
			 * typedef struct{
				int idCliente;
				int idPedido;
				int kgCargamento;
				int estadoPedido;

			}ePedido;
			 */

			MostrarListadoClientes(listaClientes, TAM);
			puts("-------------------------------------------");
			idABM = IngresarEntero("Ingrese el id del usuario a cargar el pedido \n",400, &validacionIdABM);
			puts("-------------------------------------------");
			kgIngresados = IngresarEntero("Ingrese la cantidad de kg a transportar\n",9999, &validacionKgIngresados);
			for(int i=0; i<TAM; i++){
				MostrarCliente(listaClientes[i],0);
				for(int j=0; j<TAM2; j++){
					if(validacionIdABM == 0 && validacionKgIngresados == 0){
						if(listaPedidos[j].estadoPedido != 1 && listaClientes[i].idCliente==idABM){
							idPedidos ++;
							listaPedidos[j] =IngresarUnPedido(listaPedidos, idPedidos, idABM, kgIngresados,1, validacionIdABM, validacionKgIngresados, &pValidaciones);
							break;
						}
					}

				}
				if(pValidaciones == 0){
					puts("-------------------------------------------");
					printf("Ingresado correctamente. El pesaje del pedido del cliente es de %.2f\n", kgIngresados);
					totalKgPedidos += kgIngresados;
					break;
				}
			}
			if(pValidaciones != 0){
				puts("-------------------------------------------");
				puts("No se encontro un cliente con el id ingresado\n");
			}
			pValidaciones = 0;

		break;
		case 5:
			isListadoVacio = MostrarListadoPedidos(listaPedidos, TAM2);
			idABM = IngresarEntero("Ingrese el id del pedido a procesar\n", 800, &validacionIdABM);
			if(validacionIdABM == 0 && isListadoVacio != -1){
				for(int i=0; i < TAM; i++){
					for(int j=0; j<TAM2; j++){

						BuscarEstadoPedido(j, i, 1, &estadoProceso);
						estadoComparacion = CompararIdCliente(listaClientes[i].idCliente, listaPedidos[i].idCliente);
						if(estadoComparacion == 0 && estadoProceso == 0 && listaPedidos[j].idPedido == idABM){

							listaPlasticos[j].idPedido = listaPedidos[i].idPedido;

							MostrarPedido(listaPedidos[j]);

							puts("-------------------------------------------");
							printf("El cuit del cliente es: %d\n", listaClientes[i].cuit);
							printf("La direccion del cliente es: %s\n", listaClientes[i].direccion);
							puts("Estado del pedido: PENDIENTE\n");

							AdministrarPlasticos(listaPlasticos, listaPedidos[j].kgCargamento, j, &pValidaciones);

							if(pValidaciones == 0){
								listaPedidos[j].estadoPedido = -1;
								MostrarPlasticos(listaPlasticos, j);
								estadoProceso = 0;
								puts("-------------------------------------------");
								puts("Pedido procesado exitosamente");
								break;
							}
						}
					}
				}
			}
			if(pValidaciones != 0 ){
				puts("-------------------------------------------");
				puts("No se encontraron pedidos pendientes\n");
				estadoProceso = 0;
			}
			pValidaciones = -1;

		break;
		case 6:
			isListadoVacio = MostrarListadoPedidos(listaPedidos, TAM2);
			if(isListadoVacio != -1){
				for(int i=0; i < TAM; i++){
					for(int j=0; j<TAM2; j++){
						estadoComparacion = CompararIdCliente(listaClientes[i].idCliente, listaPedidos[j].idCliente);
						if(listaPedidos[j].estadoPedido == 1 && estadoComparacion != -1 ){
							cantidadPedidosPendientes++;
						}
					}
					if(cantidadPedidosPendientes > 0  && listaClientes[i].isEmpty != 0){
						puts("-------------------------------------------");
						MostrarCliente(listaClientes[i], cantidadPedidosPendientes);
						cantidadPedidosPendientes = 0;

					}else if(listaClientes[i].isEmpty != 0){
						puts("-------------------------------------------");
						MostrarCliente(listaClientes[i],0);
						puts("-------------------------------------------");
						puts("no se encontraron pedidos pendientes para este cliente\n");

					}
				}
			}else{
				puts("Listado de pedidos vacio\n");
			}
			estadoComparacion = -1;
		break;
		case 7:
			for(int i=0; i < TAM; i++){
				for(int j=0; j<TAM2; j++){
					BuscarEstadoPedido(j, i, 1,&pValidaciones);
				}
			}
		if(pValidaciones != 0){
			puts("-------------------------------------------");
			puts("No se encontraron pedidos pendientes\n");
			estadoProceso = 0;
		}

		break;
		case 8:
			for(int i=0; i<TAM;i++){
				for(int j=0; j<TAM2; j++){
					BuscarEstadoPedido(j, i, -1, &pValidaciones);
				}
			}
			if(pValidaciones != 0){
				puts("-------------------------------------------");
				puts("No se encontraron pedidos completados\n");
				pValidaciones = 0;
			}
		break;
		case 9:
			puts("-------------------------------------------");
			getString(busquedaLocalidad, "Ingrese una localidad a buscar\n", 50, &pValidaciones);
				for(int i=0; i < TAM; i++){
					estadoComparacion = strcmp(busquedaLocalidad, listaClientes[i].localidad);

					if((estadoComparacion != 0 && pValidaciones != 0) && listaClientes[i].isEmpty == 0 ){
						continue;
					}
					for(int j=0; j<TAM2; j++){
						if(listaPedidos[j].estadoPedido == 1  && listaClientes[i].idCliente == listaPedidos[j].idCliente){
							puts("-------------------------------------------");
							MostrarPedido(listaPedidos[j]);
							cantidadPedidosPendientes++;
						}
					}
				}

			if(cantidadPedidosPendientes != 0){
				puts("-------------------------------------------");
				printf("La cantidad de pedidos pendientes para %s es de %d\n", busquedaLocalidad, cantidadPedidosPendientes);
				cantidadPedidosPendientes = 0;
				pValidaciones = 1;
			}else{
				puts("-------------------------------------------");
				puts("No se encontraron pedidos para esta localidad\n");
				pValidaciones = 1;
			}

			estadoComparacion = -1;
		break;
		case 10:
			CalcularPropilenoPromedio(listaPlasticos, cantidadDeClientes,TAM2);
		break;

		}
	}while(opcion > 0 && opcion < 11);
	puts("Gracias por utilizar nuestro sistema");
}
