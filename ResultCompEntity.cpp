// ResultCompEntity.cpp: ResultCompEntity クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ResultCompEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int ResultCompEntity::m_iSizeStr    = 10;
int ResultCompEntity::m_iSizeDouble = 2;
int ResultCompEntity::m_iSizeBool   = 7;
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ResultCompEntity::ResultCompEntity()
{

}

ResultCompEntity::~ResultCompEntity()
{

}

/*
void ResultCompEntity::SetSize(int iSize)
{
	int i;

	for (i = 0; i < m_iSizeStr; i++) {
		m_smapAttr[i].SetSize(iSize);		
		CMap
	}

	for (i = 0; i < m_iSizeDouble; i++) {
		m_dmapAttr[i].SetSize(iSize);
	}

	for (i = 0; i < m_iSizeBool; i++) {
		m_bmapAttr[i].SetSize(iSize);
	}
}
*/

CMap<int, int, CString, CString> &ResultCompEntity::GetStringMap(RCE_FIELD_STRING eFieldIdx)
{
	return m_smapAttr[eFieldIdx];
}

CMap<int, int, double, double> &ResultCompEntity::GetDoubleMap(RCE_FIELD_DOUBLE eFieldIdx)
{
	return m_dmapAttr[eFieldIdx];
}

CMap<int, int, AcDbObjectId, AcDbObjectId> &ResultCompEntity::GetObjectIdMap(RCE_FIELD_OBJID eFieldIdx)
{
	return m_idmapEnt[eFieldIdx];
}



//CMap<int, int, bool, bool> &ResultCompEntity::GetBoolMap(RCE_FIELD_BOOL eFieldIdx)
//{
//	return m_bmapAttr[eFieldIdx];
//}

CMap<int, int, ResultCompEntity::RCE_TYPE_RESULT, ResultCompEntity::RCE_TYPE_RESULT> 
&ResultCompEntity::GetResultMap(RCE_FIELD_RESULT eFieldIdx)
{
	return m_resmapAttr[eFieldIdx];
}

/*
void ResultCompEntity::SetValue(
	int iKey, 
	AcDbHandle hdlEnt, AcDbObjectId idEnt1, AcDbObjectId idEnt2, 
	CString strEnttype1, CString strEnttype2,
	CString strColor1, CString strColor2,
	CString strLayer1, CString strLayer2, 
	CString strLinetype1, CString strLinetype2,
	CString strPlotStyle1, CString strPlotStyle2,
	CString strLineWeight1, CString strLineWeight2,
	CString strHyperLink, CString strLineHyperLink,
	double dLinetypeScale1, double dLinetypeScale2,
	bool bDiffAll, bool bDiffGeom, 
	bool bDiffColor, bool bDiffLayer, 
	bool bDiffLinetype, bool bDiffPlotstylename, 
	bool bDiffLinetypeScale, bool bDiffLineWeight)
{
	m_hdlmapEnt[iKey] = hdlEnt;

	m_idmapEnt[FIRST][iKey]  = idEnt1;
	m_idmapEnt[SECOND][iKey] = idEnt2;

	m_smapAttr[ENTTYPE1][iKey]	  = strEnttype1;
	m_smapAttr[ENTTYPE2][iKey]	  = strEnttype2;
	m_smapAttr[COLOR1][iKey]	  = strColor1;
	m_smapAttr[COLOR2][iKey]	  = strColor2;
	m_smapAttr[LAYER1][iKey]	  = strLayer1;
	m_smapAttr[LAYER2][iKey]	  = strLayer2;
	m_smapAttr[LINETYPE1][iKey]   = strLinetype1;
	m_smapAttr[LINETYPE2][iKey]   = strLinetype2;
	m_smapAttr[PLOTSTYLE1][iKey]  = strPlotStyle1;
	m_smapAttr[PLOTSTYLE2][iKey]  = strPlotStyle2;
	m_smapAttr[LINEWEIGHT1][iKey] = strLineWeight1;
	m_smapAttr[LINEWEIGHT2][iKey] = strLineWeight2;

	m_dmapAttr[LINETYPESCALE1][iKey] = dLinetypeScale1;
	m_dmapAttr[LINETYPESCALE2][iKey] = dLinetypeScale2;

	//m_bmapAttr[DIFFALL][iKey]		    = bDiffAll;
	//m_bmapAttr[DIFFGEOM][iKey]			= bDiffGeom;
	//m_bmapAttr[DIFFCOLOR][iKey]			= bDiffColor;
	//m_bmapAttr[DIFFLAYER][iKey]			= bDiffLayer;
	//m_bmapAttr[DIFFLINETYPE][iKey]		= bDiffLinetype;
	//m_bmapAttr[DIFFPLOTSTYLENAME][iKey] = bDiffPlotstylename;
	//m_bmapAttr[DIFFLINETYPESCALE][iKey] = bDiffLinetypeScale;
	//m_bmapAttr[DIFFLINEWEIGHT][iKey]	= bDiffLineWeight;	
}
*/

void ResultCompEntity::SetValue1(int iKey, AcDbObjectId idEnt1, 
	CString strEnttype1, CString strColor1, CString strLayer1,  
	CString strLinetype1, CString strPlotStyle1, CString strLineWeight1, 
	CString strHyperLink1, double dLinetypeScale1)
{	
	m_idmapEnt[FIRST][iKey]  = idEnt1;
	
	m_smapAttr[ENTTYPE1][iKey]	  = strEnttype1;
	m_smapAttr[COLOR1][iKey]	  = strColor1;	
	m_smapAttr[LAYER1][iKey]	  = strLayer1;	
	m_smapAttr[LINETYPE1][iKey]   = strLinetype1;	
	m_smapAttr[PLOTSTYLE1][iKey]  = strPlotStyle1;	
	m_smapAttr[LINEWEIGHT1][iKey] = strLineWeight1;	
	m_smapAttr[HYPERLINK1][iKey]  = strHyperLink1;

	m_dmapAttr[LINETYPESCALE1][iKey] = dLinetypeScale1;	
}

void ResultCompEntity::SetValue2(int iKey, AcDbObjectId idEnt2, 
	CString strEnttype2, CString strColor2, CString strLayer2,  
	CString strLinetype2, CString strPlotStyle2, CString strLineWeight2, 
	CString strHyperLink2, double dLinetypeScale2)
{
	m_idmapEnt[SECOND][iKey]  = idEnt2;

	m_smapAttr[ENTTYPE2][iKey]	  = strEnttype2;	
	m_smapAttr[COLOR2][iKey]	  = strColor2;	
	m_smapAttr[LAYER2][iKey]	  = strLayer2;	
	m_smapAttr[LINETYPE2][iKey]   = strLinetype2;	
	m_smapAttr[PLOTSTYLE2][iKey]  = strPlotStyle2;	
	m_smapAttr[LINEWEIGHT2][iKey] = strLineWeight2;
	m_smapAttr[HYPERLINK2][iKey]  = strHyperLink2;

	m_dmapAttr[LINETYPESCALE2][iKey] = dLinetypeScale2;
}

void ResultCompEntity::SetDiff(
	int iKey, 		
	bool bDiffAll, bool bDiffGeom, 
	bool bDiffColor, bool bDiffLayer, 
	bool bDiffLinetype, bool bDiffPlotstylename, 
	bool bDiffLinetypeScale, bool bDiffLineWeight)
{
	//m_bmapAttr[DIFFALL][iKey]		    = bDiffAll;
	//m_bmapAttr[DIFFGEOM][iKey]			= bDiffGeom;
	//m_bmapAttr[DIFFCOLOR][iKey]			= bDiffColor;
	//m_bmapAttr[DIFFLAYER][iKey]			= bDiffLayer;
	//m_bmapAttr[DIFFLINETYPE][iKey]		= bDiffLinetype;
	//m_bmapAttr[DIFFPLOTSTYLENAME][iKey] = bDiffPlotstylename;
	//m_bmapAttr[DIFFLINETYPESCALE][iKey] = bDiffLinetypeScale;
	//m_bmapAttr[DIFFLINEWEIGHT][iKey]	= bDiffLineWeight;	
}

void ResultCompEntity::SetHandle(int iKey, AcDbHandle hdlEnt)
{
	m_hdlmapEnt[iKey] = hdlEnt;
}

// 比較結果のフィールドに設定する。
void ResultCompEntity::SetResult(
	int iKey,
	RCE_TYPE_RESULT resAll, RCE_TYPE_RESULT resGeom)
{
	m_resmapAttr[COMPALL][iKey]  = resAll;
	m_resmapAttr[COMPGEOM][iKey] = resGeom;	
}

// ハッシュテーブルのサイズを指定する。実際にセットする要素数である必要はない。
// iSizeは素数がよいらしい
void ResultCompEntity::SetHashTableSize(int iSize)
{
	int i;	
	
	for (i = 0; i < RCE_NUM_FIELD_STRING; i++) 
		m_smapAttr[i].InitHashTable(iSize);

	for (i = 0; i < RCE_NUM_FIELD_DOUBLE; i++) 
		m_dmapAttr[i].InitHashTable(iSize);

	//for (i = 0; i < RCE_NUM_FIELD_BOOL; i++) 
	//	m_bmapAttr[RCE_NUM_FIELD_BOOL];

	for (i = 0; i < RCE_NUM_FIELD_RESULT; i++) 
		m_resmapAttr[i].InitHashTable(iSize);
}

// 全ての要素を削除する。
void ResultCompEntity::RemoveAll()
{
	int i;	
	
	for (i = 0; i < RCE_NUM_FIELD_STRING; i++) {
		m_smapAttr[i].RemoveAll();
		m_smapAttr[i].InitHashTable(0);
	}

	for (i = 0; i < RCE_NUM_FIELD_DOUBLE; i++) { 
		m_dmapAttr[i].RemoveAll();
		m_dmapAttr[i].InitHashTable(0);
	}

	//for (i = 0; i < RCE_NUM_FIELD_BOOL; i++) 
	//	m_bmapAttr[RCE_NUM_FIELD_BOOL];

	for (i = 0; i < RCE_NUM_FIELD_RESULT; i++) {
		m_resmapAttr[i].RemoveAll();
		m_resmapAttr[i].InitHashTable(0);
	}
}

// 結果セットの中から、指定したインデックスの配列に対応するObjectIDの配列を返す。
void ResultCompEntity::GetSelId(
	const CMap<int, int, int, int> &imapSel, ResultCompEntity::RCE_FIELD_OBJID rceObjId,
	CMap<int, int, AcDbObjectId, AcDbObjectId> &idmapRet)
{
	int iCount = imapSel.GetCount();	
	int iIdxAdd = 0;
	
	idmapRet.InitHashTable(iCount);

	for (int i = 0; i < iCount; i++) {
		AcDbObjectId idEnt = AcDbObjectId::kNull;
		int	iIdx;

		if (imapSel.Lookup(i, iIdx) != FALSE) {
			m_idmapEnt[rceObjId].Lookup(iIdx, idEnt);
			
			if (!idEnt.isNull()) {
				idmapRet[iIdxAdd] = idEnt;
				iIdxAdd++;
			}
		}
	}
}

// 結果セットのカウントを返す。
int ResultCompEntity::GetCount()
{
	return m_smapAttr[ENTTYPE1].GetCount();
}
