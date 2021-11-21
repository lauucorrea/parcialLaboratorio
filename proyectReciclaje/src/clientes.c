/*
 * clientes.c
 *
 *  Created on: 8 Oct 2021
 *      Author: Lauta
 */

#include "clientes.h"
#include "funciones.h"
void InicializarListaClientes(eCliente listaClientes[], int tam){
	for(int i = 0;i < tam; i++)
	{
	listaClientes[i].isEmpty = EMPTY;
	}
}
//estadoIngreso =
// 1 Ingresado correctamente
// 0 No se Ingreso en ningun momento
//-1 si hubo algun error (a implementar)

eCliente IngresarUnCliente(eCliente lista[],int idCliente,int* validacion){
	eCliente cliente;
	int validacionCuit;
	int validacionDireccion;
	int validacionEmpresa;
	int validacionLocalidad;

	cliente.idCliente = idCliente;
	getString(cliente.empresa,"Ingresar nombre de la empresa\n",50, &validacionEmpresa);
	cliente.cuit = IngresarEntero("Ingresa tu numero de cuit\n",999999999, &validacionCuit);
	getString(cliente.direccion,"Ingresar la direccion de su domicilio\n",50, &validacionDireccion);
	getString(cliente.localidad,"Ingresar la localidad de su domicilio\n",50, &validacionLocalidad);

	if(validacionEmpresa == 0 && validacionDireccion == 0 && validacionCuit == 0 && validacionLocalidad == 0){
		cliente.isEmpty = 1;
		*validacion = 0;
	}else{
		cliente.isEmpty = 0;
		*validacion = -1;
	}
	return cliente;
}
void BorrarCliente(eCliente lista[], int tam, int *pValidacion)
{
  int i;
  int validacion;
  int idABM;
  char respuesta;
  MostrarListadoClientes(lista, tam);
  idABM = IngresarEntero("Ingrese el id del cliente a eliminar\n", 400, &validacion);
  if(validacion == 0){
	  for (i = 0; i < tam; i++)
	  {
		  if (lista[i].isEmpty != 0 && lista[i].idCliente == idABM)
		  {
			  do{
				  printf("Esta seguro que desea eliminar a %s?\n", lista[i].empresa);
				  fflush(stdin);
				  scanf("%c", &respuesta);
				  validacion = ValidarString(respuesta);

			  }while(validacion != 0 || (respuesta != 'n' && respuesta != 's'));

			  if(respuesta == 's'){
				  lista[i].isEmpty = 0;
				  *pValidacion = 0;
				  break;
			  }else{
				  *pValidacion = -1;
				  break;
			  }
		  }
	  }
  }
}


void MostrarListadoClientes(eCliente lista[], int tam)
{
	int flagListaVacia = 0;
	for (int i = 0; i < tam; i++)
	{
		if(lista[i].isEmpty == FILLED){
			MostrarCliente(lista[i],0);
			flagListaVacia = 1;
		}else{
			if(flagListaVacia == 0){
				puts("Listado de clientes vacia.\n");
				flagListaVacia = 1;
			}

		}
	}
}

/*int GestionarCambiosCliente(eCliente lista[],int indexCliente, int IdAbm){
	char nombreDireccion[50];
	char nombreLocalidad[50];
	if(lista[indexCliente].idCliente == IdAbm && lista[indexCliente].isEmpty != 0){
		puts("-------------------------------------------");
		 printf("Cliente encontrado. El id correspondiente es: %d\n", lista[indexCliente].idCliente);
		 puts("-------------------------------------------");
		 getString(nombreDireccion, "Ingrese la nueva direccion del cliente\n", 50);
		 puts("-------------------------------------------");
		 getString(nombreLocalidad, "Ingrese la nueva localidad del cliente\n", 50);
		 lista[indexCliente].isEmpty = 1;
		 CargarCambios(nombreDireccion, nombreLocalidad, lista, indexCliente);
		return 1;
	}else{
		return 0;
	}
}*/
void OrdenarListaClientesPorId (eCliente lista[], int tam)
{
  eCliente auxiliarProducto;
  for (int i = 0; i < tam - 1; i++)
    {
      for (int j = i + 1; j < tam; j++)
	{
	  if (lista[i].idCliente < lista[j].idCliente)
	    {
	      auxiliarProducto = lista[i];
	      lista[i] = lista[j];
	      lista[j] = auxiliarProducto;
	    }
	}
      lista[i].idCliente = 200+i;
    }

}

void MostrarCliente(eCliente unCliente, int cantidadPedidos)
{
	puts("CLIENTE:");
	if(cantidadPedidos != 0){
		printf ("Id\tEmpresa\t\tCuit\tDireccion\tLocalidad\tPedidos\n");
		printf("%d %10s %16d %8s %15s %10d\n", unCliente.idCliente, unCliente.empresa,
		unCliente.cuit, unCliente.direccion, unCliente.localidad, cantidadPedidos);
	}else{
		printf ("Id\tEmpresa Cuit\tDireccion\tLocalidad\n");
		printf("%d %10s %10d %6s %15s\n", unCliente.idCliente, unCliente.empresa,
		unCliente.cuit, unCliente.direccion, unCliente.localidad);
	}

}
void CargarCambios(char direccion[],char localidad[], eCliente listaClientes[],int posicion){
	for(int i=0; i<=strlen(direccion); i++){
		listaClientes[posicion].direccion[i] = direccion[i];
	}
	for(int j=0;j <=strlen(localidad); j++){
		listaClientes[posicion].localidad[j] = localidad[j];
	}
}


int CompararIdCliente(int idCliente, int IdPedido){
	if(idCliente == IdPedido){
		return 0;
	}else{
		return -1;
	}
}

