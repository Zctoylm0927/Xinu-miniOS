/* clkinit.c - clkinit (x86) */

#include <xinu.h>

uint32	clktime;		/* Seconds since boot			*/
uint32	count1000;		/* Milliseconds since last clock tick   */
qid16	sleepq;			/* Queue of sleeping processes		*/
uint32	preempt;		/* Preemption counter			*/

/*------------------------------------------------------------------------
 * clkinit  -  Initialize the clock and sleep queue at startup (x86)
 *------------------------------------------------------------------------
 */
void	clkinit(void)
{
	uint16	intv;		/* Clock rate in KHz			*/
	/* Allocate a queue to hold the delta list of sleeping processes*/

	sleepq = newqueue();
	/* Initialize the preemption count */

	preempt = QUANTUM;

	/* Initialize the time since boot to zero */

	clktime = 0;
        count1000 = 0;
	/* Set interrupt vector for the clock to invoke clkdisp */
	//Lab3 2020200671
	set_evec(IRQBASE, (uint32)clkdisp, 0);

	outb(CLKCNTL, 0x34);

	/* Set the clock rate to 1.190 Mhz; this is 1 ms interrupt rate */

	intv = 1193;	/* Using 1193 instead of 1190 to fix clock skew	*/

	/* Must write LSB first, then MSB */

	outb(CLOCK0, (char) (0xff & intv) );
	outb(CLOCK0, (char) (0xff & (intv>>8)));

	return;
}
