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
    char animal[30];
    int cantidad;
    int habitat;
} animal;

typedef struct nodo
{
    animal dato;
    struct nodo * siguiente;
} nodo;

typedef struct
{
    int idEspecie;
    char especie[20];
    nodo * lista;
} celdaEspecie;

nodo * iniclista();
nodo * crearNodo(animal dato);
int cargarDatos(celdaEspecie celda[], char nombreAr[], int dimension);
int alta(celdaEspecie celda[], animal dato, registroArchivo registro, int validos);
int buscarPosEspecie(celdaEspecie celda[], int especie, int validos);
int agregarEspecie(celdaEspecie celda[], registroArchivo registro, int validos);
nodo * agregarPrincipio(nodo * lista, nodo * nuevo);


int main()
{
    char nombreAr[] = "animales.dat";
    celdaEspecie celda[20];
    nodo * lista = iniclista();
    int validos = cargarDatos(celda, nombreAr, 20);
    for(int i = 0; i<validos; i++)
    {
        printf("Especie: %s \n", celda[i].especie);
        printf("ID Especie: %d \n \n", celda[i].idEspecie);
        mostrar(celda[i].lista);
    }

    return 0;
}

nodo * iniclista()
{
    return NULL;
}

nodo * crearNodo(animal dato)
{
    nodo * aux = (nodo*) malloc(sizeof(nodo));
    aux->dato = dato;
    aux->siguiente = NULL;

    return aux;
}

int cargarDatos(celdaEspecie celda[], char nombreAr[], int dimension)
{
    int validos = 0;
    registroArchivo registro;
    animal dato;
    celdaEspecie especie;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&registro, sizeof(registroArchivo),1, buffer) > 0 && validos < dimension)
        {
            strcpy(dato.animal, registro.animal);
            dato.cantidad = registro.cant;
            dato.habitat = registro.habitat;
            strcpy(especie.especie, registro.especie);
            especie.idEspecie = registro.idEspecie;
            validos = alta(celda, dato, registro, validos);
        }
        fclose(buffer);
    }
    return validos;
}

int alta(celdaEspecie celda[], animal dato, registroArchivo registro, int validos)
{
    nodo * aux = crearNodo(dato);
    int pos = buscarPosEspecie(celda, registro.idEspecie, validos);
    if(pos == -1)
    {
        validos = agregarEspecie(celda, registro, validos);
        pos = validos-1;
    }
    celda[pos].lista = agregarPrincipio(celda[pos].lista, aux);
    return validos;
}

int buscarPosEspecie(celdaEspecie celda[], int especie, int validos)
{
    int pos = -1;
    int i = 0;
    while(i<validos && pos== -1)
    {
        if(especie == celda[i].idEspecie)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

int agregarEspecie(celdaEspecie celda[], registroArchivo registro, int validos)
{
    celda[validos].idEspecie = registro.idEspecie;
    strcpy(celda[validos].especie, registro.especie);
    celda[validos].lista = iniclista();
    validos++;
    return validos;
}

nodo * agregarPrincipio(nodo * lista, nodo * nuevo)
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

void mostrar(nodo * lista)
{
    nodo * seg = lista;
    if(lista != NULL)
    {
        while(seg != NULL)
        {
            printf("Animal: %s \n", seg->dato.animal);
            printf("Cantidad: %d \n", seg->dato.cantidad);
            printf("Habitat: %d \n" , seg->dato.habitat);
            printf("\n-------------------------------------------------\n");
            seg = seg->siguiente;
        }
    }
}

