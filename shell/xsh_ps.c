/* xsh_ps.c - xsh_ps */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_ps - shell command to print the process table
 *------------------------------------------------------------------------
 */
/*Lab4 2020200671:Begin*/
shellcmd xsh_ps(int nargs, char *args[])
{
	struct	procent	*prptr;		/* pointer to process		*/
	int32	i;			/* index into proctabl		*/
	char *pstate[]	= {		/* names for process states	*/
		"free ", "curr ", "ready", "recv ", "sleep", "susp ",
		"wait ", "rtime"};

	/* For argument '--help', emit help about the 'ps' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		u2020200671_syscall_printf("Use: %s\n\n", args[0]);
		u2020200671_syscall_printf("Description:\n");
		u2020200671_syscall_printf("\tDisplays information about running processes\n");
		u2020200671_syscall_printf("Options:\n");
		u2020200671_syscall_printf("\t--help\t display this help and exit\n");
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1) {
		u2020200671_syscall_fprintf(stderr, "%s: too many arguments\n", args[0]);
		u2020200671_syscall_fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	/* Print header for items from the process table */
	/* Lab5 2020200671:Begin*/
	// u2020200671_syscall_printf("%3s %-16s %5s %4s %4s %15s %17s %-10s %10s\n",
	// 	   "Pid", "Name", "State", "Prio", "Ppid", "User Stack Base",
	// 	   "Kernel Stack Base", "Stack Ptr", "Stack Size");

	// u2020200671_syscall_printf("%3s %-16s %5s %4s %4s %15s %17s %-10s %10s\n",
	// 	   "---", "----------------", "-----", "----", "----",
	// 	   "---------------", "-----------------", "----------", 
	// 	   "----------");
	
	u2020200671_syscall_printf("%3s %-16s %5s %4s %4s %-10s\n",
		   "Pid", "Name", "State", "Prio", "Ppid", "Stack Ptr");

	u2020200671_syscall_printf("%3s %-16s %5s %4s %4s %-10s\n",
		   "---", "----------------", "-----", "----", "----", "----------");
	/* Lab5 2020200671:End*/

	/* Output information for each process */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		if (prptr->prstate == PR_FREE) {  /* skip unused slots	*/
			continue;
		}
		/* Lab5 2020200671:Begin*/
		// u2020200671_syscall_printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X 0x%08X %8d\n",
		// 	i, prptr->prname, pstate[(int)prptr->prstate],
		// 	prptr->prprio, prptr->prparent, prptr->userstkbase,
		// 	prptr->kstkbase, prptr->prstkptr, prptr->prstklen);
		u2020200671_syscall_printf("%3d %-16s %s %4d %4d 0x%08X\n",
			i, prptr->prname, pstate[(int)prptr->prstate],
			prptr->prprio, prptr->prparent, prptr->prstkptr);
		/* Lab5 2020200671:End*/
	}
	return 0;
}
/*Lab4 2020200671:End*/