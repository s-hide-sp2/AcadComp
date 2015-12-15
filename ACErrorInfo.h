// ACErrorInfo.h: ACErrorInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACERRORINFO_H__659D9B37_D02C_4A61_A8E7_8751954DDF7A__INCLUDED_)
#define AFX_ACERRORINFO_H__659D9B37_D02C_4A61_A8E7_8751954DDF7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACErrorInfo  
{
public:
	enum ACEI_TYPE_ERROR {
		INFO  = 0,
		ALERT = 1,
		ERR   = 2,
		NONE  = 3
	};

	ACErrorInfo();
	ACErrorInfo(ACEI_TYPE_ERROR eiType, CString strMsg);

	virtual ~ACErrorInfo();
	
	// ACEI_TYPE_ERRORに関連した、メッセージボックスのタイプを取得する。
	UINT GetMBType(ACEI_TYPE_ERROR eiType); 


private:

public:
	CString m_strMsg;
	ACEI_TYPE_ERROR m_eiType;

	void ShowMsgDlg(HWND hWnd, LPCTSTR strCaption);
};

#endif // !defined(AFX_ACERRORINFO_H__659D9B37_D02C_4A61_A8E7_8751954DDF7A__INCLUDED_)
