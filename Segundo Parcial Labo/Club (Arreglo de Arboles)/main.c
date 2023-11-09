#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char NombreDeporte[50];
} stClub;

typedef struct
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    float valorCuota;
    int edad;
} socio;

typedef struct
{
    int idDeporte;
    char NombreDeporte[50];
} deporte;

typedef struct
{
    deporte dato;
    struct nodoArbol * arbol;
} celda;

typedef struct nodoArbol
{
    socio datito;
    struct nodoArbol * der;
    struct nodoArbol * izq;
} nodoArbol;

nodoArbol * insertar (nodoArbol * arbol, socio datito);

int main()
{
    char nombreAr[] = "registroClub.dat";
    celda adl[20];
    int validos = cargarDatos(nombreAr, adl, 20);
    mostrar(adl, validos);
    int pos = contarSocios(adl, validos);
    printf("Deporte con mas Socios: %s", adl[pos].dato.NombreDeporte);
    return 0;
}

nodoArbol * inicarbol()
{
    return NULL;
}

nodoArbol * crearNodo(socio datito)
{
    nodoArbol * aux = (nodoArbol*) malloc(sizeof(nodoArbol));
    aux->der = NULL;
    aux->izq = NULL;
    aux->datito = datito;
    return aux;
}

int cargarDatos(char nombreAr[], celda adl[], int dimension)
{
    int validos = 0;
    stClub registro;
    deporte dato;
    socio datito;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&registro, sizeof(stClub),1, buffer) > 0 && validos < dimension)
        {
            strcpy(dato.NombreDeporte, registro.NombreDeporte);
            dato.idDeporte = registro.idDeporte;

            strcpy(datito.nya, registro.nya);
            datito.valorCuota = registro.valorCuota;
            datito.idSocio = registro.idSocio;
            datito.ultimaCuotaPaga = registro.ultimaCuotaPaga;
            datito.edad = registro.edad;

            validos = alta(adl, dato, datito, validos);
        }
        fclose(buffer);
    }
    return validos;
}

int alta(celda adl[], deporte dato, socio datito, int validos)
{
    int pos = buscarPos(adl, dato.idDeporte, validos);

    if(pos == -1)
    {
        validos = agregarDeporte(adl, validos, dato);
        pos = validos - 1;
    }
    adl[pos].arbol = insertar(adl[pos].arbol, datito);
    return validos;
}

nodoArbol * insertar (nodoArbol * arbol, socio datito)
{
    if(arbol == NULL)
    {
        arbol = crearNodo(datito);
    }
    else
    {
        if(datito.idSocio > arbol->datito.idSocio)
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

int buscarPos(celda adl[], int dato, int validos)
{
    int pos = -1;
    int i = 0;
    while(i<validos)
    {
        if(adl[i].dato.idDeporte == dato)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

int agregarDeporte(celda adl[], int validos, deporte dato)
{
    strcpy(adl[validos].dato.NombreDeporte, dato.NombreDeporte);
    adl[validos].dato.idDeporte = dato.idDeporte;
    adl[validos].arbol = inicarbol();
    validos++;
    return validos;
}

void mostrar(celda adl[], int validos)
{
    int i = 0;
    while(i<validos)
    {
        nodoArbol * aux = adl[i].arbol;
        printf("\n\nDeporte: %s\n \n", adl[i].dato.NombreDeporte);
        printf("ID Deporte: %d \n", adl[i].dato.idDeporte);
        if(aux != NULL)
        {
            inorder(aux);
        }
        i++;
    }
}

void inorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->der);
        printf("Nombre y Apellido: %s \n", arbol->datito.nya);
        printf("Edad: %d \n", arbol->datito.edad);
        printf("ID Socio: %d\n", arbol->datito.idSocio);
        printf("Ultima Cuota paga: %d \n", arbol->datito.ultimaCuotaPaga);
        printf("Valor cuota: %.2f \n", arbol->datito.valorCuota);
        printf("\n");
        inorder(arbol->izq);
    }
}

int contarSocios(celda adl[], int validos)
{
    int i = 0;
    int total = 0;
    int pos = 0;
    while(i<validos)
    {
        int cantidad = recorrerArbol(adl[i].arbol);
        if(total < cantidad){
            total = cantidad;
            pos = i;
        }
        i++;
    }
    return pos;
}

int recorrerArbol(nodoArbol * arbol)
{
    int total = 0;
    if(arbol != NULL)
    {
        total = 1 + recorrerArbol(arbol->der) + recorrerArbol(arbol->izq);
    }
    return total;
}
