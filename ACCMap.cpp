// ACCMap.cpp: ACCMap クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACCMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACCMap::ACCMap()
{

}

ACCMap::~ACCMap()
{

}

// 文字列型のマップのキーに対応する値を返す。
CString ACCMap::GetKeyVal(const CMap<int, int, CString, CString> &strmapSrc, int lKey)
{
	CString strRet = _T("");

	strmapSrc.Lookup(lKey, strRet);
	
	return strRet;
}

// int型のマップのキーに対応する値を返す。
int ACCMap::GetKeyVal(const CMap<int, int, int, int> &imapSrc, int lKey)
{	
	int iRet = -1;

	imapSrc.Lookup(lKey, iRet);
	
	return iRet;
}

/*
// T3型のマップのキーに対応する値を返す。
template<class T1, class T2, class T3, class T4> 
T3 ACCMap::GetKeyVal(const CMap<T1, T2, T3, T4> &tmapSrc, T1 tKey)
{
	T3 tVal;
	tmapSrc.Lookup(tKey, tVal);

	return tVal;		
}
*/