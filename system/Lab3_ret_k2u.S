/* k2020200671_ret_k2u.S - ret_k2u (for x86) */
    .globl	k2020200671_ret_k2u

k2020200671_ret_k2u:
    pop %eax;
    movw %ds, %ax;
    movw %es, %ax;
    movw %fs, %ax
    movw %gs, %ax;
    iret