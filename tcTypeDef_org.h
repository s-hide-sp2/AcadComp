#pragma once

#ifdef _IMPORT_TCS
	#define TCS_EXPORT_CLASS	__declspec( dllimport )
#else
	#define TCS_EXPORT_CLASS	__declspec( dllexport )
#endif

/////////////////////////////////////////////////////////////
//
//	レジストリ


namespace Tcs{
	enum Result{
		rOk,					//	OK
		rFail,					//	失敗
		rOverUseSpan,			//	使用期間オーバー
		rInvalidRegistryInfo,	//	レジストリ情報無効
		rFailToAccessRegistry,	//	レジストリアクセス失敗
		rOutOfBuffer			//	バッファ不足
	};
};

/////////////////////////////////////////////////////////////
//
//	レジストリ

#define TCS_REG_KEY_INSTALL_INFO	_T("CLSID\\{124E9F44-658E-4bf5-BE5A-C57BCAFAE8A0}")	//	インストール情報格納キー
#define TCS_REG_DATA_INSTALL_DAY	_T("InstallDay")			//	インストール日付
#define TCS_REG_DATA_ACCESS_DAY		_T("AccessDay")				//	最終アクセス日付
#define TCS_REG_DATA_USE_SPAN		_T("UseSpan")				//	使用期間
