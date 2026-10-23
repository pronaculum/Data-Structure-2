#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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

void queue_delete_queue(queue* queue) {
    if (queue == NULL) return;
    free(queue->items);
    free(queue);
}

int queue_is_empty(queue* queue) {
    return queue->front == queue->rear;
}

int queue_is_full(queue* queue) {
    return (queue->rear + 1) % queue->max_size == queue->front;
}

void queue_enqueue(queue* queue, queueitem item) {
    if (queue == NULL || queue->items == NULL || queue_is_full(queue)) return;
    queue->rear = (queue->rear + 1) % queue->max_size;
    queue->items[queue->rear] = item;
}

queueitem queue_dequeue(queue* queue) {
    if (queue == NULL || queue->items == NULL || queue_is_empty(queue)) return NULL;
    queue->front = (queue->front + 1) % queue->max_size;
    queueitem item = queue->items[queue->front];
    return item;
}

queueitem queue_peek(queue* queue) {
    if (queue == NULL || queue->items == NULL || queue_is_empty(queue)) return NULL;
    return queue->items[(queue->front + 1) % queue->max_size];
}
#pragma endregion