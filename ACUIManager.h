// ACUIManager.h: ACUIManager クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACUIMANAGER_H__09D95F28_3F51_4B55_AA1B_39DF6FBA4281__INCLUDED_)
#define AFX_ACUIMANAGER_H__09D95F28_3F51_4B55_AA1B_39DF6FBA4281__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACUIManager  
{
public:
	ACUIManager();
	virtual ~ACUIManager();
	
	void ReqSomeKey(LPCTSTR lpctMsg);
};

#endif // !defined(AFX_ACUIMANAGER_H__09D95F28_3F51_4B55_AA1B_39DF6FBA4281__INCLUDED_)
