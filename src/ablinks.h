/* Link header for application - AppBuilder 2.03  */

extern ApContext_t AbContext;

ApWindowLink_t PinionBearingPreloadTorqueMeter = {
	"PinionBearingPreloadTorqueMeter.wgtw",
	&AbContext,
	AbLinks_PinionBearingPreloadTorqueMeter, 0, 6
	};

ApDialogLink_t aboutDlg = {
	"aboutDlg.wgtd",
	&AbContext,
	AbLinks_aboutDlg, 8, 1
	};

ApDialogLink_t calibrateDialog = {
	"calibrateDialog.wgtd",
	&AbContext,
	AbLinks_calibrateDialog, 10, 7
	};

static ApItem_t ApItems_FileMenu[ 2 ] = {
	{ 1, 1, 0, NULL, 0, "fileQuitMenuItem", "Quit", NULL },
	{ 0, 0, NULL, NULL, 0, NULL, NULL, NULL } };

ApMenuLink_t FileMenu = {
	"FileMenu",
	"",
	NULL,
	NULL,
	2,
	ApItems_FileMenu,
	& AbContext,
	AbLinks_FileMenu,
	23, 1, 1
	};

static ApItem_t ApItems_EditMenu[ 2 ] = {
	{ 1, 1, 0, NULL, 0, "CalibrateMenuItem", "Calibrate", NULL },
	{ 0, 0, NULL, NULL, 0, NULL, NULL, NULL } };

ApMenuLink_t EditMenu = {
	"EditMenu",
	"",
	NULL,
	NULL,
	2,
	ApItems_EditMenu,
	& AbContext,
	AbLinks_EditMenu,
	25, 1, 1
	};

static ApItem_t ApItems_HelpMenu[ 2 ] = {
	{ 1, 1, 0, NULL, 0, "AboutMenuItem", "About", NULL },
	{ 0, 0, NULL, NULL, 0, NULL, NULL, NULL } };

ApMenuLink_t HelpMenu = {
	"HelpMenu",
	"",
	NULL,
	NULL,
	2,
	ApItems_HelpMenu,
	& AbContext,
	AbLinks_HelpMenu,
	27, 1, 1
	};

