#pragma once

#include "zfcTypeDef.h"

/**
 * ユーティリティクラス
 * 
 */
class zfcUtility
{
public:

	//	図面を読み込む
	static Acad::ErrorStatus readDwg( AcDbDatabase*& pDb, const CString& strPath );

	//	図面内全要素のIDを取得する
	static Acad::ErrorStatus getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb );

	//	図面内の全要素を取得する
	static Acad::ErrorStatus getAllEntity( zfc::entityContainer& conEntity, AcDbDatabase* pDb, AcDb::OpenMode mode );

	//	ブロックテーブルレコード内の全要素を取得する
	static Acad::ErrorStatus getAllEntity( zfc::entityContainer& conEntity, AcDbBlockTableRecordIterator* pBlkRecItr, AcDb::OpenMode mode );

	//	ブロック参照内の全属性を取得する
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

