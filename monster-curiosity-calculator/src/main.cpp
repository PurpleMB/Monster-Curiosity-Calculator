#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"
#include "mcc_gui_windows.h"
#include  "mcc_structs.h"

namespace monster_calculator {

// Extends App-provided boilerplate to handle drawing of 
// windows and GUI elements for MCC.
class MCCApp : public App {
public:
	MCCApp() = default;
	~MCCApp() = default;

	virtual void StartUp() final {

	}

	// Put any logic for the GUI that needs to be drawn every frame in here
	virtual void Update() final {
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window_)
			ImGui::ShowDemoWindow(&show_demo_window_);

		ImVec2 window_size = {350, 0};
		ImVec2 window_pos = {kWindowMargin, kWindowMargin};

		// welcome window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Welcome";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;

			monster_calculator::DrawWelcomeWindow(window_params, output_environment);

			window_pos.y += kWindowMargin + window_params.window_size.y;
		}

		// set restriction window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Dataset Refinement";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;

			monster_calculator::DrawSetParameterWindow(window_params, output_environment);

			window_pos.y += kWindowMargin + window_params.window_size.y;
		}

		// value definition window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Output Value Selection";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;

			monster_calculator::DrawValueParameterWindow(window_params);

			window_pos.x += kWindowMargin + window_params.window_size.x;
			window_pos.y = kWindowMargin;
		}

		// set display window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Subset Display";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;

			monster_calculator::DrawSetDisplayWindow(window_params, output_environment);

			window_pos.y += kWindowMargin + window_params.window_size.y;
		}

		// output log window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Output Log";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;

			monster_calculator::DrawOutputLogWindow(window_params, output_environment);
		}
	}

private:
	bool show_demo_window_ = true;
	bool show_another_window_ = false;

	const int kDefaultImGuiWindowSettings = ImGuiWindowFlags_NoResize | 
											ImGuiWindowFlags_NoCollapse | 
											ImGuiWindowFlags_NoMove;
	const float kWindowMargin = 25;

	OutputEnvironment output_environment;
};

} // namespace monster_calculator

// Main code
int main(int, char**) {
	monster_calculator::MCCApp app;
	app.Run();

	return 0;
}
