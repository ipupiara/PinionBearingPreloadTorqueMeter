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
setupCalibrateDialog( PtWidget_t *link_instance, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	/* eliminate 'unreferenced' warnings */
	link_instance = link_instance, apinfo = apinfo, cbinfo = cbinfo;

//  retrieve fValue (restored on application intialization

//	long fValue = 0;

//	if (cbinfo->reason == 0)   some kind of checking if called on open or close ?
//	{
//		PtSetResource( ABW_PtNumericIntegerRightTurnCalibTorque, Pt_ARG_NUMERIC_VALUE, fValue, 0);
//	}

	return( Pt_CONTINUE );

	}

