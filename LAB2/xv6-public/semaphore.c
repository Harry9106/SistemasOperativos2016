#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "semaphore.h"

int
sem_init(int sem, int value)
{
	if(sema[sem].active != 0)
		return -1;
	acquire(&sema[sem].lock);
	sema[sem].active = 1;
	if(value >= 0)
	  sema[sem].value = value;
	release(&sema[sem].lock);
  	return 0;
}

int
sem_release(int sem)
{
	acquire(&sema[sem].lock);
	sema[sem].active = 0;
	release(&sema[sem].lock);
	return 0;
}

int
sem_up(int sem)
{
	if(sema[sem].active == 0)
		return -1;
	acquire(&sema[sem].lock);
	sema[sem].value = sema[sem].value + 1;
	if(sema[sem].value > 0)
		wakeup(&sema[sem]);
	release(&sema[sem].lock);
	return 0;
}

int
sem_down(int sem)
{
	if(sema[sem].active == 0)
		return -1;
	acquire(&sema[sem].lock);
	while(sema[sem].value < 1)
		sleep(&sema[sem], &sema[sem].lock);
	sema[sem].value = sema[sem].value - 1;
	release(&sema[sem].lock);

  return 0;
}
