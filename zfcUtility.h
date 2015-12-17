#pragma once

#include "zfcTypeDef.h"

class zfcUtility
{
public:

	static Acad::ErrorStatus readDwg( AcDbDatabase*& pDb, const CString& strPath );

	static Acad::ErrorStatus getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb );

	static Acad::ErrorStatus getAllEntity( zfc::entityContainer& conEntity, AcDbDatabase* pDb, AcDb::OpenMode mode );

	static Acad::ErrorStatus getAllEntity( zfc::entityContainer& conEntity, AcDbBlockTableRecordIterator* pBlkRecItr, AcDb::OpenMode mode );

	static Acad::ErrorStatus getAllAttribute( zfc::entityContainer& conEntity, AcDbBlockReference* pBlockRef, AcDb::OpenMode mode );

	//	ログファイル名を返す
	static CString logFileName();

	//	ファイルパスを返す
	static CString filePath( const CString& strFolderPath, const CString& strFileName, const CString& strExt = _T("") );

protected:

	zfcUtility(void);
	virtual ~zfcUtility(void);

};

