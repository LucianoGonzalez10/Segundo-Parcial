#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char animal[30];
    int cant;
    int habitat;
    int idEspecie;
    char especie[20];
} registroArchivo;

typedef struct
{
    char nombreAnimal[30];
    int cantidad;
    int habitat;
} animal;

typedef struct
{
    int idEspecie;
    char especie[20];
} especie;
typedef struct nodoSecundario
{
    animal dato;
    struct nodoSecundario * siguiente;
} nodoSecundario;

typedef struct nodoPrincipal
{
    especie datito;
    nodoSecundario * nodoSec;
    struct nodoPrincipal * siguiente;
} nodoPrincipal;

nodoPrincipal * iniclista();
nodoSecundario * iniclista2();
nodoPrincipal * crearNodo(especie datito);
nodoSecundario * crearNodo2(animal dato);
nodoPrincipal * agregarPrincipio(nodoPrincipal * nodoPri, nodoPrincipal * nuevo);
nodoSecundario * agregarPrincipio2(nodoSecundario * nodoSec, nodoSecundario * nuevo);
nodoPrincipal * cargarDatos(nodoPrincipal * nodoPri, char nombreAr[]);
nodoPrincipal * alta(nodoPrincipal * nodoPri, animal dato, especie datito);
nodoPrincipal * buscarEspecie(nodoPrincipal * nodoPri, int dato);
nodoPrincipal * buscarUltimo(nodoPrincipal * nodoPri);
nodoPrincipal * agregarFinal(nodoPrincipal * nodoPri, nodoPrincipal * nuevo);
nodoSecundario * buscarUltimo2(nodoSecundario * nodoPri);
nodoSecundario * agregarFinal2(nodoSecundario * nodoPri, nodoSecundario * nuevo);

int main()
{
    char nombreAr[] = "animales.dat";
    nodoPrincipal * lista = iniclista();
    lista = cargarDatos(lista, nombreAr);
    mostrarLista(lista);

    return 0;
}

nodoPrincipal * iniclista()
{
    return NULL;
}
nodoSecundario * iniclista2()
{
    return NULL;
}

nodoPrincipal * crearNodo(especie datito)
{
    nodoPrincipal * nuevo = (nodoPrincipal*) malloc(sizeof(nodoPrincipal));
    nuevo->datito = datito;
    nuevo->siguiente = NULL;
    nuevo->nodoSec = iniclista2();

    return nuevo;
}

nodoSecundario * crearNodo2(animal dato)
{
    nodoSecundario * nuevo = (nodoSecundario*) malloc(sizeof(nodoSecundario));
    nuevo->dato = dato;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoPrincipal * agregarPrincipio(nodoPrincipal * nodoPri, nodoPrincipal * nuevo)
{
    if(nodoPri == NULL)
    {
        nodoPri = nuevo;
    }
    else
    {
        nuevo->siguiente = nodoPri;
        nodoPri = nuevo;
    }
    return nodoPri;
}

nodoSecundario * agregarPrincipio2(nodoSecundario * nodoSec, nodoSecundario * nuevo)
{
    if(nodoSec == NULL)
    {
        nodoSec = nuevo;
    }
    else
    {
        nuevo->siguiente = nodoSec;
        nodoSec = nuevo;
    }
    return nodoSec;
}

nodoPrincipal * cargarDatos(nodoPrincipal * nodoPri, char nombreAr[])
{
    registroArchivo registro;
    animal dato;
    especie datito;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&registro, sizeof(registroArchivo),1, buffer) > 0)
        {
            strcpy(dato.nombreAnimal, registro.animal);
            dato.cantidad = registro.cant;
            dato.habitat = registro.habitat;
            strcpy(datito.especie, registro.especie);
            datito.idEspecie = registro.idEspecie;
            nodoPri = alta(nodoPri, dato, datito);
        }
        fclose(buffer);
    }
    return nodoPri;
}

nodoPrincipal * alta(nodoPrincipal * nodoPri, animal dato, especie datito)
{
    nodoSecundario * aux = crearNodo2(dato);
    nodoPrincipal * buscado = buscarEspecie(nodoPri, datito.idEspecie);
    if(buscado == NULL)
    {
        nodoPrincipal * nuevo = crearNodo(datito);
        nodoPri = agregarPrincipio(nodoPri, nuevo);
        buscado = nodoPri;
    }
    buscado->nodoSec = agregarFinal2(buscado->nodoSec, aux);
    return nodoPri;
}

nodoPrincipal * buscarEspecie(nodoPrincipal * nodoPri, int dato)
{
    nodoPrincipal * seg = nodoPri;
    nodoPrincipal * buscado = NULL;

    if(seg != NULL)
    {
        while(seg != NULL && buscado == NULL)
        {
            if(seg->datito.idEspecie == dato)
            {
                buscado = seg;
            }
            seg = seg->siguiente;
        }
    }
    return buscado;
}

void mostrarLista(nodoPrincipal * lista)
{
    nodoPrincipal * seg = lista;
    if(seg != NULL)
    {
        printf("Especie: %s \n", seg->datito.especie);
        printf("Id Especie: %d \n \n", seg->datito.idEspecie);
        while(seg->nodoSec != NULL)
        {
            printf("Nombre: %s \n", seg->nodoSec->dato.nombreAnimal);
            printf("Habitat: %d \n", seg->nodoSec->dato.habitat);
            printf("Cantidad: %d \n \n", seg->nodoSec->dato.cantidad);
            seg->nodoSec = seg->nodoSec->siguiente;
        }
        printf("-----------------------\n");
        mostrarLista(lista->siguiente);
    }
}

nodoPrincipal * buscarUltimo(nodoPrincipal * nodoPri){
    nodoPrincipal * seg = nodoPri;
    if(seg != NULL){
        while(seg->siguiente != NULL){
            seg = seg->siguiente;
        }
    }
    return seg;
}
nodoPrincipal * agregarFinal(nodoPrincipal * nodoPri, nodoPrincipal * nuevo){
    if(nodoPri == NULL){
        nodoPri = nuevo;
    }
    else{
        nodoPrincipal * ultimo = buscarUltimo(nodoPri);
        ultimo->siguiente = nuevo;
    }
    return nodoPri;
}

nodoSecundario * buscarUltimo2(nodoSecundario * nodoPri){
    nodoSecundario * seg = nodoPri;
    if(seg != NULL){
        while(seg->siguiente != NULL){
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoSecundario * agregarFinal2(nodoSecundario * nodoPri, nodoSecundario * nuevo){
    if(nodoPri == NULL){
        nodoPri = nuevo;
    }
    else{
        nodoSecundario * ultimo = buscarUltimo2(nodoPri);
        ultimo->siguiente = nuevo;
    }
    return nodoPri;
}
