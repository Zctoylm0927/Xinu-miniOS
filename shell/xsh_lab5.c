/* xsh_lab5.c - xsh_test_VGA */

#include <xinu.h>

shellcmd u2020200671_xsh_lab5(int nargs, char *args[]) {
    int x;
    u2020200671_syscall_printf("&x=0x%x\n", &x);
    for(int i = 0; i < nargs; i++) 
        u2020200671_syscall_printf("arg-%d: %s\n", i, args[i]);
    
    u2020200671_syscall_printf("2020200671 Zhou Kaijun\n");

    u2020200671_syscall_printf("Next test close to overflow\n");
    for(int i = 0; i < 80; i++)
        u2020200671_syscall_printf("1");
    
    u2020200671_syscall_printf("\nNext test overflow\n");
    for(int i = 0; i < 81; i++)
        u2020200671_syscall_printf("1");

    u2020200671_syscall_printf("\n\n");
    return 0;
}