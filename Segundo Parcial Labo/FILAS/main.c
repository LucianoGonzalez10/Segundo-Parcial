#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    struct nodo * cabecera;
    struct nodo * cola;
} fila;

typedef struct
{
    int dato;
    struct nodo * sig;
    struct nodo * ante;
} nodo;

nodo * iniclista();
void inicfila(fila * fila);
nodo * crearNodo(int dato);
void agregar(fila * fila, int dato);
nodo * agregarAlFinal(nodo * lista, nodo * nuevo);
nodo * buscarUltimo(nodo * lista);
nodo * borrarPrime(nodo * lista);

int main()
{
    fila * fila;
    inicfila(&fila);
    for(int i = 0; i<10; i++)
    {
        agregar(&fila, i);
    }
   int resp = extraer(fila);
   printf("Nodo Extraido: %d", resp);

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
    aux->sig = NULL;
    aux->ante = NULL;
    return aux;
}

void agregar(fila * fila, int dato)
{
    nodo* nuevo = crearNodo(dato);
    fila->cola=agregarAlFinal(fila->cola, nuevo);
    if(fila->cabecera == NULL){
        fila->cabecera = fila->cola;
    }
    fila->cola = nuevo;
}

nodo * agregarAlFinal(nodo * lista, nodo * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nodo * ultimo = buscarUltimo(lista);
        ultimo->sig = nuevo;
        nuevo->ante = ultimo;
    }
    return lista;
}

nodo * buscarUltimo(nodo * lista)
{
    nodo * seg = lista;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

int extraer(fila * fila)
{
    int resp = -1;
    if(fila->cabecera != NULL)
    {
        resp = verPrimero(fila->cabecera);
        fila->cabecera = borrarPrime(fila->cabecera);
        if(fila->cabecera==NULL)
        {
            fila->cola = iniclista();
        }
    }
    return resp;
}

int verPrimero(nodo * lista)
{
    int rta = 0;
    if(lista)
    {
        rta = lista->dato;
    }
    return rta;
}

nodo * borrarPrime(nodo * lista)
{
    nodo * borrar = lista;
    if(lista != NULL)
    {
        lista = lista->sig;
        if(lista != NULL)
        {
            lista->ante = NULL;
            free(borrar);
        }
    }
    return lista;
}
