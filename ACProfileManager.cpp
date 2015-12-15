// ACProfileManager.cpp: ACProfileManager クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ACProfileManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString ACProfileManager::m_strUserProfilePath = _T("");
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

ACProfileManager::ACProfileManager()
{
	InitUserPath();
}

ACProfileManager::~ACProfileManager()
{

}

void ACProfileManager::InitUserPath()
{
	// 個別ユーザーファイルのパス
	TCHAR szPath[256];    
	HWND hWnd = NULL;
	CString strPath;
	HRESULT hRes;
	CFile   fileInfo;
	CFileStatus fStatus;	
	
	if (!m_strUserProfilePath.IsEmpty())
		return;

	// 何故かERROR_INVALID_FUNCTIONのエラーが発生するが、パスは取れるので無視する。
	hRes = SHGetSpecialFolderPath(hWnd, szPath, CSIDL_APPDATA, TRUE); 		
	if (hRes == NOERROR || hRes == ERROR_INVALID_FUNCTION) {
		m_strUserProfilePath = szPath;
// [Taka 2009/06] ARX2010対応  次1行コメントアウト 次1行追加
// SoftAliveを変更
//		m_strUserProfilePath += _T("\\SoftAlive");
		m_strUserProfilePath += _T("\\OtsukaACADAddinsCOMP");
		if (CFile::GetStatus(m_strUserProfilePath, fStatus) == FALSE) {
			if (_tmkdir(m_strUserProfilePath) != 0) { //2006.07.20
				m_strUserProfilePath = _T("");
				return;
			}
		}

			
		m_strUserProfilePath += _T("\\ACUserAppInfo.ini");			
	}	
		
}

// ユーザー個別ファイルに指定した情報を書き込む
// strSec: セクション, strKey: キー
bool ACProfileManager::WriteProfileString(const CString strSec, const CString strKey, const CString strWrite)
{	
	if (WritePrivateProfileString(strSec, strKey, strWrite, m_strUserProfilePath) == TRUE) 
		return true;
	else
		return false;
}

// ユーザー個別ファイルから情報を読み込む
// strSec: セクション, strKey: キー
bool ACProfileManager::ReadProfileString(const CString strSec, const CString strKey, CString& strRet)
{	
	TCHAR cRet[AC_REG_BUFF];//2006.07.20
		
	if (GetPrivateProfileString(strSec, strKey, _T(""), cRet, AC_REG_BUFF, m_strUserProfilePath) == 0) {
		strRet = _T("");
		return false;
	}
	else {
		strRet = cRet;
		return true;
	}
	
}

// 許容誤差を書き込む
void ACProfileManager::SetUserTol(double dTol)
{
	CString strWrite;

	strWrite = ACString::NumberToString(dTol);
	WriteProfileString(ACP_SEC_COMPDWG, _T("TOL"), strWrite);  //2006.07.20
}

// 選択ディレクトリパスを書き込む
void ACProfileManager::SetUserOpenDirPath(LPCTSTR lpctPath)
{	
	WriteProfileString(ACP_SEC_COMPDWG, _T("DIRPATH"), lpctPath); //2006.07.20	
}

// CSVの保存先ディレクトリを保存する。
void ACProfileManager::SetUserSaveCSVPath(LPCTSTR lpctPath)
{
	WriteProfileString(ACP_SEC_COMPDWG, _T("CSVDIRPATH"), lpctPath);	//2006.07.20
}


// 許容誤差を得る
double ACProfileManager::GetUserTol()
{
	CString strRet;
	double dTol;

	ReadProfileString(ACP_SEC_COMPDWG, _T("TOL"), strRet);//2006.07.20
	if (ACString::StringToNumber(strRet, dTol) == false)
		return 0.0001;
	else
		return dTol;	
}

// 変更前文字から変更先へ線を引く最低距離(文字高さｘこの数値)
double ACProfileManager::GetUserModTextArrowMinLength()
{
	CString strRet;
	double dLen;

	ReadProfileString(ACP_SEC_COMPDWG, _T("MODTEXTARROWMINLENGTH"), strRet);
	if (ACString::StringToNumber(strRet, dLen) == false)
		return 3;
	else
		return dLen;	
}

// 選択ディレクトリパスを返す。
CString ACProfileManager::GetUserOpenDirPath()
{
	CString strRet;

	ReadProfileString(ACP_SEC_COMPDWG, _T("DIRPATH"), strRet);//2006.07.20
	return strRet;
}

// CSVの保存先ディレクトリパスを返す。
CString ACProfileManager::GetUserSaveCSVPath()
{
	CString strRet;

	ReadProfileString(ACP_SEC_COMPDWG, _T("CSVDIRPATH"), strRet);//2006.07.20
	return strRet;
}