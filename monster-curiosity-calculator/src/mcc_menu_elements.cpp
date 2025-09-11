#pragma once

#include "mcc_window_management.h"

#include "mcc_communication_structs.h"

#include "mcc_menu_elements.h"

namespace monster_calculator {

// menu bar elements
void DrawMenuBarMenu(OutputEnvironment& output_environment) {
	ImGui::MenuItem("Options", NULL, &output_environment.show_settings);
}

void DrawMenuBarTools(OutputEnvironment& output_environment) {
	if (ImGui::BeginMenu("Database")) {
		ImGui::MenuItem("Rebuild Database from JSON", NULL, &output_environment.show_database_rebuild);
		ImGui::EndMenu();
	}
	static bool log_bool = false;
	ImGui::MenuItem("Open Program Log", NULL, &output_environment.show_program_log);
}

void DrawMenuBarHelp(OutputEnvironment& output_environment) {
	ImGui::MenuItem("User Guide", NULL, &output_environment.show_user_guide);
	ImGui::MenuItem("Program Info", NULL, &output_environment.show_program_info);
}

// menu windows
void DrawSettingsWindow(OutputEnvironment& output_environment) {

}

// tools windows
void DrawDatabaseRebuildWindow(OutputEnvironment& output_environment) {

}

void DrawProgramLogWindow(OutputEnvironment& output_environment) {

}

// help windows
void DrawUserGuideWindow(OutputEnvironment& output_environment) {

}

void DrawProgramInfoWindow(OutputEnvironment& output_environment) {

}

} // namespace monster_calculator