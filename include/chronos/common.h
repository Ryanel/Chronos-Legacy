/*
common.h - includes all common header files, including freetstanding headers that are usefull
By:Corwin Mcknight
*/
#ifndef CHRONOS_COMMON_H
#define CHRONOS_COMMON_H
#ifdef __GNUC__ //For GCC only, it has a good definiton
#include <stdbool.h>
#else //Backup Definitions
typedef char bool;
#define true 1
#define false 0
#endif
typedef unsigned int   uint32_t;
typedef          int   sint32_t;
typedef unsigned short uint16_t;
typedef          short sint16_t;
typedef unsigned char  uint8_t;
typedef          char  sint8_t;

inline void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}	
inline uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
inline uint16_t inw(uint16_t port)
{
   uint8_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
#endif
