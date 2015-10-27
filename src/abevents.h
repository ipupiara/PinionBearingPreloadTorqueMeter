/* Event header for application - AppBuilder 2.03  */

static const ApEventLink_t AbApplLinks[] = {
	{ 3, 0, 0L, 0L, 0L, &PinionBearingPreloadTorqueMeter, NULL, NULL, 0, NULL, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_PinionBearingPreloadTorqueMeter[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PinionBearingPreloadTorqueMeter", 1013, UnRealizeMainWidget, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PinionBearingPreloadTorqueMeter", 1012, realizedMainWidget, 0, 0, 0, 0, },
	{ 5, 0, 0L, 0L, 0L, &FileMenu, NULL, "FileMenuButton", 2007, NULL, 0, 1, 0, 0, },
	{ 5, 0, 0L, 0L, 0L, &EditMenu, NULL, "EditMenuButton", 2007, NULL, 0, 1, 0, 0, },
	{ 5, 0, 0L, 0L, 0L, &HelpMenu, NULL, "PtMenuButtonHelp", 2007, NULL, 0, 1, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtTimerTMWidget", 41002, onTimerTMWidget, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_aboutDlg[] = {
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "PtButtonAboutDone", 2009, NULL, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_calibrateDialog[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "calibrateDialog", 18023, onOpenCalibrateDialog, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButtonRightTurnReady", 2009, rightTurnCalibReady, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButtonLeftTurnReady", 2009, leftTurnCalibReady, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "PtButtonCalibOk", 2009, calibOK, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButtonZeroNcmNow", 2009, onButtonPressedZeroNcmNow, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtTimerCalibDia", 41002, onTimerCalibDia, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtToggleButtonInvertRL", 2009, InvertLRPressed, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_FileMenu[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "fileQuitMenuItem", 2009, quit, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_EditMenu[] = {
	{ 4, 0, 0L, 0L, 0L, &calibrateDialog, NULL, "CalibrateMenuItem", 2009, setupCalibrateDialog, 0, 9, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_HelpMenu[] = {
	{ 4, 0, 0L, 0L, 0L, &aboutDlg, NULL, "AboutMenuItem", 2009, NULL, 0, 9, 0, 0, },
	{ 0 }
	};

const char ApOptions[] = AB_OPTIONS;
