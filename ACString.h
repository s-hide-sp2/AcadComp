// ACString.h: ACString クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACSTRING_H__86A415AD_82AD_484C_A8CB_98CE54704E70__INCLUDED_)
#define AFX_ACSTRING_H__86A415AD_82AD_484C_A8CB_98CE54704E70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACString  
{
public:
	ACString();
	virtual ~ACString();

	static bool    StringToNumber(CString strSrc, double &dRet);
	static CString NumberToString(double dSrc);

	// 指定した文字列を指定した文字で区切った前後の文字列を返す。
	static CString GetSegmentR(CString strSrc, char cSeparator, bool bRetAfter, bool bInclude);

	// CSV形式のファイルの1行を受け取り、要素に分解してCStringArrayで返す。""がある場合は取り除く。
	static void SplitLine(CString strSrc, CStringArray& aryRetElm);

};

#endif // !defined(AFX_ACSTRING_H__86A415AD_82AD_484C_A8CB_98CE54704E70__INCLUDED_)
