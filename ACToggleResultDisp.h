#pragma once

class ACToggleResultDisp
{
public:
	ACToggleResultDisp(void);
	~ACToggleResultDisp(void);

	bool IsResultDrawing();
	bool ToggleDisp( Adesk::UInt16 uiColIdx );
};
