/*  main.c  - main */

#include <xinu.h>

void sndA() {
	while(1) {
		putc(CONSOLE, 'A');
	}
}

void sndB() {
	while(1) {
		putc(CONSOLE, 'B');
	}
}

process	main(void)
{

	/* Run the Xinu shell */

	/*Lab4 2020200671:Begin*/
	u2020200671_syscall_recvclr();
	u2020200671_syscall_resume(u2020200671_syscall_create(shell, 8192, 50, "shell", 1, CONSOLE));

	//resume(create(sndA, 4096, 20, "processA", 1, CONSOLE));
	//resume(create(sndB, 4096, 20, "processB", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		u2020200671_syscall_receive();
		u2020200671_syscall_sleepms(200);
		u2020200671_syscall_printf("\n\nMain process recreating shell\n\n");
		u2020200671_syscall_resume(u2020200671_syscall_create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	/*Lab4 2020200671:End*/
	return OK;
    
}
