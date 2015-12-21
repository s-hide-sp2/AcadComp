#include "stdafx.h"
#include "resource.h"
#include "zfcUtility.h"
#include "zfcComparetor.h"
#include "ACDocManager.h"
#include "ResultCompEntity.h"
#include "zfcLogger.h"

zfcComparetor::zfcComparetor(void)
{
	init();
}


zfcComparetor::~zfcComparetor(void)
{
}

//	シングルトンオブジェクトを返す
zfcComparetor& zfcComparetor::instance()
{
	static zfcComparetor sigleton;

	return sigleton;
}

//	初期化処理
void zfcComparetor::init()
{
	m_nCntCorrespond = 0;
	m_nCntDiscord = 0;
	m_nCntWarning = 0;
	m_nCntError = 0;
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

	//	ファイル状態(更新日時・サイズ)で比較
	if( !compareFileStatus(strPathOldDwg, strPathNewDwg) )
		return true;

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
		
		if( bResult ){
			if( resultCompEntity.GetCount() == 0 ){
				incrementCorrespond();
				zfcUtility::writeLog2( IDS_CORRESPOND, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
			}
			else{
				incrementDiscord();
				zfcUtility::writeLog2( IDS_DISCORD, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
			}
		}
		else{
			zfcUtility::writeLog2( IDS_FAIL_TO_COMPARE_DWG, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
		}
	}
	
	//	合成図面作成
	if( bResult && 0 < resultCompEntity.GetCount() ){
		bResult = docManager.DrawResultDwg(pDbNew->blockTableId(), pDbOld->blockTableId(), resultCompEntity, conObjectIdNew);

		if( !bResult ){
			zfcUtility::writeLog2( IDS_FAIL_TO_COMPOUND_DWG, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
		}
	}

	if( !bResult )
		incrementError();

	delete pDbOld;
	delete pDbNew;

	return bResult;
}

//	ファイル状態(更新日時・サイズ)で比較
bool zfcComparetor::compareFileStatus( const CString& strPathOldDwg, const CString strPathNewDwg ) const
{
	bool bContinue = true;
	CFileStatus fileStatusOld;
	CFileStatus fileStatusNew;

	VERIFY( CFile::GetStatus( strPathOldDwg, fileStatusOld ) );
	VERIFY( CFile::GetStatus( strPathNewDwg, fileStatusNew ) );

	if( fileStatusOld.m_mtime == fileStatusNew.m_mtime && fileStatusOld.m_size == fileStatusNew.m_size ){
		incrementCorrespond();
		zfcUtility::writeLog2( IDS_CORRESPOND, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
		bContinue = false;
	}
	else if( fileStatusNew.m_mtime < fileStatusOld.m_mtime ){
		incrementWarning();
		zfcUtility::writeLog2( IDS_OLD_DWG_TIMESTAMP_IS_NEW, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
		bContinue = false;
	}

	return bContinue;
}

//	図面読み込み
bool zfcComparetor::readDwg( AcDbDatabase*& pDb, const CString& strPath ) const
{
	bool bResult = true;
	auto es = zfcUtility::readDwg( pDb, strPath );

	if( Acad::eOk != es ){
		zfcUtility::writeLog1( IDS_FAIL_TO_READ_DWG, strPath );
		bResult = false;
	}
	
	return bResult;
}

//	図面内要素のオブジェクトID取得
bool zfcComparetor::getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb ) const
{
	bool bResult = true;
	auto es = zfcUtility::getAllObjectId( conObjectId, pDb );

	if( Acad::eOk != es ){
		// todo API調査
		zfcUtility::writeLog1( IDS_FAIL_TO_GET_ID, pDb->document()->title() );
		bResult = false;
	}
	
	return bResult;
}

