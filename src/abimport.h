/* Import (extern) header for application - AppBuilder 2.03  */

#include "abdefine.h"

extern ApWindowLink_t PinionBearingPreloadTorqueMeter;
extern ApDialogLink_t aboutDlg;
extern ApDialogLink_t calibrateDialog;
extern ApWidget_t AbWidgets[ 23 ];

extern ApMenuLink_t FileMenu;
extern ApMenuLink_t EditMenu;
extern ApMenuLink_t HelpMenu;

#ifdef __cplusplus
extern "C" {
#endif
int quit( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int setupCalibrateDialog( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int calibOK( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int rightTurnCalibReady( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int leftTurnCalibReady( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int onButtonPressedZeroNcmNow( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int UnRealizeMainWidget( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int realizedMainWidget( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int onTimerTMWidget( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int onTimerCalibDia( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int onOpenCalibrateDialog( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int InvertLRPressed( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#ifdef __cplusplus
}
#endif
