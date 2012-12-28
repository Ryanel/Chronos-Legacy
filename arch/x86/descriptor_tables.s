;====================================================
;gdt_flush
;Flushes the GDT.
;CLM-PF
;====================================================
[global gdt_flush]

gdt_flush:
	mov eax, [esp+4] ;Get the pointer to the GDT, (paramater)
	lgdt [eax]
	
	mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
	; Load all data segment selectors
	mov ds, ax        
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 0x08 is the offset to the code segment, doing a Far jump!
.flush:
	ret
	
