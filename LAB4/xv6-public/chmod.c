#include "types.h"
#include "user.h"
#include "stat.h"

int
main(int argc, char *argv[])
{
	if(argc < 3) exit();
	char *path = argv[2];
	int perm = atoi(argv[1]);
	 if(perm >= 0 && perm < 8)
		chmod(path, perm);
	else
		printf(1,"Second argument must be between 0 and 7\n");
	exit();
}
