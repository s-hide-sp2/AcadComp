// ACProfileManager.h: ACProfileManager クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACPROFILEMANAGER_H__90551992_6BB4_4027_B574_C9D7B20DC68E__INCLUDED_)
#define AFX_ACPROFILEMANAGER_H__90551992_6BB4_4027_B574_C9D7B20DC68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define AC_REG_BUFF 1024
#define ACP_SEC_COMPDWG "COMPDWG"

#include <direct.h>
#include "ACString.h"

class ACProfileManager  
{
public:
	ACProfileManager();
	virtual ~ACProfileManager();


	// 許容誤差を書き込む
	void SetUserTol(double dTol);

	// 選択ディレクトリパスを書き込む
	void SetUserOpenDirPath(LPCTSTR lpctPath);

	// CSVの保存先ディレクトリを保存する。
	void SetUserSaveCSVPath(LPCTSTR lpctPath);


	// 許容誤差を得る
	double GetUserTol();

	// 変更前文字から変更先へ線を引く最低距離(文字高さｘこの数値)
	double GetUserModTextArrowMinLength();

	// 選択ディレクトリパスを返す。
	CString GetUserOpenDirPath();
	
	// CSVの保存先ディレクトリパスを返す。
	CString GetUserSaveCSVPath();

protected:
	// ユーザー個別ファイルに指定した情報を書き込む
	// strSec: セクション, strKey: キー
	bool WriteProfileString(const CString strSec, const CString strKey, const CString strWrite);

	// ユーザー個別ファイルから情報を読み込む
	// strSec: セクション, strKey: キー
	bool ReadProfileString(const CString strSec, const CString strKey, CString& strRet);

private:
	// ログインユーザーのプロファイルパスを得て、メンバ変数にセットする。
	void InitUserPath();

	static CString m_strUserProfilePath;	
	
	
};

#endif // !defined(AFX_ACPROFILEMANAGER_H__90551992_6BB4_4027_B574_C9D7B20DC68E__INCLUDED_)
