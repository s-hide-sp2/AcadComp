// ResultRecord.h: ResultRecord クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTRECORD_H__C2EEBA64_DF07_49F8_811F_F3B75A03C747__INCLUDED_)
#define AFX_RESULTRECORD_H__C2EEBA64_DF07_49F8_811F_F3B75A03C747__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class ResultRecord  
{
public:
	ResultRecord();
	virtual ~ResultRecord();
	
public:
	// 2つの図形共通のハンドル(どちらか片方の場合もある。)
	AcDbHandle m_hdlEnts;
	// それぞれのオブジェクトID
	AcDbObjectId m_idObj1;
	AcDbObjectId m_idObj2;	


	/*
	// 色(名前の場合とインデックスの場合がある。)
	CString m_strColor1;
	CString m_strColor2;
	// レイヤー
	CString m_strLayer1;
	CString m_strLayer2;
	// 線種
	CString m_strLinetype1;
	CString m_strLinetype2;
	// 印刷スタイル
	CString m_strPlotstyleName1;
	CString m_strPlotstyleName2;
	// 線の太さ(Bylayerなどの場合がある。)
	CString m_strLineWeight1;	
	CString m_strLineWeight2;	
	// 線種尺度
	double  m_dLinetypeScale1;
	double  m_dLinetypeScale2;
	// ジオメトリに違いがある場合true
	bool    m_bDiffGeom; 
    // 色に違いがある場合true
	bool    m_bDiffColor;
	// レイヤーに違いがある場合true
	bool    m_bDiffLayer;
	// 線種に違いがある場合true
	bool    m_bDiffLinetype;
	// 印刷スタイルに違いがある場合true
	bool	m_bDiffPlotstyleName;
	// 線種尺度に違いがある場合true
	bool	m_bLinetypeScale;
	// 線の太さに違いがある場合true
	bool	m_bLineWeight;
	*/
private:
	CString m_strAttr[10];

};

#endif // !defined(AFX_RESULTRECORD_H__C2EEBA64_DF07_49F8_811F_F3B75A03C747__INCLUDED_)
