/**
	CSerial
	An abstract base class to support devices that use a serial interface for communication.
*/
#include <drivers/serial.h>
#include <chronos/common.h>
void NCommunicationIO::CSerial::init_interface(int nPort)
{
	if(nPort>0 && nPort<5)
	{
		//Credit to OSDev Wiki for this initialization code, modified of course.
		nBaudRateDivisor = 115200;
		nComPort=nPort;
		outb(nComPortAddr[nComPort] + 1, 0x00);    // Disable all interrupts
		outb(nComPortAddr[nComPort] + 3, 0x80);    // Enable DLAB (set baud rate divisor)
		outb(nComPortAddr[nComPort] + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
		outb(nComPortAddr[nComPort] + 1, 0x00);    //                  (hi byte)
		outb(nComPortAddr[nComPort] + 3, 0x03);    // 8 bits, no parity, one stop bit
		outb(nComPortAddr[nComPort] + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
		outb(nComPortAddr[nComPort] + 4, 0x0B);    // IRQs enabled, RTS/DSR set
		bIsSerialInitialized=true;
	}
	else
	{
		return;
	}
}
void NCommunicationIO::CSerial::setRateDivisor(int nDivisor)
{
	nBaudRateDivisor=nDivisor;
}
void NCommunicationIO::CSerial::putChar(char cha)
{
	while ((inb(nComPort + 5) & 0x20)== 0); //Checks if any transit is empty.
	outb(nComPortAddr[nComPort],cha); //char is stored in port addr.
}
char NCommunicationIO::CSerial::getChar()
{
	while ((inb(nComPortAddr[nComPort] + 5) & 1)== 0); //Checks if any data is recieved.
	return inb(nComPortAddr[nComPort]); //char is stored in port addr.
}

char* NCommunicationIO::CSerial::getString()
{
	//TODO:Implement getString()
	return 0;
}
void NCommunicationIO::CSerial::putString(char* pchstring)
{
	while(*pchstring!=0)
	{
		putChar(*pchstring++);
	}
}
