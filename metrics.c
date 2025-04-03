#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "metrics.h"
#include "order.h"

//====================================================
// Métrica: Pizza más vendida (pms)
//====================================================
typedef struct {
    char pizza_name[MAX_STR_LEN];
    int count;
} PizzaCount;

char* metric_pms(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    PizzaCount *counts = malloc(capacity * sizeof(PizzaCount));
    if (!counts) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(counts[j].pizza_name, orders[i].pizza_name) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                counts = realloc(counts, capacity * sizeof(PizzaCount));
            }
            strncpy(counts[num].pizza_name, orders[i].pizza_name, MAX_STR_LEN);
            counts[num].count = 1;
            num++;
        }
    }
    
    int max_index = 0;
    for (int i = 1; i < num; i++) {
        if (counts[i].count > counts[max_index].count)
            max_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "%s (vendida %d veces)", counts[max_index].pizza_name, counts[max_index].count);
    free(counts);
    return result;
}

//====================================================
// Métrica: Pizza menos vendida (pls)
//====================================================
char* metric_pls(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    PizzaCount *counts = malloc(capacity * sizeof(PizzaCount));
    if (!counts) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(counts[j].pizza_name, orders[i].pizza_name) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                counts = realloc(counts, capacity * sizeof(PizzaCount));
            }
            strncpy(counts[num].pizza_name, orders[i].pizza_name, MAX_STR_LEN);
            counts[num].count = 1;
            num++;
        }
    }
    
    int min_index = 0;
    for (int i = 1; i < num; i++) {
        if (counts[i].count < counts[min_index].count)
            min_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "%s (vendida %d veces)", counts[min_index].pizza_name, counts[min_index].count);
    free(counts);
    return result;
}

//====================================================
// Métrica: Fecha con más ventas (dinero) (dms)
//====================================================
typedef struct {
    char date[MAX_STR_LEN];
    float total_money;
} DateAggregate;

char* metric_dms(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    DateAggregate *aggregates = malloc(capacity * sizeof(DateAggregate));
    if (!aggregates) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(aggregates[j].date, orders[i].order_date) == 0) {
                aggregates[j].total_money += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                aggregates = realloc(aggregates, capacity * sizeof(DateAggregate));
            }
            strncpy(aggregates[num].date, orders[i].order_date, MAX_STR_LEN);
            aggregates[num].total_money = orders[i].total_price;
            num++;
        }
    }
    
    int max_index = 0;
    for (int i = 1; i < num; i++) {
        if (aggregates[i].total_money > aggregates[max_index].total_money)
            max_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "Fecha: %s, Total recaudado: %.2f", aggregates[max_index].date, aggregates[max_index].total_money);
    free(aggregates);
    return result;
}

//====================================================
// Métrica: Fecha con menos ventas (dinero) (dls)
//====================================================
char* metric_dls(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    DateAggregate *aggregates = malloc(capacity * sizeof(DateAggregate));
    if (!aggregates) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(aggregates[j].date, orders[i].order_date) == 0) {
                aggregates[j].total_money += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                aggregates = realloc(aggregates, capacity * sizeof(DateAggregate));
            }
            strncpy(aggregates[num].date, orders[i].order_date, MAX_STR_LEN);
            aggregates[num].total_money = orders[i].total_price;
            num++;
        }
    }
    
    int min_index = 0;
    for (int i = 1; i < num; i++) {
        if (aggregates[i].total_money < aggregates[min_index].total_money)
            min_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "Fecha: %s, Total recaudado: %.2f", aggregates[min_index].date, aggregates[min_index].total_money);
    free(aggregates);
    return result;
}

//====================================================
// Métrica: Fecha con más ventas (cantidad de pizzas) (dmsp)
//====================================================
typedef struct {
    char date[MAX_STR_LEN];
    int total_quantity;
} DateQuantity;

char* metric_dmsp(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    DateQuantity *aggregates = malloc(capacity * sizeof(DateQuantity));
    if (!aggregates) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(aggregates[j].date, orders[i].order_date) == 0) {
                aggregates[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                aggregates = realloc(aggregates, capacity * sizeof(DateQuantity));
            }
            strncpy(aggregates[num].date, orders[i].order_date, MAX_STR_LEN);
            aggregates[num].total_quantity = orders[i].quantity;
            num++;
        }
    }
    
    int max_index = 0;
    for (int i = 1; i < num; i++) {
        if (aggregates[i].total_quantity > aggregates[max_index].total_quantity)
            max_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "Fecha: %s, Total pizzas: %d", aggregates[max_index].date, aggregates[max_index].total_quantity);
    free(aggregates);
    return result;
}

//====================================================
// Métrica: Fecha con menos ventas (cantidad de pizzas) (dlsp)
//====================================================
char* metric_dlsp(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    DateQuantity *aggregates = malloc(capacity * sizeof(DateQuantity));
    if (!aggregates) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(aggregates[j].date, orders[i].order_date) == 0) {
                aggregates[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                aggregates = realloc(aggregates, capacity * sizeof(DateQuantity));
            }
            strncpy(aggregates[num].date, orders[i].order_date, MAX_STR_LEN);
            aggregates[num].total_quantity = orders[i].quantity;
            num++;
        }
    }
    
    int min_index = 0;
    for (int i = 1; i < num; i++) {
        if (aggregates[i].total_quantity < aggregates[min_index].total_quantity)
            min_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "Fecha: %s, Total pizzas: %d", aggregates[min_index].date, aggregates[min_index].total_quantity);
    free(aggregates);
    return result;
}

//====================================================
// Métrica: Promedio de pizzas por orden (apo)
//====================================================
char* metric_apo(int *size, Order *orders) {
    int n = *size;
    if (n == 0) return NULL;
    long total_pizzas = 0;
    for (int i = 0; i < n; i++) {
        total_pizzas += orders[i].quantity;
    }
    float promedio = (float) total_pizzas / n;
    char *result = malloc(512);
    snprintf(result, 256, "Promedio de pizzas por orden: %.2f", promedio);
    return result;
}

//====================================================
// Métrica: Promedio de pizzas por día (apd)
//====================================================
char* metric_apd(int *size, Order *orders) {
    int n = *size;
    if (n == 0) return NULL;
    long total_pizzas = 0;
    int unique_days = 0;
    // Arreglo para almacenar fechas únicas (solo se libera el arreglo, no las cadenas)
    char **dates = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        total_pizzas += orders[i].quantity;
        int found = 0;
        for (int j = 0; j < unique_days; j++) {
            if (strcmp(dates[j], orders[i].order_date) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            dates[unique_days] = orders[i].order_date;
            unique_days++;
        }
    }
    float promedio = (float) total_pizzas / unique_days;
    char *result = malloc(512);
    snprintf(result, 512, "Promedio de pizzas por día: %.2f", promedio);
    free(dates);
    return result;
}

//====================================================
// Métrica: Ingrediente más vendido (ims) 
//====================================================
typedef struct {
    char ingredient[MAX_STR_LEN];
    int count;
} IngredientCount;

char* metric_ims(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    IngredientCount *counts = malloc(capacity * sizeof(IngredientCount));
    if (!counts) return NULL;
    
    for (int i = 0; i < n; i++) {
        // Cada orden puede tener varios ingredientes separados por coma
        char ingredients_copy[MAX_STR_LEN];
        strncpy(ingredients_copy, orders[i].pizza_ingredients, MAX_STR_LEN);
        char *token = strtok(ingredients_copy, ",");
        while (token != NULL) {
            // Quitar espacios en blanco al inicio y al final del token
            while(isspace((unsigned char)*token)) token++;
            char *end = token + strlen(token) - 1;
            while(end > token && isspace((unsigned char)*end)) {
                *end = '\0';
                end--;
            }
            int found = 0;
            for (int j = 0; j < num; j++) {
                if (strcmp(counts[j].ingredient, token) == 0) {
                    counts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                if (num >= capacity) {
                    capacity *= 2;
                    counts = realloc(counts, capacity * sizeof(IngredientCount));
                }
                strncpy(counts[num].ingredient, token, MAX_STR_LEN);
                counts[num].count = 1;
                num++;
            }
            token = strtok(NULL, ",");
        }
    }
    
    int max_index = 0;
    for (int i = 1; i < num; i++) {
        if (counts[i].count > counts[max_index].count)
            max_index = i;
    }
    
    char *result = malloc(512);
    snprintf(result, 512, "Ingrediente: %s (vendido %d veces)", counts[max_index].ingredient, counts[max_index].count);
    free(counts);
    return result;
}

//====================================================
// Métrica: Cantidad de pizzas por categoría vendidas (hp)
//====================================================
char* metric_hp(int *size, Order *orders) {
    int n = *size;
    int capacity = 10, num = 0;
    typedef struct {
        char category[MAX_STR_LEN];
        int total;
    } CategoryCount;
    
    CategoryCount *counts = malloc(capacity * sizeof(CategoryCount));
    if (!counts) return NULL;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < num; j++) {
            if (strcmp(counts[j].category, orders[i].pizza_category) == 0) {
                counts[j].total += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num >= capacity) {
                capacity *= 2;
                counts = realloc(counts, capacity * sizeof(CategoryCount));
            }
            strncpy(counts[num].category, orders[i].pizza_category, MAX_STR_LEN);
            counts[num].total = orders[i].quantity;
            num++;
        }
    }
    
    char *result = malloc(1024);
    if (!result) {
        free(counts);
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < num; i++) {
        char buffer[256];  // Buffer local aumentado a 256 bytes
        snprintf(buffer, 512, "Categoria: %s, Total: %d\n", counts[i].category, counts[i].total);
        strncat(result, buffer, 1024 - strlen(result) - 1);
    }
    
    free(counts);
    return result;
}

