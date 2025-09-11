#pragma once

#include "imgui.h"

#include "mcc_communication_structs.h"

#include "mcc_window_management.h"

namespace monster_calculator {

void BeginStyledWindow(WindowParameters& window_parameters) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);
}

void EndStyledWindow(WindowParameters& window_parameters) {
	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void BeginDynamicWindow(WindowParameters& window_parameters, bool* p_open) {
	ImGui::SetNextWindowSize(window_parameters.window_size, ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(window_parameters.window_position, ImGuiCond_Appearing);

	ImGui::Begin(window_parameters.name.c_str(), p_open, window_parameters.imgui_window_settings);
}

void EndDynamicWindow(WindowParameters& window_parameters) {
	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}


} // namespace monster_calculator