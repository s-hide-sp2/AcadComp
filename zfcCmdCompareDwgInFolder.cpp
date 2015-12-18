#include "stdafx.h"
#include "resource.h"
#include "zfcCmdCompareDwgInFolder.h"
#include "zfcUtility.h"
#include "zfcLogger.h"
#include "zfcComparetor.h"
#include "zfcDlgSelectFolder.h"

zfcCmdCompareDwgInFolder::zfcCmdCompareDwgInFolder(void)
{
}

zfcCmdCompareDwgInFolder::~zfcCmdCompareDwgInFolder(void)
{
	VERIFY( zfcLogger::instance().close() );
}

bool zfcCmdCompareDwgInFolder::execute()
{
	zfc::pathContainer conPathOld;
	zfc::pathContainer conPathNew;

	//	各種フォルダを選択する
	if( !selectFolder() )
		return true;

	CString strLogPath = zfcUtility::filePath( folderOutput(), zfcUtility::logFileName() );

	{
		CWaitCursor wait;
		VERIFY( zfcLogger::instance().open( strLogPath ) );

		zfcUtility::writeLog1( IDS_OLD_DWG_FOLDER, folderOldDwg() );
		zfcUtility::writeLog1( IDS_NEW_DWG_FOLDER, folderNewDwg() );

		//	フォルダ下のファイル情報取得
		getDwgInFoder( conPathOld, folderOldDwg() );
		getDwgInFoder( conPathNew, folderNewDwg() );

		// 比較実行
		zfc::for_each( conPathNew, [=](zfc::pathContainer::const_reference pairNew){ compare( pairNew, conPathOld ); } );

		// 旧図面フォルダにしかないファイル情報をログ出力
		writeLogOnlyExistInOldDwgFolder( conPathOld );

		// 新図面フォルダにしかないファイル情報をログ出力
		writeLogOnlyExistInNewDwgFolder();
	}

	AfxMessageBox( IDS_COMPLETE_COMPARE_DWG );
	::ShellExecute( AfxGetMainWnd()->GetSafeHwnd(), _T("open"), strLogPath, NULL, folderOutput(), SW_SHOWNORMAL );
	
	return true;
}

//	各種フォルダを選択する
bool zfcCmdCompareDwgInFolder::selectFolder()
{
	auto& dlg = zfcDlgSelectFolder::instance();
	bool bSelect = false;

	//	フォルダ選択ダイアログ
	if( dlg.DoModal() == IDOK ){
		m_strFolderOldDwg = dlg.folderOldDwg();
		m_strFolderNewDwg = dlg.folderNewDwg();
		m_strFolderOutput = dlg.folderCompoundDwg();
		bSelect = true;
	}

	return bSelect;
}

//	フォルダ下の図面ファイルを取得
void zfcCmdCompareDwgInFolder::getDwgInFoder( zfc::pathContainer& conPath, const CString& strFolder ) const
{
	CFileFind ff;
	CString strFindFile;
	BOOL bFlg = TRUE;

	strFindFile.Format( _T("%s\\*.dwg"), strFolder );
	bFlg = ff.FindFile( strFindFile );

	while( bFlg ){
		bFlg = ff.FindNextFile();

		if( bFlg && !ff.IsDots() && !ff.IsDirectory() ){
			auto itp = conPath.insert( zfc::pathContainer::value_type( ff.GetFileTitle(), ff.GetFilePath() ) );
			assert( itp.second );
		}
	}
}

//	ファイルパスを検出
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

//	図面を比較する
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

// 旧図面フォルダにしかないファイル情報をログ出力
void zfcCmdCompareDwgInFolder::writeLogOnlyExistInOldDwgFolder(zfc::pathContainer& conPathOld) const
{
	zfcUtility::writeLog1( IDS_ONLY_EXIST_OLD_DWG_FOLDER, _T("") );

	//	旧図面フォルダに存在したファイルコンテナから、処理済のファイルを除去
	zfc::for_each( m_conProcessed, [&](zfc::pathContainer::const_reference pair){conPathOld.erase(pair.first);} );

	//	旧図面フォルダのみに存在したファイルを出力
	zfcUtility::writeFileName( conPathOld );
}

// 新図面フォルダにしかないファイル情報をログ出力
void zfcCmdCompareDwgInFolder::writeLogOnlyExistInNewDwgFolder() const
{
	zfcUtility::writeLog1( IDS_ONLY_EXIST_NEW_DWG_FOLDER, _T("") );
	zfcUtility::writeFileName( m_conUnProcessed );
}
