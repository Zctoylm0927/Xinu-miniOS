/* k2020200671_ltss.S - ltss (for x86) */
    .globl	k2020200671_ltss

k2020200671_ltss:
    movl 4(%esp), %eax
    ltr %ax
    ret