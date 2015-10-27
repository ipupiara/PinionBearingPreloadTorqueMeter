/* Define header for application - AppBuilder 2.03  */

/* 'PinionBearingPreloadTorqueMeter' Window link */
extern const int ABN_PinionBearingPreloadTorqueMeter;
#define ABW_PinionBearingPreloadTorqueMeter  AbGetABW( ABN_PinionBearingPreloadTorqueMeter )
extern const int ABN_FileMenuButton;
#define ABW_FileMenuButton                   AbGetABW( ABN_FileMenuButton )
extern const int ABN_EditMenuButton;
#define ABW_EditMenuButton                   AbGetABW( ABN_EditMenuButton )
extern const int ABN_PtMenuButtonHelp;
#define ABW_PtMenuButtonHelp                 AbGetABW( ABN_PtMenuButtonHelp )
extern const int ABN_PtMeterTorque;
#define ABW_PtMeterTorque                    AbGetABW( ABN_PtMeterTorque )
extern const int ABN_PtNumericIntegerTorque;
#define ABW_PtNumericIntegerTorque           AbGetABW( ABN_PtNumericIntegerTorque )
extern const int ABN_PtNumericIntegerADC;
#define ABW_PtNumericIntegerADC              AbGetABW( ABN_PtNumericIntegerADC )
extern const int ABN_PtTimerTMWidget;
#define ABW_PtTimerTMWidget                  AbGetABW( ABN_PtTimerTMWidget )

/* 'aboutDlg' Dialog link */
extern const int ABN_aboutDlg;
#define ABW_aboutDlg                         AbGetABW( ABN_aboutDlg )
extern const int ABN_PtButtonAboutDone;
#define ABW_PtButtonAboutDone                AbGetABW( ABN_PtButtonAboutDone )

/* 'calibrateDialog' Dialog link */
extern const int ABN_calibrateDialog;
#define ABW_calibrateDialog                  AbGetABW( ABN_calibrateDialog )
extern const int ABN_PtNumericIntegerRightTurnCalibTorque;
#define ABW_PtNumericIntegerRightTurnCalibTorque AbGetABW( ABN_PtNumericIntegerRightTurnCalibTorque )
extern const int ABN_PtNumericIntegerLeftTurnCalibTorque;
#define ABW_PtNumericIntegerLeftTurnCalibTorque AbGetABW( ABN_PtNumericIntegerLeftTurnCalibTorque )
extern const int ABN_PtButtonRightTurnReady;
#define ABW_PtButtonRightTurnReady           AbGetABW( ABN_PtButtonRightTurnReady )
extern const int ABN_PtButtonLeftTurnReady;
#define ABW_PtButtonLeftTurnReady            AbGetABW( ABN_PtButtonLeftTurnReady )
extern const int ABN_PtButtonCalibOk;
#define ABW_PtButtonCalibOk                  AbGetABW( ABN_PtButtonCalibOk )
extern const int ABN_PtNumericIntegerRightTurnCalibADC;
#define ABW_PtNumericIntegerRightTurnCalibADC AbGetABW( ABN_PtNumericIntegerRightTurnCalibADC )
extern const int ABN_PtNumericIntegerLeftTurnCalibADC;
#define ABW_PtNumericIntegerLeftTurnCalibADC AbGetABW( ABN_PtNumericIntegerLeftTurnCalibADC )
extern const int ABN_PtButtonZeroNcmNow;
#define ABW_PtButtonZeroNcmNow               AbGetABW( ABN_PtButtonZeroNcmNow )
extern const int ABN_PtNumericIntegerZeroCalibADC;
#define ABW_PtNumericIntegerZeroCalibADC     AbGetABW( ABN_PtNumericIntegerZeroCalibADC )
extern const int ABN_PtNumericIntegerCurrentADC;
#define ABW_PtNumericIntegerCurrentADC       AbGetABW( ABN_PtNumericIntegerCurrentADC )
extern const int ABN_PtTimerCalibDia;
#define ABW_PtTimerCalibDia                  AbGetABW( ABN_PtTimerCalibDia )
extern const int ABN_PtToggleButtonInvertRL;
#define ABW_PtToggleButtonInvertRL           AbGetABW( ABN_PtToggleButtonInvertRL )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

/* 'FileMenu' Menu link */
extern const int ABN_FileMenu;
extern const int ABN_fileQuitMenuItem;

/* 'EditMenu' Menu link */
extern const int ABN_EditMenu;
extern const int ABN_CalibrateMenuItem;

/* 'HelpMenu' Menu link */
extern const int ABN_HelpMenu;
extern const int ABN_AboutMenuItem;

#define AB_OPTIONS "s:x:y:h:w:S:"
