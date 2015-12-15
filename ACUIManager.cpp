// ACUIManager.cpp: ACUIManager クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACUIManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACUIManager::ACUIManager()
{

}

ACUIManager::~ACUIManager()
{

}

// 何かキーが押された時に終了する。
void ACUIManager::ReqSomeKey(LPCTSTR lpctMsg) 
{
	ads_point aptSel;
	//int iRes;
	
	//acutPrintf("\n'zoom\n"); //###


	//iRes = 
	acedGetPoint(NULL, lpctMsg, aptSel);

	acutPrintf(_T("\nｺﾏﾝﾄﾞ: "));//2006.07.20
}
