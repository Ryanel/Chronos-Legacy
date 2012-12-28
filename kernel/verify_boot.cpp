/*
Verify Boot
By: Corwin Mcknight
Ensures that the computer was booted into a acceptable state, and also deals with any compiler magic to start the kernel.
If not, it will whine like Rarity from My Little Pony (Youtube it).
Order in boot process
|Start|Verify|Initialize|Abstract|Run]
       ^^^^^^
*/
#include "init.h" //To start the kernel proper
#include <chronos/version.h> //The version of chronos
#include <security/verification/boot.h> //The verification signatures.
#include <stdio.h>
#include <log.h>
#include <chronos/common.h>
#ifdef __GNUC__ //For GCC, currently only compiler supported
extern "C" void __verifyboot()
{
	const char* vb_untampered_result;
	//Test to see if Kernel Version matches hash, a novel way of testing integrety
	//or if it is a development build.                                                 |      |
	
	int rs_version=0;
	//Calculate hash
	rs_version+=CHRONOS_VERSION_MAJOR*1000;
	rs_version+=CHRONOS_VERSION_MINOR*100;
	rs_version+=CHRONOS_VERSION_REVISION*10;
	rs_version+=CHRONOS_VERSION_PATCH;
	if(rs_version!=SECURITY_VERIFY_BOOT_VERSIONMAGIC)
	{
		vb_untampered_result="[FAIL]";	
		if(SECURITY_VERIFY_BOOT_QUITONMAGICMISMATCH)
		{
			if(!DEVELOPMEMT_MODE)
			{
				printf("[PANIC]:Kernel has been tampered with!\n");
				//Versions don't match, failsafe halt.
				asm("hlt");
				while(true)
				{
					//THE KERNEL WILL BE HERE FOREVER!!! HAHAHAHAHAHA!!!
				}
			}
			else
			{
				printf("Warning:Computer is in development mode.\n");
			}
		}
	}
	else
	{
		vb_untampered_result="  [OK]";
	}
	debug_printf("Verifying by software if kernel image is untampered...                    %s",vb_untampered_result);
	extern uint32_t magic;
	if(magic!=0x2BADB002)
	{
		vb_untampered_result="[FAIL]";	
	}
	else
	{
		vb_untampered_result="  [OK]";	
	}
	debug_printf("Checking if kernel was booted correctly...                                %s",vb_untampered_result);
	//Initialize the kernel.
	int rc_init=kernel_init();
	if(rc_init!=0)
	{
	}
}
#endif
