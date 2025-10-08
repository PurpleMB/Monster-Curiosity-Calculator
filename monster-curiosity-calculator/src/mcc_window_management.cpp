#pragma once

#include "imgui.h"

#include "mcc_communication_structs.h"

#include "mcc_window_management.h"

namespace monster_calculator {

// TODO: change the handling of WindowParameters to be more descripive. For windows to be placed on 
// some sort of group with margins, construct a WindowPlacement object class that handles maintaining proper margins
// and so on that gets passed into those functions similarly to passing in vector bounds for scaling windows

void BeginStyledWindow(WindowParameters& window_parameters) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::SetNextWindowCollapsed(false, ImGuiCond_Appearing);

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

void BeginSubMenuWindow(WindowParameters& window_parameters, bool* p_open) {
	ImGui::SetNextWindowSize(window_parameters.window_size, ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(window_parameters.window_position, ImGuiCond_Appearing);
	
	ImGui::SetNextWindowCollapsed(false, ImGuiCond_Appearing);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);

	ImGui::Begin(window_parameters.name.c_str(), p_open, window_parameters.imgui_window_settings);

	ImGui::PopStyleVar();
}

void EndSubMenuWindow(WindowParameters& window_parameters) {
	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void BeginScalingWindow(WindowParameters& window_parameters, ImVec2 starting_pos, ImVec2 ending_pos) {
	// TODO: do some more math here to balance the margins for the ratio of the viewport
	ImVec2 screen_size = ImGui::GetMainViewport()->WorkSize;

	ImVec2 window_start = ImVec2(starting_pos.x * screen_size.x, starting_pos.y * screen_size.y);
	ImVec2 window_end = ImVec2(ending_pos.x * screen_size.x, ending_pos.y * screen_size.y);
	
	ImVec2 window_size = ImVec2(window_end.x - window_start.x, window_end.y - window_start.y);

	ImGui::SetNextWindowPos(window_start);
	ImGui::SetNextWindowSize(window_size);

	ImGui::SetNextWindowCollapsed(false, ImGuiCond_Appearing);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);
}

void EndScalingWindow(WindowParameters& window_parameters) {
	window_parameters.window_size.x = ImGui::GetWindowWidth();
	window_parameters.window_size.y = ImGui::GetWindowHeight();

	ImGui::End();
}


} // namespace monster_calculator