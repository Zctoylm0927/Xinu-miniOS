/* xsh_lab2.c - xsh_test_myshell */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>

void _2020200671_myprintf_1(int args, ...) {
    kprintf("2020200671 Zhou Kaijun myprintf_1\n");
    if(args == -1) return;
    kprintf("%d ",args);
    va_list ap;
    va_start (ap,args);
    while(233) {
        int ival = va_arg(ap, int);
        if(ival == -1) break;
        kprintf("%d ",ival);
    }
    va_end(ap);
}

void _2020200671_printf2_help(char* p) {
    while(233) {
        int ival = va_arg(p, int);
        if(ival == -1) break;
        kprintf("%d ",ival);
    }
}

void _2020200671_myprintf_2(int args, ...) {
    kprintf("2020200671 Zhou Kaijun myprintf_2\n");
    if(args == -1) return;
    kprintf("%d ",args);
    va_list ap ;
    va_start (ap,args);
    _2020200671_printf2_help(ap);
    va_end(ap);
}

void _2020200671_delay_test(int seconds, char* p) {
    int args_num[5]={0};
    for(int i = 0; i < 5;++i) {
        args_num[i] = va_arg(p, int);
        if(args_num[i] == -1) break;
    }
    sleep(seconds);
    printf("delay_test: %d.%d\n", clktime, count1000);
    _2020200671_myprintf_1(args_num[0], args_num[1], args_num[2], args_num[3], args_num[4]);
    printf("\n");
}

void _2020200671_delay(int seconds, void* func, ...) {
    va_list ap;
    va_start (ap, func);
    pid32 pid = create(_2020200671_delay_test, 8192, 30, "delay_test", 0, 2, seconds, ap);
    resume(pid);
    va_end(ap);
}

/*------------------------------------------------------------------------
 * xsh_lab2 - shell to test my shell command
 *------------------------------------------------------------------------
 */
shellcmd _2020200671_xsh_lab2(int nargs, char *args[]) {

    // Test my_printf_1
    if(nargs == 2 && strcmp(args[1], "printf1") == 0) {
        kprintf("Test my_printf_1");
        kprintf("\ntask #1 normal end: 0 0 0 1 2\n");                   
        _2020200671_myprintf_1(0,0,0,1,2,-1);
        kprintf("\ntask #2 early end: 1 2\n");
        _2020200671_myprintf_1(1,2,-1,3,4,-1);
        kprintf("\ntask #3 normal end: 10 11 12\n"); 
        _2020200671_myprintf_1(10,11,12,-1);
        kprintf("\ntask #4 normal end: 0\n");
        _2020200671_myprintf_1(0,-1);
        kprintf("\ntask #5: directly end\n");
        _2020200671_myprintf_1(-1,1,2,3,10,3,2,1,-1);
        kprintf("\n");

        return 0;
    }
    // Test my_printf_2
    if(nargs == 2 && strcmp(args[1], "printf2") == 0) {
        kprintf("Test my_printf_2");
        kprintf("\ntask #1 normal end: 0 1 2\n");                   
        _2020200671_myprintf_2(0,1,2,-1);
        kprintf("\ntask #2 early end: 1 2\n");
        _2020200671_myprintf_2(1,2,-1,3,4,-1);
        kprintf("\ntask #3 normal end: 10 11 12\n");
        _2020200671_myprintf_1(10,11,12,-1);
        kprintf("\ntask #4 normal end: 0\n");
        _2020200671_myprintf_2(0,-1);
        kprintf("\ntask #5: directly end\n");
        _2020200671_myprintf_2(-1,1,2,3,10,3,2,1,-1);
        kprintf("\n");

        return 0;
    }

    if(nargs == 2 && strcmp(args[1], "delay") == 0) {
        kprintf("Test my_delay\n");
        printf("main(1): %d.%d\n", clktime, count1000); 
        _2020200671_delay(2, _2020200671_delay_test, 1, 114514, -1);
        printf("main(2): %d.%d\n", clktime, count1000); 
        _2020200671_delay(3, _2020200671_delay_test, 2, 102, -1);
        printf("main(3): %d.%d\n", clktime, count1000); 
        _2020200671_delay(4, _2020200671_delay_test, 3, 927, -1);

        return 0;
    }
    if(nargs > 1) {
        fprintf(stderr, "%s: Sorry I haven't finished so many arguments\n", args[0]);
        return 1;
    }
    return 0;
}