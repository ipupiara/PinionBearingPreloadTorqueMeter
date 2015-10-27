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
calibOK( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

//	double * fValue = 0;

//	if (cbinfo->reason == 0)   some kind of checking if called on open or close ?
//	{
//		PtGetResource( ABW_PtNumericFloatRightTurnCalibTorque, Pt_ARG_NUMERIC_VALUE,
//				(long) fValue, 0);
//	}

//  store fValue

	return( Pt_CONTINUE );

	}

