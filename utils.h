#ifndef UTILS_H
#define UTILS_H

#include "order.h"

// Lee el archivo CSV y almacena las órdenes en un arreglo dinámico.
// Retorna el número de órdenes leídas.
int load_orders(const char *filename, Order **orders);

#endif
