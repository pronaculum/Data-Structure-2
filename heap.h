#ifndef HEAP_H
#define HEAP_H

#define ENOMEM 12
#define EINVAL 22
#define ERANGE 34

// 맨날 하는거
typedef struct heap     heap;
typedef int             heapitem;
typedef enum {
    MIN_HEAP,
    MAX_HEAP
}heap_type;

struct heap {
    heapitem*   items;
    int         max_size;
    int         cur_size;
    heap_type   type;
};

// 외부 함수
int heap_create_heap(heap** h, int max_size, heap_type type);
int heap_delete_heap(heap* h);
int heap_push(heap* h, heapitem* weight, heapitem* item);
int heap_pop(heap* h, heapitem* weight, heapitem* item);
int heap_peek(heap* h, heapitem* weight, heapitem* item);
#endif