// InfoDwgEntity.h: InfoDwgEntity クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFODWGENTITY_H__54CE6E21_08BB_47EA_A0C2_5075093BFC59__INCLUDED_)
#define AFX_INFODWGENTITY_H__54CE6E21_08BB_47EA_A0C2_5075093BFC59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

#define NUM_FIELD_STR    6
#define NUM_FIELD_DOUBLE 1

class InfoDwgEntity  
{
public:
	InfoDwgEntity();
	virtual ~InfoDwgEntity();
	
// 文字列型のフィールド配列のインデックス
	enum IDE_FIELD_STRING {
		ENTTYPE,
		COLOR,		
		LAYER,		
		LINETYPE,		
		PLOTSTYLE,		
		LINEWEIGHT,		
	};

	// 倍浮動小数点型のフィールド配列のインデックス
	enum IDE_FIELD_DOUBLE {
		LINETYPESCALE,		
	};

	// 配列のサイズをセットする。
	void SetSize(int iSize);

	// 配列に値をセットする。
	// 文字列型
	void SetValue(IDE_FIELD_STRING eFieldIdx, int iIdx, CString strValue);
	// 倍浮動小数点型
	void SetValue(IDE_FIELD_DOUBLE eFieldIdx, int iIdx, double dValue);

	// 全要素
	void SetValue(int iIdx, AcDbObjectId idEnt, AcDbHandle hdlEnt, CString strColor, CString strLayer,
		CString strLinetype, CString strPlotStyle, CString strLineWeight, double dLinetypeScale);

	// 配列を得る。
	CStringArray		   &GetStringArray(IDE_FIELD_STRING eFieldIdx);
	CArray<double, double> &GetDoubleArray(IDE_FIELD_DOUBLE eFieldIdx);	

	// 図形IDの列
	AcDbObjectIdArray      m_idaryEnt;
	// 図形ハンドルの列
	AcArray<AcDbHandle>    m_hdlaryEnt;
private:	
				
	CStringArray		   m_straryAttr[NUM_FIELD_STR];
	CArray<double, double> m_daryAttr[NUM_FIELD_DOUBLE];	

};

#endif // !defined(AFX_INFODWGENTITY_H__54CE6E21_08BB_47EA_A0C2_5075093BFC59__INCLUDED_)
