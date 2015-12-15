// ACString.cpp: ACString クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACString::ACString()
{

}

ACString::~ACString()
{

}

// 文字列が倍浮動小数値である場合はその数を返す。数値でない文字が1つでも含まれるときはfalseを返す。
bool ACString::StringToNumber(CString strNum, double& dRetNum)
{	
	int iLen = strNum.GetLength();	

	if (iLen == 0)
		return false;

	TCHAR * cEnd;	//2006.07.20					
	dRetNum = _tcstod(strNum, &cEnd); //2006.07.20
	
	if (dRetNum == HUGE_VAL || dRetNum == -HUGE_VAL)
		return false;
	else if (*cEnd != _T('\0'))//2006.07.20 
		return false;	
	else
		return true;
}

CString ACString::NumberToString(double dSrc)
{
	CString strRet;

	strRet.Format(_T("%f"), dSrc);//2006.07.20

	return strRet;
}

CString ACString::GetSegmentR(CString strSrc, char cSeparator, bool bRetAfter, bool bInclude)
{	
	int iPosSep, iLenSrc, iRev = 0;
	CString strRet;

	iPosSep = strSrc.ReverseFind(cSeparator);
	iLenSrc = strSrc.GetLength();

	if (iPosSep == -1)
		iPosSep = iLenSrc;

	if (bInclude)
		iRev = 1;

	if (bRetAfter)
		strRet = strSrc.Mid(iPosSep + 1 - iRev , iLenSrc - iPosSep + iRev);
	else
		strRet = strSrc.Mid(0, iPosSep + iRev);

	return strRet;
}

// CSV形式のファイルの1行を受け取り、要素に分解してCStringArrayで返す。文字列に含まれる"(DQ)は取り除く
void ACString::SplitLine(CString strSrc, CStringArray& aryRetElm) //, CByteArray& aryRetType)
{
	CStringArray aryTmpElm, aryTmpType;
	int iLen = strSrc.GetLength(), iPosStart = 0, iSize = 0; 
	int iPos, iPosPre = 0;
	bool bDQ1 = false; 
	CString strAdd;
	bool bEnd;

	aryRetElm.SetSize(15, 4);

	while (1) {
		iPos = strSrc.Find(_T(','));
		
		if (iPos == -1) {			
			iPos = strSrc.GetLength();
			bEnd = true;
		}
		
		strAdd.Empty();
		strAdd = strSrc.Mid(0, iPos);				
		strSrc = strSrc.Mid(iPos + 1, iLen - iPosPre);

		// 一番最初と最後にDQがある場合は取り除く。
		strAdd.Replace(_T("\""), _T(""));//2006.07.20
		//RemoveFLDQ(strAdd);		
		aryRetElm.SetAtGrow(iSize, strAdd);
		iSize++;

		if (bEnd == true)
			break;
	}

	aryRetElm.SetSize(iSize);
}
