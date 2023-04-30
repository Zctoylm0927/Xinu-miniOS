/* u2020200671_create.S - create (for x86) */
    .globl	u2020200671_create

u2020200671_create:
    movl %esp, %edi
    add $4, %edi
    int $51
    ret