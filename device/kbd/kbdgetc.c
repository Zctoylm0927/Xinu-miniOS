/* Lab5_kbdgetc.c - kbdgetc */

#include <xinu.h>

devcall	kbdgetc(struct dentry *devptr)
{
	/* Wait for a character in the buffer and extract one character	*/
	wait(kbdcb.tyisem);
	char ch = *kbdcb.tyihead++;
	/* Wrap around to beginning of buffer, if needed */
	if (kbdcb.tyihead >= &kbdcb.tyibuff[TY_IBUFLEN]) {
		kbdcb.tyihead = kbdcb.tyibuff;
	}
	return (devcall)ch;
}