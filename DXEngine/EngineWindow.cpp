#include "pch.h"
#include "EngineWindow.h"

#include <string>

#include "EngineCore.h"

EngineWindow::EngineWindow()
{
}

EngineWindow::~EngineWindow()
{
	DestroyWindow(mHandle);
}

void EngineWindow::RegisterWindowClass(std::wstring_view _WindowName, bool _Menu)
{
	WNDCLASSEXW WC = {};

	WC.lpszClassName = _WindowName.data();
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = EngineWindow::DefaultProc;
	WC.lpszMenuName = nullptr;

	WC.cbSize = sizeof(WNDCLASSEXW);
	WC.hInstance = EngineCore::Core->mHInst;
	WC.hIcon = nullptr;
	WC.hIconSm = nullptr;
	WC.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	ATOM Result = RegisterClassExW(&WC);
	assert(Result);
}

EngineWindow* EngineWindow::CreateEngineWindow(std::wstring_view _WindowName, std::wstring_view _TitleName)
{
	if (FindEngineWindow(_WindowName) != nullptr)
	{
		return nullptr;
	}

	EngineWindow* NewWindow = new EngineWindow();
	NewWindow->mWindowName = _WindowName;
	HWND& WHandle = NewWindow->mHandle;
	HINSTANCE HInst = EngineCore::Core->mHInst;

	WHandle = CreateWindowExW(0, _WindowName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, HInst, nullptr);
	assert(WHandle);

	EngineCore::Core->mWindows.push_back(NewWindow);

	return NewWindow;
}

EngineWindow* EngineWindow::CreateEngineWindow(std::wstring_view _WindowName)
{
	return CreateEngineWindow(_WindowName, _WindowName);
}

void EngineWindow::Show()
{
	ShowWindow(mHandle, SW_SHOW);
}

void EngineWindow::Hide()
{
	ShowWindow(mHandle, HIDE_WINDOW);
}

void EngineWindow::Destroy()
{
	std::vector<EngineWindow*>& Windows = EngineCore::Core->mWindows;
	for (size_t i = 0; i < Windows.size(); ++i)
	{
		if (Windows[i]->mHandle == mHandle)
		{
			Windows.erase(Windows.begin() + i);
			DestroyWindow(mHandle);
			break;
		}
	}
}

void EngineWindow::Destroy(std::wstring_view _WindowName)
{
	EngineWindow* Window = FindEngineWindow(_WindowName);
	assert(Window);
	Window->Destroy();
}

void EngineWindow::Destroy(HWND _WindowHandle)
{
	EngineWindow* Window = FindEngineWindow(_WindowHandle);
	assert(Window);
	Window->Destroy();
}

void EngineWindow::SetTitleName(std::wstring_view _TitleName) noexcept
{
	SetWindowTextW(mHandle, _TitleName.data());
}

void EngineWindow::SetPosition(IntVector2 _Position)
{
	SetTransform(_Position, mSize);
}

void EngineWindow::SetSize(IntVector2 _Size)
{
	SetTransform(mPosition, _Size);
}

void EngineWindow::SetTransform(IntVector2 _Position, IntVector2 _Size)
{
	RECT Rect = {};
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = _Size.x;
	Rect.bottom = _Size.y;

	AdjustWindowRectEx(&Rect, WS_OVERLAPPEDWINDOW, false, false);

	int Width = Rect.right - Rect.left;
	int Height = Rect.bottom - Rect.top;

	MoveWindow(mHandle, _Position.x - (Width / 2), _Position.y - (Height / 2), Width, Height, false);
}

EngineWindow* EngineWindow::FindEngineWindow(std::wstring_view _WindowName) noexcept
{
	std::vector<EngineWindow*>& Windows = EngineCore::Core->mWindows;

	for (size_t i = 0; i < Windows.size(); ++i)
	{
		if (Windows[i]->mWindowName == _WindowName)
		{
			return Windows[i];
		}
	}

	return nullptr;
}

EngineWindow* EngineWindow::FindEngineWindow(HWND _WindowHandle) noexcept
{
	std::vector<EngineWindow*>& Windows = EngineCore::Core->mWindows;

	for (size_t i = 0; i < Windows.size(); ++i)
	{
		if (Windows[i]->mHandle == _WindowHandle)
		{
			return Windows[i];
		}
	}

	return nullptr;
}

LRESULT EngineWindow::DefaultProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EngineWindow* Window = FindEngineWindow(hWnd);
		assert(Window);
		Window->Destroy();
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}