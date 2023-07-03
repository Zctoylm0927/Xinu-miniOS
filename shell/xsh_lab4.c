/* xsh_lab4.c - xsh_virtual memory */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>

void k2020200671_printf_lab4(int type, int num) {
    if(type == -1) printf("&x=0x%x\n", num);
    else if(type >= 0) printf("arg-%d: %s\n", type, num);
    else printf("2020200671 Zhou Kaijun\n");
}

shellcmd u2020200671_xsh_lab4(int nargs, char *args[]) { 
    int x;
    u2020200671_printf_lab4(-1, &x);
    for(int i = 0; i < nargs; ++i)
        u2020200671_printf_lab4(i, args[i]);
    u2020200671_printf_lab4(-2, 0);
    return 0;
}