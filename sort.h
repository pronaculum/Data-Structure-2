#ifndef SORT_H
#define SORT_H

// 맨날 하는거
typedef enum {
    ARRAY_INT,
    DUAL_ARRAY_INT,
    STACK,
    QUEUE,
    LIST
} sort_base_type;
typedef enum {
    MERGE
} sort_sorting_type;
typedef enum {
    HIGH,
    LOW
} sort_order_type;

// 외부 함수
int sort_Merge(void* base, int length, sort_base_type base_type, sort_order_type order_type);
void sort_print(void* array, int length, sort_sorting_type sorting_type, sort_order_type order_type);
#endif