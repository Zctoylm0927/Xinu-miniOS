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

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	//resume(create(sndA, 4096, 20, "processA", 1, CONSOLE));
	//resume(create(sndB, 4096, 20, "processB", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
