//
// ObjectARX defined commands, created by  [2004/02/06], , 


#include "StdAfx.h"
#include "StdArx.h"

#include "DialogCompDwg.h"
#include "ACCompRect.h"
#include "CheckLisence.h"
#//include "tcUtility.h"
#include "ACDocManager.h"
#include "ACToggleResultDisp.h"

// [Taka 2009/06] ARX2010対応  次1行コメントアウト 
//#define SAMPLE_CAD

//AutoCADのバージョンを取得する
bool GetAcadVersion(CString & aver);

//使用可能期間をチェックする
bool CheckUsableTerm();


//-----------------------------------------------------------------------------
// This is command 'COMPDWG, by  [2004/02/06], , 
void DAACMPCompDwg()
{
#ifdef OARXWIZDEBUG
	acutPrintf (_T("\nOARXWIZDEBUG - DAACMPCompDwg() called."));
#endif // OARXWIZDEBUG

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);//2006.07.20
		return;
	}

	struct resbuf res; 
	acedGetVar(_T("SDI"),&res);//2006.07.20
	if( res.resval.rint == 1 ) {
		AfxMessageBox( _T("SDIモードでは使用できません。") );//2006.07.20
		return;
	}

	DialogCompDwg::CreateInstance();			
}

//-----------------------------------------------------------------------------
// This is command 'COMPRECT, by  [2005/06/13], , 
void DAACMPCOMPRECT()
{
#ifdef OARXWIZDEBUG
	acutPrintf (_T("\nOARXWIZDEBUG - DAACMPCOMPRECT() called."));
#endif // OARXWIZDEBUG

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);//2006.07.20
		return;
	}
	ACCompRect acRect;
	acRect.DrawCompRect();
}

//-----------------------------------------------------------------------------
// This is command 'TEST01, by  [2005/06/13], , 
void DAACMPTEST01()
{
#ifdef OARXWIZDEBUG
	acutPrintf (_T("\nOARXWIZDEBUG - DAACMPTEST01() called."));
#endif // OARXWIZDEBUG

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);//2006.07.20
		return;
	}
	
	ACCompRect acRect;
	acRect.ShowName();

}

//-----------------------------------------------------------------------------
// This is command 'TEST02, by  [2005/06/13], , 
void DAACMPTEST02()
{
#ifdef OARXWIZDEBUG
	acutPrintf (_T("\nOARXWIZDEBUG - DAACMPTEST02() called."));
#endif // OARXWIZDEBUG

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);//2006.07.20
		return;
	}
	ACCompRect acRect;
	acRect.Test02();
}

//-----------------------------------------------------------------------------
// This is command 'DELCOMPRECT, by  [2005/06/13], , 
void DAACMPDELCOMPRECT()
{
#ifdef OARXWIZDEBUG
	acutPrintf (_T("\nOARXWIZDEBUG - DAACMPDELCOMPRECT() called."));
#endif // OARXWIZDEBUG

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);
		return;
	}
	ACCompRect acRect;
	acRect.DeleteCompRect();
}

//AutoCADのバージョンを取得する
bool GetAcadVersion(CString & aver)
{
	TCHAR str[MAX_PATH+1];//2006.07.20
	struct resbuf rbw;

	if (acedGetVar(_T("ACADVER"),&rbw)!=RTNORM){//2006.07.20
		return FALSE;
	}

	_tcscpy(str, rbw.resval.rstring);
	str[4]=0;
	aver = str;
	aver = _T("R")+ aver;
	return true;
}


//使用期間をチェックする
bool CheckUsableTerm()
{
	CString aver, ver;

	GetAcadVersion(ver);


	if (ver.Left(5) == _T("R14.0")) {
		aver = _T("ACADCOMP14");
	}
	else if (ver.Left(5) == _T("R15.0")) {
		aver = _T("ACADCOMP2002");
	}
	else if (ver.Left(5) == _T("R16.0")){
		aver = _T("ACADCOMP2004");
	}
	else if (ver.Left(5) == _T("R16.1")){
		aver = _T("ACADCOMP2005");
	}
	else if (ver.Left(5) == _T("R16.2")){
		aver = _T("ACADCOMP2006");
	}
	//2006.07.01
	else if (ver.Left(5) == _T("R17.0")){
		aver = _T("ACADCOMP2007");
	}
	//2007.05.08
	else if (ver.Left(5) == _T("R17.1")){
		aver = _T("ACADCOMP2008");
	}
	//2008.04.14
	else if (ver.Left(5) == _T("R17.2")){
		aver = _T("ACADCOMP2009");
	}
	else {
		aver = _T("");
	}

#ifdef SAMPLE_CAD
	if (CCheckLisence::CheckUsableTerm(aver, ver)) {
		return true;
	}
	else {
		return false;
	}
#else
	return true;
#endif
}// This is command 'GETSCREENPOS'

//-----------------------------------------------------------------------------
// This is command 'TOGGLEDISPADD, by  [2007/03/13], , 
void DAACMPTOGGLEDISPADD()
{
#ifdef OARXWIZDEBUG
	acutPrintf ("\nOARXWIZDEBUG - DAACMPTOGGLEDISPADD() called.");
#endif // OARXWIZDEBUG

	CAcModuleResourceOverride resOverride;

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);
		return;
	}

	ACToggleResultDisp	acToggleDisp;
	if( !acToggleDisp.IsResultDrawing() ) {
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("合成図面を選択してください。"), _T("警告"), MB_OK);
		return;
	}

	acToggleDisp.ToggleDisp( ACDM_COLOR_NEW );
}

//-----------------------------------------------------------------------------
// This is command 'TOGGLEDISPDELETE, by  [2007/03/13], , 
void DAACMPTOGGLEDISPDELETE()
{
#ifdef OARXWIZDEBUG
	acutPrintf ("\nOARXWIZDEBUG - DAACMPTOGGLEDISPDELETE() called.");
#endif // OARXWIZDEBUG

	CAcModuleResourceOverride resOverride;

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);
		return;
	}

	ACToggleResultDisp	acToggleDisp;
	if( !acToggleDisp.IsResultDrawing() ) {
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("合成図面を選択してください。"), _T("警告"), MB_OK);
		return;
	}

	acToggleDisp.ToggleDisp( ACDM_COLOR_DELETE );
}

//-----------------------------------------------------------------------------
// This is command 'TOGGLEDISPMODIFY, by  [2007/03/13], , 
void DAACMPTOGGLEDISPMODIFY()
{
#ifdef OARXWIZDEBUG
	acutPrintf ("\nOARXWIZDEBUG - DAACMPTOGGLEDISPMODIFY() called.");
#endif // OARXWIZDEBUG

	CAcModuleResourceOverride resOverride;

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);
		return;
	}

	ACToggleResultDisp	acToggleDisp;
	if( !acToggleDisp.IsResultDrawing() ) {
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("合成図面を選択してください。"), _T("警告"), MB_OK);
		return;
	}

	acToggleDisp.ToggleDisp( ACDM_COLOR_NOT_EQUAL );
	acToggleDisp.ToggleDisp( ACDM_PREVMODIFY_COLOR );
}

//-----------------------------------------------------------------------------
// This is command 'TOGGLEDISPSAME, by  [2007/03/13], , 
void DAACMPTOGGLEDISPSAME()
{
#ifdef OARXWIZDEBUG
	acutPrintf ("\nOARXWIZDEBUG - DAACMPTOGGLEDISPSAME() called.");
#endif // OARXWIZDEBUG

	CAcModuleResourceOverride resOverride;

	// TODO: Implement the command
	if (CheckUsableTerm()==false){
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("使用期間が過ぎています。"), _T("警告"), MB_OK);
		return;
	}

	ACToggleResultDisp	acToggleDisp;
	if( !acToggleDisp.IsResultDrawing() ) {
		HWND hWnd = adsw_acadDocWnd();
		MessageBox(hWnd, _T("合成図面を選択してください。"), _T("警告"), MB_OK);
		return;
	}

	acToggleDisp.ToggleDisp( ACDM_COLOR_EQUAL );
}



