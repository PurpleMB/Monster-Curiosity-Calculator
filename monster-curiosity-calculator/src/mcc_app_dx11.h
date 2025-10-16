#pragma once
#include <d3d11.h>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

namespace monster_calculator {

// Encloses and obfuscates boilerplate DearImGui code
// Each class method, including constructors and destructors,
// simply contains code required to get DearImGui running.
// Ideally, a child class of App only needs to define its
// own Update() implementation to handle its own GUI drawing
// without worrying about defining any buffers, fonts, etc..
class App {
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
void CreateRenderTarget();
void CleanupRenderTarget(); 
bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
// Open and read a file, then forward to LoadTextureFromMemory()
bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

} // namespace monster_calculator