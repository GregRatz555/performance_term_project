#ifndef _ENTRY_
#define _ENTRY_

.section      .text.entry
.globl _entry

_entry:
lui     sp,%hi(__stack_top)                                             
addi    sp,sp,%lo(__stack_top)
jal   zero, _start

#endif
