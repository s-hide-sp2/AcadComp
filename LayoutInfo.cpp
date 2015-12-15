// LayoutInfo.cpp: LayoutInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "LayoutInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

LayoutInfo::LayoutInfo()
{

}

LayoutInfo::~LayoutInfo()
{

}

void LayoutInfo::SetInfo(LPCTSTR strName, AcDbObjectId idBlkRec)
{
	m_strLayoutName = strName;
	m_idBlkRec = idBlkRec;
}

LPCTSTR LayoutInfo::GetLayoutName()
{
	return (LPCTSTR)m_strLayoutName;
}


AcDbObjectId &LayoutInfo::GetBlockTableRecordId()
{
	return m_idBlkRec;
}
