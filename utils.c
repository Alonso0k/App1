#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "order.h"

#define INITIAL_SIZE 100

int load_orders(const char *filename, Order **orders) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error al abrir el archivo");
        return 0;
    }

    // Se ignora la primera línea (cabecera)
    char line[1024];
    fgets(line, sizeof(line), fp);

    int count = 0, capacity = INITIAL_SIZE;
    *orders = malloc(capacity * sizeof(Order));
    if (!*orders) {
        fclose(fp);
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (count >= capacity) {
            capacity *= 2;
            *orders = realloc(*orders, capacity * sizeof(Order));
        }
        Order *order = &(*orders)[count];
        // Se usa strtok para parsear los campos (parseo simplificado asumiendo formato válido)
        char *token = strtok(line, ",");
        order->pizza_id = atof(token);

        token = strtok(NULL, ",");
        order->order_id = atof(token);

        token = strtok(NULL, ",");
        strncpy(order->pizza_name_id, token, MAX_STR_LEN);

        token = strtok(NULL, ",");
        order->quantity = atoi(token);

        token = strtok(NULL, ",");
        strncpy(order->order_date, token, MAX_STR_LEN);

        token = strtok(NULL, ",");
        strncpy(order->order_time, token, MAX_STR_LEN);

        token = strtok(NULL, ",");
        order->unit_price = atof(token);

        token = strtok(NULL, ",");
        order->total_price = atof(token);

        token = strtok(NULL, ",");
        strncpy(order->pizza_size, token, MAX_STR_LEN);

        token = strtok(NULL, ",");
        strncpy(order->pizza_category, token, MAX_STR_LEN);

        token = strtok(NULL, ",");
        // Este campo puede estar entre comillas si contiene comas
        strncpy(order->pizza_ingredients, token, MAX_STR_LEN);

        token = strtok(NULL, "\n");
        if (token) {
            strncpy(order->pizza_name, token, MAX_STR_LEN);
        } else {
            order->pizza_name[0] = '\0';
        }
        count++;
    }
    fclose(fp);
    return count;
}
