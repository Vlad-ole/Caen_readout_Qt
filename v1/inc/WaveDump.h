/******************************************************************************
* 
* CAEN SpA - Front End Division
* Via Vetraia, 11 - 55049 - Viareggio ITALY
* +390594388398 - www.caen.it
*
***************************************************************************//**
* \note TERMS OF USE:
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation. This program is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. The user relies on the 
* software, documentation and results solely at his own risk.
******************************************************************************/

#ifndef _WAVEDUMP_H_
#define _WAVEDUMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <fstream.h>
#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>

#ifdef WIN32

    #include <time.h>
    #include <sys/timeb.h>
    #include <conio.h>
    #include <process.h>

	#define getch _getch     /* redefine POSIX 'deprecated' */
	#define kbhit _kbhit     /* redefine POSIX 'deprecated' */

	#define		_PACKED_
	#define		_INLINE_		

#else
    #include <unistd.h>
    #include <stdint.h>   /* C99 compliant compilers: uint64_t */
    #include <ctype.h>    /* toupper() */
    #include <sys/time.h>

	#define		_PACKED_		__attribute__ ((packed, aligned(1)))
	#define		_INLINE_		__inline__ 

#endif

#ifdef LINUX
#define DEFAULT_CONFIG_FILE  "/etc/wavedump/WaveDumpConfig.txt"
#define GNUPLOT_DEFAULT_PATH ""
#else
#define DEFAULT_CONFIG_FILE  "WaveDumpConfig.txt"  /* local directory */
#define GNUPLOT_DEFAULT_PATH ""
#endif

#define OUTFILENAME "wave"  /* The actual file name is wave_n.txt, where n is the channel */
#define MAX_CH  64          /* max. number of channels */
#define MAX_SET 16           /* max. number of independent settings */

#define MAX_GW  1000        /* max. number of generic write commads */

#define PLOT_REFRESH_TIME 1000

#define VME_INTERRUPT_LEVEL      1
#define VME_INTERRUPT_STATUS_ID  0xAAAA
#define INTERRUPT_MODE           CAEN_DGTZ_IRQ_MODE_ROAK
#define INTERRUPT_TIMEOUT        200  // ms
        
#define PLOT_WAVEFORMS   0
#define PLOT_FFT         1
#define PLOT_HISTOGRAM   2

#define CFGRELOAD_CORRTABLES_BIT (0)
#define CFGRELOAD_DESMODE_BIT (1)

/* ###########################################################################
   Typedefs
   ###########################################################################
*/

typedef enum {
	OFF_BINARY=	0x00000001,			// Bit 0: 1 = BINARY, 0 =ASCII
	OFF_HEADER= 0x00000002,			// Bit 1: 1 = include header, 0 = just samples data
} OUTFILE_FLAGS;


typedef struct {
    int LinkType;
    int LinkNum;
    int ConetNode;
    uint32_t BaseAddress;
    int Nch;
    int Nbit;
    float Ts;
    int NumEvents;
    uint32_t RecordLength;
    int PostTrigger;
    int InterruptNumEvents;
    int TestPattern;
    CAEN_DGTZ_EnaDis_t DesMode;
    int TriggerEdge;
    CAEN_DGTZ_IOLevel_t FPIOtype;
    CAEN_DGTZ_TriggerMode_t ExtTriggerMode;
    uint16_t EnableMask;
    char GnuPlotPath[1000];
    CAEN_DGTZ_TriggerMode_t ChannelTriggerMode[MAX_SET];
    uint32_t DCoffset[MAX_SET];
    int32_t  DCoffsetGrpCh[MAX_SET][MAX_SET];
    uint32_t Threshold[MAX_SET];
	uint8_t GroupTrgEnableMask[MAX_SET];
    uint32_t MaxGroupNumber;
	
	uint32_t FTDCoffset[MAX_SET];
	uint32_t FTThreshold[MAX_SET];
	CAEN_DGTZ_TriggerMode_t	FastTriggerMode;
	uint32_t	 FastTriggerEnabled;
    int GWn;
    uint32_t GWaddr[MAX_GW];
    uint32_t GWdata[MAX_GW];
	uint32_t GWmask[MAX_GW];
	OUTFILE_FLAGS OutFileFlags;
	uint16_t DecimationFactor;
    int useCorrections;
    int UseManualTables;
    char TablesFilenames[MAX_X742_GROUP_SIZE][1000];
    CAEN_DGTZ_DRS4Frequency_t DRS4Frequency;
} WaveDumpConfig_t;


typedef struct WaveDumpRun_t {
    int Quit;
    int AcqRun;
    int PlotType;
    int ContinuousTrigger;
    int ContinuousWrite;
    int SingleWrite;
    int ContinuousPlot;
    int SinglePlot;
    int SetPlotOptions;
    int GroupPlotIndex;
    int ChannelPlotMask;
    int Restart;
    int RunHisto;
    uint32_t *Histogram[MAX_CH];
    FILE *fout[MAX_CH];
} WaveDumpRun_t;





//vlad change start
//------------------------------------------------------------------------

#define WaveDump_Release        "3.7.0_20151030"
#define WaveDump_Release_Date   "Oct 2015"
#define DBG_TIME


/* Error messages */
typedef enum  {
    ERR_NONE= 0,
    ERR_CONF_FILE_NOT_FOUND,
    ERR_DGZ_OPEN,
    ERR_BOARD_INFO_READ,
    ERR_INVALID_BOARD_TYPE,
    ERR_DGZ_PROGRAM,
    ERR_MALLOC,
    ERR_RESTART,
    ERR_INTERRUPT,
    ERR_READOUT,
    ERR_EVENT_BUILD,
    ERR_HISTO_MALLOC,
    ERR_UNHANDLED_BOARD,
    ERR_OUTFILE_WRITE,
    ERR_OVERTEMP,

    ERR_DUMMY_LAST,
} ERROR_CODES;
static char ErrMsg[ERR_DUMMY_LAST][100] = {
    "No Error",                                         /* ERR_NONE */
    "Configuration File not found",                     /* ERR_CONF_FILE_NOT_FOUND */
    "Can't open the digitizer",                         /* ERR_DGZ_OPEN */
    "Can't read the Board Info",                        /* ERR_BOARD_INFO_READ */
    "Can't run WaveDump for this digitizer",            /* ERR_INVALID_BOARD_TYPE */
    "Can't program the digitizer",                      /* ERR_DGZ_PROGRAM */
    "Can't allocate the memory for the readout buffer", /* ERR_MALLOC */
    "Restarting Error",                                 /* ERR_RESTART */
    "Interrupt Error",                                  /* ERR_INTERRUPT */
    "Readout Error",                                    /* ERR_READOUT */
    "Event Build Error",                                /* ERR_EVENT_BUILD */
    "Can't allocate the memory fro the histograms",     /* ERR_HISTO_MALLOC */
    "Unhandled board type",                             /* ERR_UNHANDLED_BOARD */
    "Output file write error",                          /* ERR_OUTFILE_WRITE */
    "Over Temperature",									/* ERR_OVERTEMP */

};

//-------------------------------------------------------------------------
//vlad change stop

/* Function prototypes */
int ParseConfigFile(FILE *f_ini, WaveDumpConfig_t *WDcfg);


#endif /* _WAVEDUMP__H */
