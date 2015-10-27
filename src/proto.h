
/* CSerial.c */
void createCSerial ( void );
void destructCSerial ( void );
int Open_port ( void );
int Configure_port ( void );
int Write_port ( char *buffer , long len , long *dwBytesTransferred );
int Read_port ( void *lpBuffer , long len , long *dwBytesTransferred );
int Close_port ( void );
int isConnected ( void );

/* InvertLRPressed.c */
int InvertLRPressed ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* UnRealizeMainWidget.c */
int UnRealizeMainWidget ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* abmain.c */

/* calibOK.c */
int calibOK ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* leftTurnCalibReady.c */
int leftTurnCalibReady ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* minIni.c
#define assert ( int e );
int ini_gets ( const TCHAR *Section , const TCHAR *Key , const TCHAR *DefValue , TCHAR *Buffer , int BufferSize , const TCHAR *Filename );
long ini_getl ( const TCHAR *Section , const TCHAR *Key , long DefValue , const TCHAR *Filename );
INI_REAL ini_getf ( const TCHAR *Section , const TCHAR *Key , INI_REAL DefValue , const TCHAR *Filename );
int ini_getbool ( const TCHAR *Section , const TCHAR *Key , int DefValue , const TCHAR *Filename );
int ini_getsection ( int idx , TCHAR *Buffer , int BufferSize , const TCHAR *Filename );
int ini_getkey ( const TCHAR *Section , int idx , TCHAR *Buffer , int BufferSize , const TCHAR *Filename );
int ini_browse ( INI_CALLBACK Callback , const void *UserData , const TCHAR *Filename );
int ini_puts ( const TCHAR *Section , const TCHAR *Key , const TCHAR *Value , const TCHAR *Filename );
int ini_putl ( const TCHAR *Section , const TCHAR *Key , long Value , const TCHAR *Filename );
int ini_putf ( const TCHAR *Section , const TCHAR *Key , INI_REAL Value , const TCHAR *Filename );
int strnicmp ( const TCHAR *s1 , const TCHAR *s2 , size_t n );

 onButtonPressedZeroNcmNow.c */
int onButtonPressedZeroNcmNow ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* onOpenCalibrateDialog.c */
int onOpenCalibrateDialog ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* onTimerCalibDia.c */
int onTimerCalibDia ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* onTimerTMWidget.c */
int onTimerTMWidget ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* quit.c */
int quit ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* realizedMainWidget.c */
int realizedMainWidget ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* rightTurnCalibReady.c */
int rightTurnCalibReady ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* setupCalibrateDialog.c */
int setupCalibrateDialog ( PtWidget_t *link_instance , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* torqueMeter.c */
void setIniFilePath ( void );
double getIniValue ( char *id , double defaultVal );
double setIniValue ( char *id , double val );
int getIniInt ( char *id , int defaultVal );
int setIniInt ( char *id , long val );
void checkInitialization ( void );
int getRightCalibTorque ( void );
int setInvertRL ( int val );
int getInvertRL ( void );
int setRightCalibTorque ( int val );
int getLeftCalibTorque ( void );
int setLeftCalibTorque ( int val );
long getRightCalibADC ( void );
long getLeftCalibADC ( void );
long getZeroCalibADC ( void );
long setRightCalibADC ( long val );
long setLeftCalibADC ( long val );
long setZeroCalibADC ( long val );
int isCalibValid ( void );
long torqueNcmFromADC ( long adcV );
int isTorqueMeterDeviceRunning ( void );
void setDeviceRunning ( int runOK );
void setStopCond ( void );
long incMeasure ( double torqueADCVal );
int isStopCondSet ( void );
int getSensorValues ( void );
void *torqueMeterThreadMethod ( void *parm );
void initCalibrateDialog ( void );
void getTorqueMeterValues ( long *torqADCValue , long *cnt , char *stateText , int maxChars );
long getAdcValue ( void );
int startTorqueMeter ( void );
int stopTorqueMeter ( void );
