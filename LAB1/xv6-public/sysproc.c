#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_modeswitch(void)
{	
	int mode;
	argint(0, &mode);
	
	if(mode > 0)
	{
        set_graphical_mode();
        int height = 200;
        int width = 320;
    	uchar *vga = (uchar*)P2V(0xA0000);
    	int i;
    	for(i=0;i<height*width;i++)
    	   vga[i]=0x36;	
    }
	else
	{
		set_text_mode();
        uchar *vga = (uchar*)P2V(0xb8000);
        int offset, orange, j;
    
        offset = 160*24 + 148;
        orange = 0x36;
        vga[offset] = 0x53;
        vga[offset+2] = 0x4F;
        vga[offset+4] = 0x32;
        vga[offset+6] = 0x30;
        vga[offset+8] = 0x31;
        vga[offset+10] = 0x36;
        for(j = 0; j < 6; j++)
          vga[offset+(2*j+1)] = orange;
	}
	return 0;
}

int
sys_plotpixel(void)
{
	int x,y,colour;
	argint(0, &x);
	argint(1, &y);
	argint(2, &colour);

	uchar *vga = (uchar*)P2V(0xA0000);

	vga[320*y+x]=colour;
	
	return 0;
}
