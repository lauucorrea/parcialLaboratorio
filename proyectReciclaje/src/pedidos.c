#include "pedidos.h"
#include "clientes.h"
/*
 * typedef struct{
	int idCliente;
	int idPedido;
	int kgCargamento;
	int estadoPedido;

}ePedido;
 */
//0 vacio
//1 cargado
//-1 pedido completado
ePedido IngresarUnPedido(ePedido lista[],int idPedido,int idCliente,float kgCargamento,int estadoPedido, int validacionId, int validacionKg, int* pValidacion){
	ePedido pedido;
	pedido.idCliente = idCliente;
	pedido.idPedido = idPedido;
	pedido.kgCargamento = kgCargamento;

	if(validacionId == 0 && validacionKg == 0){
		pedido.estadoPedido = 1;
		*pValidacion = 0;
	}else{
		pedido.estadoPedido = 0;
		*pValidacion = -1;
	}


	return pedido;
}

void InicializarListaPedidos(ePedido listaPedidos[], int tam){
	for(int i = 0;i < tam; i++)
	{
      listaPedidos[i].estadoPedido = 0;
    }
}

void MostrarPedido(ePedido unPedido){
	puts("PEDIDO:");
	puts("-------------------------------------------");
	printf ("Id Cliente\tId Pedido\tKg Cargamento\n");
	printf("%d %15d %20.2f\n", unPedido.idCliente, unPedido.idPedido,unPedido.kgCargamento);
}

int MostrarListadoPedidos(ePedido lista[], int tam)
{
	int flagListaVacia = -1;
	for (int i = 0; i < tam; i++)
	{
		if(lista[i].estadoPedido == FILLED){
			MostrarPedido(lista[i]);
			flagListaVacia = 0;
		}

	}
	return flagListaVacia;
}
//busca el estadoABuscar en el estado del pedido. devuelve 0 si se encontro, y devuelve -1 si no se encontro en el cliente
void BuscarEstadoPedido(int indicePedidos, int indiceClientes, int estadoABuscar, int* pValidacion){
	if(listaPedidos[indicePedidos].estadoPedido == estadoABuscar && listaClientes[indiceClientes].idCliente == listaPedidos[indicePedidos].idCliente){
		*pValidacion = 0;
	}else{
		*pValidacion = -1;
	}
}
