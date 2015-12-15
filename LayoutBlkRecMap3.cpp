// LayoutBlkRecMap3.cpp: LayoutBlkRecMap3 クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "LayoutBlkRecMap3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

LayoutBlkRecMap3::LayoutBlkRecMap3()
{
	m_idDwg1LayoutBlkRec   = AcDbObjectId::kNull;
	m_idDwg2LayoutBlkRec   = AcDbObjectId::kNull;
	m_idNewDwgLayoutBlkRec = AcDbObjectId::kNull;
}

LayoutBlkRecMap3::LayoutBlkRecMap3(
	AcDbObjectId idDwg1LayoutBlkRec, AcDbObjectId idDwg2LayoutBlkRec, AcDbObjectId idNewDwgLayoutBlkRec)
{
	m_idDwg1LayoutBlkRec   = idDwg1LayoutBlkRec;
	m_idDwg2LayoutBlkRec   = idDwg2LayoutBlkRec;
	m_idNewDwgLayoutBlkRec = idNewDwgLayoutBlkRec;
}



LayoutBlkRecMap3::~LayoutBlkRecMap3()
{

}

void LayoutBlkRecMap3::SetDwg1LayoutBlkRecObjectId(AcDbObjectId idBlkRecObject)
{
	m_idDwg1LayoutBlkRec = idBlkRecObject;
}

void LayoutBlkRecMap3::SetDwg2LayoutBlkRecObjectId(AcDbObjectId idBlkRecObject)
{
	m_idDwg2LayoutBlkRec = idBlkRecObject;	
}

void LayoutBlkRecMap3::SetNewDwgLayoutBlkRecObjectId(AcDbObjectId idBlkRecObject)
{
	m_idNewDwgLayoutBlkRec = idBlkRecObject;
}

AcDbObjectId &LayoutBlkRecMap3::GetDwg1LayoutBlkRecObjectId()
{
	return m_idDwg1LayoutBlkRec;
}
AcDbObjectId &LayoutBlkRecMap3::GetDwg2LayoutBlkRecObjectId()
{
	return m_idDwg2LayoutBlkRec;
}

AcDbObjectId &LayoutBlkRecMap3::GetNewDwgLayoutBlkRecObjectId()
{
	return m_idNewDwgLayoutBlkRec;
}
