#include "pch.h"

#include "EngineCore.h"
#include "EngineWindow.h"

EngineCore::EngineCore(HINSTANCE _HInst)
{
	CoreInit(_HInst);
}

EngineCore::~EngineCore()
{
	for (size_t i = 0; i < mWindows.size(); ++i)
	{
		if (mWindows[i] != nullptr)
		{
			delete mWindows[i];
			mWindows[i] = nullptr;
		}
	}
	mWindows.clear();
}

void EngineCore::CoreInit(HINSTANCE _HInst)
{
	assert(!Core && "Twice Make of Engine Core.");

	Core = this;
	mHInst = _HInst;
}

void EngineCore::EngineLoop()
{
	MSG Msg = {};

	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessageW(&Msg);
		}
		else
		{
			// TODO.. Loop Code..

		}
	}
}

void EngineCore::QuitEngine()
{
	PostQuitMessage(0);
}

