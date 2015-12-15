// ACRetType.cpp: ACRetType クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACRetType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int ACRetType::m_i1 = -1;
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACRetType::ACRetType()
{

}

ACRetType::~ACRetType()
{

}

CString ACRetType::GetMsg(ACRETTYPE rType)
{
	CString strMsg;

	switch (rType) {
		case rOk:
			return CString(_T("正常終了")); //2006.07.20		
		case rCommandRunning:
			strMsg.Format(_T("図面%dはコマンド実行中です。"), m_i1);//2006.07.20
			return strMsg;
		case rInvalidDwg:
			strMsg.Format(_T("図面%dは無効です。"), m_i1);//2006.07.20
			return strMsg;
		default:
			strMsg.Empty();
			return strMsg;
	}		
}
	
void ACRetType::SetI1(const int &i)
{
	m_i1 = i;
}


	