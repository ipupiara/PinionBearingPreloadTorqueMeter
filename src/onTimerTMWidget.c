/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.03  */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"


#define tBuffSz  30

int
onTimerTMWidget( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	long    adcV = 0;
	long  tCnt=  0;
	char  tBuffer [tBuffSz];
	long torqueV;
	double adcVD;

	getTorqueMeterValues(&adcV, &tCnt, tBuffer, tBuffSz  );
	adcVD = adcV;
	torqueV = torqueNcmFromADC(adcV);

	if (!(tCnt & 0x01))  {
		if (getInvertRL()) {
			PtSetResource( ABW_PtMeterTorque, Pt_ARG_METER_NEEDLE_POSITION, (-1 * torqueV), 0);
		} else {
			PtSetResource( ABW_PtMeterTorque, Pt_ARG_METER_NEEDLE_POSITION, torqueV, 0);
		}
	}
	PtSetResource( ABW_PtNumericIntegerTorque, Pt_ARG_NUMERIC_VALUE, torqueV, 0);
	PtSetResource( ABW_PtNumericIntegerADC, Pt_ARG_NUMERIC_VALUE, adcV, 0);

	return( Pt_CONTINUE );

	}

