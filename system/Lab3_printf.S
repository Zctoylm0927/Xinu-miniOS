/* k2020200671_printf.S - printf (for x86) */
    .globl	u2020200671_printf

u2020200671_printf:
    movl 8(%esp), %esi
    movl 4(%esp), %edi
    int $48
    ret