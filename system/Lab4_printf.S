/* k2020200671_printf_lab4.S - printf (for x86) */
    .globl	u2020200671_printf_lab4

u2020200671_printf_lab4:
    movl 8(%esp), %esi
    movl 4(%esp), %edi
    int $52
    ret