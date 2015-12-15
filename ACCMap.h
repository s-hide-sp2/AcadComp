// ACCMap.h: ACCMap クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCMAP_H__59AAA95D_CD56_4E53_9B12_34E0EABA510A__INCLUDED_)
#define AFX_ACCMAP_H__59AAA95D_CD56_4E53_9B12_34E0EABA510A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACCMap  
{
public:
	ACCMap();
	virtual ~ACCMap();	
	

	// 文字列型のマップのキーに対応する値を返す。
	static CString GetKeyVal(const CMap<int, int, CString, CString> &strmapSrc, int lKey);

	// int型のマップのキーに対応する値を返す。
	static int GetKeyVal(const CMap<int, int, int, int> &imapSrc, int lKey);	

	// T3型のマップのキーに対応する値を返す。
	//template<class T1, class T2, class T3, class T4> static T3 GetKeyVal(const CMap<T1, T2, T3, T4> &imapSrc, T1 lKey);
};

#endif // !defined(AFX_ACCMAP_H__59AAA95D_CD56_4E53_9B12_34E0EABA510A__INCLUDED_)
