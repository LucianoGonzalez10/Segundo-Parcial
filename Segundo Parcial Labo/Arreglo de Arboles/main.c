#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
} stRegistroDisfraz;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
} stSucursal;

typedef struct
{
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
} Disfraz;

typedef struct nodoArbolSub
{
    Disfraz datito;
    struct nodoArbolSub * izq;
    struct nodoArbolSub * der;
} nodoArbolSub;

typedef struct nodoPrincipal
{
    stSucursal dato;
    struct nodoArbolSub * arbol;
    struct nodoPrincipal * siguiente;
} nodoPrincipal;

nodoPrincipal * iniclista();
nodoArbolSub * inicarbol();
nodoPrincipal * crearNodo(stSucursal dato);
nodoArbolSub * crearArbol(Disfraz datito);
nodoPrincipal * cargarDatos(nodoPrincipal * lista, char nombreAr[]);
nodoPrincipal * buscarSucursal(nodoPrincipal * lista, int dato);
nodoPrincipal * agregarPrincipio(nodoPrincipal * lista, nodoPrincipal * nuevo);
nodoArbolSub * insertar(nodoArbolSub * arbol, Disfraz datito);
nodoPrincipal * alta(nodoPrincipal * lista, stSucursal dato, Disfraz datito);

int main()
{
    char nombreAr[] = "archivoDisfraces.bin";
    nodoPrincipal * lista = iniclista();
    lista = cargarDatos(lista, nombreAr);
    mostrarLista(lista);

    int stock = 0;
    char genero[20];
    printf("Dime el genero a contar el stock. \n");
    fflush(stdin);
    scanf("%s", &genero);
    stock = contarStock(genero, lista);
    printf("La cantidad de stock de %s es %d", genero, stock);

    return 0;
}

nodoPrincipal * iniclista()
{
    return NULL;
}

nodoArbolSub * inicarbol()
{
    return NULL;
}

nodoPrincipal * crearNodo(stSucursal dato)
{
    nodoPrincipal * aux = (nodoPrincipal*) malloc(sizeof(nodoPrincipal));
    aux->arbol = inicarbol();
    aux->siguiente = NULL;
    aux->dato = dato;

    return aux;
}

nodoArbolSub * crearArbol(Disfraz datito)
{
    nodoArbolSub * arbol = (nodoArbolSub*) malloc(sizeof(nodoArbolSub));
    arbol->izq = NULL;
    arbol->der = NULL;
    arbol->datito = datito;

    return arbol;
}

nodoPrincipal * cargarDatos(nodoPrincipal * lista, char nombreAr[])
{
    stRegistroDisfraz registro;
    stSucursal dato;
    Disfraz datito;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&registro, sizeof(stRegistroDisfraz),1, buffer) > 0)
        {
            dato.idSucursal = registro.idSucursal;
            strcpy(dato.nombreSucursal, registro.nombreSucursal);

            datito.stockDisfraz = registro.stockDisfraz;
            strcpy(datito.generoDisfraz, registro.generoDisfraz);
            strcpy(datito.nombreDisfraz, registro.nombreDisfraz);
            lista = alta(lista, dato, datito);
        }
        fclose(buffer);
    }
    return lista;
}

nodoPrincipal * alta(nodoPrincipal * lista, stSucursal dato, Disfraz datito)
{
    nodoPrincipal * buscado = buscarSucursal(lista, dato.idSucursal);
    if(buscado == NULL)
    {
        nodoPrincipal * nuevo = crearNodo(dato);
        lista = agregarPrincipio(lista, nuevo);
        buscado = lista;
    }
    buscado->arbol = insertar(buscado->arbol, datito);

    return lista;
}

nodoPrincipal * buscarSucursal(nodoPrincipal * lista, int dato)
{
    nodoPrincipal * aux = lista;
    nodoPrincipal * buscado = NULL;
    if(aux!= NULL)
    {
        while(aux != NULL)
        {
            if(aux->dato.idSucursal == dato)
            {
                buscado = aux;
            }
            aux = aux->siguiente;
        }
    }
    return buscado;
}

nodoPrincipal * agregarPrincipio(nodoPrincipal * lista, nodoPrincipal * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}

nodoArbolSub * insertar(nodoArbolSub * arbol, Disfraz datito)
{
    if(arbol == NULL)
    {
        arbol = crearArbol(datito);
    }
    else
    {
        if(datito.stockDisfraz > arbol->datito.stockDisfraz)
        {
            arbol->der = insertar(arbol->der, datito);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, datito);
        }
    }
    return arbol;
}

void inorder(nodoArbolSub * arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->der);
        printf("Nombre Disfraz: %s \n",arbol->datito.nombreDisfraz);
        printf("Genero del Disfraz: %s \n", arbol->datito.generoDisfraz);
        printf("Stock Disfraz: %d \n \n", arbol->datito.stockDisfraz);
        inorder(arbol->izq);
    }
}

void mostrarLista(nodoPrincipal * lista)
{
    if(lista != NULL)
    {
        while(lista != NULL)
        {
            printf("---------------------------------------------\n");
            printf("Nombre Sucursal: %s \n", lista->dato.nombreSucursal);
            printf("ID Sucursal: %d \n", lista->dato.idSucursal);
            inorder(lista->arbol);
            lista = lista->siguiente;
        }
    }
}

int stockGenero(char genero[], nodoArbolSub * arbol)
{
    int stock = 0;
    if(arbol != NULL)
    {
        if(strcmpi(arbol->datito.generoDisfraz, genero) != 0)
        {
            stock = stockGenero(arbol->der, genero) + stockGenero(arbol->izq, genero);
        }
        else
        {
            stock = arbol->datito.stockDisfraz + stockGenero(arbol->der, genero) + stockGenero(arbol->izq, genero);
        }
    }
    return stock;
}

int contarStock(char genero[], nodoPrincipal * lista){
    int stock = 0;
    if(lista != NULL){
        while(lista != NULL){
            stock = stockGenero(genero, lista->arbol);
        }
    }
    return stock;
}

