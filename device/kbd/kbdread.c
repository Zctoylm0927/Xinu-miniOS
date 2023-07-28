/* Lab5 kbdread.c - kbdread */

#include <xinu.h>

devcall	kbdread(struct dentry *devptr,char *buff,int32 count)
{
	if (count < 0) {
		return SYSERR;
	}

	/* Block until input arrives */
	int firstch = kbdgetc(devptr);
	if (firstch == EOF) {
		return EOF;
	}
	/* Read up to a line */
	char ch = (char) firstch;
	*buff++ = ch;
	int nread = 1;
	while ((nread < count) && ch != TY_NEWLINE && ch != TY_RETURN) {
		ch = kbdgetc(devptr);
		*buff++ = ch;
		nread++;
	}
	return nread;
}