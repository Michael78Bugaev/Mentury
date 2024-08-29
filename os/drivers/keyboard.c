#include <drv/ps2.h>
#include <drv/vga.h>
#include <cpu/io.h>
#include <cpucall.h>
#include <stdint.h>
#include <task/shell.h>
#include <stdbool.h>
#include <stddef.h>
#include <cpu/string.h>

unsigned int keyReadSleep = 25000000;
unsigned int lastCharDel = 0;

static char key_buffer[256];
#define BACKSPACE_KEY 0x0E

char get_ascii_char(unsigned char key_code)
{
  switch (key_code)
  {
  case KEY_A:
    return 'a';
  case KEY_B:
    return 'b';
  case KEY_C:
    return 'c';
  case KEY_D:
    return 'd';
  case KEY_E:
    return 'e';
  case KEY_F:
    return 'f';
  case KEY_G:
    return 'g';
  case KEY_H:
    return 'h';
  case KEY_I:
    return 'i';
  case KEY_J:
    return 'j';
  case KEY_K:
    return 'k';
  case KEY_L:
    return 'l';
  case KEY_M:
    return 'm';
  case KEY_N:
    return 'n';
  case KEY_O:
    return 'o';
  case KEY_P:
    return 'p';
  case KEY_Q:
    return 'q';
  case KEY_R:
    return 'r';
  case KEY_S:
    return 's';
  case KEY_T:
    return 't';
  case KEY_U:
    return 'u';
  case KEY_V:
    return 'v';
  case KEY_W:
    return 'w';
  case KEY_X:
    return 'x';
  case KEY_Y:
    return 'y';
  case KEY_Z:
    return 'z';
  case KEY_1:
    return '1';
  case KEY_2:
    return '2';
  case KEY_3:
    return '3';
  case KEY_4:
    return '4';
  case KEY_5:
    return '5';
  case KEY_6:
    return '6';
  case KEY_7:
    return '7';
  case KEY_8:
    return '8';
  case KEY_9:
    return '9';
  case KEY_0:
    return '0';
  case KEY_MINUS:
    return '-';
  case KEY_EQUAL:
    return '=';
  case KEY_SQUARE_OPEN_BRACKET:
    return '[';
  case KEY_SQUARE_CLOSE_BRACKET:
    return ']';
  case KEY_SEMICOLON:
    return ';';
  case KEY_BACKSLASH:
    return '\\';
  case KEY_COMMA:
    return ',';
  case KEY_DOT:
    return '.';
  case KEY_FORESLHASH:
    return '/';
  case KEY_SPACE:
    return ' ';
  default:
    return 0;
  }
}

int backspace_func(char buffer[])
{
    int len = strlen(buffer);
    if (len > 0)
    {
        buffer[len - 1] = '\0';
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_backspace()
{
    int new = get_cursor() - 2;
    write(' ', 0x07, new);
    set_cursor(new);
}

static void keyboard_callback()
{
    while (1 == 1)
    {
        uint8_t scancode = port_byte_in(0x60);

        if (scancode == BACKSPACE_KEY)
        {
            if (backspace_func(key_buffer))
            {
                print_backspace();
            }
        }
        else
        {
            char letter = get_ascii_char(scancode);
            join(key_buffer, letter);
            char str[2] = {letter, '\0'};
            kprint((u8*)str);
        }
    }
}

void wait_for_io(uint32_t timer_count)
{
  while (1)
  {
    __asm__("nop");
    timer_count--;
    if (timer_count <= 0)
      break;
  }
}

char get_input_keycode()
{
  char ch = 0;
  while ((ch = port_byte_in(KEYBOARD_PORT)) != 0)
  {
    if (ch > 0)
      return ch;
  }
  return ch;
}

void debug()
{
  char keycode = 0;
  char ch = 0;
  while (1 == 1)
  {
    keycode = get_input_keycode();
    ch = get_ascii_char(keycode);
  }
}

void keyboardInstance()
{
  set_cursor(0);
  kprint_colored("| Mentury shell         | 0.07                           Type 'help' for help  |", 0x1F);
  kprint("\n");
  set_cursor(((2 * 80 * 2) + (0 * 2)));
  kprint_colored("MenturyOS> ", 0x0B);
  char ch = 0;
  char data = 0;
  char keycode = 0;
  char *textData;
  int readyToSend = true;

  while (1)
  {
    data = port_byte_in(KEYBOARD_PORT);

    if (data < 0)
    { // not pressed
      readyToSend = true;
    }

    if (data >= 0)
    { // pressed
      if (readyToSend == true)
      {
        readyToSend = false;
        keycode = get_input_keycode();
        
        // move the cursor one to the right
        if (keycode == KEY_LEFT)
        {
          int offset = get_cursor();
          offset--;
          set_cursor(offset);
        }
        else if (keycode == KEY_RIGHT){
          int offset = get_cursor();
          offset++;
          offset++;
          set_cursor(offset);
        }
        
        else if (keycode == KEY_ENTER)
        {
          kprint("\n");
          exec(key_buffer);
          key_buffer[0] = '\0';

          int old = get_cursor();
          set_cursor(0);
          kprint_colored("| Mentury shell         | 0.07                           Type 'help' for help  |", 0x1F);
          kprint("\n");
          set_cursor(old);

          kprint_colored("MenturyOS> ", 0x0B);
        }
        else if (keycode == KEY_BACKSPACE)
        {
          if (backspace_func(key_buffer))
            print_backspace();
        }
        else
        {
          char letter = get_ascii_char(keycode);
          join(key_buffer, letter);
          char str[2] = {letter, '\0'};
          kprint_colored(str, 0x07);
          // strncat(textData, ch);
        }
      }
    }
  }
}