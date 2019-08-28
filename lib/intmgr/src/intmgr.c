#include "m68k/intmgr.h"

#define INTERRUPT_VECTOR_SIZE 62
#define TOTAL_INTERRUPTS      46

#define AT(SectName) __attribute__((section(SectName)))

#define DECLARE_IVEC_ENTRY(Number) \
static void iv_entry_##Number(void);

#define DEFINE_IVEC_ENTRY(Number)                   \
void __attribute__((interrupt)) iv_entry_##Number() \
{                                                   \
    interrupt_table[Number]();                      \
}

#define NAME_IVEC_ENTRY(Number) iv_entry_##Number

static void ih_halt(void);

DECLARE_IVEC_ENTRY(M68KINO_BUSERR)
DECLARE_IVEC_ENTRY(M68KINO_ADDRERR)
DECLARE_IVEC_ENTRY(M68KINO_ILLEGAL)
DECLARE_IVEC_ENTRY(M68KINO_ZERODIV)
DECLARE_IVEC_ENTRY(M68KINO_CHK)
DECLARE_IVEC_ENTRY(M68KINO_TRAPV)
DECLARE_IVEC_ENTRY(M68KINO_PRIVVIOL)
DECLARE_IVEC_ENTRY(M68KINO_TRACE)
DECLARE_IVEC_ENTRY(M68KINO_LINE1010)
DECLARE_IVEC_ENTRY(M68KINO_LINE1111)
DECLARE_IVEC_ENTRY(M68KINO_UNINIT)
DECLARE_IVEC_ENTRY(M68KINO_SPURIOUS)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_1)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_2)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_3)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_4)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_5)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_6)
DECLARE_IVEC_ENTRY(M68KINO_LEVEL_7)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_0)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_1)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_2)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_3)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_4)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_5)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_6)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_7)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_8)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_9)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_10)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_11)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_12)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_13)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_14)
DECLARE_IVEC_ENTRY(M68KINO_TRAP_15)

m68k_ih_t* const __interrupt_vector[INTERRUPT_VECTOR_SIZE] AT(".intvec") = {
    [M68KINO_BUSERR] = &NAME_IVEC_ENTRY(M68KINO_BUSERR),
    [M68KINO_ADDRERR] = &NAME_IVEC_ENTRY(M68KINO_ADDRERR),
    [M68KINO_ILLEGAL] = &NAME_IVEC_ENTRY(M68KINO_ILLEGAL),
    [M68KINO_ZERODIV] = &NAME_IVEC_ENTRY(M68KINO_ZERODIV),
    [M68KINO_CHK] = &NAME_IVEC_ENTRY(M68KINO_CHK),
    [M68KINO_TRAPV] = &NAME_IVEC_ENTRY(M68KINO_TRAPV),
    [M68KINO_PRIVVIOL] = &NAME_IVEC_ENTRY(M68KINO_PRIVVIOL),
    [M68KINO_TRACE] = &NAME_IVEC_ENTRY(M68KINO_TRACE),
    [M68KINO_LINE1010] = &NAME_IVEC_ENTRY(M68KINO_LINE1010),
    [M68KINO_LINE1111] = &NAME_IVEC_ENTRY(M68KINO_LINE1111),
    [M68KINO_UNINIT] = &NAME_IVEC_ENTRY(M68KINO_UNINIT),
    [M68KINO_SPURIOUS] = &NAME_IVEC_ENTRY(M68KINO_SPURIOUS),
    [M68KINO_LEVEL_1] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_1),
    [M68KINO_LEVEL_2] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_2),
    [M68KINO_LEVEL_3] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_3),
    [M68KINO_LEVEL_4] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_4),
    [M68KINO_LEVEL_5] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_5),
    [M68KINO_LEVEL_6] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_6),
    [M68KINO_LEVEL_7] = &NAME_IVEC_ENTRY(M68KINO_LEVEL_7),
    [M68KINO_TRAP_0] = &NAME_IVEC_ENTRY(M68KINO_TRAP_0),
    [M68KINO_TRAP_1] = &NAME_IVEC_ENTRY(M68KINO_TRAP_1),
    [M68KINO_TRAP_2] = &NAME_IVEC_ENTRY(M68KINO_TRAP_2),
    [M68KINO_TRAP_3] = &NAME_IVEC_ENTRY(M68KINO_TRAP_3),
    [M68KINO_TRAP_4] = &NAME_IVEC_ENTRY(M68KINO_TRAP_4),
    [M68KINO_TRAP_5] = &NAME_IVEC_ENTRY(M68KINO_TRAP_5),
    [M68KINO_TRAP_6] = &NAME_IVEC_ENTRY(M68KINO_TRAP_6),
    [M68KINO_TRAP_7] = &NAME_IVEC_ENTRY(M68KINO_TRAP_7),
    [M68KINO_TRAP_8] = &NAME_IVEC_ENTRY(M68KINO_TRAP_8),
    [M68KINO_TRAP_9] = &NAME_IVEC_ENTRY(M68KINO_TRAP_9),
    [M68KINO_TRAP_10] = &NAME_IVEC_ENTRY(M68KINO_TRAP_10),
    [M68KINO_TRAP_11] = &NAME_IVEC_ENTRY(M68KINO_TRAP_11),
    [M68KINO_TRAP_12] = &NAME_IVEC_ENTRY(M68KINO_TRAP_12),
    [M68KINO_TRAP_13] = &NAME_IVEC_ENTRY(M68KINO_TRAP_13),
    [M68KINO_TRAP_14] = &NAME_IVEC_ENTRY(M68KINO_TRAP_14),
    [M68KINO_TRAP_15] = &NAME_IVEC_ENTRY(M68KINO_TRAP_15),
};

static m68k_ih_t* interrupt_table[TOTAL_INTERRUPTS] = {
    [M68KINO_BUSERR] = &ih_halt,
    [M68KINO_ADDRERR] = &ih_halt,
    [M68KINO_ILLEGAL] = &ih_halt,
    [M68KINO_ZERODIV] = &ih_halt,
    [M68KINO_CHK] = &ih_halt,
    [M68KINO_TRAPV] = &ih_halt,
    [M68KINO_PRIVVIOL] = &ih_halt,
    [M68KINO_TRACE] = &ih_halt,
    [M68KINO_LINE1010] = &ih_halt,
    [M68KINO_LINE1111] = &ih_halt,
    [M68KINO_UNINIT] = &ih_halt,
    [M68KINO_SPURIOUS] = &ih_halt,
    [M68KINO_LEVEL_1] = &ih_halt,
    [M68KINO_LEVEL_2] = &ih_halt,
    [M68KINO_LEVEL_3] = &ih_halt,
    [M68KINO_LEVEL_4] = &ih_halt,
    [M68KINO_LEVEL_5] = &ih_halt,
    [M68KINO_LEVEL_6] = &ih_halt,
    [M68KINO_LEVEL_7] = &ih_halt,
    [M68KINO_TRAP_0] = &ih_halt,
    [M68KINO_TRAP_1] = &ih_halt,
    [M68KINO_TRAP_2] = &ih_halt,
    [M68KINO_TRAP_3] = &ih_halt,
    [M68KINO_TRAP_4] = &ih_halt,
    [M68KINO_TRAP_5] = &ih_halt,
    [M68KINO_TRAP_6] = &ih_halt,
    [M68KINO_TRAP_7] = &ih_halt,
    [M68KINO_TRAP_8] = &ih_halt,
    [M68KINO_TRAP_9] = &ih_halt,
    [M68KINO_TRAP_10] = &ih_halt,
    [M68KINO_TRAP_11] = &ih_halt,
    [M68KINO_TRAP_12] = &ih_halt,
    [M68KINO_TRAP_13] = &ih_halt,
    [M68KINO_TRAP_14] = &ih_halt,
    [M68KINO_TRAP_15] = &ih_halt,
};

DEFINE_IVEC_ENTRY(M68KINO_BUSERR)
DEFINE_IVEC_ENTRY(M68KINO_ADDRERR)
DEFINE_IVEC_ENTRY(M68KINO_ILLEGAL)
DEFINE_IVEC_ENTRY(M68KINO_ZERODIV)
DEFINE_IVEC_ENTRY(M68KINO_CHK)
DEFINE_IVEC_ENTRY(M68KINO_TRAPV)
DEFINE_IVEC_ENTRY(M68KINO_PRIVVIOL)
DEFINE_IVEC_ENTRY(M68KINO_TRACE)
DEFINE_IVEC_ENTRY(M68KINO_LINE1010)
DEFINE_IVEC_ENTRY(M68KINO_LINE1111)
DEFINE_IVEC_ENTRY(M68KINO_UNINIT)
DEFINE_IVEC_ENTRY(M68KINO_SPURIOUS)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_1)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_2)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_3)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_4)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_5)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_6)
DEFINE_IVEC_ENTRY(M68KINO_LEVEL_7)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_0)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_1)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_2)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_3)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_4)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_5)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_6)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_7)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_8)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_9)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_10)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_11)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_12)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_13)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_14)
DEFINE_IVEC_ENTRY(M68KINO_TRAP_15)

_Noreturn
void ih_halt(void)
{
    while (1) {
        // do nothing
    }
}

m68k_ih_t* m68k_setih(uint8_t ino, m68k_ih_t* new_ih)
{
    m68k_ih_t* ret = interrupt_table[ino];
    interrupt_table[ino] = new_ih;
    return ret;
}