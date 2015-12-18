#pragma once


// zfcDlgSelectFolder ダイアログ

class zfcDlgSelectFolder : public CDialogEx
{
	DECLARE_DYNAMIC(zfcDlgSelectFolder)

public:
	zfcDlgSelectFolder(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~zfcDlgSelectFolder();

	static zfcDlgSelectFolder& instance();

	///////////////////////////////////////////////////////
	//
	//	Get/Set

	const CString& folderOldDwg() const;
	const CString& folderNewDwg() const;
	const CString& folderCompoundDwg() const;

// ダイアログ データ
	enum { IDD = IDD_DLG_SEL_FOLDER };

private:
	//	フォルダの存在チェック
	BOOL checkFolder( int nEditCtrlID ) const;
	BOOL selectFolder( CString& strSelFolder, const CString& strIniFolder );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFolderOldDwg();
private:
	CString m_strFolderOldDwg;
	CString m_strFolderNewDwg;
	CString m_strFolderCompoundDwg;
public:
	afx_msg void OnBnClickedBtnFolderNewDwg();
	afx_msg void OnBnClickedBtnFolderCompoundDwg();
	afx_msg void OnBnClickedExecute();
};

inline const CString& zfcDlgSelectFolder::folderOldDwg() const
{
	return m_strFolderOldDwg;
}

inline const CString& zfcDlgSelectFolder::folderNewDwg() const
{
	return m_strFolderOldDwg;
}

inline const CString& zfcDlgSelectFolder::folderCompoundDwg() const
{
	return m_strFolderCompoundDwg;
}

