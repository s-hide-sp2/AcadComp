// ResultRecordEntity.cpp: ResultRecordEntity クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ResultRecordEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ResultRecordEntity::ResultRecordEntity()
{	
	m_hdlEnts.setNull();
	m_idObj1.setNull();
	m_idObj2.setNull();

	for (int i = 0; i < 2; i++) { 
		m_dAttr[i] = 0;
	}

	for (int j = 0; j < 7; j++) {
		m_bAttr[j] = false;
	}
}

ResultRecordEntity::~ResultRecordEntity()
{

}

// 各フィールドに値をセットする。
void ResultRecordEntity::SetData(
	AcDbHandle hdlEnts, AcDbObjectId idObj1, AcDbObjectId idObj2, bool bDiffGeom, 
	CString strColor1, CString strColor2, CString strLayer1, CString strLayer2,
	CString strLinetype1, CString strLinetype2, CString strPlotstyle1, CString strPlotstyle2,
	CString strLineWeight1, CString strLineWeight2, double dLineTypeScale1, double dLineTypeScale2)
{
	m_hdlEnts = hdlEnts;
	m_idObj1  = idObj1;
	m_idObj2  = idObj2;

	m_strAttr[E_FIELD_STRING::COLOR1]      = strColor1;
	m_strAttr[E_FIELD_STRING::COLOR2]	   = strColor2;
	m_strAttr[E_FIELD_STRING::LAYER1]	   = strLayer1;
	m_strAttr[E_FIELD_STRING::LAYER2]	   = strLayer2;
	m_strAttr[E_FIELD_STRING::LINETYPE1]   = strLinetype1;
	m_strAttr[E_FIELD_STRING::LINETYPE2]   = strLinetype2;
	m_strAttr[E_FIELD_STRING::PLOTSTYLE1]  = strPlotstyle1;
	m_strAttr[E_FIELD_STRING::PLOTSTYLE2]  = strPlotstyle2;
	m_strAttr[E_FIELD_STRING::LINEWEIGHT1] = strLineWeight1;
	m_strAttr[E_FIELD_STRING::LINEWEIGHT2] = strLineWeight2;
	
	m_dAttr[E_FIELD_DOUBLE::LINETYPESCALE1] = dLineTypeScale1;
	m_dAttr[E_FIELD_DOUBLE::LINETYPESCALE2] = dLineTypeScale2;

	m_bAttr[E_FIELD_BOOL::DIFFGEOM]  		 = bDiffGeom;
	m_bAttr[E_FIELD_BOOL::DIFFCOLOR]		 = (strColor1 == strColor2);
	m_bAttr[E_FIELD_BOOL::DIFFLAYER]		 = (strLayer1 == strLayer2);
	m_bAttr[E_FIELD_BOOL::DIFFLINETYPE]		 = (strLinetype1 == strLinetype2);
	m_bAttr[E_FIELD_BOOL::DIFFPLOTSTYLENAME] = (strPlotstyle1 == strPlotstyle2);
	m_bAttr[E_FIELD_BOOL::DIFFLINETYPESCALE] = (dLineTypeScale1 == dLineTypeScale2);
	m_bAttr[E_FIELD_BOOL::DIFFLINEWEIGHT]	 = (strLineWeight1 == strLineWeight2);
}

// 文字列型のフィールドのインデックス名を指定し、その値を得る。
LPCTSTR ResultRecordEntity::GetValue(E_FIELD_STRING eFieldIdx)
{
	return m_strAttr[eFieldIdx];
}

// 倍浮動小数点型のフィールドのインデックス名を指定し、その値を得る。
double ResultRecordEntity::GetValue(E_FIELD_DOUBLE eFieldIdx)
{
	return m_dAttr[eFieldIdx];
}

// 真偽型のフィールドのインデックス名を指定し、その値を得る。
bool ResultRecordEntity::GetValue(E_FIELD_BOOL eFieldIdx)
{
	return m_bAttr[eFieldIdx];
}
