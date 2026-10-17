#ifndef QUEUE_H
#define QUEUE_H

// 맨날 하는거
typedef struct queue    queue;
typedef void*           queueitem;

struct queue {
    queueitem*  items;
    int         front;
    int         rear;
    int         max_size;
};

// 외부 함수
queue* queue_create_queue(int max_size);
void queue_delete_queue(queue* queue);
void queue_enqueue(queue* queue, queueitem item);
queueitem queue_dequeue(queue* queue);
int queue_is_empty(queue* queue);
int queue_is_full(queue* queue);

#endif