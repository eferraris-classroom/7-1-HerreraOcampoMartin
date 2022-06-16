#include "Transacciones.h"
#include <stdlib.h>
#include <stdio.h>

ListadoCuentas *crearListadoCuentas() {
    ListadoCuentas *listado = (ListadoCuentas*) malloc(sizeof (ListadoCuentas));

    if(listado == NULL){
        printf("No hay memoria libre.\n");
        exit(-1);
    }

    listado->tam = 0;
    listado->lista = NULL;

    return listado;
}

Cuenta *crearCuenta(int numCuenta) {
    Cuenta *nueva = (Cuenta*) malloc(sizeof (Cuenta));

    if(nueva == NULL){
        printf("No hay memoria libre.\n");
        exit(-1);
    }

    nueva->numCuenta = numCuenta;
    nueva->saldo = 0;
    nueva->siguiente = NULL;

    return nueva;
}

void insertarCuenta(ListadoCuentas *listado, Cuenta *nueva){
    if ( listado->lista == NULL ) {
        listado->lista = nueva;
    } else {

        Cuenta *act = NULL, * ant = NULL;
        act = listado->lista;
        ant = act;

        while ( act != NULL && act->numCuenta < nueva->numCuenta ) {
            ant = act;
            act = act->siguiente;
        }

        if ( act == NULL ) {
            ant->siguiente = nueva;
        } else if ( act == ant ) {
            listado->lista = nueva;
            nueva->siguiente = act;
        } else {
            nueva->siguiente = act;
            ant->siguiente = nueva;
        }

    }

    listado->tam++;
}

ListadoTransacciones *crearListadoTransacciones() {
    ListadoTransacciones *listado = (ListadoTransacciones*) malloc(sizeof(ListadoTransacciones));

    if(listado == NULL){
        printf("No hay memoria libre.\n");
        exit(-1);
    }

    listado->tam = 0;
    listado->lista = NULL;

    return listado;
}

Transaccion *hacerTransaccion(int numCuenta, float importe, int tipoMovimiento, ListadoCuentas *listado) {
    Transaccion *nueva = (Transaccion*) malloc(sizeof(Transaccion));

    if(nueva == NULL){
        printf("No hay memoria libre.\n");
        exit(-1);
    }

    Cuenta *usuario = verificarSiExiste(numCuenta, listado);
    if(usuario == NULL) {
        printf("El número de cuenta (%d) ingresado no es válido.\n", numCuenta);
        return NULL;
    }

    if(verificarSiHaySaldo(importe, tipoMovimiento, usuario) != 1){
        printf("La cuenta %d no puede gastar %.2f porque no tiene saldo (tiene %.2f).\n", numCuenta, importe, usuario->saldo);
        return NULL;
    }

    nueva->numCuenta = numCuenta;
    nueva->importe = importe;
    nueva->tipoMovimiento = tipoMovimiento;
    nueva->siguiente = NULL;

    if(tipoMovimiento == 1){
        usuario->saldo = usuario->saldo + importe;
    }else {
        usuario->saldo = usuario->saldo - importe;
    }

    return nueva;
}

void insertarTransaccion(ListadoTransacciones *listado, Transaccion *nuevo){
    Transaccion *aux = listado->lista;

    if(aux == NULL){
        listado->lista = nuevo;
        return;
    }

    for (; aux->siguiente != NULL; aux = aux->siguiente) {}

    aux->siguiente = nuevo;
    listado->tam++;
}

Cuenta *verificarSiExiste(int numCuenta, ListadoCuentas *listado){
    Cuenta *aux = listado->lista;

    if(aux == NULL){

        printf("La lista esta vacía.\n");

    }else{

        for(; aux != NULL; aux = aux->siguiente){
            if(aux->numCuenta == numCuenta){
                break;
            }
        }

    }

    return aux;
}

int verificarSiHaySaldo(float importe, int tipoMovimiento, Cuenta *actual){
    int respuesta = 0;

    if(actual == NULL){

        printf("La lista esta vacía.\n");

    } else if(tipoMovimiento == 1){
        respuesta = 1; //Si se ingresa dinero, entonces no
        //tengo que verificar nada, porque no se esta restando nada.
    } else{
        if(actual->saldo - importe > 0){
            respuesta = 1;
        }
    }

    return respuesta;
}

void mostrarCuentas(ListadoCuentas *listado) {
    Cuenta *aux = listado->lista;
    if(aux == NULL){
        printf("No hay cuentas creadas.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguiente) {
        printf("Num. cuenta: %d - Saldo: %.2f\n", aux->numCuenta, aux->saldo);
    }
}

void mostrarTransacciones(ListadoTransacciones *listado) {
    Transaccion *aux = listado->lista;
    if(aux == NULL){
        printf("No hay cuentas creadas.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguiente) {
        printf("Num. cuenta: %d - Transacción: %.2f - Tipo movimiento: %d\n", aux->numCuenta, aux->importe, aux->tipoMovimiento);
    }
}

float totalSalida(ListadoTransacciones *listado) {
    float suma = 0;
    Transaccion *aux = listado->lista;

    for (; aux != NULL; aux = aux->siguiente) {
        if(aux->tipoMovimiento == 2)
            suma += aux->importe;
    }

    return suma;
}

float totalEntrada(ListadoTransacciones *listado) {
    float suma = 0;
    Transaccion *aux = listado->lista;

    for (; aux != NULL; aux = aux->siguiente) {
        if(aux->tipoMovimiento == 1)
            suma += aux->importe;
    }

    return suma;
}

Transaccion *buscarMayorTransaccion(ListadoTransacciones *listado) {
    Transaccion *aux = listado->lista;
    Transaccion *mayor = NULL;

    if(aux == NULL){
        return NULL;
    }

    mayor = aux;
    for (; aux != NULL; aux = aux->siguiente) {
        if(aux->importe > mayor->importe){
            mayor = aux;
        }
    }

    return mayor;
}


