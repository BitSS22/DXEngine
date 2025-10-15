#pragma once

#include <Windows.h>
#include <string>

class EngineWindow
{
public:
	enum class ECloseAction : int8_t
	{
		DESTROY,
		HIDE
	};

public:
	EngineWindow();
	~EngineWindow();

	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

private:
	std::wstring mWindowName = {};
	HWND mHandle = {};
	IntVector2 mPosition = {};
	IntVector2 mSize = {};
	ECloseAction mCloseAction = ECloseAction::DESTROY;

public:
	static void RegisterWindowClass(std::wstring_view _WindowName);
	static EngineWindow* CreateEngineWindow(std::wstring_view _WindowName, std::wstring_view _TitleName);
	static EngineWindow* CreateEngineWindow(std::wstring_view _WindowName);
	static EngineWindow* FindEngineWindow(std::wstring_view _WindowName) noexcept;
	static EngineWindow* FindEngineWindow(HWND _WindowHandle) noexcept;
	void Show();
	void Hide();
	void Destroy();
	static void Destroy(std::wstring_view _WindowName);
	static void Destroy(HWND _WindowHandle);
	void SetTitleName(std::wstring_view _TitleName) noexcept;
	void SetPosition(IntVector2 _Position);
	void SetSize(IntVector2 _Size);
	void SetTransform(IntVector2 _Position, IntVector2 _Size);

private:
	static LRESULT DefaultProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void SetCloseAction(ECloseAction _Action) noexcept
	{
		mCloseAction = _Action;
	}

};

