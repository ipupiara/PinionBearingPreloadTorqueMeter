/*
 * torqueMeter.c
 *
 *  Created on: 20.04.2013
 *      Author: duenda
 */

#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/time.h>
#include  <string.h>
#include <string.h>
#include <pthread.h>

#include "torqueMeter.h"
#include "minIni.h"


/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"


int deviceRunning;
int initialized = 0;
int TMstarted = 0;

pthread_t torqueMeterThread;  // Thread reading values from Sensor


int torqueMeterStopCond;  // event variable to communicate to the hygrothread that it shall stop
							// used an int because pThread_cond_wait and pThread_cond_timedwait could  not be linked ???
							// and what libraries are actually linked together in this IDE   ?????????????
long adcValue;
long measureCount;

long privateRightCalibADCValue;
long privateLeftCalibADCValue;
long privateZeroCalibADCValue;
long privateRightCalibTorque;
long privateLeftCalibTorque;
long privateInvertRL;


char privateIniFilePath [256];

void setIniFilePath()
{
//	char cwd [256];
//	MessageBox(NULL,"must be specified","error",MB_OK);

	memset(&privateIniFilePath,0,sizeof(privateIniFilePath));
/*	if (getcwd(cwd,sizeof(cwd))) {
		strncpy(iniFilePath,cwd,strlen(cwd));
		strcat(iniFilePath,"/LinuxClimate.ini");
		info_printf("ini File path %s\n",iniFilePath);
	} else */ {
		strcat(privateIniFilePath,"/fs/sda/home/");
		strcat(privateIniFilePath,"PinionBearingPreloadTM.ini");
	}
}


double getIniValue(char* id, double defaultVal)
{
	char buffer [50];
	memset(buffer,0,sizeof(buffer));
//	GetPrivateProfileString("Behaviour",id, "", buffer, sizeof(buffer), iniFilePath);
	ini_gets("Behaviour",id, "", buffer, sizeof(buffer), privateIniFilePath);
//	printf("\n 1. %s %s\n",id,buffer);
	if (strlen(buffer) == 0)  {
		sprintf(buffer,"%.2f",defaultVal);
//		WritePrivateProfileString("Behaviour",id, buffer, iniFilePath);
		ini_puts("Behaviour",id, buffer, privateIniFilePath);
//		printf("\ndefValString %s\n",buffer);
	}
	return atof(buffer);
//	return 0;
}

double setIniValue(char* id, double val)
{
	char buffer [50];
	memset(buffer,0,sizeof(buffer));
	sprintf(buffer,"%.2f",val);
	ini_puts("Behaviour",id, buffer, privateIniFilePath);
	return val;
}

int getIniInt(char* id, int defaultVal)
{

	int res = ini_getl("Behaviour",id, 0xFF,  privateIniFilePath);
//	info_printf("GetIniInt  %s %i\n",id,res);
	if (res == 0xFF)  {
		char buffer [50];
		sprintf(buffer,"%i",defaultVal);
		res = defaultVal;
		ini_puts("Behaviour",id, buffer, privateIniFilePath);
//		info_printf("defValString %s\n",buffer);
	}
	return res;
//		return 0;
}

int setIniInt(char* id, long val)
{
	int res = 0;
	char buffer [50];
	sprintf(buffer,"%li",val);
	ini_puts("Behaviour",id, buffer, privateIniFilePath);
//	info_printf("defValString %s\n",buffer);

return res;
//	return 0;
}


void checkInitialization()
{
	if (!initialized)  {
		setIniFilePath();
		privateRightCalibADCValue = getIniInt("RightCalibADCValue",0);
		privateLeftCalibADCValue = getIniInt("LeftCalibADCValue",0);
		privateZeroCalibADCValue = getIniInt("ZeroCalibADCValue",0);
		privateRightCalibTorque = getIniInt("RightCalibTorque",0);
		privateLeftCalibTorque  = getIniInt("LeftCalibTorque",0);
		privateInvertRL = getIniInt("InvertLeftRight",0);
		initialized = 1;
	}
}

int getRightCalibTorque()
{
	checkInitialization();
	return privateRightCalibTorque;
}

int setInvertRL(int val)
{
	privateInvertRL = val;
	setIniInt("InvertLeftRight",val);
	return val;
}

int getInvertRL()
{
	checkInitialization();
	return privateInvertRL;
}

int setRightCalibTorque(int val)
{
	privateRightCalibTorque = val;
	setIniInt("RightCalibTorque",val);
	return val;
}

int getLeftCalibTorque()
{
	checkInitialization();
	return privateLeftCalibTorque;
}

int setLeftCalibTorque(int val)
{
	privateLeftCalibTorque = val;
	setIniInt("LeftCalibTorque",val);
	return val;
}

long getRightCalibADC()
{
	checkInitialization();
	return privateRightCalibADCValue;

}

long getLeftCalibADC()
{
	checkInitialization();
	return privateLeftCalibADCValue;
}

long getZeroCalibADC()
{
	checkInitialization();
	return privateZeroCalibADCValue;
}

long setRightCalibADC(long val)
{
	privateRightCalibADCValue = val;
	setIniInt("RightCalibADCValue",val);
	return val;      // also an assignement operator return the assigned value !
}

long setLeftCalibADC(long val)
{
	privateLeftCalibADCValue = val;
	setIniInt("LeftCalibADCValue",val);
	return val;      // also an assignement operator return the assigned value !
}

long setZeroCalibADC(long val)
{
	privateZeroCalibADCValue = val;
	setIniInt("ZeroCalibADCValue",val);
	return val;      // also an assignement operator return the assigned value !
}

int isCalibValid()
{
	int res = 0;
	if (   // need to be somewhat in reasonable region
			 ( (getZeroCalibADC() + 50) < getRightCalibADC() )
			&& ( getLeftCalibADC() < (getZeroCalibADC() - 50) ) ) {
		res = 1;
	} else if (  ( (getZeroCalibADC() + 50) < getLeftCalibADC() )
				   && ( getRightCalibADC() < (getZeroCalibADC() - 50) ) ) {
		res = 1;
	}
	return res;
}

long torqueNcmFromADC(long adcV)
{
	double Tres = 0.0;
	double dT;
	double dA;
	double Arel;
	long res = 0;
	if (isCalibValid()) {
		if (adcV > getZeroCalibADC()) {
			dA = (getRightCalibADC() - getZeroCalibADC());
			dT = getRightCalibTorque();
			Arel = (double) (adcV - getZeroCalibADC());
			Tres = Arel * (dT/dA);
			res = (long) (Tres + 0.5); // 0.5 for rounding
		} else if(adcV < getZeroCalibADC()) {
			dA = (getLeftCalibADC() - getZeroCalibADC());
			dT = getLeftCalibTorque();
			Arel = (double) (adcV - getZeroCalibADC());
			Tres = Arel * (dT/dA);
			res = (long) (Tres + 0.5); // 0.5 for rounding
			} else {
				dT=0.0;
				dA=1.0;
				res = 0;
		}
	}
	return  res;
}




pthread_mutex_t mcMutex  = PTHREAD_MUTEX_INITIALIZER;


int isTorqueMeterDeviceRunning()
{
	int res = FALSE;
	pthread_mutex_lock( &mcMutex );
	res = deviceRunning;
	pthread_mutex_unlock( &mcMutex );
	return res;
}

void setDeviceRunning(int runOK)
{
	pthread_mutex_lock( &mcMutex );
	deviceRunning = runOK;
	pthread_mutex_unlock( &mcMutex );
}


void setStopCond()
{
	pthread_mutex_lock( &mcMutex );
	torqueMeterStopCond = 1;
	pthread_mutex_unlock( &mcMutex );
}

long incMeasure(double  torqueADCVal)
{
	long res;

	pthread_mutex_lock( &mcMutex );
	res = (measureCount ++);
	adcValue = torqueADCVal;
	deviceRunning = TRUE;

	pthread_mutex_unlock( &mcMutex );
	return res;
}


// the safest way to terminate an other thread
int isStopCondSet()
{
	pthread_mutex_lock( &mcMutex );
	int res = torqueMeterStopCond;
	pthread_mutex_unlock( &mcMutex );

	return (res);
}


int getSensorValues()
{
	char buffer [300];
	long amtRcv = 0;

	memset(&buffer, 0, sizeof(buffer));

	delay (200); // wait 0.2 sec for the case, if last Read_port started during
	                 // receiption of a message, because last Read_port will only leave the
					 // Read_port call after having received amtRcv charachters - again in mid of a 
					 // message. This delay helps to come out of this "looping" situation.
					// (see also timeout and vmin behaviour of unix serial comms methods, which
					// lacks oridnary wait-for-message-timeout and inter-character-timeout
					// pn 15. sept 12

	Read_port(&buffer, sizeof(buffer), &amtRcv);

//	sleep(10);   // pn 19. sept 12 set temporarely to test threading without uart beeing used

// #pragma "todo:  set size of message"
// applicationMsgSize defined in CSerial.h !
	if (amtRcv == applicationMsgSize) {

		char* torqueS;
		long mCnt;

		torqueS = strstr(buffer,"01V")+4;
		*(torqueS+5) = 0;

		long torqueI = strtoul(torqueS ,NULL,0x0A);

/*		long teI, hyI;
		int res;
		res = sscanf(tempS,"%X",&teI);
		res = sscanf(hydS,"%X",&hyI);
*/
//		double temp = tempI / 100;
//		double hyd = hydI / 200;

		mCnt = incMeasure(torqueI); // sets also deviceRunning true
//		info_printf("Step %i temp V01: %s %f / hyd V02: %s %f\n",mCnt,tempS, temp,hydS, hyd);
	} else
	{
		setDeviceRunning(FALSE);
	}
	return  TRUE;
}

void* torqueMeterThreadMethod(void* parm)
{
	int step = 0;

    while (! isStopCondSet()) {
		++ step;

		if (! getSensorValues()) {

		}
	}
	return 0;
}


void initCalibrateDialog( )
{
	long highCT = getRightCalibTorque();
	long lowCT = getLeftCalibTorque();
	long lowADC =  getLeftCalibADC();
	long highADC = getRightCalibADC();
	long zeroADC  = getZeroCalibADC();
	long invSet = getInvertRL();

	PtSetResource( ABW_PtNumericIntegerRightTurnCalibTorque, Pt_ARG_NUMERIC_VALUE, highCT, 0);
	PtSetResource( ABW_PtNumericIntegerLeftTurnCalibTorque, Pt_ARG_NUMERIC_VALUE, lowCT, 0);
	PtSetResource( ABW_PtNumericIntegerRightTurnCalibADC, Pt_ARG_NUMERIC_VALUE, highADC, 0);
	PtSetResource( ABW_PtNumericIntegerLeftTurnCalibADC, Pt_ARG_NUMERIC_VALUE, lowADC, 0);
	PtSetResource( ABW_PtNumericIntegerZeroCalibADC, Pt_ARG_NUMERIC_VALUE, zeroADC, 0);

	if (invSet) {
		PtSetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, Pt_TRUE, Pt_SET);
	} else {
		PtSetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, Pt_FALSE, Pt_SET);
	}

/*
	PtSetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, Pt_TRUE, Pt_SET);
	PtGetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, &testGet, Pt_SET);
	testGetVal = *testGet & Pt_SET ;
	testGetVal = PtWidgetFlags( ABW_PtToggleButtonInvertRL ) & Pt_SET;

	PtSetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, Pt_FALSE, Pt_SET);
	PtGetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, &testGet, Pt_SET);
	testGetVal = *testGet & Pt_SET   ;
	testGetVal = PtWidgetFlags( ABW_PtToggleButtonInvertRL ) & Pt_SET;

	if ( PtWidgetFlags( ABW_PtToggleButtonInvertRL ) & Pt_SET )   {
		testGetVal = 1;
	} else {
		testGetVal= 0;
	}
//	PtGetResource(ABW_PtToggleButtonInvertRL, Pt_ARG_FLAGS, &testGet, Pt_SET);
//	testGetVal = *testGet;
 *
 */
}



void getTorqueMeterValues( long* torqADCValue,  long* cnt, char* stateText, int maxChars)
{
	int running;
	pthread_mutex_lock( &mcMutex );
	*torqADCValue = adcValue;
	*cnt = measureCount;
	running = deviceRunning;
	pthread_mutex_unlock( &mcMutex );
	if (!running) {
		strncpy(stateText,"sensor not ready",maxChars);
		stateText[maxChars-1] = 0;
	}
}

long getAdcValue()
{
	return adcValue;
}


int startTorqueMeter()
{
	int res = tmFailed;

	if (!TMstarted) {
		checkInitialization();
		torqueMeterStopCond = 0;
		createCSerial();
		Open_port();

		/*
		 * pn 19. sept 12, leave this evaluation for later , and continue with default attributes right now.
		 * but finally priority of the serial thread should be somewhat higher than the application thread's prio
		 * and system preemptive threads should be used for this purpose.
		 *
		pthread_attr_t thAttr;
		int scope;
		int ret;

		ret = pthread_attr_init(&thAttr);
		ret = pthread_attr_getscope(&thAttr,&scope);
		printf("pthread getScope returned %i, scopeval %i (proc/syst %i/%i ) \n",ret,scope,
				PTHREAD_SCOPE_PROCESS,PTHREAD_SCOPE_SYSTEM);
		*/


		pthread_create( &torqueMeterThread, NULL,&torqueMeterThreadMethod, NULL);
		TMstarted = 1;
		res = tmOK;
	}
	return res;
}


int stopTorqueMeter()
{
//	DWORD tmOut;
	int res = tmFailed;

	if (TMstarted) {
		setStopCond();

		/*
		tmOut = GBSerialReadTotalTimeoutConstant  \
				+ GBReadIntervalTimeout  \
				+ 2000;  //  max calculation time
		*/

		pthread_join(torqueMeterThread,NULL);    // pn 22. sept 12,     Angstroem linux library:
											// timeout would be desirable, but not possible via join (timedjoin), seems not be supported
											// in the library, according to pthread.h. Could be implemented by slowly polling for
											// a thread-terminated-variable with max counter condition. Or with a call to
											// pthread_cond_timedwait when waiting for a thread terminated condition
											// currently left this point open for later implementation

		// pn 8. Jun 12: also qnx does not allow timeout on pthread_join, nor does it implement
		//  any evident read timeouts on raw "posix-serial-transfers"..  annoying
#pragma todo:"implement and test the cow-boy way of thread termination (hava gun'n'just kill'em)"


		Close_port();
		destructCSerial();
		TMstarted = 0;
		res = tmOK;
	}
	return res;
}


