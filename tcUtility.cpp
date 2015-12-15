#include "StdAfx.h"
#include "tcUtility.h"
#include "tcRegistry.h"

//	インストール情報をレジストリに登録する
extern "C" long __stdcall tcRegInstallInfo( 
	LPCTSTR lpszAppKey,		//(i)アプリケーションキー
	long lUseTerm,			//(i)使用期間
	bool bOverWrite			//(i)上書きフラグ
	)
{
	Tcs::Result result = Tcs::rOk;
	TCHAR szKey[1024];

	//	レジストリキー文字列取得
	result = tcGetRegKey( szKey, lpszAppKey, sizeof(szKey) );
	
	if( result == Tcs::rOk ){
		tcRegistry reg;
		TCHAR szInstallDay[8+1];
		TCHAR szUseTerm[128];
		bool bReg = false;
	
		reg.SetKey( szKey );

		//	使用期間を取得しインストール情報の有無を判定する
		result = reg.ReadData( szUseTerm, TCS_REG_DATA_USE_SPAN, sizeof(szUseTerm) );
		
		//	インストール情報情報がない場合は登録
		if(	result == Tcs::rFailToAccessRegistry )
			bReg = true;
		//	インストール情報情報がある場合は上書き
		else if	( result == Tcs::rOk && bOverWrite )
			bReg = true;
		
		if( bReg ){
			//	インストール日付登録
			tcGetDayString( szInstallDay, CTime::GetCurrentTime() );
			result = reg.WriteData( szInstallDay, TCS_REG_DATA_INSTALL_DAY );
			
			//	使用期間登録
			if( result == Tcs::rOk )
				//2006.07.01
				result = reg.WriteData( (LPCTSTR)_itoa(lUseTerm,(char *)szUseTerm,10), TCS_REG_DATA_USE_SPAN );

			//	アクセス日を更新する
			if( result == Tcs::rOk )
				result = (Tcs::Result)tcUpdateAccessDay( lpszAppKey );
		}
	}

	return ( result );
}

//	アクセス日を更新する
extern "C" long __stdcall tcUpdateAccessDay( 
	LPCTSTR lpszAppKey //(i)アプリケーションキー
	)
{
	Tcs::Result result = Tcs::rOk;
	TCHAR szKey[1024];

	//	レジストリキー文字列取得
	result = tcGetRegKey( szKey, lpszAppKey, sizeof(szKey) );
	
	if( result == Tcs::rOk ){
		tcRegistry reg;
		TCHAR szAccessDay[8+1];
	
		reg.SetKey( szKey );

		//	アクセス日を登録する
		tcGetDayString( szAccessDay, CTime::GetCurrentTime() );
		result = reg.WriteData( szAccessDay, TCS_REG_DATA_ACCESS_DAY );
	}

	return ( result );
}

//	使用期間をチェックする
extern "C" long __stdcall tcCheckUseTerm( 
	LPCTSTR lpszAppKey //(i)アプリケーションキー
	)
{
	Tcs::Result result = Tcs::rOk;
	TCHAR szKey[1024];
	TCHAR szInstallDay[8+1];
	TCHAR szAccessDay[8+1];
	TCHAR szUseTerm[128];



	//	レジストリキー文字列取得
	result = tcGetRegKey( szKey, lpszAppKey, sizeof(szKey) );
	
	if( result == Tcs::rOk ){
		tcRegistry reg;
		
		reg.SetKey(szKey);

		//	インストール日付取得
		result = reg.ReadData( szInstallDay, TCS_REG_DATA_INSTALL_DAY, sizeof(szInstallDay) );

		//	アクセス日付取得
		if( result == Tcs::rOk )
			result = reg.ReadData( szAccessDay, TCS_REG_DATA_ACCESS_DAY, sizeof(szAccessDay) );

		//	使用期間取得
		if( result == Tcs::rOk )
			result = reg.ReadData( szUseTerm, TCS_REG_DATA_USE_SPAN, sizeof(szUseTerm) );
	}

	//	使用期間をチェック
	if( result == Tcs::rOk ){
		CString strInstallDay( szInstallDay );
		CString strAccessDay( szAccessDay );
		CTime timeCur = CTime::GetCurrentTime();
		CTime timeInst( _ttoi(strInstallDay.Left(4)), _ttoi(strInstallDay.Mid(4,2)), _ttoi(strInstallDay.Mid(6,2)), 0,0,0  );
		CTime timeAccess( _ttoi(strAccessDay.Left(4)), _ttoi(strAccessDay.Mid(4,2)), _ttoi(strAccessDay.Mid(6,2)), 0,0,0  );
		
		//	インストール日付 <= 更新日付 <= 現在日付 チェック
		if( timeInst <= timeAccess && timeAccess <= timeCur ){
			CTimeSpan span = timeCur - timeInst;
			//2006.07.01
			LONG lUseSpan = (LONG)span.GetDays();
			
			//更新日付を更新する suda
			tcUpdateAccessDay(lpszAppKey);

			//	使用期間チェック
			if( _ttol(szUseTerm) <= lUseSpan )
				result = Tcs::rOverUseSpan;
		}
		else
			result = Tcs::rInvalidRegistryInfo;
	}

	return ( result );
}

//	レジストリキーを取得する
Tcs::Result tcGetRegKey( 
	LPTSTR lpszRegKey,	//(o)レジストリキー
	LPCTSTR lpszAppKey,	//(i)アプリケーションキー
	DWORD dwSize		//(i)バッファサイズ
	)
{
	Tcs::Result result = Tcs::rOk;
	TCHAR szBuff[1024];

	//	レジストリキーセット
	_stprintf( szBuff, _T("%s\\%s"), TCS_REG_KEY_INSTALL_INFO, lpszAppKey );
	if( _tcslen( szBuff ) < dwSize )
		_tcscpy( lpszRegKey, szBuff );
	else 
		result = Tcs::rOutOfBuffer;

	return ( result );
}

//	日付文字列(YYYYMMDD)を取得する
void tcGetDayString( 
	LPTSTR lpszString,	//(o)日付文字列
	const CTime& time	//(i)時間
	)
{
	_stprintf( lpszString, _T("%04d%02d%02d"), time.GetYear(), time.GetMonth(), time.GetDay() );
}
