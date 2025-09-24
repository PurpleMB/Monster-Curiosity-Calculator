#pragma once
#include <string>
#include <vector>

#include "mcc_display_constants.h"

#include "mcc_database_constants.h"
#include "mcc_database_querying.h"
#include "mcc_json_constants.h"
#include "mcc_json_processing.h"

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
	ImGui::MenuItem("Program Log", NULL, &output_environment.show_program_log);
}

void DrawMenuBarHelp(OutputEnvironment& output_environment) {
	ImGui::MenuItem("User Guide", NULL, &output_environment.show_user_guide);
	ImGui::MenuItem("Program Info", NULL, &output_environment.show_program_info);
}

// menu windows
void DrawSettingsWindow(OutputEnvironment& output_environment) {
	ImGui::Text("Table Color Intensity");
	const float f32_zero = 0.f;
	const float f32_one = 1.f;
	ImGui::SliderScalar("##color_intensity_slider", ImGuiDataType_Float, &output_environment.table_color_intensity, &f32_zero, &f32_one, "");
	int percentage = output_environment.table_color_intensity * 100;
	std::string percentage_text = std::to_string(percentage) + "%%";
	ImGui::SameLine();
	ImGui::Text(percentage_text.c_str());
}

// tools windows
void DrawDatabaseRebuildWindow(OutputEnvironment& output_environment) {
	std::string explanation = "In the event that any database files have been lost or corrupted, you may use this to rebuild the files";
	ImGui::Text(explanation.c_str());

	std::string warning = "This operation may take several minutes. If you are certain you want to rebuild the database, click the \"Rebuild Database\" button";
	ImGui::Text(warning.c_str());

	if (ImGui::Button("Rebuild Database")) {
		CreateTableFromSchema(output_environment, kMainTableName, kMainTableSchemaList);
		ClearTableContents(output_environment, kMainTableName);
		auto monster_data = CompileMonsterJsonData(kMonsterJsonDataPath);
		PopulateTableFromList(output_environment, kMainTableName, kMainTableSchemaList, monster_data);
	}
}

void DrawProgramLogWindow(OutputEnvironment& output_environment) {
	ImVec2 outer_size = ImGui::GetContentRegionAvail();
	const int kColumnCount = 5;
	const int kTableFlags = ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size)) {
		// prepare table header
		ImGui::TableSetupColumn("Entry #", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Timestamp", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Entry Type", ImGuiTableColumnFlags_WidthFixed);
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
			ImGui::Text(entry.GetEntryTimestamp().c_str());

			ImGui::TableSetColumnIndex(2);
			EntryType entry_type = entry.GetEntryType();
			switch (entry_type) {
				case Neutral:
					ImGui::Text("Neutral");
					break;
				case Success:
					ImGui::TextColored(kGreenColor.GetColorValues(), "Success");
					break;
				case Warning:
					ImGui::TextColored(kYellowColor.GetColorValues(), "Warning");
					break;
				case Error:
					ImGui::TextColored(kRedColor.GetColorValues(), "Error");
					break;
			}

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(entry.GetEntryCode().c_str());

			ImGui::TableSetColumnIndex(4);
			ImGui::TextWrapped(entry.GetEntryMessage().c_str());
		}
		ImGui::EndTable();
	}
}

// help windows
void DrawUserGuideWindow(OutputEnvironment& output_environment) {

}

void DrawProgramInfoWindow(OutputEnvironment& output_environment) {
	const std::string version_text = "Version 0.1";
	ImGui::Text(version_text.c_str());

	ImTextureID program_logo = output_environment.GetTextureFromMap("placeholder");
	float image_width = ImGui::GetWindowSize().x * .95f;
	ImVec2 image_size = {image_width, image_width};
	ImGui::Image(program_logo, image_size);

	ImGui::Text("Repository:");
	ImGui::SameLine();
	ImGui::SmallButton("TODO: OPEN REPOSITORY");

	ImGui::Separator();

	ImGui::TextWrapped("Monster Curiosity Calculator uses the following libraries and tools:");

	std::vector<std::string> source_texts = {
		"PokeAPI v2 - https://pokeapi.co/",
		"Bulbagarden Archives - https://archives.bulbagarden.net/",
		"DearImGui - https://github.com/ocornut/imgui",
		"JsonCpp - https://github.com/open-source-parsers/jsoncpp",
		"STB Image Library - https://github.com/nothings/stb",
		"SQLite - https://www.sqlite.org/",
		"Icon8 - https://icons8.com"
	};

	ImVec2 list_box_size = {ImGui::GetWindowSize().x * .95f, ImGui::GetTextLineHeightWithSpacing() * 6};
	if (ImGui::BeginListBox("##sources", list_box_size)) {
		for (int n = 0; n < source_texts.size(); n++) {
			std::string source = source_texts[n];
			ImGui::Text(source.c_str());
		}
		ImGui::EndListBox();
	}

}

} // namespace monster_calculator