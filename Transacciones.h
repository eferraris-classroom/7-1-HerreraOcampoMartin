#ifndef INC_7_1_HERRERAOCAMPOMARTIN_TRANSACCIONES_H
#define INC_7_1_HERRERAOCAMPOMARTIN_TRANSACCIONES_H

typedef struct cuenta {
    int numCuenta;
    float saldo;
    struct cuenta *siguiente;
} Cuenta;

typedef struct listadoCuentas {
    int tam;
    Cuenta *lista;
} ListadoCuentas;

typedef struct transaccion {
    int numCuenta;
    int tipoMovimiento;
    float importe;
    struct transaccion *siguiente;
} Transaccion;

typedef struct listadoTransacciones {
    int tam;
    Transaccion *lista;
} ListadoTransacciones;

ListadoCuentas *crearListadoCuentas();
Cuenta *crearCuenta(int numCuenta);
void insertarCuenta(ListadoCuentas *listado, Cuenta *nueva);
Cuenta *verificarSiExiste(int numCuenta, ListadoCuentas *listado);
int verificarSiHaySaldo(float importe, int tipoMovimiento, Cuenta *actual);

ListadoTransacciones *crearListadoTransacciones();
Transaccion *hacerTransaccion(int numCuenta, float importe, int tipoMovimiento, ListadoCuentas *listado);
void insertarTransaccion(ListadoTransacciones *listado, Transaccion *nuevo);

void mostrarCuentas(ListadoCuentas *listado);
void mostrarTransacciones(ListadoTransacciones *listado);

float totalSalida(ListadoTransacciones *listado);
float totalEntrada(ListadoTransacciones *listado);
Transaccion *buscarMayorTransaccion(ListadoTransacciones *listado);

#endif //INC_7_1_HERRERAOCAMPOMARTIN_TRANSACCIONES_H
