#pragma once
#include <string>

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
	ImGui::Text("Table Color Intensity");
	static float temp = .5f;
	const float f32_zero = 0.f;
	const float f32_one = 1.f;
	ImGui::SliderScalar("##color_intensity_slider", ImGuiDataType_Float, &temp, &f32_zero, &f32_one, "");
	int percentage = temp * 100;
	std::string percentage_text = std::to_string(percentage) + "%%";
	ImGui::SameLine();
	ImGui::Text(percentage_text.c_str());
}

// tools windows
void DrawDatabaseRebuildWindow(OutputEnvironment& output_environment) {

}

void DrawProgramLogWindow(OutputEnvironment& output_environment) {
	ImVec2 outer_size = ImVec2(0.0f, 300.0f);
	const int kColumnCount = 4;
	const int kTableFlags = ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size)) {
		// prepare table header
		ImGui::TableSetupColumn("Entry #", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Timestamp", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Event Code", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Message", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupScrollFreeze(frozen_columns, frozen_rows);

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		for (int column = 0; column < kColumnCount; column++) {
			ImGui::TableSetColumnIndex(column);
			const char* column_name = ImGui::TableGetColumnName(column);
			ImGui::TableHeader(column_name);
		}



		// print log entries
		for (int i = 0; i < output_environment.log_entries.size(); i++) {
			LogEntry entry = output_environment.log_entries[i];

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			int displayed_index = i + 1;
			ImGui::Text(std::to_string(displayed_index).c_str());

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(entry.timestamp.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text(entry.message_code.c_str());

			ImGui::TableSetColumnIndex(3);
			ImGui::TextWrapped(entry.log_message.c_str());
		}
		ImGui::EndTable();
	}
}

// help windows
void DrawUserGuideWindow(OutputEnvironment& output_environment) {

}

void DrawProgramInfoWindow(OutputEnvironment& output_environment) {

}

} // namespace monster_calculator