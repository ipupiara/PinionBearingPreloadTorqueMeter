/*
 * torqueMeter.h
 *
 *  Created on: 20.04.2013
 *      Author: duenda
 */

#include "CSerial.h"

#ifndef TORQUEMETER_H_
#define TORQUEMETER_H_

#define tmOK  1
#define tmFailed 0

#define torqueMeterMeasureDelay 1051

int isTorqueMeterDeviceRunning();

int startTorqueMeter();

void getTorqueMeterValues( long* torqADCValue, long* cnt, char* stateText, int maxChars);

int stopTorqueMeter();

long getAdcValue();

int getRightCalibTorque();
int setRightCalibTorque(int val);
int getLeftCalibTorque();
int setLeftCalibTorque(int val);
long getRightCalibADC();
long getLeftCalibADC();
long getZeroCalibADC();
long setRightCalibADC(long val);
long setLeftCalibADC(long val);
long setZeroCalibADC(long val);
long torqueNcmFromADC(long adcV);

#endif /* TORQUEMETER_H_ */
