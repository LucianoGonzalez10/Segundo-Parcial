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
} medico;

typedef struct
{
    int idRegistro;
    int idPaciente;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11]; /// formato: AAAA-mm-DD
    char nombreDoctor[30];
} paciente;

typedef struct nodo2
{
    paciente datito;
    struct nodo2 * siguiente;
    struct nodo2 * anterior;
} nodo2;

typedef struct nodo
{
    medico dato;
    nodo2 * nodo2;
    struct nodo * sig;
} nodo;

nodo * iniclista();
nodo2 * iniclista2();
nodo * crearNodo(medico dato);
nodo2 * crearNodo2(paciente datito);
nodo * cargarDatos(nodo * lista, char nombreAr[]);
nodo * alta(nodo * lista,medico dato, paciente datito);
nodo * agregarPrincipio(nodo * lista, nodo * nuevo);
nodo2 * agregarPrincipio2(nodo2 * lista, nodo2 * nuevo);
nodo * buscarEspecialidad(nodo * lista, int dato);
nodo2 * agregarFinal2(nodo2 * lista, nodo2 * nuevo);
nodo2 * buscarUltimo(nodo2 * lista);
int buscarPaciente(nodo * lista, char nombrePac[]);
nodo * solicitarUsuarioDatos(nodo * lista);

int main()
{
    char nombreAr[] = "registroMedico.dat";
    nodo * lista = iniclista();
    lista = cargarDatos(lista, nombreAr);
    mostrarLista(lista);
    // printf("MOSTRAR DESDE EL ARCHIVO: \n \n \n");
    // mostrarArchivo(nombreAr);


    char nombrePac[30];
    printf("Dime el nombre del paciente que quieres saber si existe: \n");
    fflush(stdin);
    scanf("%s", &nombrePac);

    int buscado = buscarPaciente(lista, nombrePac);
    if(buscado == 1)
    {
        printf("El paciente fue encontrado. \n");
    }
    else
    {
        printf("El Paciente no existe. \n");
    }


    contarAtencionesMedicas(lista);

    /* char especialidad[20];
     printf("Dime la especialidad que quieres pasar al archivo: \n");
    fflush(stdin);
    scanf("%s", &especialidad);
    pasarAtenciones(especialidad, lista);

     mostrarArchivo("archivo.bin"); */

    lista = solicitarUsuarioDatos(lista);
    mostrarLista(lista);
    return 0;
}

nodo * iniclista()
{
    return NULL;
}

nodo2 * iniclista2()
{
    return NULL;
}

nodo * crearNodo(medico dato)
{
    nodo * aux = (nodo*) malloc(sizeof(nodo));
    aux->dato = dato;
    aux->sig = NULL;
    aux->nodo2 = iniclista2();

    return aux;
}

nodo2 * crearNodo2(paciente datito)
{
    nodo2 * aux = (nodo2*) malloc(sizeof(nodo2));
    aux->datito = datito;
    aux->siguiente = NULL;
    aux->anterior = NULL;

    return aux;
}

nodo * cargarDatos(nodo * lista, char nombreAr[])
{
    stRegistroMedico archivo;
    medico dato;
    paciente datito;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&archivo, sizeof(stRegistroMedico),1, buffer) > 0)
        {
            strcpy(dato.especialidadMedica, archivo.especialidadMedica);
            dato.idEspecialidad = archivo.idEspecialidad;

            strcpy(datito.nombreDoctor, archivo.nombreDoctor);
            strcpy(datito.nombrePaciente, archivo.nombrePaciente);
            strcpy(datito.apellidoPaciente, archivo.apellidoPaciente);
            strcpy(datito.diagnostico, archivo.diagnostico);
            datito.idPaciente = archivo.idPaciente;
            datito.idRegistro = archivo.idRegistro;
            lista = alta(lista, dato, datito);
        }
        fclose(buffer);
    }
    return lista;
}

nodo * alta(nodo * lista, medico dato, paciente datito)
{
    nodo2 * aux = crearNodo2(datito);
    nodo * buscado = buscarEspecialidad(lista, dato.idEspecialidad);
    if(buscado == NULL)
    {
        nodo * nuevo = crearNodo(dato);
        lista = agregarPrincipio(lista, nuevo);
        buscado = lista;
    }
    buscado->nodo2 = agregarPrincipio2(buscado->nodo2, aux);
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
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}

nodo2 * agregarPrincipio2(nodo2 * lista, nodo2 * nuevo)
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

nodo * buscarEspecialidad(nodo * lista, int dato)
{
    nodo * aux = lista;
    nodo * buscado = NULL;
    if(aux != NULL)
    {
        while(aux != NULL && buscado == NULL)
        {
            if(aux->dato.idEspecialidad == dato)
            {

                buscado = aux;
            }
            aux = aux->sig;
        }
    }
    return buscado;
}

void mostrarLista(nodo * lista)
{
    while(lista != NULL)
    {
        printf("Especialidad: %s \n", lista->dato.especialidadMedica);
        printf("ID De la Especialidad: %d \n", lista->dato.idEspecialidad);
        nodo2 * seg = lista->nodo2;
        while(seg != NULL)
        {
            printf("Nombre y apellido del paciente: %s %s \n ", seg->datito.nombrePaciente, seg->datito.apellidoPaciente);
            printf("Id del Paciente: %d \n", seg->datito.idPaciente);
            printf("Id del Registro: %d \n", seg->datito.idRegistro);
            printf("Diagnostico: %s \n", seg->datito.diagnostico);
            printf("Nombre Doctor: %s \n", seg->datito.nombreDoctor);
            printf("-------------------------------------------\n");
            seg = seg->siguiente;
        }
        printf("\n\n");
        lista = lista->sig;
    }
}

nodo2 * agregarFinal2(nodo2 * lista, nodo2 * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nodo2 * ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
    }
    return lista;
}

nodo2 * buscarUltimo(nodo2 * lista)
{
    nodo2 * seg = lista;
    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

void mostrarArchivo(char nombreAr[])
{
    stRegistroMedico archivo;
    medico dato;
    paciente datito;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&archivo, sizeof(stRegistroMedico),1, buffer) > 0)
        {
            printf("Especialidad: %s \n", archivo.especialidadMedica);
            printf("ID De la Especialidad: %d \n", archivo.idEspecialidad);
            printf("Nombre y apellido del paciente: %s %s \n ", archivo.nombrePaciente, archivo.apellidoPaciente);
            printf("Id del Paciente: %d \n", archivo.idPaciente);
            printf("Id del Registro: %d \n", archivo.idRegistro);
            printf("Diagnostico: %s \n", archivo.diagnostico);
            printf("Nombre Doctor:: %s \n", archivo.nombreDoctor);
            printf("-------------------------------------------\n");
        }
        fclose(buffer);
    }
}

int buscarPaciente(nodo * lista, char nombrePac[])
{
    int encontrado = 0;
    while(lista != NULL && encontrado == 0)
    {
        nodo2 * aux = lista->nodo2;
        while(aux != NULL)
        {
            if(strcmpi(nombrePac, aux->datito.nombrePaciente) == 0)
            {
                encontrado = 1;
            }
            aux = aux->siguiente;
        }
        lista = lista->sig;
    }
    return encontrado;
}

void contarAtencionesMedicas(nodo * lista)
{
    int neumologiaPe = 0;
    int neumologia = 0;
    int pediatria = 0;
    int clinica = 0;
    int traumatologia = 0;
    int psicologia = 0;
    int psiquiatria = 0;
    int alternativa = 0;
    while(lista != NULL )
    {
        nodo2 * aux = lista->nodo2;
        while(aux != NULL)
        {
            if(lista->dato.idEspecialidad == 0)
            {
                neumologiaPe = neumologiaPe + 1;
            }
            if(lista->dato.idEspecialidad == 1)
            {
                neumologia = neumologia + 1;
            }
            if(lista->dato.idEspecialidad == 2)
            {
                pediatria = pediatria + 1;
            }
            if(lista->dato.idEspecialidad == 3)
            {
                clinica = clinica + 1;
            }
            if(lista->dato.idEspecialidad == 4)
            {
                traumatologia = traumatologia + 1;
            }
            if(lista->dato.idEspecialidad == 5)
            {
                psicologia = psicologia + 1;
            }
            if(lista->dato.idEspecialidad == 6)
            {
                psiquiatria = psiquiatria + 1;
            }
            if(lista->dato.idEspecialidad == 4)
            {
                alternativa = alternativa + 1;
            }
            aux = aux->siguiente;
        }
        lista = lista->sig;
    }
    printf("Neumologia Pediatrica: %d \n", neumologiaPe);
    printf("Neumologia: %d \n", neumologia);
    printf("Pediatria: %d \n", pediatria);
    printf("Clinica: %d \n", clinica);
    printf("Traumatologia: %d \n", traumatologia);
    printf("Psicologia: %d \n", psicologia);
    printf("Psiquiatria: %d \n", psiquiatria);
    printf("Alternativa: %d \n", alternativa);
}

void pasarAtenciones(char especialidad[], nodo * lista)
{
    stRegistroMedico archivo;
    nodo * aux = lista;
    FILE * buffer = fopen("archivo.bin", "ab");
    if(buffer)
    {
        if(aux != NULL)
        {
            while(aux != NULL)
            {
                if(strcmpi(aux->dato.especialidadMedica, especialidad) == 0)
                {
                    fwrite((&aux->nodo2->datito), sizeof(paciente),1, buffer);
                }
                aux = aux->sig;
            }
        }
        fclose(buffer);
    }
}

nodo * solicitarUsuarioDatos(nodo * lista)
{
    char control = 's';
    printf("Desea cargar datos? \n");
    fflush(stdin);
    scanf("%c", &control);

    medico dato;
    paciente datito;
    while(control == 's')
    {
        printf("Dime la especialidad: \n");
        fflush(stdin);
        scanf("%s", &dato.especialidadMedica);

        printf("Dime el ID De la especialidad: \n");
        scanf("%d", &dato.idEspecialidad);

        printf("Dime el nombre del paciente: \n");
        fflush(stdin);
        scanf("%s", &datito.nombrePaciente);

        printf("Dime el apellido del paciente: \n");
        fflush(stdin);
        scanf("%s", &datito.apellidoPaciente);

        printf("Dime el diagnostico del paciente: \n");
        fflush(stdin);
        scanf("%s", &datito.diagnostico);

        printf("Dime el nombre del Doctor: \n");
        fflush(stdin);
        scanf("%s", &datito.nombreDoctor);

        printf("Dime el ID del paciente: \n");
        scanf("%d", &datito.idPaciente);

        printf("Dime el ID del Registro: \n");
        scanf("%d", &datito.idRegistro);

        lista = alta(lista, dato, datito);

        printf("Desea seguir cargando datos? \n");
        fflush(stdin);
        scanf("%c", &control);
    }
    return lista;
}

nodo * agregarOrdenado(nodo * lista, nodo * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        if(nuevo->dato.idEspecialidad < lista->dato.idEspecialidad)
        {
            lista = agregarPrincipio(lista, nuevo);
        }
        else
        {
            nodo * seg = lista->sig;
            nodo * ante = lista;
            while(seg != NULL && nuevo->dato.idEspecialidad > seg->dato.idEspecialidad)
            {
                ante = seg;
                seg = seg->sig;
            }
            ante->sig = nuevo;
            nuevo->sig = seg;
        }
        return lista;
    }
}
