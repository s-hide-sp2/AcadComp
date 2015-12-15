// ACConvertName.h: ACConvertName クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCONVERTNAME_H__0C0F27BE_B4D4_4FAB_A2B5_941D8FFCCDC8__INCLUDED_)
#define AFX_ACCONVERTNAME_H__0C0F27BE_B4D4_4FAB_A2B5_941D8FFCCDC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACConvertName  
{
public:
	ACConvertName();
	virtual ~ACConvertName();

	static CString GetColorStr(int iIdx);
	static CString GetLineWeightStr(AcDb::LineWeight lw);

	// 図形タイプの一般名を得る。
	static CString GetEntityTypeStr(AcDbEntity *pEnt);
};

#endif // !defined(AFX_ACCONVERTNAME_H__0C0F27BE_B4D4_4FAB_A2B5_941D8FFCCDC8__INCLUDED_)
