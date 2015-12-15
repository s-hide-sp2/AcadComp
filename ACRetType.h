// ACRetType.h: ACRetType クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACRETTYPE_H__A1A86464_FD3A_4EB2_BFEC_0BAFDAF499AC__INCLUDED_)
#define AFX_ACRETTYPE_H__A1A86464_FD3A_4EB2_BFEC_0BAFDAF499AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACRetType  
{
public:
	ACRetType();
	virtual ~ACRetType();
	
	enum ACRETTYPE {
		rOk				= 0,
		rCommandRunning = 1,
		rInvalidDwg		= 2,				
	};

	static CString GetMsg(ACRETTYPE rType);
	
	static void SetI1(const int &i);

private:
	static int m_i1;
};

#endif // !defined(AFX_ACRETTYPE_H__A1A86464_FD3A_4EB2_BFEC_0BAFDAF499AC__INCLUDED_)
