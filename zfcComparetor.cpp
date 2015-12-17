#include "stdafx.h"
#include "resource.h"
#include "zfcUtility.h"
#include "zfcComparetor.h"
#include "ACDocManager.h"
#include "ResultCompEntity.h"
#include "zfcLogger.h"

zfcComparetor::zfcComparetor(void)
{
}


zfcComparetor::~zfcComparetor(void)
{
}

//	図面比較を行う
bool zfcComparetor::execute( const CString& strPathOldDwg, const CString strPathNewDwg )
{
	bool bResult = false;
	AcDbDatabase* pDbOld = nullptr;
	AcDbDatabase* pDbNew = nullptr;
	acd::objectIdContainer conObjectIdOld;
	acd::objectIdContainer conObjectIdNew;
	ResultCompEntity resultCompEntity;
	ACDocManager docManager;
	CString strLog;

	//	新・旧図面読み込み
	bResult = readDwg( pDbOld, strPathOldDwg );
	if( bResult )
		bResult = readDwg( pDbNew, strPathNewDwg );

	//	新・旧図面の全エンティティのID取得
	if( bResult )
		bResult = getAllObjectId( conObjectIdOld, pDbOld );
	if( bResult )
		bResult = getAllObjectId( conObjectIdNew, pDbNew );
	
	//	比較実行
	if( bResult ){
		resultCompEntity.SetHashTableSize( conObjectIdOld.GetCount() + conObjectIdNew.GetCount() );
		bResult = docManager.CompDwgs( conObjectIdOld, conObjectIdNew, resultCompEntity );
		
		if( !bResult ){
			AfxFormatString2( strLog, IDS_FAIL_TO_COMPARE_DWG, strPathOldDwg, strPathNewDwg );
			zfcLogger::instance().write( _T("\n%s"), strLog );
		}
	}
	
	//	合成図面作成
	if( bResult && 0 < resultCompEntity.GetCount() ){
		bResult = docManager.DrawResultDwg(pDbNew->blockTableId(), pDbOld->blockTableId(), resultCompEntity, conObjectIdNew);

		if( !bResult ){
			AfxFormatString2( strLog, IDS_FAIL_TO_COMPOUND_DWG, strPathOldDwg, strPathNewDwg );
			zfcLogger::instance().write( _T("\n%s"), strLog );
		}
	}

	delete pDbOld;
	delete pDbNew;

	return bResult;
}

bool zfcComparetor::readDwg( AcDbDatabase*& pDb, const CString& strPath ) const
{
	bool bResult = true;
	auto es = zfcUtility::readDwg( pDb, strPath );

	if( Acad::eOk != es ){
		CString str;

		AfxFormatString1( str, IDS_FAIL_TO_READ_DWG, strPath );
		zfcLogger::instance().write( _T("\n%s"), str );
		bResult = false;
	}
	
	return bResult;
}

bool zfcComparetor::getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb ) const
{
	bool bResult = true;
	auto es = zfcUtility::getAllObjectId( conObjectId, pDb );

	if( Acad::eOk != es ){
		CString str;

		// todo API調査
		AfxFormatString1( str, IDS_FAIL_TO_GET_ID, pDb->document()->title() );
		zfcLogger::instance().write( _T("\n%s"), str );
		bResult = false;
	}
	
	return bResult;
}
