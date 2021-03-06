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
* Description:  String to double conversion helper routine.
*
****************************************************************************/


#include "variety.h"
#include <stdlib.h>
#include <stdarg.h>
#include "myvalist.h"
#include "xfloat.h"
#include "farsupp.h"
#include "printf.h"
#include "fltsupp.h"


/* This routine is called from scnf.c */

VISIBILITY void __cnvs2d( char *buf, double *value )
{
    *value = strtod( buf, NULL );
}

#if defined( __MAKE_DLL_MATHLIB )
_type_EFG_cnvs2d *__get_EFG_cnvs2d( void )
{
    return( &__cnvs2d );
}
#endif
