#include <stdint.h>
typedef unsigned int	u32;	// беззнаковое целое число размером 32 бита
typedef 		 int	s32; 	// целое число 32 бита со знаком
typedef unsigned short	u16;	// и т.д.
typedef 		 short	s16;
typedef unsigned char	u8;
typedef 		 char	s8;
typedef unsigned long        size_t;

#define INTERRUPT_ENABLE_REGISTER_ADDRESS 0x21
#define INTERRUPT_DISABLE_REGISTER_ADDRESS 0xA1

unsigned char   port_byte_in(unsigned short port);
void    port_byte_out(unsigned short port, unsigned char data);
unsigned char   port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
void	memcopy(u8 *src, u8 *dest, u32 bytes);
void cpu_enable_interrupt(int interrupt_number);
void cpucall_set_interrupt_handler(int interrupt_number, void (*handler)());