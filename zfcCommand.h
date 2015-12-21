#pragma once

/**
 * 図面比較コマンド基底クラス
 * 
 */
class zfcCommand
{
public:
	zfcCommand(void);
	virtual ~zfcCommand(void);
	
	//	コマンドを実行する
	static bool execute( zfcCommand& cmd );

protected:

	//	コマンドを実行する
	virtual bool execute() = 0;
};

