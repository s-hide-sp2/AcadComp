#include "StdAfx.h"
#include "tcTypeDef.h"
#include "tcRegistry.h"
	

//	コンストラクタ
tcRegistry::tcRegistry()
{
	SetHKey( HKEY_CLASSES_ROOT );
	SetKey( TCS_REG_KEY_INSTALL_INFO );
}

//	デストラクタ
tcRegistry::~tcRegistry()
{
}

//	レジストリデータを読み込む
Tcs::Result tcRegistry::ReadData( 
	LPTSTR lpszValue,	//(o)値
	LPCTSTR lpszData,	//(i)データ名
	DWORD dwSize		//(i)バッファサイズ
	) const
{
	Tcs::Result result = Tcs::rOk;
	HKEY hKey;
	long lResult = ::RegOpenKeyEx( GetHKey(), GetKey(), 0, KEY_EXECUTE, &hKey );
	
	if( lResult == ERROR_SUCCESS ){
		DWORD dwSizeTemp = dwSize;

		lResult = ::RegQueryValueEx( hKey, lpszData, NULL, NULL, (LPBYTE)lpszValue, &dwSizeTemp );
		::RegCloseKey( hKey );
	}
	
	if( lResult != ERROR_SUCCESS )
		result = Tcs::rFailToAccessRegistry;
	
	return ( result );	
}

//	レジストリデータを書き込む
Tcs::Result tcRegistry::WriteData( 
	LPCTSTR lpszValue,	//(i)値
	LPCTSTR lpszData	//(i)データ名
	) const
{
	Tcs::Result result = Tcs::rOk;
	HKEY hKey;
	DWORD dwDisposition;
	long lResult = ::RegCreateKeyEx( GetHKey(), GetKey(), 0, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition );

	if( lResult == ERROR_SUCCESS ){
		
		lResult = ::RegSetValueEx( hKey, lpszData, 0, REG_SZ, (CONST LPBYTE)lpszValue, (_tcslen(lpszValue)+1)*sizeof(TCHAR) );
		::RegCloseKey( hKey );
	}
	
	if( lResult != ERROR_SUCCESS )
		result = Tcs::rFailToAccessRegistry;

	return ( result );
}

