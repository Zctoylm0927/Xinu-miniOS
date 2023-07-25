/* create.c - create, newpid */

#include <xinu.h>

local	int newpid();

/*------------------------------------------------------------------------
 *  create  -  Create a process to start running a function on x86
 *------------------------------------------------------------------------
 */
pid32	create(
	  void		*funcaddr,	/* Address of the function	*/
	  uint32	ssize,		/* Stack size in bytes		*/
	  pri16		priority,	/* Process priority > 0		*/
	  char		*name,		/* Name (for debugging)		*/
	  uint32	nargs,		/* Number of args that follow	*/
	  ...
	)
{
	uint32		savsp, *pushsp;
	intmask 	mask;    	/* Interrupt mask		*/
	pid32		pid;		/* Stores new process id	*/
	struct	procent	*prptr;		/* Pointer to proc. table entry */
	int32		i;
	uint32		*a;		/* Points to list of args	*/
	uint32		*ksaddr;		/* Kernel Stack address		*/
	uint32		*usaddr;		/* User Stack address		*/

	mask = disable();
	if (ssize < MINSTK)
		ssize = MINSTK;
	/*Lab4 2020200671:Begin*/
	ssize = roundpg(ssize);
	if ( (priority < 1) || ((pid=newpid()) == SYSERR) ) {
		restore(mask);
		return SYSERR;
	}
	struct pgtab *newpgdir = (struct pgtab *)getmem(PAGE_SIZE);
	if(newpgdir == (struct pgtab *)SYSERR) {
		restore(mask);
		return SYSERR;
	}
	memset((void *)newpgdir, 0, PAGE_SIZE);

	struct pgtab *newpt0, *oldpt0, *newptx;
	newpt0 = (struct pgtab *)getmem(PAGE_SIZE);
	if(newpt0 == (struct pgtab *)SYSERR) {
		freemem((char *)newpgdir, PAGE_SIZE);
		restore(mask);
		return SYSERR;
	}
	oldpt0 = (struct pgtab *)0x800000;
	for(i = 0; i < PT_NENTRY; ++ i)
		newpt0->entry[i] = oldpt0->entry[i];
	newptx = (struct pgtab *)getmem(PAGE_SIZE);
	if(newptx == (struct pgtab *)SYSERR) {
		freemem((char *)newpgdir, PAGE_SIZE);
		freemem((char *)newpt0, PAGE_SIZE);
		restore(mask);
		return SYSERR;
	}
	memset((void *)newptx, 0, PAGE_SIZE);
	newpgdir->entry[0] = log2ph((char *)newpt0) | PT_ENTRY_P | PT_ENTRY_W | PT_ENTRY_U;
	newpgdir->entry[1] = pgdir->entry[1];
	newpgdir->entry[2] = log2ph((char *)newpgdir) | PT_ENTRY_P | PT_ENTRY_W | PT_ENTRY_U;
	newpgdir->entry[1015] = log2ph((char *)newptx) | PT_ENTRY_P | PT_ENTRY_W | PT_ENTRY_U;


	ksaddr = (uint32 *)getstk(KERNELSTK, newpt0, TRUE);
	if(ksaddr == (uint32 *)SYSERR) {
		freemem((char *)newpgdir, PAGE_SIZE);
		freemem((char *)newpt0, PAGE_SIZE);
		freemem((char *)newptx, PAGE_SIZE);
		restore(mask);
		return SYSERR;
	}
	usaddr = (uint32 *)getstk(ssize, newptx, FALSE);
	if(usaddr == (uint32 *)SYSERR) {
		freemem((char *)newpgdir, PAGE_SIZE);
		freemem((char *)newpt0, PAGE_SIZE);
		freemem((char *)newptx, PAGE_SIZE);
		freestk((char *)ksaddr, KERNELSTK);
		restore(mask);
		return SYSERR;
	}
	/*Lab4 2020200671:End*/

	prcount++;
	prptr = &proctab[pid];

	/* Initialize process table entry for new process */
	prptr->prstate = PR_SUSP;	/* Initial state is suspended	*/
	prptr->prprio = priority;
	//Lab4 2020200671
	prptr->kstkbase = (char *)ksaddr;
	prptr->userstkbase = (char *)usaddr;
	prptr->prpgdir = log2ph((char *)newpgdir);
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=name[i])!=NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE;

	/* Set up stdin, stdout, and stderr descriptors for the shell	*/
	prptr->prdesc[0] = CONSOLE;
	prptr->prdesc[1] = CONSOLE;
	prptr->prdesc[2] = CONSOLE;

	/* Initialize user stack*/
	*usaddr = STACKMAGIC;
	/* Push arguments */
	a = (uint32 *)(&nargs + 1);	/* Start of args		*/
	a += nargs -1;			/* Last argument		*/
	for (i = nargs ; i > 0 ; i--)	/* Machine dependent; copy args	*/
		*--usaddr = *a--;	/* onto created process's stack	*/
	*--usaddr = (long)INITRET;	/* Push on return address	*/
	usaddr = (uint32 *)(USTKBASE - ((uint32)prptr->userstkbase - (uint32)usaddr));

	/* Initialize kernel stack*/
	*ksaddr = STACKMAGIC;
	savsp = (KSTKBASE - ((uint32)prptr->kstkbase - (uint32)(ksaddr)));
	/* Push arguments */
	a = (uint32 *)(&nargs + 1);	/* Start of args		*/
	a += nargs -1;			/* Last argument		*/
	for (i = nargs ; i > 0 ; i--)	/* Machine dependent; copy args	*/
		*--ksaddr = *a--;	/* onto created process's stack	*/
	*--ksaddr = (uint32)INITRET;	/* Push on return address	*/
	//Lab3 2020200671
	//TSS.ss0 = (0x3 << 3);
	//TSS.esp0 = (long) ksaddr;
	prptr->prkstp = (char *)(KSTKBASE - ((uint32)prptr->kstkbase - (uint32)(ksaddr)));

	*--ksaddr = BASE_USER_SS;	//SS
	*--ksaddr = (uint32)usaddr;	/*	ESP		*/
	*--ksaddr = 0x00000200;	/*	EFLAGS		*/
	*--ksaddr = BASE_USER_CS;	//CS
	*--ksaddr = (uint32)funcaddr;
	*--ksaddr = BASE_USER_DS;	//DS


	/* The following entries on the stack must match what ctxsw	*/
	/*   expects a saved process state to contain: ret address,	*/
	/*   ebp, interrupt mask, flags, registers, and an old SP	*/

	*--ksaddr = (uint32)k2020200671_ret_k2u;
	*--ksaddr = savsp;		/* This will be register ebp	*/
					/*   for process exit		*/
	savsp = (KSTKBASE - ((uint32)prptr->kstkbase - (uint32)(ksaddr)));		/* Start of frame for ctxsw	*/
	*--ksaddr = 0x00000200;		/* New process runs with	*/
					/*   interrupts enabled		*/

	/* Basically, the following emulates an x86 "pushal" instruction*/

	*--ksaddr = 0;			/* %eax */
	*--ksaddr = 0;			/* %ecx */
	*--ksaddr = 0;			/* %edx */
	*--ksaddr = 0;			/* %ebx */
	*--ksaddr = 0;			/* %esp; value filled in below	*/
	pushsp = ksaddr;			/* Remember this location	*/
	*--ksaddr = savsp;		/* %ebp (while finishing ctxsw)	*/
	*--ksaddr = 0;			/* %esi */
	*--ksaddr = 0;			/* %edi */

	/*Lab4 2020200671:Begin*/
	prptr->prstkptr = (char *)(KSTKBASE - ((uint32)prptr->kstkbase - (uint32)(ksaddr)));
	*pushsp = (uint32)prptr->prstkptr;

	fill_pgentry((char *)newpgdir, 0, 0, TRUE);
	invlpg((void *)newpgdir);
	fill_pgentry((char *)newpt0, 0, 0, TRUE);
	invlpg((void *)newpt0);
	fill_pgentry((char *)newptx, 0, 0, TRUE);
	invlpg((void *)newptx);

	//lab4 need to do
	for (i = 0; i < KERNELSTK; i += PAGE_SIZE) {
		kprintf("Alloc kerpage page at 0x%x\n", prptr->kstkbase + i);
		fill_pgentry(prptr->kstkbase + i, 0, 0, TRUE);
		invlpg((void *)(prptr->kstkbase + i));
	}
	for (i = 0; i < ssize; i += PAGE_SIZE) {
		kprintf("Alloc user page at 0x%x\n", prptr->userstkbase + i);
		fill_pgentry(prptr->userstkbase + i, 0, 0, TRUE);
		invlpg((void *)(prptr->userstkbase + i));
	}
	prptr->kstkbase = (char *)KSTKBASE;
	prptr->userstkbase = (char *)USTKBASE;
	/*Lab4 2020200671:End*/
	restore(mask);
	return pid;
}

/*------------------------------------------------------------------------
 *  newpid  -  Obtain a new (free) process ID
 *------------------------------------------------------------------------
 */
local	pid32	newpid(void)
{
	uint32	i;			/* Iterate through all processes*/
	static	pid32 nextpid = 1;	/* Position in table to try or	*/
					/*   one beyond end of table	*/

	/* Check all NPROC slots */

	for (i = 0; i < NPROC; i++) {
		nextpid %= NPROC;	/* Wrap around to beginning */
		if (proctab[nextpid].prstate == PR_FREE) {
			return nextpid++;
		} else {
			nextpid++;
		}
	}kprintf("newpid error\n");
	return (pid32) SYSERR;
}
