#include "list.h"

#ifndef HASH_H
#define HASH_H

// 맨날 하는거
#define GOLD 0.6180339887
typedef struct hash         hash;
typedef struct hashnode     hashnode;
typedef struct context      context;

typedef void*   hashdata;
typedef void*   hashkey;

typedef enum {
    STRING,
    UNSIGNEDINT,
    INDEX
} hashtype;
struct hashnode {
    hashdata    item;
    hashkey     key;
};
struct hash {
    list**      buckets;
    int         length;
    int         count;
    hashtype    type;
};

//외부 함수
hash* hash_create_hash(int length, hashtype type);
void hash_push(hash* hash, hashdata item, hashkey key);
void hash_push_hard(hash* hash, hashdata item, hashkey key);
hashnode* hash_pop(hash* hash, hashkey key);
hashnode* hash_peek(hash* hash, hashkey key);
list* hash_peek_bucket_item(hash* hash, hashkey key);
void hash_print_node(hashnode* node, void(*print)(void*));
#endif