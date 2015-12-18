#pragma once

#include "zfcTypeDef.h"
#include "ResultCompEntity.h"

class zfcComparetor
{
public:
	zfcComparetor(void);
	virtual ~zfcComparetor(void);

	//	図面比較を行う
	Acad::ErrorStatus execute( const CString& strPathOldDwg, const CString strPathNewDwg );

protected:
	//	ファイル状態(更新日時・サイズ)で比較
	bool compareFileStatus( const CString& strPathOldDwg, const CString strPathNewDwg ) const;

	bool readDwg( AcDbDatabase*& pDb, const CString& strPath ) const;

	bool getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb ) const;

private:
};

