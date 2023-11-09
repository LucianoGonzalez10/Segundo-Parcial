#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

nodoArbol * inicarbol();
nodoArbol * crearNodo(int dato);
nodoArbol * insertar(nodoArbol * arbol, int dato);
nodoArbol * cargarDatos(nodoArbol * arbol);


int main()
{
    nodoArbol * arbol = inicarbol();
    arbol = cargarDatos(arbol);
    printf("PREORDEN: \n");
    preOrden(arbol);
    printf("\n----------------\n \n");
    printf("INORDEN: \n");
    inorden(arbol);
    printf("\n-----------------\n \n");
    printf("POSORDEN: \n");
    posOrden(arbol);
    return 0;
}

nodoArbol * inicarbol()
{
    return NULL;
}

nodoArbol * crearNodo(int dato)
{
    nodoArbol * nuevo = (nodoArbol*) malloc(sizeof(nodoArbol));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

nodoArbol * insertar(nodoArbol * arbol, int dato)
{
    if(arbol == NULL)
    {
        arbol = crearNodo(dato);
    }
    else
    {
        if(dato > arbol->dato)
        {
            arbol->der = insertar(arbol->der, dato);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, dato);
        }
    }
    return arbol;
}

nodoArbol * cargarDatos(nodoArbol * arbol)
{
    int dato = 0;
    char control = 's';
    while(control == 's')
    {
        printf("Dime el dato a ingresar: \n");
        scanf("%d", &dato);

        arbol = insertar(arbol, dato);
        printf("Desea seguir cargando datos? \n");
        fflush(stdin);
        scanf("%c", &control);
    }

    return arbol;
}

void preOrden(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        printf("- %i -  ", arbol->dato);
        preOrden(arbol->der);
        preOrden(arbol->izq);
    }

}


void inorden(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        preOrden(arbol->der);
        printf("- %i -  ", arbol->dato);
        preOrden(arbol->izq);
    }

}


void posOrden(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        preOrden(arbol->der);
        preOrden(arbol->izq);
        printf("- %i -  ", arbol->dato);
    }

}
