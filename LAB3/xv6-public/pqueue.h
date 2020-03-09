#include "param.h"
#include "cbuffer.h"

// Process queue.
struct pqueue {
  struct proc * array[NPROC];       // Where pointers to process are stored.
  struct cbuffer wrapper;			// Wrapper to make a circular buffer from an array.
  int tickets;						// Timeslices given per process.
};

void pqueue_init(struct pqueue * pq, int tickets);

int pqueue_is_full(const struct pqueue * pq);

int pqueue_is_empty(const struct pqueue * pq);

void pqueue_write(struct pqueue * pq, struct proc ** elem);

void pqueue_read(struct pqueue * pq, struct proc ** elem);