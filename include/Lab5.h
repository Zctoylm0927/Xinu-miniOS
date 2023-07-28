#define	KBSTATP		0x64    // kbd controller status port(I)
#define	KBS_DIB		0x01    // kbd data in buffer
#define	KBDATAP		0x60    // kbd data port(I)
#define	E0ESC		(1<<6)

#define	NO		0

//same as the shiftcode[256]
#define	SHIFT	(1<<0)
#define	CTL		(1<<1)
#define	ALT		(1<<2)

#define	CAPSLOCK	(1<<3)
#define	NUMLOCK		(1<<4)
#define	SCROLLLOCK	(1<<5)

// Special keycodes
#define	KEY_HOME	0xE0
#define	KEY_END		0xE1
#define	KEY_UP		0xE2
#define	KEY_DN		0xE3
#define	KEY_LF		0xE4
#define	KEY_RT		0xE5
#define	KEY_PGUP	0xE6
#define	KEY_PGDN	0xE7
#define	KEY_INS		0xE8
#define	KEY_DEL		0xE9

// C('A') == Control-A
#define	C(x)		(x - '@')

#define	TAB_WIDTH	8

/* Characters with meaning to the kbd driver */

#define	TY_TAB		'\t'		/* Tab				*/
#define	TY_ESC		'\033'		/* Escape			*/

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