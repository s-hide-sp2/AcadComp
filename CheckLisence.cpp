// CheckLisence.cpp: CCheckLisence クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CheckLisence.h"
#include <io.h>
#include <fcntl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CCheckLisence::CCheckLisence()
{

}

CCheckLisence::~CCheckLisence()
{

}

BOOL CCheckLisence::CheckUsableTerm(CString strAppName, CString strAcadVer)
{
	CString			strRegPath;
	CString			strCRC;
	CString			strBuf;
	CString			strVersion=_T(""), strOverride=_T(""), strTarFolder=_T(""),
					strInstallDate=_T(""), strLastAccess=_T(""),
					strUsableTerm=_T(""),  strCheckPrgName=_T(""),  strPrgCRC=_T("");
	unsigned short	crc;
	long			lRet;
	HKEY			hKey; 
	CString			strCheckFileName;
	BOOL			bRet = FALSE;

	//レジストリパスを取得する
	if (GetRegBase(strAcadVer, strRegPath)==FALSE){
//::MessageBox( adsw_acadMainWnd(), _T("strRegPathが取得できません。"), _T("エラー"), MB_ICONINFORMATION );
		return FALSE;
	}
	strRegPath += "_"; 
	strRegPath += strAppName;
	lRet = RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS, &hKey);
	if (lRet == ERROR_SUCCESS){

		lRet = RegQueryValueAcad(hKey, ITM_VERSION,		  	strVersion);
		lRet = RegQueryValueAcad(hKey, ITM_OVERRIDE,	  	strOverride);
		lRet = RegQueryValueAcad(hKey, ITM_INSTALLFOLDER, 	strTarFolder);
		lRet = RegQueryValueAcad(hKey, ITM_INSTALLDATE,   	strInstallDate);
		lRet = RegQueryValueAcad(hKey, ITM_LASTACCESS,    	strLastAccess);
		lRet = RegQueryValueAcad(hKey, ITM_USABLETERM,  	strUsableTerm);
		lRet = RegQueryValueAcad(hKey, ITM_CHECKPRG,  		strCheckPrgName);
		lRet = RegQueryValueAcad(hKey, ITM_REVISION,  		strPrgCRC);
		lRet = RegQueryValueAcad(hKey, ITM_REVISIONSUB, 	strCRC);
		RegCloseKey(hKey);
		if (lRet != ERROR_SUCCESS || strCRC == _T("")){
//::MessageBox( adsw_acadMainWnd(), _T("レジストリが取得できません。"), _T("エラー"), MB_ICONINFORMATION );
			return FALSE;
		}
		strBuf = strVersion + strOverride + strTarFolder + strInstallDate + strLastAccess +
				 strUsableTerm + strCheckPrgName + strPrgCRC;
		GetCRCVal(strBuf, crc);
		strBuf.Format (_T("%d"), crc);
		if (strBuf != strCRC){
//::MessageBox( adsw_acadMainWnd(), _T("CRCが一致しません。"), _T("エラー"), MB_ICONINFORMATION );
			return FALSE;
		}
		if (strCheckPrgName != _T("")){
			strCheckFileName = strTarFolder + _T("\\") + strCheckPrgName;
			if (GetCRCValFile(strCheckFileName, crc)){
				strBuf.Format(_T("%d"), crc);
				if (strBuf != strPrgCRC){
//::MessageBox( adsw_acadMainWnd(), _T("チェックプログラムCRCが一致しません。"), _T("エラー"), MB_ICONINFORMATION );
					return FALSE;
				}
			}
			else {
//::MessageBox( adsw_acadMainWnd(), _T("チェックプログラムCRCが取得できません。"), _T("エラー"), MB_ICONINFORMATION );
				return FALSE;
			}
		}
		bRet = FALSE;
		CTime timeCur = CTime::GetCurrentTime();	
		CTime timeInst( _ttoi(strInstallDate.Left(4)), _ttoi(strInstallDate.Mid(4,2)), _ttoi(strInstallDate.Mid(6,2)), 0,0,0  );
		CTime timeAccess( _ttoi(strLastAccess.Left(4)), _ttoi(strLastAccess.Mid(4,2)), _ttoi(strLastAccess.Mid(6,2)), 0,0,0  );
		//	インストール日付 <= 更新日付 <= 現在日付 チェック
		if( timeInst <= timeAccess && timeAccess <= timeCur ){
			CTimeSpan span = timeCur - timeInst;
			LONG lUseSpan = span.GetDays();
			
			//	使用期間チェック
			if( _ttol(strUsableTerm) <= lUseSpan ){
//::MessageBox( adsw_acadMainWnd(), _T("期間が過ぎています1。"), _T("エラー"), MB_ICONINFORMATION );
				bRet = FALSE;
			}
			//　最終アクセス日を更新する
			else {
				long restDays = _ttol(strUsableTerm) - lUseSpan;
				CString strMsg;
				strMsg.Format (_T("使用可能日数：%d日  "),restDays);
				::MessageBox( adsw_acadMainWnd(), strMsg, _T("お知らせ"), MB_ICONINFORMATION );
				bRet = TRUE;
			}
		}
		else {
//::MessageBox( adsw_acadMainWnd(), _T("期間が過ぎています2。"), _T("エラー"), MB_ICONINFORMATION );
			bRet = FALSE;
		}
		if (timeAccess < timeCur ){
			TCHAR timeBuf[9];
			GetDayString(timeBuf, timeCur);
			strLastAccess = timeBuf;
			strBuf = strVersion + strOverride + strTarFolder + strInstallDate + strLastAccess +
					 strUsableTerm + strCheckPrgName + strPrgCRC;
			GetCRCVal(strBuf, crc);
			strBuf.Format (_T("%d"), crc);
			lRet = RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_WRITE | KEY_READ | KEY_ENUMERATE_SUB_KEYS, &hKey);
			if (lRet == ERROR_SUCCESS){
				lRet = RegSetValueAcad(hKey, ITM_LASTACCESS,   strLastAccess);
				lRet = RegSetValueAcad(hKey, ITM_REVISIONSUB,  strBuf);
				RegCloseKey(hKey);
			}
		}
		return bRet;
	}
	else {
//::MessageBox( adsw_acadMainWnd(), _T("カレントユーザが開けません。"), _T("エラー"), MB_ICONINFORMATION );
		return FALSE;
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
//アプリケーションのレジストリフォルダを取得する
// strCadVer    : AutoCADのバージョン 
// strRegPath	: アプリケーションを管理するレジストリパス（返す）
// 戻り値		: 失敗した場合はエラーコード
BOOL CCheckLisence::GetRegBase(CString strCadVer, CString & strRegPath)
{
	strRegPath = _T("");
	if (strCadVer == VER_14)
		strRegPath = CAD_14REG;
	else if (strCadVer == VER_2000)
		strRegPath = CAD_2000REG;
	else if (strCadVer == VER_2004)
		strRegPath = CAD_2004REG;
	else if (strCadVer == VER_2005)
		strRegPath = CAD_2005REG;
	else if (strCadVer == VER_2006)
		strRegPath = CAD_2006REG;
	//2006.07.02
	else if (strCadVer == VER_2007)
		strRegPath = CAD_2007REG;
	//2007.05.08
	else if (strCadVer == VER_2008)
		strRegPath = CAD_2008REG;
	//2008.04.14
	else if (strCadVer == VER_2009)
		strRegPath = CAD_2009REG;
	else return FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// レジストリから値を取得する
// hKey		：レジストリキー
// strItem	：項目名
// strStr	：値を取得する
// 戻り値	：0=成功  その他=エラーコード
long CCheckLisence::RegQueryValueAcad(HKEY hKey, CString strItem, CString &strStr)
{
	long lRet;
	DWORD dwDataSize, dwDataType;
	static TCHAR szStr[BUF_MAX + 1];

	dwDataSize = BUF_MAX;
	szStr[0]=0;
	lRet = RegQueryValueEx(hKey, strItem, NULL, &dwDataType, (LPBYTE)szStr, &dwDataSize);
	strStr = szStr;
	return lRet;
}


//	日付文字列(YYYYMMDD)を取得する
void CCheckLisence::GetDayString( 
	TCHAR * lpszString,	//(o)日付文字列
	const CTime& time	//(i)時間
	)
{
	_stprintf( lpszString, _T("%04d%02d%02d"), time.GetYear(), time.GetMonth(), time.GetDay() );
}

/////////////////////////////////////////////////////////////////////////////
// レジストリに値をセットする
// hKey		：レジストリキー
// strItem	：項目名
// strStr	：値
// 戻り値	：0=成功  その他=エラーコード
long CCheckLisence::RegSetValueAcad(HKEY hKey, CString strItem,  CString strStr)
{
	long lRet;
	static TCHAR szStr[MAX_PATH * 4 + 1];

	if (strStr.GetLength () <= MAX_PATH*4){
		_tcscpy(szStr, strStr);
		lRet = RegSetValueEx(hKey, strItem,  NULL, REG_SZ, (LPBYTE)szStr, _tcslen(szStr)*sizeof(TCHAR));
		return lRet;
	}
	return ERROR_OUTOFMEMORY;
}



//////////////////////////////////////////////////////////////////////
// CRCを取得する
// strBuf	: CRCを生成するバッファ
// crc      : CRCの値
// 戻り値	: Err_Nothing=成功	その他=失敗
BOOL CCheckLisence::GetCRCVal(CString strBuf, unsigned short & crc)
{
	int l,i,j; 
	TCHAR ch;
	unsigned long	sum;
	unsigned long	polynomial = 	0x01102100;	//CCITT-16	

	sum = 0;

	l =  strBuf.GetLength();
	for (i=0; i<l; i++){
		ch = strBuf[i];
		sum |= (unsigned long)ch;
		for( j=0; j< 8; j++)
		{
			sum <<= 1;
			if( sum & 0x01000000 )
			sum ^= polynomial; 	
		}
	}
	for( i=0; i< 2; i++)	// last 2 byte zero
	{	
		sum |= 0x00;
		for( j=0; j< 8; j++)
		{
			sum <<= 1;
			if( sum & 0x01000000 )
			sum ^= polynomial; 	
		}
	}

	crc =(unsigned short) (( sum>>8 ) & 0x0000FFFF);

	return TRUE;

}

//////////////////////////////////////////////////////////////////////
// CRCを取得する
// strItem	: INIファイル名
// crc      : CRCの値
// 戻り値	: Err_Nothing=成功	その他=失敗
BOOL CCheckLisence::GetCRCValFile(CString strInpFile, unsigned short & crc)
{
	int fh;
	int l,i,j; 
	char ch;
	unsigned long	sum;
	unsigned long	polynomial = 	0x01102100;	//CCITT-16	
	CFile cf;

	sum = 0;

	fh = _topen(strInpFile, O_RDONLY|O_BINARY);
	if (fh > 0){
		l =  _filelength(fh);
		for (i=0; i<l; i++){
			_read(fh, &ch, 1);
			sum |= (unsigned long)ch;
			for( j=0; j< 8; j++)
			{
				sum <<= 1;
				if( sum & 0x01000000 )
				sum ^= polynomial; 	
			}
		}
		for( i=0; i< 2; i++)	// last 2 byte zero
		{	
			sum |= 0x00;
			for( j=0; j< 8; j++)
			{
				sum <<= 1;
				if( sum & 0x01000000 )
				sum ^= polynomial; 	
			}
		}

		crc =(unsigned short) (( sum>>8 ) & 0x0000FFFF);
		_close(fh);
	}
	else {
		return FALSE;
	}
	

	return TRUE;

}
