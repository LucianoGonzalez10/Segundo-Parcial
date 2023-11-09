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
    char nombreAnimal [30];
    int cantidad;
    int habitat;
} animal;

typedef struct
{
    animal dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct
{
    int idEspecie;
    char especie [20];
    nodoArbol * arbolDeAnimales;
} celdaEspecie;


int main()
{
    char nombreAr[] = "animales.dat";
    celdaEspecie adl[10];
    int validos = cargarDatos(adl, nombreAr, 20);
    mostrar(adl, validos);
    return 0;
}

nodoArbol * inicarbol()
{
    return NULL;
}

nodoArbol * crearNodo(animal dato)
{
    nodoArbol * aux = (nodoArbol*) malloc(sizeof(nodoArbol));
    aux->izq = NULL;
    aux->der=NULL;
    aux->dato = dato;

    return aux;
}

nodoArbol * insertar(nodoArbol * arbol, animal dato)
{
    if(arbol == NULL)
    {
        arbol = crearNodo(dato);
    }
    else
    {
        if(arbol->dato.cantidad < dato.cantidad)
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

int cargarDatos(celdaEspecie adl[], char nombreAr[], int dimension)
{
    registroArchivo registro;
    animal dato;
    celdaEspecie datito;
    int validos = 0;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&registro, sizeof(registroArchivo),1, buffer) > 0 && validos < dimension)
        {
            strcpy(dato.nombreAnimal, registro.animal);
            dato.habitat = registro.habitat;
            dato.cantidad = registro.cant;

            datito.idEspecie = registro.idEspecie;
            strcpy(datito.especie, registro.especie);
            validos = alta(adl, datito, dato, validos);
        }
        fclose(buffer);
    }
    return validos;
}

int alta(celdaEspecie adl[], celdaEspecie datito, animal dato, int validos)
{
    int pos = buscarPos(adl, datito.idEspecie, validos);
    if(pos == -1)
    {
        validos = agregarEspecie(adl, datito, validos);
        pos = validos-1;
    }
    adl[pos].arbolDeAnimales = insertar(adl[pos].arbolDeAnimales, dato);
    return validos;
}

int buscarPos(celdaEspecie adl[], int dato, int validos)
{
    int pos = -1;
    int i = 0;
    while(i<validos)
    {
        if(adl[i].idEspecie == dato)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

int agregarEspecie(celdaEspecie adl[], celdaEspecie datito, int validos)
{
    adl[validos].idEspecie = datito.idEspecie;
    strcpy(adl[validos].especie, datito.especie);
    adl[validos].arbolDeAnimales = inicarbol();
    validos++;

    return validos;
}

void mostrar(celdaEspecie celda[], int validos)
{
    int i = 0;
    while(i<validos)
    {
        printf("\n\nEspecie: %s \n", celda[i].especie);
        printf("ID Especie: %d \n \n", celda[i].idEspecie);
        inorder(celda[i].arbolDeAnimales);
        i++;
    }
}

void inorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->der);
        printf("Nombre animal: %s \n", arbol->dato.nombreAnimal);
        printf("Cantidad: %d \n", arbol->dato.cantidad);
        printf("Habitat: %d \n", arbol->dato.habitat);
        inorder(arbol->izq);
    }
}
