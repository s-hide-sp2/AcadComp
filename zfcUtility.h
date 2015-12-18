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

	//	ログ出力する
	static void writeLog1( int nResourceId, const CString& strFmt1 );

	//	ログ出力する
	static void writeLog2( int nResourceId, const CString& strFmt1, const CString& strFmt2 );

	//	ファイル名をログ出力出力する
	static void writeFileName( const zfc::pathContainer& conPath );

	//	ファイルパスからファイル名を返す
	static CString fileName( const CString& strPath );

protected:

	zfcUtility(void);
	virtual ~zfcUtility(void);

};

