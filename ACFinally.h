// ACFinally.h: ACFinally クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACFINALLY_H__6330C2FF_6D43_40F6_A25B_AAF22A09AA3E__INCLUDED_)
#define AFX_ACFINALLY_H__6330C2FF_6D43_40F6_A25B_AAF22A09AA3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class ACFinally  
{
public:
	ACFinally();
	virtual ~ACFinally();
	
};

#define ACTRY    \
	try	{	     \
	try {	      

#define ACCATCH(ptype, ppval) \
	throw (ACFinally()); \
	} catch (ptype * ppval) {  

#define ACFINALLY \
	throw (ACFinally()); \
	}} catch (ACFinally fn){ 

#define ACEND     \
	}


#endif // !defined(AFX_ACFINALLY_H__6330C2FF_6D43_40F6_A25B_AAF22A09AA3E__INCLUDED_)
