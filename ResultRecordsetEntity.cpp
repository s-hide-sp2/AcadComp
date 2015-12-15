// ResultRecordsetEntity.cpp: ResultRecordsetEntity クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ResultRecordsetEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int ResultRecordsetEntity::m_iSizeStr    = 10;
int ResultRecordsetEntity::m_iSizeDouble = 2;
int ResultRecordsetEntity::m_iSizeBool   = 7;
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ResultRecordsetEntity::ResultRecordsetEntity()
{

}

ResultRecordsetEntity::~ResultRecordsetEntity()
{

}

void ResultRecordsetEntity::SetSize(int iSize)
{
	int i;

	for (i = 0; i < m_iSizeStr; i++) {
		m_straryAttr[i].SetSize(iSize);
	}

	for (i = 0; i < m_iSizeDouble; i++) {
		m_daryAttr[i].SetSize(iSize);
	}

	for (i = 0; i < m_iSizeBool; i++) {
		m_baryAttr[i].SetSize(iSize);
	}
}

CStringArray &ResultRecordsetEntity::GetStringArray(E_FIELD_STRING eFieldIdx)
{
	return m_straryAttr[eFieldIdx];
}

CArray<double, double> &ResultRecordsetEntity::GetDoubleArray(E_FIELD_STRING eFieldIdx)
{
	return m_daryAttr[eFieldIdx];
}

CArray<bool, bool> &ResultRecordsetEntity::GetBoolArray(E_FIELD_STRING eFieldIdx)
{
	return m_baryAttr[eFieldIdx];
}
