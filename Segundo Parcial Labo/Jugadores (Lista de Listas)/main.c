#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int idEquipo;
    char nombreEquipo[30];
    int idJugador;
    int nroCamisetaJugador;
    char nombreJugador[30];
    int puntosAnotados;
} stJugadorEquipo;

typedef struct
{
    int idEquipo;
    char nombreEquipo[30];
} stEquipo;

typedef struct
{
    int idJugador;
    int nroCamisetaJugador;
    char nombreJugador[30];
    int puntosAnotados;
} stJugador;

typedef struct nodoSecundario
{
    stJugador datito;
    struct nodoSecundario * siguiente;
} nodoSecundario;

typedef struct nodoPrincipal
{
    stEquipo dato;
    nodoSecundario * nodoSecundario;
    struct nodoPrincipal * siguiente;
} nodoPrincipal;

nodoPrincipal * iniclista();
nodoSecundario * iniclista2();
nodoPrincipal * crearNodo(stEquipo dato);
nodoSecundario * crearNodo2(stJugador datito);
nodoPrincipal * cargarDatos(nodoPrincipal*lista, char nombreAr[]);
nodoPrincipal * alta(nodoPrincipal * lista, stEquipo dato, stJugador datito);
nodoPrincipal * buscarNodo(nodoPrincipal * lista, int dato);
nodoPrincipal * agregarPrincipio(nodoPrincipal * lista, nodoPrincipal * nuevo);
nodoSecundario * agregarPrincipio2(nodoSecundario * lista, nodoSecundario * nuevo);
nodoSecundario * buscarGoleador(nodoSecundario * aux);
int main()
{
    char nombreAr[] = "registroJugador.dat";
    stJugador datito;
    nodoPrincipal * lista = iniclista();
    lista = cargarDatos(lista, nombreAr);
    mostrar(lista);
    stJugador arreglo[10];
    int validos = cargarArreglo(arreglo, datito, 10);
    for(int i = 0; i<validos; i++){
        printf("Nombre del Jugador: %s \n", arreglo[i].nombreJugador);
    }


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
nodoPrincipal * crearNodo(stEquipo dato)
{
    nodoPrincipal * aux = (nodoPrincipal*) malloc(sizeof(nodoPrincipal));
    aux->dato = dato;
    aux->siguiente = NULL;
    aux->nodoSecundario = iniclista2();

    return aux;
}

nodoSecundario * crearNodo2(stJugador datito)
{
    nodoSecundario * aux = (nodoSecundario*) malloc(sizeof(nodoSecundario));
    aux->datito = datito;
    aux->siguiente = NULL;

    return aux;
}

nodoPrincipal * cargarDatos(nodoPrincipal * lista, char nombreAr[])
{
    stJugadorEquipo registro;
    stEquipo dato;
    stJugador datito;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&registro, sizeof(stJugadorEquipo),1, buffer) > 0)
        {
            strcpy(dato.nombreEquipo, registro.nombreEquipo);
            dato.idEquipo = registro.idEquipo;

            strcpy(datito.nombreJugador, registro.nombreJugador);
            datito.idJugador = registro.idJugador;
            datito.nroCamisetaJugador = registro.nroCamisetaJugador;
            datito.puntosAnotados = registro.puntosAnotados;
            lista = alta(lista, dato, datito);
        }
        fclose(buffer);
    }
    return lista;
}

nodoPrincipal * alta(nodoPrincipal * lista, stEquipo dato, stJugador datito)
{
    nodoSecundario * aux = crearNodo2(datito);
    nodoPrincipal * buscado = buscarNodo(lista, dato.idEquipo);
    if(buscado == NULL)
    {
        nodoPrincipal * nuevo = crearNodo(dato);
        lista = agregarPrincipio(lista, nuevo);
        buscado = lista;
    }
    buscado->nodoSecundario = agregarPrincipio2(buscado->nodoSecundario, aux);
    return lista;
}
nodoPrincipal * buscarNodo(nodoPrincipal * lista, int dato)
{
    nodoPrincipal * aux = lista;
    nodoPrincipal * buscado = NULL;
    if(aux != NULL && buscado == NULL)
    {
        while(aux != NULL)
        {
            if(aux->dato.idEquipo == dato)
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

nodoSecundario * agregarPrincipio2(nodoSecundario * lista, nodoSecundario * nuevo)
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

void mostrar(nodoPrincipal * lista)
{
    if(lista != NULL)
    {
        while(lista != NULL)
        {
            nodoSecundario * aux = lista->nodoSecundario;
            mostrarPrin(lista->dato);

            while(aux != NULL)
            {
                mostrarSub(aux->datito);
                aux = aux->siguiente;
            }
            lista = lista->siguiente;
        }
    }
}

void mostrarPrin(stEquipo dato)
{
    printf("\n\nNombre Equipo: %s \n", dato.nombreEquipo);
    printf("ID Equipo: %d \n\n", dato.idEquipo);
}

void mostrarSub(stJugador datito)
{
    printf("Nombre Jugador: %s \n", datito.nombreJugador);
    printf("Numero Jugador %d  \n", datito.nroCamisetaJugador);
    printf("Puntos Anotados: %d \n", datito.puntosAnotados);
    printf("ID Jugador: %d \n", datito.idJugador);
}

int goleadores(nodoPrincipal * lista, stJugador arreglo[], int dimension)
{
    int validos = 0;
    nodoSecundario * aux = lista->nodoSecundario;
    if(lista != NULL)
    {
        while(lista != NULL)
        {
            nodoSecundario * goleador = buscarGoleador(aux);
            validos = cargarArreglo(arreglo, goleador->datito.nombreJugador);
            lista = lista->siguiente;
        }
    }
    return validos;
}

nodoSecundario * buscarGoleador(nodoSecundario * aux)
{
    nodoSecundario * goleador = NULL;
    if(aux != NULL)
    {
        while(aux != NULL)
        {
            if(aux->datito.puntosAnotados > goleador->datito.puntosAnotados || goleador == NULL)
            {
                goleador = aux;
            }
            else if(aux->datito.puntosAnotados == goleador->datito.puntosAnotados)
            {
                if(aux->datito.nroCamisetaJugador > goleador->datito.nroCamisetaJugador)
                {
                    goleador = aux;
                }
            }
            aux = aux->siguiente;
        }
    }
    return goleador;
}

int cargarArreglo(stJugador arreglo[], stJugador datito, int dimension){
    int i = 0;
    while(i<dimension){
            strcpy(arreglo[i].nombreJugador, datito.nombreJugador);
            i++;
    }
    return i;
}
