/*
|Start|Verify|Initialize|Abstract|Run]
              ^^^^^^^^^^|^^^^^^^^|
*/
#include <stdio.h>
#include <chronos/version.h>
#include <log.h>
#ifdef _Processor_is_x86
#include <arch/x86/descriptor_tables.h>
#endif
void pae_init()
{
	debug_printf("Enabling PAE...\n");
	asm volatile ("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4"); // Enabling PAE
}
#ifdef _Processor_is_x86
void x86_init()
{
	debug_printf("Initializing x86 hardware...\n");
	init_descriptor_tables();
	debug_printf("Hardware tables initialized and flushed...\n");
}
#endif
int kernel_init()
{
	printf("Chronos Kernel Version %d.%d.%d;\n",1,0,0);
	//Initialization Routine
	pae_init();
	x86_init();
	return 0;
}

