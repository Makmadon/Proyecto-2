#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef _LIBRERIA
#define _LIBRERIA
typedef struct nodo{
    int elemento;
    struct nodo *AA;
}Nodo;

typedef struct lista
{
    Nodo *primer,*ultimo;
}Lista;

Nodo *XOR(Nodo *a, Nodo *b);

Lista *crearLista();

void inicializar(Lista *list);

Nodo *crearNodo(int val);

bool esVacia(Lista *list);

bool insertarPrincipio(Lista *list, int val);

bool insertarFinal(Lista *list,int val);

bool insertarOrden(Lista *list,int val);

bool buscar(Lista *list, int val);

bool sacarPrincipio(Lista *list, int *val);

bool sacarFinal(Lista *list, int *val);

bool sacarPrimeraOcurrencia(Lista *list, int val);

void listarInicioAFinal(Lista *list);

void listarFinalAInicio(Lista *list);

int cantidadElementos(Lista *list);


#include "Xor.c"
#endif