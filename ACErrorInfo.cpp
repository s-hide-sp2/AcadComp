// ACErrorInfo.cpp: ACErrorInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACErrorInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACErrorInfo::ACErrorInfo()
{

}

ACErrorInfo::ACErrorInfo(ACEI_TYPE_ERROR eiType, CString strMsg)
{
	m_eiType = eiType;
	m_strMsg = strMsg;
}

ACErrorInfo::~ACErrorInfo()
{

}

// ACEI_TYPE_ERRORに関連した、メッセージボックスのタイプを取得する。
UINT ACErrorInfo::GetMBType(ACEI_TYPE_ERROR eiType)
{
	switch (eiType)
	{
		case INFO:
			return (MB_OK | MB_ICONINFORMATION);			
		case ALERT:
			return (MB_OK | MB_ICONWARNING);
		case ERR:
			return (MB_OK | MB_ICONERROR);
		default:
			return (MB_OK | MB_ICONINFORMATION);
	}
} 

// エラーダイアログを表示する。エラータイプがNONEの場合は表示しない。
void ACErrorInfo::ShowMsgDlg(HWND hWnd, LPCTSTR strCaption)
{
	if (this->m_eiType != NONE)
		MessageBox(hWnd, this->m_strMsg, strCaption, this->GetMBType(this->m_eiType));
}