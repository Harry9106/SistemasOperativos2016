#define MAX_SEMA 4

struct semaphore {
	int active;
	int value;
	struct spinlock lock;
};

struct semaphore sema[MAX_SEMA];
