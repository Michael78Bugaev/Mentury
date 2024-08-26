typedef unsigned int	u32;	// беззнаковое целое число размером 32 бита
typedef 		 int	s32; 	// целое число 32 бита со знаком
typedef unsigned short	u16;	// и т.д.
typedef 		 short	s16;
typedef unsigned char	u8;
typedef 		 char	s8;

unsigned char   port_byte_in(unsigned short port);
void    port_byte_out(unsigned short port, unsigned char data);
unsigned char   port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
void	memcpy(u8 *src, u8 *dest, u32 bytes);