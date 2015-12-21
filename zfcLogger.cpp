#include "stdafx.h"
#include "zfcLogger.h"


zfcLogger::zfcLogger(void)
	: m_fp(nullptr)
{
}


zfcLogger::~zfcLogger(void)
{
	close();
}

//	シングルトンオブジェクトを返す
zfcLogger& zfcLogger::instance()
{
	static zfcLogger singleton;

	return singleton;
}

//	ログファイルオープン
bool zfcLogger::open( const CString& strPath )
{
	bool bResult = true;
	
	if( nullptr != m_fp )
		m_fp = _tfopen( strPath, _T("a") );	

	if( nullptr == m_fp )
		bResult = false;

	return bResult;
}

//	ログファイルクローズ
bool zfcLogger::close()
{
	bool bResult = true;

	if( nullptr != m_fp ){
		if( fclose(m_fp) != 0 )
			bResult = false;
		
		m_fp = nullptr;
	}

	return bResult;
}

//	ログ出力
bool zfcLogger::write( 
	LPCTSTR lpszLog,		//(i)出力内容
	...	)					//(i)フォーマット引数
{
	bool bResult = true;
	va_list	ap;
	TCHAR* lpszBuff = nullptr;
	int nLen = 0;

	va_start(ap, lpszLog);
	nLen = _vsctprintf( lpszLog, ap ) + 1;

	try{
		lpszBuff = new TCHAR[nLen];

#ifdef _UNICODE
		_vstprintf( lpszBuff, nLen, lpszLog, ap );
#else
		_vstprintf( lpszBuff, lpszLog, ap );
#endif
		_ftprintf( m_fp, lpszBuff );
		va_end(ap);
		delete [] lpszBuff;
	}
	catch( ... ){
		bResult = false;
	}

	return bResult;
}
