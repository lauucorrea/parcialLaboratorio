/*
 * plasticos.h
 *
 *  Created on: 12 Oct 2021
 *      Author: Lauta
 */

#ifndef PLASTICOS_H_
#define PLASTICOS_H_
#define EMPTY 0
#define FILLED 1
#define MODIFIED -1
#define TAM 200
#define TAM2 400
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	int idPedido;
	float altaDensidad;
	float bajaDensidad;
	float polipropileno;
	float basura;
}ePlasticos;

ePlasticos listaPlasticos[TAM2];
void InicializarListaPlasticos(ePlasticos listaPlasticos[], int tam);
void AdministrarPlasticos(ePlasticos listaPlasticos[], float kgPedido,int index, int* pValidacion);
void MostrarPlasticos(ePlasticos lista[], int index);
void CalcularPropilenoPromedio(ePlasticos listaPlasticos[], int totalClientes, int tam);
#endif /* PLASTICOS_H_ */
