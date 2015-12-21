#pragma once
#include "zfccommand.h"

class zfcCmdCompareDwgInFolder : public zfcCommand
{
public:
	zfcCmdCompareDwgInFolder(void);
	virtual ~zfcCmdCompareDwgInFolder(void);

	//	図面比較を実行する
	virtual bool execute();

	/////////////////////////////////////////////////
	//
	//	Get/Set

	void setFolderOldDwg(const CString& value );
	const CString& folderOldDwg() const;

	void setFolderNewDwg( const CString& value );
	const CString& folderNewDwg() const;

	void setfolderOutput(const CString& value);
	const CString& folderOutput() const;

protected:
	//	各種フォルダを選択する
	bool selectFolder();

	//	フォルダ下の図面ファイルを取得
	void getDwgInFoder( zfc::pathContainer& conPath, const CString& strFolder ) const;

	//	ファイルパスを検出
	bool findPath( zfc::pathContainer::const_iterator itPath, const CString& strFind, const zfc::pathContainer& conPath ) const;

	//	図面を比較する
	void compare( zfc::pathContainer::const_reference pairNew, const zfc::pathContainer& conPathOld ) const;

	//	処理済み図面を追加
	void addProcessed( const CString& strTitle, const CString& strPath );
	
	//	未処理図面を追加
	void addUnProcessed( const CString& strTitle, const CString& strPath );

	// 旧図面フォルダにしかないファイル情報をログ出力
	void writeLogOnlyExistInOldDwgFolder(zfc::pathContainer& conPathOld) const;

	// 新図面フォルダにしかないファイル情報をログ出力
	void writeLogOnlyExistInNewDwgFolder() const;

	// 比較結果をログ出力する
	void writeLogResult() const;

private:
	//	旧図面格納フォルダ
	CString m_strFolderOldDwg;

	//	新図面格納フォルダ
	CString m_strFolderNewDwg;

	//	出力フォルダ
	CString m_strFolderOutput;

	//	処理済ファイル
	zfc::pathContainer m_conProcessed;

	//	未処理ファイル
	zfc::pathContainer m_conUnProcessed;
};

inline void zfcCmdCompareDwgInFolder::setFolderOldDwg(const CString& value )
{
	m_strFolderOldDwg = value;
}

inline const CString& zfcCmdCompareDwgInFolder::folderOldDwg() const
{
	return m_strFolderOldDwg;
}

inline void zfcCmdCompareDwgInFolder::setFolderNewDwg( const CString& value )
{
	m_strFolderNewDwg = value;
}

inline const CString& zfcCmdCompareDwgInFolder::folderNewDwg() const
{
	return m_strFolderNewDwg;
}

inline void zfcCmdCompareDwgInFolder::setfolderOutput(const CString& value)
{
	m_strFolderOutput = value;
}

inline const CString& zfcCmdCompareDwgInFolder::folderOutput() const
{
	return m_strFolderOutput;
}

inline void zfcCmdCompareDwgInFolder::addProcessed( const CString& strTitle, const CString& strPath )
{
	auto itp = m_conProcessed.insert( zfc::pathContainer::value_type( strTitle, strPath ) );
	assert( itp.second );
}

inline void zfcCmdCompareDwgInFolder::addUnProcessed( const CString& strTitle, const CString& strPath )
{
	auto itp = m_conUnProcessed.insert( zfc::pathContainer::value_type( strTitle, strPath ) );
	assert( itp.second );
}
