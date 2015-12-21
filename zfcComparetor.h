#pragma once

#include "zfcTypeDef.h"
#include "ResultCompEntity.h"

/**
 * 図面比較クラス
 * 
 */
class zfcComparetor
{
public:

	//	シングルトンオブジェクトを返す
	static zfcComparetor& instance();

	//	初期化処理
	void init();

	//	図面比較を行う
	Acad::ErrorStatus execute( const CString& strPathOldDwg, const CString strPathNewDwg );

	//	一致図面数
	int cntCorrespond() const;

	//	不一致図面数
	int cntDiscord() const;

	//	警告数
	int cntWarning() const;

	//	エラー数
	int cntError() const;

protected:

	zfcComparetor(void);
	virtual ~zfcComparetor(void);

	//	ファイル状態(更新日時・サイズ)で比較
	bool compareFileStatus( const CString& strPathOldDwg, const CString strPathNewDwg ) const;

	//	図面読み込み
	bool readDwg( AcDbDatabase*& pDb, const CString& strPath ) const;

	//	図面内要素のオブジェクトID取得
	bool getAllObjectId( acd::objectIdContainer& conObjectId, AcDbDatabase* pDb ) const;

	//	一致図面インクリメント
	void incrementCorrespond();

	//	不一致図面インクリメント
	void incrementDiscord();

	//	警告数インクリメント
	void incrementWarning();

	//	エラー数インクリメント
	void incrementError();

private:
	//	一致図面数
	int m_nCntCorrespond;

	//	不一致図面数
	int m_nCntDiscord;

	//	警告数
	int m_nCntWarning;

	//	エラー数
	int m_nCntError;
};

//	一致図面数
inline int zfcComparetor::cntCorrespond() const
{
	return m_nCntCorrespond;
}

//	不一致図面数
inline int zfcComparetor::cntDiscord() const
{
	return m_nCntDiscord;
}

//	警告数
inline int zfcComparetor::cntWarning() const
{
	return m_nCntWarning;
}

//	エラー数
inline int zfcComparetor::cntError() const
{
	return m_nCntError;
}

//	一致図面インクリメント
inline void zfcComparetor::incrementCorrespond()
{
	m_nCntCorrespond++;
}

//	不一致図面インクリメント
inline void zfcComparetor::incrementDiscord()
{
	m_nCntDiscord++;
}

//	警告数インクリメント
inline void zfcComparetor::incrementWarning()
{
	m_nCntWarning++;
}

//	エラー数インクリメント
inline void zfcComparetor::incrementError()
{
	m_nCntError++;
}

