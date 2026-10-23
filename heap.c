#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#pragma region 내부_함수
int heap_is_empty(heap* h) { return h->cur_size == 0; }
int heap_is_full(heap* h) { return h->cur_size == h->max_size; }
void heap_bottom_up(heap* h) {
    if (h->cur_size < 2) return;
    int cur = h->cur_size-1;
    int par = (h->cur_size - 2) / 2;
    int tmp;
    int* items = h->items;
    if(!h->type) { while (par >= 0) { //MIN_HEAP
        if (items[par*2] > items[cur*2]) {
            tmp = items[cur*2];
            items[cur*2] = items[par*2];
            items[par*2] = tmp;
            tmp = items[cur*2+1];
            items[cur*2+1] = items[par*2+1];
            items[par*2+1] = tmp;
        }
        else break;
        cur = par;
        par = (cur - 1) / 2;
    }}
    else { while (par >= 0) { //MAX_HEAP
        if (items[par*2] < items[cur*2]) {
            tmp = items[cur*2];
            items[cur*2] = items[par*2];
            items[par*2] = tmp;
            tmp = items[cur*2+1];
            items[cur*2+1] = items[par*2+1];
            items[par*2+1] = tmp;
        }
        else break;
        cur = par;
        par = (cur - 1) / 2;
    }}
}
void heap_top_down(heap* h) {
    int boundary = h->cur_size-1;
    int cur = 0, change = 0, left, right, tmp;
    int* items = h->items;
    tmp = items[cur*2];
    items[cur*2] = items[boundary*2];
    items[boundary*2] = tmp;
    tmp = items[cur*2+1];
    items[cur*2+1] = items[boundary*2+1];
    items[boundary*2+1] = tmp;
    if(!h->type) { while (1) { //MIN_HEAP
        cur = change; left = cur*2+1; right = cur*2+2;
        if (left < boundary && items[cur*2] > items[left*2]) {
            change = left;
        }
        if (right < boundary && items[cur*2] > items[right*2]) {
            if (cur == change) change = right;
            else if (items[left*2] > items[right*2]) change = right;
        }
        if (cur == change) break;
        tmp = items[cur*2];
        items[cur*2] = items[change*2];
        items[change*2] = tmp;
        tmp = items[cur*2+1];
        items[cur*2+1] = items[change*2+1];
        items[change*2+1] = tmp;
    }}
    else { while (1) { //MIN_HEAP
        cur = change; left = cur*2+1; right = cur*2+2;
        if (left < boundary && items[cur*2] < items[left*2]) {
            change = left;
        }
        if (right < boundary && items[cur*2] < items[right*2]) {
            if (cur == change) change = right;
            else if (items[left*2] < items[right*2]) change = right;
        }
        if (cur == change) break;
        tmp = items[cur*2];
        items[cur*2] = items[change*2];
        items[change*2] = tmp;
        tmp = items[cur*2+1];
        items[cur*2+1] = items[change*2+1];
        items[change*2+1] = tmp;
    }}
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
int heap_create_heap(heap** h, int max_size, heap_type type) {
    *h = (heap*)malloc(sizeof(heap));
    if (*h == NULL) return ENOMEM;
    (*h)->items = (int*)malloc(sizeof(int)*max_size*2);
    if ((*h)->items == NULL) {
        free(*h);
        return ENOMEM;
    }
    (*h)->max_size = max_size;
    (*h)->cur_size = 0;
    (*h)->type = type;
    return EXIT_SUCCESS;
}
int heap_delete_heap(heap* h) {
    if (h == NULL)          return EINVAL;
    free(h->items);free(h); return EXIT_SUCCESS;
}

int heap_push(heap* h, heapitem* weight, heapitem* item) {
    if (h == NULL)          return EINVAL;
    if (heap_is_full(h))    return ERANGE;
    h->items[h->cur_size*2] = *weight;
    h->items[h->cur_size*2+1] = *item;
    h->cur_size++;
    heap_bottom_up(h);
    return EXIT_SUCCESS;
}
int heap_pop(heap* h, heapitem* weight, heapitem* item) {
    if (h == NULL)          return EINVAL;
    if (heap_is_empty(h))   return ERANGE;
    heap_top_down(h);
    h->cur_size--;
    *weight = h->items[h->cur_size*2];
    *item = h->items[h->cur_size*2+1];
    return EXIT_SUCCESS;
}
int heap_peek(heap* h, heapitem* weight, heapitem* item) {
        if (h == NULL)      return EINVAL;
    if (heap_is_empty(h))   return ERANGE;
    *weight = h->items[0];
    *item = h->items[1];
    return EXIT_SUCCESS;
}

#pragma endregion