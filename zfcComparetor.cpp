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

//	�}�ʔ�r���s��
bool zfcComparetor::execute( const CString& strPathOldDwg, const CString strPathNewDwg )
{
	bool bResult = false;
	AcDbDatabase* pDbOld = nullptr;
	AcDbDatabase* pDbNew = nullptr;
	acd::objectIdContainer conObjectIdOld;
	acd::objectIdContainer conObjectIdNew;
	ResultCompEntity resultCompEntity;
	ACDocManager docManager;

	//	�V�E���}�ʓǂݍ���
	bResult = readDwg( pDbOld, strPathOldDwg );
	if( bResult )
		bResult = readDwg( pDbNew, strPathNewDwg );

	//	�V�E���}�ʂ̑S�G���e�B�e�B��ID�擾
	if( bResult )
		bResult = getAllObjectId( conObjectIdOld, pDbOld );
	if( bResult )
		bResult = getAllObjectId( conObjectIdNew, pDbNew );
	
	//	��r���s
	if( bResult ){
		resultCompEntity.SetHashTableSize( conObjectIdOld.GetCount() + conObjectIdNew.GetCount() );
		bResult = docManager.CompDwgs( conObjectIdOld, conObjectIdNew, resultCompEntity );
		
		if( bResult ){
			if( resultCompEntity.GetCount() == 0 )
				zfcUtility::writeLog2( IDS_CORRESPOND, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
			else
				zfcUtility::writeLog2( IDS_DISCORD, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
		}
		else{
			zfcUtility::writeLog2( IDS_FAIL_TO_COMPARE_DWG, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
		}
	}
	
	//	�����}�ʍ쐬
	if( bResult && 0 < resultCompEntity.GetCount() ){
		bResult = docManager.DrawResultDwg(pDbNew->blockTableId(), pDbOld->blockTableId(), resultCompEntity, conObjectIdNew);

		if( !bResult ){
			zfcUtility::writeLog2( IDS_FAIL_TO_COMPOUND_DWG, zfcUtility::fileName(strPathOldDwg), zfcUtility::fileName(strPathNewDwg) );
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
		zfcUtility::writeLog1( IDS_FAIL_TO_READ_DWG, strPath );
		bResult = false;
	}
	
	return bResult;
}

bool zfcComparetor::getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb ) const
{
	bool bResult = true;
	auto es = zfcUtility::getAllObjectId( conObjectId, pDb );

	if( Acad::eOk != es ){
		// todo API����
		zfcUtility::writeLog1( IDS_FAIL_TO_GET_ID, pDb->document()->title() );
		bResult = false;
	}
	
	return bResult;
}