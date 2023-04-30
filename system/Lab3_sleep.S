/* k2020200671_sleep.S - sleep (for x86) */
    .globl	u2020200671_sleep

u2020200671_sleep:
    movl 4(%esp), %edi
    int $50
    ret