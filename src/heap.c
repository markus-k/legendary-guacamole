#include "heap.h"
#include "pmm.h"

struct heap_block {
  struct heap_block *next;

  size_t len;
};

struct heap_header {
  struct heap_block first_block;
};

void heap_init() {
}

void *kalloc(size_t len) {
  return NULL;
}

void kfree(void *ptr) {
}
