// ACDatabaseUtility.cpp: ACDatabaseUtility クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACDatabaseUtility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACDatabaseUtility::ACDatabaseUtility()
{

}

ACDatabaseUtility::~ACDatabaseUtility()
{

}

bool ACDatabaseUtility::AppendEntity(AcDbEntity *pEntity, AcDbObjectId &outputId)
{
	AcDbBlockTable *pBlockTable;    
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    AcDbBlockTableRecord *pBlockRec;
	Acad::ErrorStatus es;	
    
    es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        acedAlert(_T("Failed to get block table!"));//2006.07.20
        return false;
    }

    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        acedAlert(_T("Failed to get block table record!"));//2006.07.20
        pBlockTable->close();
        return false;
    }

    es = pBlockRec->appendAcDbEntity(outputId, pEntity);
    if (es != Acad::eOk) {
        acedAlert(_T("Failed to append entity!"));//2006.07.20
        pBlockTable->close();
        pBlockRec->close();
        delete pEntity;
        return false;
    }
    pBlockRec->close();
    pBlockTable->close();
	pEntity->close();  // これがないと表示されない。
	    
    return true;
}
