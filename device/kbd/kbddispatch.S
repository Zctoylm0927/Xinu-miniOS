/* Lab5 kbddispatch.S - kbddispatch */

#include <icu.s>

		.text
		.globl  kbddispatch	
		.globl	kbdhandler

kbddispatch:
		pushal			/* Save general-purpose regs.	*/
		pushfl			/* Save the flags register	*/
		cli			/* Prevent further interrupts	*/
		movb	$EOI,%al	/* Clear the interrupt		*/
		outb	%al,$OCW1_2

		call	kbdhandler	/* Call the handler		*/
		
		sti
		popfl			/* Restore the flags register	*/
		popal			/* Restore general-purpose regs.*/
		iret			/* Return from interrupt	*/