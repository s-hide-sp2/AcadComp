// ACCommandReactor.h: ACCommandReactor クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOMMANDREACTOR_H__B4DF0C97_FF13_48D1_8241_F77664181171__INCLUDED_)
#define AFX_ACCOMMANDREACTOR_H__B4DF0C97_FF13_48D1_8241_F77664181171__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class ACCommandReactor : public AcEditorReactor  
{
public:
	ACCommandReactor();
	virtual ~ACCommandReactor();
	
	virtual void commandCancelled(const TCHAR * cmdStr);//2006.07.20

	// 終了前にトランザクションを完了させる。
	virtual void commandEnded(const TCHAR * cmdStr); //2006.07.20

	virtual void commandFailed(const TCHAR * cmdStr); //2006.07.20

};

#endif // !defined(AFX_ACCOMMANDREACTOR_H__B4DF0C97_FF13_48D1_8241_F77664181171__INCLUDED_)
