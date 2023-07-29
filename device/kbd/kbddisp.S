/* Lab5 kbddisp.S - kbddisp */

#include <icu.s>

		.text
		.globl  kbddisp	
		.globl	kbdhandler

kbddisp:
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