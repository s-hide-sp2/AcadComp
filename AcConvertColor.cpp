// AcConvertColor.cpp: AcConvertColor クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "AcConvertColor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

AcConvertColor::AcConvertColor()
{

}

AcConvertColor::~AcConvertColor()
{

}

CString AcConvertColor::GetColorStr(int iColIdx)
{	
	CString strTmp;

	switch (iColIdx) {		
		case 1:
			return CString(_T("Red"));			
		case 2:
			return CString(_T("Yellow"));
		case 3:
			return CString(_T("Green"));
		case 4:
			return CString(_T("Cyan"));
		case 5:
			return CString(_T("Blue"));	
		case 6:
			return CString(_T("Magenta"));
		case 7:
			return CString(_T("White"));  // or Black
		default:
			strTmp.Format(_T("%d"), iColIdx);
			return strTmp;			
	}
}
