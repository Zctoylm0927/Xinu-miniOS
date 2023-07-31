#include <kbd.h>

struct	kbdcblk {
	char	*tyihead;		/* Next input char to read	*/
	char	*tyitail;		/* Next slot for arriving char	*/
	char	tyibuff[TY_IBUFLEN];	/* Input buffer			*/
	sid32	tyisem;			/* Input semaphore		*/
	int32	tyicursor;		/* Current cursor position	*/
};

extern	struct	kbdcblk	kbdcb;

extern	uint8	normalmap[256];
extern	uint8	shiftcode[256];
extern	uint8	togglecode[256];
extern	uint8	shiftmap[256];
extern	uint8	ctlmap[256];

/* in file kbdcontrol.c */
extern	void	vgainit(void);
extern  devcall vgaputc(char ch, bool8);
extern	devcall	vgaerase(bool8);

/* in file kbddisp.S */
extern	interrupt	kbddisp(void);

/* in file kbdread.c */
extern	devcall	kbdread(struct dentry *, char *, int32);

/* in file kbdgetc.c */
extern	devcall	kbdgetc(struct dentry *);

/* in file kbdputc.c */
extern	devcall	kbdputc(struct dentry *, char);

/* in file kbdhandler.c */
extern	void	kbdhandler(void);

/* in file kbdinit.c */
extern	devcall	kbdinit(void);