/**
	NCommunicationIO
	A namespace that contains all classes for external communication with attached or internal devices.
*/
namespace NCommunicationIO
{
	/**
		CSerial
		An abstract base class to support devices that use a serial interface for communication.
	*/
	
	class CSerial
	{
		private:
		int nComPortAddr[4]={0x3f8,0x2f8,0x3e8,0x2e8};
		int nBaudRateDivisor; //The rate the serial port can run, set to 115200, the maximum safe value.
		bool bIsSerialInitialized = false;
		int nComPort = 0;
		int nDivisor=0;
		public:
		void init_interface(int nPort);
		void setRateDivisor(int nDivisior);
		void putChar(char cha);
		void putString(char* pchstring);
		char getChar();
		char* getString();
	};
}
