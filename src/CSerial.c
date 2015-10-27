/*
 * CSerial.c
 *
 *  Created on: 20.04.2013
 *      Author: duenda
 *
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "CSerial.h"



int hComm;

void createCSerial()
{
	hComm = 0;
};


void destructCSerial()
{
};



int Open_port(void)
{
	int res;
//	  res = open("/dev/ttyS0", O_RDWR | O_NOCTTY  | O_NDELAY );  //  | O_NDELAY com2  ts-linux
	  res = open("/dev/serusb1", O_RDWR | O_NOCTTY  | O_NDELAY);  // com2
	  if (res == -1)
	  {
//		  info_printf("open_port: Unable to open /dev/ser2 - \n");
		  hComm = 0;
      }
      else  {
//    	  info_printf("open_port successful res=%i\n",res);


    	  fcntl(res, F_SETFL, 0);
    	  hComm = res;
    	  Configure_port();
      }
      return (res);
}
//*****************************************************

int Configure_port(void)
{
	int res;
	 struct termios options;

	    res = tcgetattr(hComm, &options);
//	    info_printf("tcgetattr returned res %i\n", res);

	    res = cfsetispeed(&options, B9600);
//	    info_printf("cfsetispeed returned res %i\n", res);
//	    res = cfsetospeed(&options, B4800);
//	    info_printf("cfsetospeed returned res %i\n", res);
	    options.c_cflag |= (CLOCAL | CREAD);

	    options.c_cflag &= ~PARENB;
	    options.c_cflag &= ~CSTOPB;		// no parity, 1 stop bit
	    options.c_cflag &= ~CSIZE;
	    options.c_cflag |= CS8;    // Select 8 data bits
//	    options.c_cflag &= ~CRTSCTS;   // disable cts/rts

	    options.c_cflag &= ~IHFLOW; //not Enable INPUT hardware control
	    options.c_cflag &= ~OHFLOW; //not Enable OUTPUT hardware control



	    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // non canonical msgs

//	    options.c_iflag |= ( ISTRIP);        // in parity ck, strip parity bit
	    options.c_iflag &= ~(ISTRIP | INPCK | IXON | IXOFF | IXANY| IGNBRK);  // no xon,xoff

	    options.c_oflag &= ~OPOST;  // raw output (if any)
	    							// pn 23. oct 12,
	    options.c_cc[VTIME] = 10;  // wait 10 secs for start of message, then...???
	    							// timeout seems not to work ??????
	    options.c_cc[VMIN]  = applicationMsgSize ;  // package size 68

	    res = tcsetattr(hComm, TCSANOW, &options);
//	    info_printf("cfsetattr returned res %i\n", res);

 return TRUE;
}
//**************************************************
int Write_port(char* buffer, long len,long* dwBytesTransferred)
{
	iBytesWritten=0;

	*dwBytesTransferred = write(hComm, buffer, len);
//	printf("write() of %i bytes returned %i bytes sent!\n", len, *dwBytesTransferred);

	 return (len == *dwBytesTransferred);
	// else return true;
}
//***************************************************

int Read_port( void* lpBuffer, long len, long* dwBytesTransferred)
{
	*dwBytesTransferred = read(hComm,lpBuffer,len);
	return 0;
}

//**************************************************

int Close_port(void)
{
	close(hComm);
	hComm = 0;
	return TRUE;
}

int isConnected()
{
	return (hComm > 0);
}
//*************************************************
// main function

