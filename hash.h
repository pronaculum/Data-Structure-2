#include "list.h"

#ifndef HASH_H
#define HASH_H

// 맨날 하는거
typedef struct hash         hash;
typedef struct hashnode     hashnode;
typedef struct context      context;

typedef void*   hashdata;
typedef void*   hashkey;

typedef enum {
    STRING,
    UNSIGNEDINT
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

// 내부 함수
int hash_function(hashkey key, int length);
int hash_is_equal(hashtype type, hashkey key1, hashkey key2);
int hash_condSTR(void* context, listdata listdata);
int hash_condUINT(void* context, listdata listdata);
hashnode* hash_create_hashbucket(hashdata item, hashkey key);

//외부 함수
hash* hash_create_hash(int length, hashtype type);
void hash_push(hash* hash, hashdata item, hashkey key);
hashnode* hash_pop(hash* hash, hashkey key);
hashnode* hash_peek(hash* hash, hashkey key);
#endif