// ResultRecordsetEntity.h: ResultRecordsetEntity クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTRECORDSETENTITY_H__3A789D69_8259_4AC2_AB86_55F64FCEE7FC__INCLUDED_)
#define AFX_RESULTRECORDSETENTITY_H__3A789D69_8259_4AC2_AB86_55F64FCEE7FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ResultRecordsetEntity  
{
public:
	ResultRecordsetEntity();
	virtual ~ResultRecordsetEntity();
	
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
	
	// 配列のサイズをセットする。
	void SetSize(int iSize);

	CStringArray		   &GetStringArray(E_FIELD_STRING eFieldIdx);
	CArray<double, double> &GetDoubleArray(E_FIELD_STRING eFieldIdx);
	CArray<bool, bool>     &GetBoolArray(E_FIELD_STRING eFieldIdx);

private:
	static int m_iSizeStr;
	static int m_iSizeDouble;
	static int m_iSizeBool;

	//CMap<int, int, CString, CString> m_smapAttr[10];
	//CMap<int, int, double, double>   m_dmapAttr[2];
	//CMap<int, int, bool, bool>       m_bmapAttr[7];

	
	CStringArray		   m_straryAttr[10];
	CArray<double, double> m_daryAttr[2];
	CArray<bool, bool>     m_baryAttr[7];	
};

#endif // !defined(AFX_RESULTRECORDSETENTITY_H__3A789D69_8259_4AC2_AB86_55F64FCEE7FC__INCLUDED_)
