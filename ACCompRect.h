// ACCompRect.h: ACCompRect クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOMPRECT_H__4651332F_85EB_4C0E_896D_1884060B0BDD__INCLUDED_)
#define AFX_ACCOMPRECT_H__4651332F_85EB_4C0E_896D_1884060B0BDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ACDatabaseUtility.h"
//2006.07.20
#define  APPNAME _T("COMPDWG")
#define  OBJNAME _T("COMPRECT")


class ACCompRect  
{
public:
	// 比較範囲の矩形のObjectIdを返す。複数存在した場合は、最初のObjectIdを返す。
	// 戻り値で比較範囲の矩形の個数を返す。
	long GetCompRectId(AcDbObjectId &idCompRect);  
	void DeleteCompRect();
	void Test02();
	void Test01();
	void ShowName();
	// ユーザーに2点の入力を求め、比較範囲の矩形を描画する。XDataを設定する。	
	bool DrawCompRect();
	ACCompRect();
	virtual ~ACCompRect();

};

#endif // !defined(AFX_ACCOMPRECT_H__4651332F_85EB_4C0E_896D_1884060B0BDD__INCLUDED_)
