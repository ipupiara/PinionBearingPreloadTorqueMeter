
//#include <iostream>


//  PN 8. Nov 2005
//
//  code to access the serial port, copied from a MSDN sample
//
//

// pn 17. sept 12, commtimeouts copied from windows, linux struct to be found later


#define applicationMsgSize   17   // fortunately we just got a single message type
							// otherwise better a crlf would express end of message since more sophisticated
							//  message handling is not available within posix (or at least no obvious)


typedef char BYTE;
typedef void *HANDLE;
#define TRUE 1
#define FALSE 0



typedef struct _COMMTIMEOUTS {
    long ReadIntervalTimeout;          /* Maximum time between read chars. */
    long ReadTotalTimeoutMultiplier;   /* Multiplier of characters.        */
    long ReadTotalTimeoutConstant;     /* Constant in milliseconds.        */
    long WriteTotalTimeoutMultiplier;  /* Multiplier of characters.        */
    long WriteTotalTimeoutConstant;    /* Constant in milliseconds.        */
} COMMTIMEOUTS,*LPCOMMTIMEOUTS;




 void createCSerial();
 void destructCSerial();

 int Open_port(void);
 int Write_port(char* buffer, long len,long* dwBytesTransferred);
 int Read_port( void* lpBuffer, long len,long* dwBytesTransferred);
 int Close_port(void);
 
 int isConnected();


// DCB      m_dcb;
 COMMTIMEOUTS m_CommTimeouts;
 int     m_bPortReady;
 int     bWriteRC;
 int     bReadRC;
 long iBytesWritten;
 long iBytesRead;
 long dwBytesRead;

 int Configure_port(void);


