#ifndef ASSERT_H
#define ASSERT_H

#ifdef NDEBUG
#define assert( ignore ) ( (void) 0 )
#else
#define assert( expression ) ( ( expression ) ? (void) 0 \
        : printf("Assertion failed! %s\n--->At line: %d\n--->In file %s\n--->In function:%s\n",#expression,__LINE__,__FILE__,__func__)); asm("hlt");
#endif

#endif
