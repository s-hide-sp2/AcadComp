#include "stdafx.h"
#include "actoggleresultdisp.h"
#include "ACDocManager.h"

ACToggleResultDisp::ACToggleResultDisp(void)
{
}

ACToggleResultDisp::~ACToggleResultDisp(void)
{
}

bool ACToggleResultDisp::IsResultDrawing()
{
	bool	bRet = false;

	// カレント図面を取得
	AcDbDatabase	*pDb = acdbHostApplicationServices()->workingDatabase();

	// ブロックテーブルを取得
	AcDbBlockTable	*pBT;
	if(pDb->getBlockTable(pBT,AcDb::kForRead) != Acad::eOk){
		return false;
	}

	// モデル空間のブロックテーブルレコードを取得
	AcDbBlockTableRecord	*pBTR;
	if(pBT->getAt(ACDB_MODEL_SPACE,pBTR,AcDb::kForWrite) != Acad::eOk){
		pBT->close();
		return false;
	}
	pBT->close();

	/* 拡張ＡＰＰ名が存在しない時 */
	struct resbuf *pRb, *pRbTop;
	pRbTop = pRb = pBTR->xData(ACDM_RESULTAPPNAME);
	if( pRb == NULL ) {
		pBTR->close();
		return false;
	}

	pRb = pRb->rbnext;

	if( pRb->restype == AcDb::kDxfXdAsciiString ) {
		if( !_tcscmp( pRb->resval.rstring, ACDM_RESULTXDATA ) ) {
			bRet = true;
		}
	}

	pBTR->close();
	ads_relrb( pRbTop );

	return bRet;
}

bool ACToggleResultDisp::ToggleDisp( Adesk::UInt16 uiColIdx )
{
	// カレント図面を取得
	AcDbDatabase	*pDb = acdbHostApplicationServices()->workingDatabase();

	// ブロックテーブルレコードを取得
    AcDbBlockTableRecord	*pBTR;
	acdbOpenObject(pBTR, pDb->currentSpaceId(), AcDb::kForWrite);

	// ブロックテーブルレコードのイテレタを取得
	AcDbBlockTableRecordIterator	*pIter;
	pBTR->newIterator(pIter);
	pBTR->close();

	AcDbEntity		*pEnt;
	for(;!pIter->done();pIter->step()){
		// 開けなかったりいらない部品だったら次へ
		if( pIter->getEntity( pEnt, AcDb::kForWrite ) != Acad::eOk ) continue;

		if( pEnt->colorIndex() == uiColIdx ) {
			if( pEnt->visibility() == AcDb::kVisible ) {
				pEnt->setVisibility( AcDb::kInvisible );
			} else {
				pEnt->setVisibility( AcDb::kVisible );
			}
		}

		pEnt->close();
	}
	delete pIter;

	return true;
}
