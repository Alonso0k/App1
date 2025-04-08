#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "order.h"

#define INITIAL_SIZE 100

// Función auxiliar para parsear un campo CSV.
// Se encarga de copiar en dest el contenido del campo, manejando correctamente las comillas.
static void parse_field(char **p, char *dest) {
    int i = 0;
    // Si el campo está entrecomillado
    if (**p == '"') {
        (*p)++; // Saltar la comilla inicial
        while (**p && **p != '"' && i < MAX_STR_LEN - 1) {
            dest[i++] = **p;
            (*p)++;
        }
        dest[i] = '\0';
        if (**p == '"') {
            (*p)++; // Saltar la comilla final
        }
        if (**p == ',') {
            (*p)++; // Saltar la coma separadora
        }
    } else {
        // Si el campo no está entrecomillado, copiar hasta la coma o fin de línea.
        while (**p && **p != ',' && **p != '\n' && i < MAX_STR_LEN - 1) {
            dest[i++] = **p;
            (*p)++;
        }
        dest[i] = '\0';
        if (**p == ',') {
            (*p)++; // Saltar la coma
        }
    }
}

int load_orders(const char *filename, Order **orders) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error al abrir el archivo");
        return 0;
    }

    // Se ignora la primera línea (cabecera)
    char line[1024];
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return 0;
    }

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
        char *p = line;
        char token[MAX_STR_LEN];

        parse_field(&p, token);
        order->pizza_id = atof(token);

        parse_field(&p, token);
        order->order_id = atof(token);

        parse_field(&p, order->pizza_name_id);

        parse_field(&p, token);
        order->quantity = atoi(token);

        parse_field(&p, order->order_date);

        parse_field(&p, order->order_time);

        parse_field(&p, token);
        order->unit_price = atof(token);

        parse_field(&p, token);
        order->total_price = atof(token);

        parse_field(&p, order->pizza_size);

        parse_field(&p, order->pizza_category);

        parse_field(&p, order->pizza_ingredients);

        parse_field(&p, order->pizza_name);

        count++;
    }
    fclose(fp);
    return count;
}
