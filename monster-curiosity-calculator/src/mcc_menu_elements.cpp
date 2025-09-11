#pragma once

#include "mcc_communication_structs.h"

#include "mcc_menu_elements.h"

namespace monster_calculator {

void DrawMenuBarMenu(OutputEnvironment& output_environment) {
	ImGui::MenuItem("Options");
}

void DrawMenuBarTools(OutputEnvironment& output_environment) {
	if (ImGui::BeginMenu("Database")) {
		ImGui::MenuItem("Rebuild Database from JSON");
		ImGui::EndMenu();
	}
	static bool log_bool = false;
	ImGui::MenuItem("Open Program Log", NULL, &log_bool);
}

void DrawMenuBarHelp(OutputEnvironment& output_environment) {
	ImGui::MenuItem("User Guide");
	ImGui::MenuItem("Program Info");
}

} // namespace monster_calculator