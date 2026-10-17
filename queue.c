#include <stdio.h>
#include <stdlib.h>

#pragma region 맨날_하는거
// 맨날 하는거
typedef struct queue    queue;
typedef void*           queueitem;

struct queue {
    queueitem*  items;
    int         front;
    int         rear;
    int         max_size;
};
#pragma endregion

#pragma region 외부_함수
// 외부 함수
queue* queue_create_queue(int max_size) {
    queue* q = (queue*)malloc(sizeof(queue));
    if (q == NULL) return NULL;
    q->items = (queueitem*)malloc(sizeof(queueitem)*max_size);
    if (q->items == NULL) {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    q->max_size = max_size;
    return q;
}

void queue_delete_queue(queue* q) {
    if (q == NULL) return;
    free(q->items);
    free(q);
}

int queue_is_empty(queue* q) {
    return q->front == q->rear;
}

int queue_is_full(queue* q) {
    return (q->rear + 1) % q->max_size == q->front;
}

void queue_enqueue(queue* q, queueitem item) {
    if (q == NULL || q->items == NULL || queue_is_full(q)) return;
    q->rear = (q->rear + 1) % q->max_size;
    q->items[q->rear] = item;
}

queueitem queue_dequeue(queue* q) {
    if (q == NULL || q->items == NULL || queue_is_empty(q)) return NULL;
    q->front = (q->front + 1) % q->max_size;
    queueitem item = q->items[q->front];
    return item;
}

queueitem queue_peek(queue* q) {
    if (q == NULL || q->items == NULL || queue_is_empty(q)) return NULL;
    return q->items[(q->front + 1) % q->max_size];
}
#pragma endregion