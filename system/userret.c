/* userret.c - userret */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  userret  -  Called when a process returns from the top-level function
 *------------------------------------------------------------------------
 */
void	userret(void)
{
	//Lab4 2020200671
	u2020200671_syscall_kill(u2020200671_syscall_getpid());
}
