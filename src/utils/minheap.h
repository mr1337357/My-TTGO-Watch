#include <stdint.h>

struct minheap_s
{
    int size;
    int count;
    void **elem;
    uint64_t *prio;
};

typedef struct minheap_s minheap;

int minheap_init(minheap *mh, int size);
void *minheap_pop(minheap *mh);
int minheap_push(minheap *mh, uint64_t prio, void *elem);
uint64_t minheap_peek_prio(minheap *mh);