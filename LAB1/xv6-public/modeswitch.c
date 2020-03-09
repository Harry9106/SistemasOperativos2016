#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char **argv)
{
	int mode;
    if(*argv[1] == '1' || *argv[1] == '0')
    {
    	if(*argv[1] == '1')
    	{
    		mode = 1;
    	}
    	else
    	{
    		mode = 0;
    	}
	modeswitch(mode);
	}
 	exit();
}
