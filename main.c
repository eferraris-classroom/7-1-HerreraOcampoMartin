#include "Transacciones.h"
#include <stdio.h>

int main() {

    ListadoCuentas *cuentas = crearListadoCuentas();
    ListadoTransacciones *transacciones = crearListadoTransacciones();

    insertarCuenta(cuentas, crearCuenta(123));
    insertarCuenta(cuentas, crearCuenta(234));
    insertarCuenta(cuentas, crearCuenta(345));

    insertarTransaccion(transacciones, hacerTransaccion(123, 400, 2, cuentas));
    insertarTransaccion(transacciones, hacerTransaccion(123, 800, 1, cuentas));
    insertarTransaccion(transacciones, hacerTransaccion(345, 120.5, 1, cuentas));
    insertarTransaccion(transacciones, hacerTransaccion(234, 1500, 1, cuentas));
    insertarTransaccion(transacciones, hacerTransaccion(234, 400, 2, cuentas));

    mostrarCuentas(cuentas);
    mostrarTransacciones(transacciones);
    float sumaSalida = totalSalida(transacciones);
    float sumaEntrada = totalEntrada(transacciones);
    Transaccion *mayor = buscarMayorTransaccion(transacciones);

    printf("La suma de todas las salidas es de %.2f\n", sumaSalida);
    printf("La suma de todas las entradas es de %.2f\n", sumaEntrada);
    printf("La mayor transacción fue de %.2f, fue de tipo %d y la realizó la cuenta %d.\n", mayor->importe, mayor->tipoMovimiento, mayor->numCuenta);


    return 0;
}
