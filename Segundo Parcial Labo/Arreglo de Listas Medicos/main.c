#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int idRegistro;
    int idPaciente;
    int idEspecialidad;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11]; /// formato: AAAA-mm-DD
    char especialidadMedica[30];
    char nombreDoctor[30];
} stRegistroMedico;

typedef struct
{
    int idEspecialidad;
    char especialidadMedica[30];
} especialidad;

typedef struct
{
    int idRegistro;
    int idPaciente;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11];
    char nombreDoctor[30];
} paciente;

typedef struct nodo
{
    paciente datito;
    struct nodo * siguiente;
    struct nodo * anterior;
} nodo;

typedef struct
{
    especialidad dato;
    nodo * lista;
} celda;

nodo * iniclista();
nodo * crearNodo(paciente datito);
int cargarDatos(celda adl[], char nombreAr[], int dimension);
int alta(celda adl[], especialidad dato, paciente datito, int validos);
int buscarEspecialidad(celda adl[], especialidad dato, int validos);
int agregarEspecialidad(celda adl[], especialidad dato, int validos);
nodo * agregarOrdenado(nodo * lista, nodo * nuevo);
nodo * agregarPrincipio(nodo * lista, nodo * nuevo);
nodo * agregarOrdenado(nodo * lista, nodo * nuevo);

int main()
{
    char nombreAr[] = "registroMedico.dat";
    celda adl[20];
    int validos = cargarDatos(adl, nombreAr, 20);
    mostrar(adl);
    return 0;
}

nodo * iniclista()
{
    return NULL;
}

nodo * crearNodo(paciente datito)
{
    nodo * aux = (nodo*) malloc(sizeof(nodo));
    aux->datito = datito;
    aux->siguiente = NULL;
    aux->anterior = NULL;
    return aux;
}

int cargarDatos(celda adl[], char nombreAr[], int dimension)
{
    stRegistroMedico archivo;
    especialidad dato;
    paciente datito;
    int validos = 0;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while((fread(&archivo, sizeof(stRegistroMedico),1, buffer) > 0) && validos < dimension)
        {
            strcpy(dato.especialidadMedica, archivo.especialidadMedica);
            dato.idEspecialidad = archivo.idEspecialidad;
            strcpy(datito.apellidoPaciente, archivo.apellidoPaciente);
            strcpy(datito.nombrePaciente, archivo.nombrePaciente);
            strcpy(datito.nombreDoctor, archivo.nombreDoctor);
            strcpy(datito.diagnostico, archivo.diagnostico);
            datito.idPaciente = archivo.idPaciente;
            datito.idRegistro = archivo.idRegistro;

            validos = alta(adl, dato, datito, validos);
        }
        fclose(buffer);
    }
    return validos;
}

int alta(celda adl[], especialidad dato, paciente datito, int validos)
{
    nodo * aux = crearNodo(datito);
    int pos = buscarEspecialidad(adl, dato, validos);
    if(pos == -1)
    {
        validos = agregarEspecialidad(adl, dato, validos);
        pos = validos -1;
    }
    adl[pos].lista = agregarOrdenado(adl[pos].lista, aux);
    return validos;
}

int buscarEspecialidad(celda adl[], especialidad dato, int validos)
{
    int pos = -1;
    int i = 0;
    while(i < validos && pos == -1)
    {
        if(strcmpi(adl[i].dato.especialidadMedica, dato.especialidadMedica) == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

int agregarEspecialidad(celda adl[], especialidad dato, int validos)
{
    adl[validos].dato = dato;
    adl[validos].lista = iniclista();
    validos++;
    return validos;
}

nodo * agregarOrdenado(nodo * lista, nodo * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        if(nuevo->datito.idPaciente < lista->datito.idPaciente)
        {
            lista = agregarPrincipio(lista, nuevo);
        }
        else
        {
            nodo * seg = lista->siguiente;
            nodo * ante = lista;
            while(seg != NULL && nuevo->datito.idPaciente > seg->datito.idPaciente)
            {
                ante = seg;
                seg = seg->siguiente;
            }
            ante->siguiente = nuevo;
            nuevo->anterior = ante;
            nuevo->siguiente = seg;
            if(seg != NULL)
            {
                seg->anterior = nuevo;
            }
        }
    }
    return lista;
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
        lista->anterior = nuevo;
        lista = nuevo;
    }
    return lista;
}

void mostrar(celda adl[], int validos)
{
    int i = 0;
    while(i<validos)
    {
        printf("Especialidad: %s \n", adl[i].dato.especialidadMedica);
        printf("ID Especialidad: %d \n\n", adl[i].dato.idEspecialidad);
        while(adl[i].lista != NULL)
        {
            printf("Nombre y Apellido Paciente: %s %s \n", adl[i].lista->datito.nombrePaciente, adl[i].lista->datito.apellidoPaciente);
            printf("ID Paciente: %d \n", adl[i].lista->datito.idPaciente);
            printf("Nombre del Doctor: %s \n", adl[i].lista->datito.nombreDoctor);
            printf("\n");
            adl[i].lista = adl[i].lista->siguiente;
        }
        printf("------------------------------------------\n\n");
        i++;
    }
}
