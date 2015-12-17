#include "stdafx.h"
#include "resource.h"
#include "zfcCmdCompareDwgInFolder.h"
#include "zfcUtility.h"
#include "zfcLogger.h"
#include "zfcComparetor.h"

zfcCmdCompareDwgInFolder::zfcCmdCompareDwgInFolder(void)
{
	VERIFY( zfcLogger::instance().open( zfcUtility::filePath( folderOutput(), zfcUtility::logFileName() ) ) );
}


zfcCmdCompareDwgInFolder::~zfcCmdCompareDwgInFolder(void)
{
	VERIFY( zfcLogger::instance().close() );
}

bool zfcCmdCompareDwgInFolder::execute()
{
	zfc::pathContainer conPathOld;
	zfc::pathContainer conPathNew;

	//	フォルダ下のファイル情報取得
	getDwgInFoder( conPathOld, folderOldDwg() );
	getDwgInFoder( conPathNew, folderNewDwg() );

	// 比較実行
	zfc::for_each( conPathNew, [=](zfc::pathContainer::const_reference pairNew){ compare( pairNew, conPathOld ); } );

	// 旧図面フォルダにしかないファイル情報をログ出力

	// 新図面フォルダにしかないファイル情報をログ出力
	writeLogOnlyExistInNewDwgFolder();
}

void zfcCmdCompareDwgInFolder::getDwgInFoder( zfc::pathContainer& conPath, const CString& strFolder ) const
{
	CFileFind ff;
	CString strFindFile;
	BOOL bFlg = TRUE;

	strFindFile.Format( _T("%s\\*.dwg"), strFolder );
	bFlg = ff.FindFile( strFindFile );

	while( bFlg ){
		if( !ff.IsDots() && !ff.IsDirectory() ){
			auto itp = conPath.insert( zfc::pathContainer::value_type( ff.GetFileTitle(), ff.GetFilePath() ) );
			assert( itp.second );
		}

		bFlg = ff.FindNextFile();
	}
}

bool zfcCmdCompareDwgInFolder::findPath( zfc::pathContainer::const_iterator& itPath, const CString& strFind, const zfc::pathContainer& conPath ) const
{
	bool bFind = false;
	auto it = conPath.find( strFind );

	if( conPath.end() == it ){
		auto strNearFile = strFind.Left( strFind.GetLength()-1 );

		it = conPath.find( strNearFile );
	}

	if( conPath.end() != it ){
		bFind = true;
		itPath = it;
	}
	
	return bFind;
}

void zfcCmdCompareDwgInFolder::compare( zfc::pathContainer::const_reference pairNew, const zfc::pathContainer& conPathOld ) const
{
	const CString& strTitleNew = pairNew.first;
	zfc::pathContainer::const_iterator itOld;
	bool bFind = findPath( itOld, strTitleNew, conPathOld );
	zfcComparetor comparetor;

	if( bFind ){
		auto es = comparetor.execute( itOld->second, pairNew.second );
		assert( Acad::eOk == es );
		addProcessed( itOld->first, itOld->second );
	}
	else{
		addUnProcessed( pairNew.first, pairNew.second );
	}
}

void zfcCmdCompareDwgInFolder::writeLogOnlyExistInNewDwgFolder()
{
	CString str;

	AfxFormatString1( str, IDS_ONLY_EXIST_NEW_DWG_FOLDER, _T("") );
	
	zfcLogger::instance().write( str );

	zfc::for_each( m_conUnProcessed, [](zfc::pathContainer::const_reference pair){  zfcLogger::instance().write( _T("%s\n"), pair.second ); } );
}
