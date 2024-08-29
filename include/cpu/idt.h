#include <stdint.h>

struct idt_entry {
    uint16_t offset_low;  // Low 16 bits of the interrupt handler's address
    uint16_t selector;    // Segment selector of the interrupt handler's code segment
    uint8_t  reserved;    // Reserved for future use
    uint8_t  attributes;  // Attributes of the interrupt gate
    uint16_t offset_high; // High 16 bits of the interrupt handler's address
} __attribute__((packed));

struct idt_entry idt[256] __attribute__((aligned(8)));

struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr;

uint8_t get_irq_num(void);
void idt_init(void);
void isr_keyboard(void);
void irq_keyboard(void);
void irq_handler(void);