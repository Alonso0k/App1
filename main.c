#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"
#include "utils.h"
#include "metrics.h"

typedef struct {
    char *name;
    MetricFunc func;
} MetricMapping;

int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Uso: %s archivo.csv metricas...\n", argv[0]);
        return 1;
    }
    
    Order *orders = NULL;
    int count = load_orders(argv[1], &orders);
    if(count <= 0){
        fprintf(stderr, "Error al cargar los datos.\n");
        return 1;
    }
    
    // Definir el mapeo entre nombre de métrica y función
    MetricMapping metrics[] = {
        {"pms", metric_pms},
        {"pls", metric_pls},
        {"dms", metric_dms},
        {"dls", metric_dls},
        {"dmsp", metric_dmsp},
        {"dlsp", metric_dlsp},
        {"apo", metric_apo},
        {"apd", metric_apd},
        {"ims", metric_ims},
        {"hp", metric_hp},
    };
    int numMetrics = sizeof(metrics)/sizeof(MetricMapping);
    
    // Procesar cada métrica pasada por línea de comandos
    for(int i = 2; i < argc; i++){
        MetricFunc func = NULL;
        for(int j = 0; j < numMetrics; j++){
            if(strcmp(argv[i], metrics[j].name) == 0){
                func = metrics[j].func;
                break;
            }
        }
        if(func){
            char *result = func(&count, orders);
            if(strcmp(argv[i], "pms") == 0)
                printf("Pizza mas vendida: %s\n", result);
            else if(strcmp(argv[i], "pls") == 0)
                printf("Pizza menos vendida: %s\n", result);
            else if(strcmp(argv[i], "dms") == 0)
                printf("Fecha con mas ventas (dinero) y total recaudado: %s\n", result);
            else if(strcmp(argv[i], "dls") == 0)
                printf("Fecha con menos ventas (dinero) y total recaudado: %s\n", result);
            else if(strcmp(argv[i], "dmsp") == 0)
                printf("Fecha con mas ventas (cantidad pizzas) y total: %s\n", result);
            else if(strcmp(argv[i], "dlsp") == 0)
                printf("Fecha con menos ventas (cantidad pizzas) y total: %s\n", result);
            else if(strcmp(argv[i], "apo") == 0)
                printf("Promedio de pizzas por orden: %s\n", result);
            else if(strcmp(argv[i], "apd") == 0)
                printf("Promedio de pizzas por dia: %s\n", result);
            else if(strcmp(argv[i], "ims") == 0)
                printf("Ingrediente mas vendido: %s\n", result);
            else if(strcmp(argv[i], "hp") == 0)
                printf("Cantidad de pizzas por categoria vendidas: %s\n", result);
            
            free(result);
        } else {
            printf("Metrica %s no reconocida.\n", argv[i]);
        }
    }
    
    free(orders);
    return 0;
}
