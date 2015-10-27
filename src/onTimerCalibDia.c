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

#define tBuffSz 30

int onTimerCalibDia( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	long    adcV = 0;
	long  tCnt=  0;
	char  tBuffer [tBuffSz];
	long torqueV;

	getTorqueMeterValues(&adcV, &tCnt, tBuffer, tBuffSz  );
	torqueV = torqueNcmFromADC(adcV);

	PtSetResource( ABW_PtNumericIntegerCurrentADC, Pt_ARG_NUMERIC_VALUE, adcV, 0);

	return( Pt_CONTINUE );

	}

