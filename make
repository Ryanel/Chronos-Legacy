#=======================================================
#Makescript for Chronos
#
#=======================================================
#Setup
#-------------------------------------------------------
BASEDIR=$(pwd)
OBJ="$BASEDIR/build/objects/"
OBJK="$OBJ/kernel/"
OBJL="$OBJ/std"
#=======================================================
#Configuration
GPP="-Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -fno-stack-protector -DDEBUG -D_Processor_is_x86 -I$BASEDIR/include/ -std=c++11"
#=======================================================
#Kernel
#-------------------------------------------------------
cd kernel

i586-elf-g++ -o $OBJK/verify_boot.o -c verify_boot.cpp $GPP
i586-elf-g++ -o $OBJK/init.o -c init.cpp $GPP
i586-elf-g++ -o $OBJK/textmode.o -c display/textmode.cpp $GPP
i586-elf-g++ -o $OBJK/ssp.o -c $BASEDIR/lang/gcc/ssp.cpp $GPP
cd drivers
i586-elf-g++ -o $OBJK/serial.o -c serial.cpp $GPP
cd ../
cd ../
#======================================================
#Arch
#------------------------------------------------------
cd arch
#======================================================
#Arch/x86
#------------------------------------------------------
cd x86
nasm -f elf -o $OBJK/boot.o boot.s
nasm -f elf -o $OBJK/descriptor_tables_asm.o descriptor_tables.s
i586-elf-g++ -o $OBJK/descriptor_tables.o -c descriptor_tables.c -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -D_Processor_is_x86 -I$BASEDIR/include/
cd ../
#======================================================
#End Arch
#------------------------------------------------------
cd ../
#======================================================
#STD
#------------------------------------------------------
cd library/std
cd stdio
i586-elf-g++ -o $OBJL/printf.o -c printf.cpp $GPP
i586-elf-g++ -o $OBJL/vsprintf.o -c vsprintf.cpp $GPP
cd ../
cd ../../
#======================================================
#Linking and Media Creation
#------------------------------------------------------
cd build
cd objects
cd kernel
i586-elf-ld -T link.ld -o ../../iso/sbin/kernels/Kernel.app boot.o verify_boot.o init.o textmode.o $OBJL/vsprintf.o $OBJL/printf.o descriptor_tables_asm.o descriptor_tables.o serial.o
cd ../../
grub-mkrescue -o chronos-1-0-0-0-x86.iso iso
