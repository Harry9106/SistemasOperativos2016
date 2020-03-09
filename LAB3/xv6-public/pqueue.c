#include "types.h"
#include "defs.h"
#include "pqueue.h"

void pqueue_init(struct pqueue * pq, int tickets)
{
	cbuffer_init(&pq->wrapper,NPROC,sizeof (struct proc*),pq->array);
	pq->tickets = tickets;
}

int pqueue_is_full(const struct pqueue * pq)
{
	return cbuffer_is_full(&pq->wrapper);
}


int pqueue_is_empty(const struct pqueue * pq)
{
	return cbuffer_is_empty(&pq->wrapper);
}


void pqueue_write(struct pqueue * pq, struct proc ** elem)
{
	cbuffer_write(&pq->wrapper, elem);
}

void pqueue_read(struct pqueue * pq, struct proc ** elem)
{
	cbuffer_read(&pq->wrapper, elem);
}