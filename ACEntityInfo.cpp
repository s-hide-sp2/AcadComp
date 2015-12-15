// ACEntityInfo.cpp: ACEntityInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACEntityInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACEntityInfo::ACEntityInfo()
{

}

ACEntityInfo::~ACEntityInfo()
{

}

CString ACEntityInfo::GetHyperLink(AcDbEntity *pEnt)
{	
	AcDbHyperlinkCollection *pHLColl = NULL;
	CString strHL = _T("");

	ACRX_X_CALL(pEnt, AcDbEntityHyperlinkPE)->
		getHyperlinkCollection(pEnt, pHLColl, false, true);	

	if (pHLColl != NULL && pHLColl->count() != 0) {
		AcDbHyperlink *pHL;
		int i;

		for (i = 0; i < pHLColl->count(); i++) {
			pHL = pHLColl->item(i);

			//CString str1 = pHL->name();
			//CString str2 = pHL->subLocation();
			//CString str3 = pHL->description();
			//CString str4 = pHL->getDisplayString();
			
			if (pHL->description() != NULL)
				strHL = pHL->description();
		}
		
		for (i = 0; i < pHLColl->count() - 1; i++) {
			pHLColl->removeAt(i);
		}
	}
	if (pHLColl != NULL)
		delete pHLColl;

	return strHL;
	

	/*
	CString strRet  = "";
	LPCTSTR lpctRet = NULL;
	resbuf *prbXd;
	resbuf *prbXdNext;
	int    i;	

	prbXd = pEnt->xData();
	
	if (prbXd != NULL) {
		bool bExistHPL = false;
		//char *pcHPLink = NULL;		

		prbXdNext = prbXd;
		for (i = 0; prbXdNext != NULL && i < 30; i++) {

			if (prbXdNext->restype == ACE_DXF_HYPERLINK && i == 2) {
				strRet = prbXdNext->resval.rstring;	//hplをコピーする。			
				bExistHPL = true;
				//pcHPLink = prbXdNext->resval.rstring;				
			}		
			prbXdNext = prbXdNext->rbnext;
		}
		
		if (bExistHPL)
			lpctRet = (LPCTSTR)strRet;		
	}
	
	if (prbXd != NULL)
		acutRelRb(prbXd);	

	return lpctRet;
	*/
}