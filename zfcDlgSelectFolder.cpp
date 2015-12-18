// zfcDlgSelectFolder.cpp : 実装ファイル
//

#include "stdafx.h"
#include "resource.h"
#include "zfcDlgSelectFolder.h"
#include "afxdialogex.h"


// zfcDlgSelectFolder ダイアログ

IMPLEMENT_DYNAMIC(zfcDlgSelectFolder, CDialogEx)

zfcDlgSelectFolder::zfcDlgSelectFolder(CWnd* pParent /*=NULL*/)
	: CDialogEx(zfcDlgSelectFolder::IDD, pParent)
	, m_strFolderOldDwg(_T(""))
	, m_strFolderNewDwg(_T(""))
	, m_strFolderCompoundDwg(_T(""))
{

}

zfcDlgSelectFolder::~zfcDlgSelectFolder()
{
}

zfcDlgSelectFolder& zfcDlgSelectFolder::instance()
{
	static zfcDlgSelectFolder sigleton;

	return sigleton;
}

//	フォルダの存在チェック
BOOL zfcDlgSelectFolder::checkFolder( int nEditCtrlID ) const
{
	BOOL bResult = TRUE;
	CEdit* pEdt = (CEdit*)GetDlgItem(nEditCtrlID);	// dynamic_castだと何故かnullになる
	assert( pEdt != nullptr );
	CString strPath;
	CFileStatus fileStatus;

	pEdt->GetWindowText( strPath );
	bResult = CFile::GetStatus( strPath, fileStatus );
	
	if( bResult )
		bResult = ( CFile::Attribute::directory & fileStatus.m_attribute );

	if( !bResult ){
		AfxMessageBox( IDS_INVALID_FOLDER, MB_OK | MB_ICONEXCLAMATION );
		pEdt->SetFocus();
		pEdt->SetSel(0,-1);
	}

	return bResult;
}

BOOL zfcDlgSelectFolder::selectFolder( CString& strSelFolder, const CString& strIniFolder )
{
	auto pWinApp = reinterpret_cast<CWinAppEx*>( AfxGetApp() );
	BOOL bSelect = pWinApp->GetShellManager()->BrowseForFolder(strSelFolder, this, strIniFolder);

	return bSelect;
}

void zfcDlgSelectFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_FOLDER_OLD_DWG, m_strFolderOldDwg);
	DDX_Text(pDX, IDC_EDT_FOLDER_NEW_DWG, m_strFolderNewDwg);
	DDX_Text(pDX, IDC_EDT_FOLDER_COMPOUND_DWG, m_strFolderCompoundDwg);
}


BEGIN_MESSAGE_MAP(zfcDlgSelectFolder, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FOLDER_OLD_DWG, &zfcDlgSelectFolder::OnBnClickedBtnFolderOldDwg)
	ON_BN_CLICKED(IDC_BTN_FOLDER_NEW_DWG, &zfcDlgSelectFolder::OnBnClickedBtnFolderNewDwg)
	ON_BN_CLICKED(IDC_BTN_FOLDER_COMPOUND_DWG, &zfcDlgSelectFolder::OnBnClickedBtnFolderCompoundDwg)
	ON_BN_CLICKED(IDEXECUTE, &zfcDlgSelectFolder::OnBnClickedExecute)
END_MESSAGE_MAP()


// zfcDlgSelectFolder メッセージ ハンドラー


void zfcDlgSelectFolder::OnBnClickedBtnFolderOldDwg()
{
	if( selectFolder(m_strFolderOldDwg, m_strFolderOldDwg) ){
		UpdateData(FALSE);
	}
}

void zfcDlgSelectFolder::OnBnClickedBtnFolderNewDwg()
{
	if( selectFolder(m_strFolderNewDwg, m_strFolderNewDwg) ){
		UpdateData(FALSE);
	}
}


void zfcDlgSelectFolder::OnBnClickedBtnFolderCompoundDwg()
{
	if( selectFolder(m_strFolderCompoundDwg, m_strFolderCompoundDwg) ){
		UpdateData(FALSE);
	}
}


void zfcDlgSelectFolder::OnBnClickedExecute()
{
	int nEdtCtrIds[] = { IDC_EDT_FOLDER_OLD_DWG, IDC_EDT_FOLDER_NEW_DWG, IDC_EDT_FOLDER_COMPOUND_DWG };

	if( UpdateData(TRUE) ){
		for each( auto id in nEdtCtrIds ){ if( !checkFolder(id) ) return; }

		OnOK();
	}
}
