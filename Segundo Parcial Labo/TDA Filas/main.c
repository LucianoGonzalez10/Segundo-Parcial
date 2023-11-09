#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nodo
{
    int dato;
    struct nodo * siguiente;
    struct nodo * anterior;
} nodo;

typedef struct
{
    struct nodo * cabecera;
    struct nodo * cola;
} fila;

nodo * borrarPrimero(nodo * lista);
nodo * agregarFinal(nodo * lista, nodo * nuevo);
nodo * buscarUltimo(nodo * lista);

int main()
{
    fila * fila = inicfila();
    agregar(&fila);
    return 0;
}

nodo * iniclista()
{
    return NULL;
}

void inicfila(fila * fila)
{
    fila->cabecera = iniclista();
    fila->cola = iniclista();
}

nodo * crearNodo(int dato)
{
    nodo * aux = (nodo*) malloc(sizeof(nodo));
    aux->dato = dato;
    aux->siguiente = NULL;
    aux->anterior = NULL;
    return aux;
}

void agregar(fila * fila, int dato)
{
    nodo * nuevo = crearNodo(dato);
    if(fila->cabecera == NULL)
    {
        fila->cabecera = nuevo;
        fila->cola = nuevo;
    }
    else
    {
        fila->cabecera = agregarFinal(fila->cabecera, nuevo);
        fila->cola = nuevo;
    }
}

int extraer(fila * fila)
{
    int resp;
    if(fila->cabecera != NULL)
    {
        resp = verPrimero(fila->cabecera);
        fila->cabecera = borrarPrimero(fila->cabecera);
        if(fila->cabecera == NULL)
        {
            fila->cola = iniclista();
        }
    }
    return resp;
}

int verPrimero(nodo * lista){
    int rta = 0;
    if(lista){
        rta = lista->dato;
    }
    return rta;
}

nodo * borrarPrimero(nodo * lista){
    nodo * aborrar = lista;
    if(lista != NULL){
        lista = lista->siguiente;
        if(lista != NULL){
            lista->anterior = NULL;
        }
        free(aborrar);
    }
    return lista;
}

nodo * agregarFinal(nodo * lista, nodo * nuevo){
    if(lista == NULL){
        lista = nuevo;
    }
    else{
        nodo * ultimo = buscarUltimo(lista);
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
    }
    return lista;
}

nodo * buscarUltimo(nodo * lista){
nodo * aux = lista;
if(aux != NULL){
    while(aux->siguiente != NULL){
        aux = aux->siguiente;
    }
    return aux;
}
}
