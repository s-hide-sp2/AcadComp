// ACSort.h: ACSort クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACSORT_H__6592ED89_84C9_43AC_A40F_17A5D7802723__INCLUDED_)
#define AFX_ACSORT_H__6592ED89_84C9_43AC_A40F_17A5D7802723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ACCMap.h"

class ACSort  
{
public:
	ACSort();
	virtual ~ACSort();
	
	// 文字列のソート
	void QSort(
		CMap<int, int, CString, CString> &strmapSrc, 
		CMap<int, int, int, int> &lmapRet);
	
	// 昇順、降順を指定する。true: 昇順, false: 降順
	void SetAsc(bool bAsc);

private:
	int m_iAsc;   // 1: 昇順、 -1: 降順
	
	// クイックソート（再帰用）
	void QSortRecur(
		CMap<int, int, CString, CString> &strmapSrc, 
		CMap<int, int, int, int> &imapRet, int iLow, int iHigh);	
	
};	

#endif // !defined(AFX_ACSORT_H__6592ED89_84C9_43AC_A40F_17A5D7802723__INCLUDED_)
