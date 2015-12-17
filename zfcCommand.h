#pragma once
class zfcCommand
{
public:
	zfcCommand(void);
	virtual ~zfcCommand(void);

	static bool execute( zfcCommand& cmd );

protected:

	virtual bool execute() = 0;
};

