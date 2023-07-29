/* Lab5_kbdinit.c - kbdinit */

#include <xinu.h>

struct	kbdcblk	kbdcb;

devcall	kbdinit()
{
	set_evec(0x21, (uint32)kbddisp, 0);

	kbdcb.tyihead = kbdcb.tyitail = kbdcb.tyibuff;
	kbdcb.tyisem = semcreate(0);
	kbdcb.tyicursor = 0;

	vgainit();
}