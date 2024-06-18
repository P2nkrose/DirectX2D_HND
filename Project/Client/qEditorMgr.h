#pragma once

#include <Engine/singleton.h>

class qEditorMgr : public qSingleton<qEditorMgr>
{
	SINGLE(qEditorMgr);

public:
	void Init();
	void Tick();


private:

};

