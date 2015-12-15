#pragma once

//	レジストリ制御クラス
class TCS_EXPORT_CLASS tcRegistry{
public:
	//	コンストラクタ
	tcRegistry();

	//	デストラクタ
	virtual ~tcRegistry();

	//	レジストリデータを取得する
	virtual Tcs::Result ReadData( LPTSTR lpszValue, LPCTSTR lpszData, DWORD dwSize ) const;

	//	レジストリデータを書き込む
	virtual Tcs::Result WriteData( LPCTSTR lpszData, LPCTSTR lpszKey ) const;


	//////////////////////////////////////////////
	//
	//	Get Set 操作


	//	レジストリキー
	HKEY GetHKey() const;
	void SetHKey(HKEY value);
	
	//	レジストリキー
	LPCTSTR GetKey() const;
	void SetKey(LPCTSTR lpszKey);

protected:


private:

	HKEY m_hKey;

	//	キー
	TCHAR m_szKey[512];
};

//	レジストリキー
inline HKEY tcRegistry::GetHKey() const
{
	return ( m_hKey );
}

inline void tcRegistry::SetHKey(HKEY value)
{
	m_hKey = value;
}


//	レジストリキー
inline LPCTSTR tcRegistry::GetKey() const
{
	return ( m_szKey );
}

inline void tcRegistry::SetKey(LPCTSTR lpszKey)
{
	memset( m_szKey, 0, sizeof(m_szKey) );
	//2006.07.01
	_tcsncpy( m_szKey, lpszKey, sizeof(m_szKey)/sizeof(TCHAR)-1 );
}

