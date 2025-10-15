#pragma once

#include <Windows.h>
#include <vector>

class EngineWindow;

class EngineCore
{
public:
	friend class EngineWindow;

public:
	EngineCore(HINSTANCE _HInst);
	~EngineCore();

	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

private:
	inline static EngineCore* Core = nullptr;
	HINSTANCE mHInst = {};
	std::vector<EngineWindow*> mWindows = {};

public:
	void CoreInit(HINSTANCE _HInst);
	void EngineLoop();
	static void QuitEngine();

public:
	static EngineCore* GetCore() noexcept
	{
		return Core;
	}
	HINSTANCE GetHINSTANCE() const noexcept
	{
		return mHInst;
	}
	
};

