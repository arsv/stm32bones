ENTRY(start_reset);

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
        .text : {
		*(.text)
		*(.rodata)
	} >FLASH

	RAM_org = ABSOLUTE(ORIGIN(RAM));

	.data : {
		*(.data)
	} >RAM AT>FLASH

	RAM_bss = ABSOLUTE(.);
	ROM_brk = LOADADDR(.data);

        .bss : {
		*(.bss)
	} >RAM

	RAM_brk = ABSOLUTE(.);
	RAM_end = ABSOLUTE(ORIGIN(RAM) + LENGTH(RAM));
}
