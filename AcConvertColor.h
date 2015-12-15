// AcConvertColor.h: AcConvertColor クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCONVERTCOLOR_H__406102A9_CE6C_451E_AF60_E84AE2106579__INCLUDED_)
#define AFX_ACCONVERTCOLOR_H__406102A9_CE6C_451E_AF60_E84AE2106579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AcConvertColor  
{
public:
	AcConvertColor();
	virtual ~AcConvertColor();
	
	static CString GetColorStr(int iIdx);
};

#endif // !defined(AFX_ACCONVERTCOLOR_H__406102A9_CE6C_451E_AF60_E84AE2106579__INCLUDED_)
