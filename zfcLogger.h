#pragma once

/**
 * ログ出力クラス
 * 
 */
class zfcLogger
{
public:
	//	シングルトンオブジェクトを返す
	static zfcLogger& instance();

	//	ログファイルオープン
	bool open( const CString& strPath );

	//	ログファイルクローズ
	bool close();

	//	ログ出力
	bool write( LPCTSTR lpszLog, ...);

protected:

	zfcLogger(void);
	virtual ~zfcLogger(void);

private:
	FILE* m_fp;
};
