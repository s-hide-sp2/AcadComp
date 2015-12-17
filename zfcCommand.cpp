#include "stdafx.h"
#include "zfcCommand.h"

zfcCommand::zfcCommand(void)
{
}

zfcCommand::~zfcCommand(void)
{
}

bool zfcCommand::execute( zfcCommand& cmd )
{
	return cmd.execute();
}

