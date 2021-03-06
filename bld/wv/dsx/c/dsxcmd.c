/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include <ctype.h>
#include "dbgdefn.h"
#include "dbgdata.h"
#include "dosscrn.h"
#include "dbgio.h"
#include "dbgname.h"
#include "dbgwind.h"
#include "dpmi.h"
#include "dbgcmdln.h"
#include "dbglkup.h"


#define MAX_CMDLINE_LEN         128
#define PSP_CMDTAIL_OFF         0x80

extern char             DPMICheck;
extern addr_seg         _psp;

static char             *cmdStart;

static const char SysOptNameTab[] = {
    "CHecksize\0"
    "NOCHarremap\0"
    "NOGraphicsmouse\0"
    "Heapenable\0"
    "XXNODPMI\0"                /* DON'T DOCUMENT: Internal use only */
    "XXDPMI\0"                  /* DON'T DOCUMENT: Internal use only */
};

enum {
   OPT_CHECKSIZE,
   OPT_NOREMAP,
   OPT_NOGMOUSE,
   OPT_HEAPENABLE,
   OPT_XXNODPMI,
   OPT_XXDPMI,
};

gui_window_styles WndStyle = GUI_PLAIN+GUI_GMOUSE;


bool OptDelim( char ch )
{
    return( ch == '/' || ch == '-' );
}


/*
 * ProcSysOption -- process system option
 */

bool ProcSysOption( const char *start, unsigned len, int pass )
{
    unsigned long   num;

    pass=pass;
    switch( Lookup( SysOptNameTab, start, len ) ) {
    case OPT_NOREMAP:
        WndStyle &= ~GUI_CHARMAP_DLG;
        break;
    case OPT_NOGMOUSE:
        WndStyle &= ~GUI_CHARMAP_MOUSE;
        break;
    case OPT_CHECKSIZE:
        num = GetMemory();
        if( num < 32*1024UL ) num = 32*1024UL;
        if( num > 640*1024UL ) num = 640*1024UL;
        CheckSize = num / 16; /* Checksize is in paragraphs */
        break;
    case OPT_HEAPENABLE:
        _SwitchOn( SW_KEEP_HEAP_ENABLED );
        break;
    case OPT_XXNODPMI:
        DPMICheck = 1;
        break;
    case OPT_XXDPMI:
        DPMICheck = 2;
        break;
    default:
        return( false );
    }
    return( true );
}


/*
 * ProcSysOptInit -- initial system options
 */

void ProcSysOptInit( void )
{
    char                *ptr;

    CheckSize = 0;
    MemSize = 2L*1024*1024;
#ifdef __OSI__
    {
        extern char *_LpCmdLine;
        cmdStart = _LpCmdLine;
        ptr = ptr;
    }
#else
    ptr = (char *)( (unsigned_8 *)DPMIGetSegmentBaseAddress( _psp ) + PSP_CMDTAIL_OFF );
    ptr[*(unsigned_8 *)ptr + 1] = NULLCHAR;
    cmdStart = (char *)( (unsigned_8 *)ptr + 1 );
#endif
}


char *GetCmdArg( int num )
{
    return( num ? NULL : cmdStart );
}

void SetCmdArgStart( int num, char *ptr )
{
    num = num; /* must be zero */
    cmdStart = ptr;
}
