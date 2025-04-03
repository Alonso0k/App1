#ifndef METRICS_H
#define METRICS_H

#include "order.h"

typedef char* (*MetricFunc)(int *size, Order *orders);

// Declaración de las funciones de métricas
char* metric_pms(int *size, Order *orders);
char* metric_pls(int *size, Order *orders);
char* metric_dms(int *size, Order *orders);
char* metric_dls(int *size, Order *orders);
char* metric_dmsp(int *size, Order *orders);
char* metric_dlsp(int *size, Order *orders);
char* metric_apo(int *size, Order *orders);
char* metric_apd(int *size, Order *orders);
char* metric_ims(int *size, Order *orders);
char* metric_hp(int *size, Order *orders);

#endif
