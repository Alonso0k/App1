#ifndef ORDER_H
#define ORDER_H

#define MAX_STR_LEN 256

typedef struct {
    float pizza_id;
    float order_id;
    char pizza_name_id[MAX_STR_LEN];
    int quantity;
    char order_date[MAX_STR_LEN];
    char order_time[MAX_STR_LEN];
    float unit_price;
    float total_price;
    char pizza_size[MAX_STR_LEN];
    char pizza_category[MAX_STR_LEN];
    char pizza_ingredients[MAX_STR_LEN];
    char pizza_name[MAX_STR_LEN];
} Order;

#endif
