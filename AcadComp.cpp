// AcadComp.cpp : Initialization functions
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>

HINSTANCE _hdllInstance =NULL ;

// [ADD]
#include "DialogCompDwg.h"
#include "ACProfileManager.h"
#include "ACCompBase.h"


//DialogCompDwg *g_pDlgComp = NULL;

// This command registers an ARX command.
void AddCommand(const ACHAR* cmdGroup, const ACHAR* cmdInt, const ACHAR* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);


// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(AcadCompDLL);

// Now you can use the CAcModuleResourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
		// Extension DLL one time initialization
		AcadCompDLL.AttachInstance(hInstance);
		InitAcUiDLL();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		AcadCompDLL.DetachInstance();

	}
	return TRUE;    // ok
}



/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	/*
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);

		// ADD
		//if (!acrxClassDictionary->at("AcBrEntity")) {
		//	acrxDynamicLinker->loadModule("acbr15.dll", 1);
		//	acutPrintf("\nlibacbr loaded \n");
		//}

		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;

	*/

		switch (msg) {
	case AcRx::kInvkSubrMsg:
		//dofun();
		break;
	case AcRx::kUnloadDwgMsg:
		//funcunload();
		break;
	case AcRx::kLoadDwgMsg:
		//funcload();
		break;
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		//G_acadhChildWnd = NULL;
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;

}

// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT

	//AddCommand("DAACMP", "COMPDWG", "COMPDWG", ACRX_CMD_SESSION, DAACMPCompDwg);
	//AddCommand("DAACMP", "COMPDWG", "COMPDWG", ACRX_CMD_TRANSPARENT, DAACMPCompDwg);
	AddCommand(_T("DAACMP"), _T("COMPDWG"), _T("COMPDWG"), ACRX_CMD_TRANSPARENT, DAACMPCompDwg);//2006.07.20
	
	AddCommand(_T("DAACMP"), _T("COMPRECT"), _T("COMPRECT"), ACRX_CMD_MODAL, DAACMPCOMPRECT);
	//AddCommand("DAACMP", "TEST01", "TEST01", ACRX_CMD_MODAL, DAACMPTEST01);
	//AddCommand("DAACMP", "TEST02", "TEST02", ACRX_CMD_MODAL, DAACMPTEST02);
	AddCommand(_T("DAACMP"), _T("DELCOMPRECT"), _T("DELCOMPRECT"), ACRX_CMD_MODAL, DAACMPDELCOMPRECT);
	AddCommand(_T("DAACMP"), _T("TOGGLEDISPADD"), _T("TOGGLEDISPADD"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, DAACMPTOGGLEDISPADD);
	AddCommand(_T("DAACMP"), _T("TOGGLEDISPDELETE"), _T("TOGGLEDISPDELETE"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, DAACMPTOGGLEDISPDELETE);
	AddCommand(_T("DAACMP"), _T("TOGGLEDISPMODIFY"), _T("TOGGLEDISPMODIFY"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, DAACMPTOGGLEDISPMODIFY);
	AddCommand(_T("DAACMP"), _T("TOGGLEDISPSAME"), _T("TOGGLEDISPSAME"), ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, DAACMPTOGGLEDISPSAME);
	//}}AFX_ARX_INIT

	// TODO: add your initialization functions	


	// 許容誤差をプロファイルから読み取り、比較クラスのstaticメンバにセットする。
	ACProfileManager pMng;
	double dTol;
	dTol = pMng.GetUserTol();

	ACCompBase::SetTol(dTol);
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup(_T("DAACMP"));//2006.07.20
	//}}AFX_ARX_EXIT

	// TODO: clean up your application		
	DialogCompDwg::DeleteInstance();
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const ACHAR* cmdGroup, const ACHAR* cmdInt, const ACHAR* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	TCHAR cmdLocRes[65]; //2006.07.20

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
