// ACDbSysVar.h: ACDbSysVar クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACDBSYSVAR_H__9764701F_BDE8_4FD7_BA60_27DD7B14D5FF__INCLUDED_)
#define AFX_ACDBSYSVAR_H__9764701F_BDE8_4FD7_BA60_27DD7B14D5FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

class ACDbSysVar  
{
public:
	ACDbSysVar();
	virtual ~ACDbSysVar();
	
	// システム変数を取得／設定するデータベースを指定する。
	void SetDatabase(AcDbDatabase *pDb);

	// limmaxを得る。
	bool Getlimmax(AcGePoint2d &pt2Ret);

	// limminを得る。
	bool Getlimmin(AcGePoint2d &pt2Ret);

	
private: 
	AcDbDatabase *m_pDb;
};

#endif // !defined(AFX_ACDBSYSVAR_H__9764701F_BDE8_4FD7_BA60_27DD7B14D5FF__INCLUDED_)
