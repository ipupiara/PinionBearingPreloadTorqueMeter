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


int
leftTurnCalibReady( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	long adcV= getAdcValue();


	setLeftCalibADC ( adcV );
	long ctv =0;
	long* ctvp;

	PtSetResource( ABW_PtNumericIntegerLeftTurnCalibADC, Pt_ARG_NUMERIC_VALUE, adcV, 0);

//	PtGetResource( ABW_PtNumericIntegerLeftTurnCalibTorque, Pt_ARG_NUMERIC_VALUE, &ctv, 0);
//	setLowCalibTorque(ctv);

	PtGetResource( ABW_PtNumericIntegerLeftTurnCalibTorque, Pt_ARG_NUMERIC_VALUE, &ctvp, 0);
	ctv = *ctvp;
	setLeftCalibTorque(ctv);


	return( Pt_CONTINUE );

	}

