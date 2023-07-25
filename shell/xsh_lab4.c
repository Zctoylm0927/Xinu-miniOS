/* xsh_lab4.c - xsh_test_vitural_memory */

#include <xinu.h>

shellcmd u2020200671_xsh_lab4(int nargs, char *args[]) {
    int x;
    u2020200671_syscall_printf("&x=0x%x\n", &x);
    u2020200671_syscall_printf("%d\n",nargs);
    for(int i = 0; i < nargs; i++) 
        u2020200671_syscall_printf("arg-%d: %s\n", i, args[i]);
    u2020200671_syscall_printf("2020200671 Zhou Kaijun\n");
    return 0;
}