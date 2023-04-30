/* xsh_lab3.c - xsh_test_kenerl_user */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>

void k2020200671_printf(int procid, int num) {
    printf("proc=%d: num=%d\n", procid, num);
}

void k2020200671_create(uint32* s) {
    void* func = (void*)(*s++);
    uint32 size = (uint32)(*s++);
    uint32 pri = (uint32)(*s++);
    char* name = (char*)(*s++);
    uint32 nargs = (uint32)(*s++);
    int cnt = nargs - 1;
    while(cnt--) s++;
    int pid = ucreate(func, size, pri, name, nargs, s);
    resume(pid);
}

void u2020200671_uptest(int a, int b) {
    int pid = getpid();
    int s1 = a, s2 = b;
    u2020200671_printf(pid,s1);
    //u2020200671_sleep(1);
    u2020200671_printf(pid,s2);
}

shellcmd u2020200671_xsh_lab3(int nargs, char *args[]) {    
    u2020200671_sleep(2);
    u2020200671_create(u2020200671_uptest, 8192, 20, "uptest", 2, 3, 4);
    return 0;
}