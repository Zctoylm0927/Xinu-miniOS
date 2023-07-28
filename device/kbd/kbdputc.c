/* Lab5 kbdputc.c - kbdputc */

#include <xinu.h>

devcall	kbdputc(struct dentry *devptr,char ch)
{
    if (ch == TY_NEWLINE) kbdputc(devptr, TY_RETURN);
	vgaputc(ch, FALSE);
	return OK;
}