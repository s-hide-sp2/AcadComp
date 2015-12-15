// ResultRecordEntity.h: ResultRecordEntity クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTRECORDENTITY_H__F7E18BA1_E290_4BBC_AD62_44653E559272__INCLUDED_)
#define AFX_RESULTRECORDENTITY_H__F7E18BA1_E290_4BBC_AD62_44653E559272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ResultRecordEntity  
{
public:
	ResultRecordEntity();
	virtual ~ResultRecordEntity();
	
	// 文字列型のフィールド配列のインデックス
	enum E_FIELD_STRING {
		COLOR1,
		COLOR2,
		LAYER1,
		LAYER2,
		LINETYPE1,
		LINETYPE2,
		PLOTSTYLE1,
		PLOTSTYLE2,
		LINEWEIGHT1,
		LINEWEIGHT2,
	};

	// 倍浮動小数点型のフィールド配列のインデックス
	enum E_FIELD_DOUBLE {
		LINETYPESCALE1,
		LINETYPESCALE2
	};

	// BOOL型のフィールド配列のインデックス
	enum E_FIELD_BOOL {
		DIFFGEOM,
		DIFFCOLOR,
		DIFFLAYER,
		DIFFLINETYPE,
		DIFFPLOTSTYLENAME,
		DIFFLINETYPESCALE,
		DIFFLINEWEIGHT
	};

public:
	bool GetValue(E_FIELD_BOOL eFieldIdx);
	double GetValue(E_FIELD_DOUBLE eFieldIdx);
	LPCTSTR GetValue(E_FIELD_STRING eFieldIdx);
	// 2つの図形共通のハンドル(どちらか片方の場合もある。)
	AcDbHandle m_hdlEnts;
	// それぞれのオブジェクトID
	AcDbObjectId m_idObj1;
	AcDbObjectId m_idObj2;	
	
	// 各フィールドに値をセットする。
	void SetData(
		AcDbHandle hdlEnts, AcDbObjectId idObj1, AcDbObjectId idObj2, bool bDiffGeom, 
		CString strColor1, CString strColor2, CString strLayer1, CString strLayer2,
		CString strLinetype1, CString strLinetype2, CString strPlotstyle1, CString strPlotstyle2,
		CString strLineWeight1, CString strLineWeight2, double dLineTypeScale1, double dLineTypeScale2);

	
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
	// それぞれの型のフィールド値を保持する。	
	CString m_strAttr[10];
	double  m_dAttr[2];
	bool    m_bAttr[7];
};

#endif // !defined(AFX_RESULTRECORDENTITY_H__F7E18BA1_E290_4BBC_AD62_44653E559272__INCLUDED_)
