#include <stdint.h>
#include <cpu/string.h>
#include <task/shell.h>

void exec(char com[])
{
    // offset = (row * VGA_WIDTH * 2) + (column * 2)

    if (strcmp("help",  com) == 0)
    {
        kprint("Mentury commands list:\n");
        kprint("help        Get list of commands\n");
        kprint("clear       Clear console screen\n");
        kprint("exit        Exit shell\n");
        kprint("ver         Print Mentury current version\n\n");
    }
    else if (strcmp("clear", com) == 0)
    {
        clear_screen();
        //                                                                                              "
        kprint_colored("| Mentury shell         | 0.07                           Type 'help' for help  |", 0x1F);
        kprint("\n");
        set_cursor(((2 * 80 * 2) + (0 * 2)));
    }
    else if (strcmp("", com) == 0)
    {
    }
    else if (strcmp("437", com) == 0)
    {
        kprint("Testing codepage 437 symbols: │!\n");
    }
    else if (strcmp("ver", com) == 0)
    {
        kprint("Mentury Operating System version 0.07\n     Created in C and assembly\n");
    }
    else 
    {
        kprint_colored("Unknown command\n", 0x0C);
    }
}
void run(void)
{

}
void shell(void)
{
    
}