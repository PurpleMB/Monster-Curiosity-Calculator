#pragma once
#include <d3d11.h>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

namespace purple_mb::imgui_app {

// Encloses and obfuscates boilerplate DearImGui code
// A child class only needs to provide definitions for StartUp & Update,
// simply calling Run to begin the child application.
class App {
public:
    App();
    virtual ~App();

    // Call this once to begin the application
    void Run();

    // This will be called once at application startup, and should contain any 
    // initilization of application state.
    virtual void StartUp();

    // This will be called each frame update, and will contain functions for drawing
    // windows and updating dynamic data.
    virtual void Update();

protected:
    ImVec4 clear_color;	// the background color of the application
    ImGuiIO io;		// ImGui struct responsible for handling processing IO data

private:
    HWND hwnd;			// Windows window handle
    WNDCLASSEXW wc;		// Windows window class information
};

// Configures & creates DX11 environment
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
// handles obtaining and releasing a render buffer for the application, called as part of device creation/cleanup
void CreateRenderTarget();
void CleanupRenderTarget(); 
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);	// callback function for handling messages for the window, can tell if input should be locked

// Loads data file into a DX11 usable texture
bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
// Open and read a file, then forward to LoadTextureFromMemory()
bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

} // namespace purple_mb::imgui_app