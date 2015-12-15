// ACDbSysVar.cpp: ACDbSysVar クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACDbSysVar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACDbSysVar::ACDbSysVar()
{
	m_pDb = NULL;
}

ACDbSysVar::~ACDbSysVar()
{

}

// システム変数を取得／設定するデータベースを指定する。
void ACDbSysVar::SetDatabase(AcDbDatabase *pDb) 
{
	m_pDb = pDb;
}

// limmaxを得る。
bool ACDbSysVar::Getlimmax(AcGePoint2d &pt2Ret)
{
	if (m_pDb == NULL)
		return false;	

	pt2Ret = m_pDb->limmax();

	return true;
}

// limminを得る。
bool ACDbSysVar::Getlimmin(AcGePoint2d &pt2Ret)
{
	if (m_pDb == NULL)
		return false;	

	pt2Ret = m_pDb->limmin();

	return true;
}
