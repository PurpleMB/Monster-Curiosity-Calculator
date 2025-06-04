#pragma once
#include <d3d9.h>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

class App
{
public:
	App();
	virtual ~App();
	void Run();
	virtual void StartUp();
	virtual void Update();

protected:
	ImVec4 clear_color;
	ImGuiIO* io;

private:
	HWND hwnd;
	WNDCLASSEXW wc;
};

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);