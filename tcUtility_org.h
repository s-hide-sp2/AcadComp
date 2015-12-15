#pragma once

#include "tcTypeDef.h"

//	インストール情報をレジストリに登録する
extern "C" long __stdcall tcRegInstallInfo( LPCTSTR lpszAppKey, long lUseTerm, bool bOverWrite = false );

//	アクセス日を更新する
extern "C" long __stdcall tcUpdateAccessDay( LPCTSTR lpszAppKey );

//	使用期間をチェックする
extern "C" long __stdcall tcCheckUseTerm( LPCTSTR lpszAppKey );


//	レジストリキーを取得する
Tcs::Result tcGetRegKey( LPTSTR lpszRegKey, LPCTSTR lpszAppKey, DWORD dwSize );

//	日付文字列(YYYYMMDD)を取得する
void tcGetDayString( LPTSTR lpszString, const CTime& time );