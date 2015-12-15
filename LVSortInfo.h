// LVSortInfo.h: LVSortInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LVSORTINFO_H__0A5C9329_33DC_49A6_AF96_9EB82C6A3745__INCLUDED_)
#define AFX_LVSORTINFO_H__0A5C9329_33DC_49A6_AF96_9EB82C6A3745__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListGrid.h"

class LVSortInfo  
{
public:
	LVSortInfo();
	virtual ~LVSortInfo();
	bool m_bAsc;
	int  m_iIdx;

	ListGrid *m_pListGrid;
};

#endif // !defined(AFX_LVSORTINFO_H__0A5C9329_33DC_49A6_AF96_9EB82C6A3745__INCLUDED_)
