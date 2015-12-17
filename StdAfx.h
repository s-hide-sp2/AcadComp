// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__0B096B40_CC6C_468B_A65F_CD8DCACE5233__INCLUDED_)
#define AFX_STDAFX_H__0B096B40_CC6C_468B_A65F_CD8DCACE5233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786)
//#pragma warning(disable: 4098)

#define STRICT
#ifndef _WIN32_WINNT
// [Taka 2009/06] ARX2010対応  次1行コメントアウト 次1行追加
//#define _WIN32_WINNT 0x0400
#define _WIN32_WINNT 0x0501  //AutoCAD2010はXP以上なので Win2Kは対象外とする
#endif

// 'DEBUG workaround' below prevents the MFC or ATL #include-s 
// from pulling in "afx.h" that would force the debug CRT through
// #pragma-s.
#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#pragma message ("     Compiling MFC header files in release mode.")
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>          // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>         // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// [ADD]
// [Taka 2009/06] ARX2010対応  次1行コメントアウト 次1行追加
//#define AC_ARX2007
#define AC_ARX2010
//#define AC_ARX2013

#if 0

// AutoCAD MFC Extensions:
#include "adui.h"
#include "acui.h"
#include "acuiComboBox.h"
#include "acuiDialog.h"



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif


extern HINSTANCE _hdllInstance ;
#include "rxdebug.h"
// RX Includes
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "aced.h"               // aced stuff
#include "adslib.h"             // RXADS definitions
#include "acdocman.h"           // MDI document manager
#include "rxmfcapi.h"           // ObjectARX MFC support
#include "AcExtensionModule.h"  // Utility class for extension dlls


#include "acdocman.h"
#include "dbsymtb.h" 
#include "acutmem.h"
#include "dbcurve.h" 
#include "dbents.h"
#include "dbhatch.h"
#include "dbelipse.h"
#include "dblead.h" 
#include "dbpl.h"
#include "dbray.h"
#include "dbspline.h"
#include "dbxline.h"
#include "dbfcf.h" 
#include "dbframe.h"
#include "dbole.h" 
#include "dbimage.h"
#include "imgdef.h" 
#include "imgent.h" 
#include "dbproxy.h" 
#include "dbsol3d.h"
#include "dbbody.h" 
#include "dbregion.h"
#include "dbmline.h" 
#include "dbmstyle.h"
#include "acgs.h"
#include "gs.h"
#include "dblayout.h"
#include "AcDbLMgr.h"
#include "acaplmgr.h" 
#include "dbxutil.h" 
#include "geell2d.h"
#include "genurb2d.h"
//#include "brface.h"
//#include "brfltrav.h" 
//#include "brloop.h"
//#include "bredge.h"
//#include "brletrav.h" 
#include "achapi.h"
#include "acedxref.h"

#else

//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
//- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_			//- Support for the BRep API
//#define _HLR_SUPPORT_				//- Support for the Hidden Line Removal API
//#define _AMODELER_SUPPORT_		//- Support for the AModeler API
//#define _ASE_SUPPORT_				//- Support for the ASI/ASE API
//#define _RENDER_SUPPORT_			//- Support for the AutoCAD Render API
//#define _ARX_CUSTOM_DRAG_N_DROP_	//- Support for the ObjectARX Drag'n Drop API
//#define _INC_LEAGACY_HEADERS_		//- Include legacy headers in this project
#include "arxHeaders.h"
//#include "acadi.h"
//-----------------------------------------------------------------------------
#include "DocData.h" //- Your document specific data class holder

#endif

#if defined(AC_ARX2004)
#import "acax16enu.tlb" /*TODO:replace path for TLB */
#elif defined(AC_ARX2007)
#import "acax17enu.tlb" /*TODO:replace path for TLB */
// [Taka 2009/06] ARX2010対応  次2行追加
#elif defined(AC_ARX2010)
#import "acax18enu.tlb" /*TODO:replace path for TLB */

#elif defined(AC_ARX2013)
#import "acax19enu.tlb" /*TODO:replace path for TLB */

#else
#import "acad.tlb" /*TODO:replace path for TLB */
#endif 

//#import "D:\\Program Files\\Object Arx2002\\inc\\acad.tlb" /*TODO:replace path for TLB */
//#include "acad15.h"


#define AC_LEN_HANDLE 20

/* imgent.hでincludeされている
#include "dbents.h"
#include "dbimage.h"
#include "acgi.h"
#include "gept3dar.h"
#include "gebndpln.h"
#include "geplin2d.h"
#include "dbproxy.h"
*/



// [ADD2]
#include <math.h>  

//#include "DialogCompDwg.h"

#ifdef _FULLDEBUG_
#pragma message ("Warning! You should better not run this application in a Standard AutoCAD release.")
#pragma message ("         Due to the memory managment constraints.")
#endif

// Include this here to speed up the compile times
#include "stdarx.h"
#include "StdZfc.h"

#endif // !defined(AFX_STDAFX_H__0B096B40_CC6C_468B_A65F_CD8DCACE5233__INCLUDED)
