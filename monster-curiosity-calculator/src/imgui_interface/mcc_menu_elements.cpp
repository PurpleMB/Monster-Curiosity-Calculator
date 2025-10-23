#pragma once
#include <string>
#include <vector>

#include "mcc_display_constants.h"

#include "database_interaction/mcc_database_constants.h"
#include "database_interaction/mcc_database_querying.h"

#include "json_interaction/mcc_json_processing.h"
#include "json_interaction/mcc_json_constants.h"


#include "mcc_window_management.h"
#include "mcc_imgui_helpers.h"
#include "data_communication/mcc_communication_structs.h"

#include "mcc_menu_elements.h"

namespace purple_mb::monster_calculator {

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
	float window_width = ImGui::GetWindowWidth();

	float label_area_percent = 0.3f;
	float label_width = window_width * label_area_percent;

	float input_area_start = label_area_percent + 0.15f;;
	float input_start_x = window_width * input_area_start;
	float input_area_percent = 0.4f;
	float input_width = window_width * input_area_percent;

	float input_label_start = (input_area_start + input_area_percent) + 0.025f;
	float input_label_start_x = window_width * input_label_start;

	ImGui::SetNextItemWidth(label_width);
	std::string color_label = "Table Color Intensity";
	ImGui::TextWrapped(color_label.c_str());

	ImGui::SameLine();
	ImGui::SetCursorPosX(input_start_x);
	ImGui::SetNextItemWidth(input_width);
	const float f32_zero = 0.f;
	const float f32_one = 1.f;
	ImGui::SliderScalar("##color_intensity_slider", ImGuiDataType_Float, &output_environment.table_color_intensity, &f32_zero, &f32_one, "");

	ImGui::SameLine();
	ImGui::SetCursorPosX(input_label_start_x);
	int percentage = output_environment.table_color_intensity * 100;
	std::string percentage_text = std::to_string(percentage) + "%%";
	ImGui::Text(percentage_text.c_str());
}

// tools windows
void DrawDatabaseRebuildWindow(OutputEnvironment& output_environment) {
	std::string explanation = "In the event that the database files have been lost or corrupted, this will attempt to reparse the program data to reform the database.";
	ImGui::TextWrapped(explanation.c_str());

	ImGui::NewLine();

	std::string warning = "This operation may take several moments to complete, during which time this program may appear to freeze. If you are certain you want to rebuild the database, click the \"Rebuild Database\" button.";
	ImGui::TextWrapped(warning.c_str());

	ImGui::Separator();

	// TODO: create a helper function class to make helpful things like this reusable
	std::string button_label = "Rebuild Database";
	ImGuiStyle& style = ImGui::GetStyle();
	float button_size = ImGui::CalcTextSize(button_label.c_str()).x + (style.FramePadding.x * 2.0f);
	float content_size = ImGui::GetContentRegionAvail().x;
	float offset = (content_size - button_size) * 0.5f;
	if (offset > 0.0f) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	}
	if (ImGui::Button("Rebuild Database")) {
		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::OpenPopup("Rebuilding Database");

		CreateTableFromSchema(output_environment, kMainTableName, kMainTableSchemaList);
		ClearTableContents(output_environment, kMainTableName);
		auto monster_data = CompileMonsterJsonData(kMonsterJsonDataPath);
		PopulateTableFromList(output_environment, kMainTableName, kMainTableSchemaList, monster_data);

		ImGui::CloseCurrentPopup();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::OpenPopup("Database Rebuilt");
	}

	// TODO: currently, this database never shows up because the rebuild halts the program until it is finished
	if (ImGui::BeginPopupModal("Rebuilding Database", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Please wait while the database is rebuilt.");
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Database Rebuilt", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("The program database has been successfully rebuilt.");

		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
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
	if (ImGui::CollapsingHeader("Overview", ImGuiTreeNodeFlags_None)) {

	}
	if (ImGui::CollapsingHeader("Dataset Refinement", ImGuiTreeNodeFlags_None)) {
		if (ImGui::TreeNode("Creating a subset parameter")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Using parameter groups")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Creating a data subset")) {
			ImGui::TreePop();
		}
	}
	if (ImGui::CollapsingHeader("Subset Value Calculation", ImGuiTreeNodeFlags_None)) {
		if (ImGui::TreeNode("Calculating subset values")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Locking & re-rolling subset values")) {
			ImGui::TreePop();
		}
	}
	if (ImGui::CollapsingHeader("Subset Display", ImGuiTreeNodeFlags_None)) {
		if (ImGui::TreeNode("Viewing subset entries")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Understanding the group size display")) {
			ImGui::TreePop();
		}
	}
	if (ImGui::CollapsingHeader("Troubleshooting", ImGuiTreeNodeFlags_None)) {
		if (ImGui::TreeNode("Accessing the program log")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("JSON file recovery")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Database file recovery")) {
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Reporting a bug")) {
			ImGui::TreePop();
		}
	}
}

void DrawProgramInfoWindow(OutputEnvironment& output_environment) {
	ImVec2 logo_size = ImVec2(250.0f, 250.0f);
	// TODO: create a helper function class to make helpful things like this reusable
	ImGuiStyle& style = ImGui::GetStyle();
	float content_size = ImGui::GetContentRegionAvail().x;
	float offset = (content_size - logo_size.x) * 0.5f;
	if (offset > 0.0f) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	}

	ImTextureID program_logo = output_environment.GetTextureFromMap("logo");
	ImGui::Image(program_logo, logo_size);

	ImGui::Separator();

	const std::string version_text = "Program Version: 0.1 WIP";
	ImGui::Text(version_text.c_str());

	ImGui::Text("Code Repository:");
	ImGui::SameLine();
	ImGui::TextLinkOpenURL("Click to open", "https://github.com/PurpleMB/MCC");

	ImGui::Separator();

	ImGui::TextWrapped("Monster Curiosity Calculator uses the following libraries and tools:");

	std::vector<std::pair<std::string, std::string>> source_pairs = {
		{"PokeAPI v2", "https://pokeapi.co/"},
		{"Bulbagarden Archives", "https://archives.bulbagarden.net/"},
		{"DearImGui", "https://github.com/ocornut/imgui"},
		{"JsonCpp",  "https://github.com/open-source-parsers/jsoncpp"},
		{"STB Image Library", "https://github.com/nothings/stb"},
		{"SQLite", "https://www.sqlite.org/"},
		{"Icon8", "https://icons8.com"}
	};
	static int selected_source_index = 0;

	float child_height = ImGui::GetTextLineHeightWithSpacing() * 8.5f;
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	if (ImGui::BeginChild("##sources", ImVec2(0.0f, child_height), ImGuiChildFlags_FrameStyle, ImGuiWindowFlags_HorizontalScrollbar)) {
		for (int n = 0; n < source_pairs.size(); n++) {
			std::string source = source_pairs[n].first;
			std::string link = source_pairs[n].second;
			std::string citation = source + " - " + link;

			const bool is_selected = (selected_source_index == n);
			if (ImGui::Selectable(citation.c_str(), is_selected)) {
				selected_source_index = n;
			}

			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndChild();
	}

	if (ImGui::Button("Copy selected link to clipboard")) {
		ImGui::LogToClipboard();
		ImGui::LogText(source_pairs[selected_source_index].second.c_str());
		ImGui::LogFinish();
		ImGui::OpenPopup("Copied to clipboard");
	}

	// Always center this window when appearing
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("Copied to clipboard", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		std::string success_msg = "Successfully copied source link for "
			+ source_pairs[selected_source_index].first + " to clipboard";
		ImGui::Text(success_msg.c_str());

		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void DrawLicenseDisclaimerWindow(OutputEnvironment& output_environment) {
	std::string license_label = "Software License";
	float license_label_width = ImGui::CalcTextSize(license_label.c_str()).x;
	CenterNextElem(license_label_width);
	ImGui::Text(license_label.c_str());

	ImGui::NewLine();
	std::string license_content = "The SQLite, STB Image Library, and JsonCPP libraries are used under Public Domain within the project. In areas that do not recognize Public Domain, they are used uder the MIT license.\n\n"
		"DearImGui is used under the MIT license. The full text of the MIT license may be found at the link below.\n\n"
		"Images from Bulbagarden are used under the Creative Commons Attribution-NonCommercial-ShareAlike 2.5 Generic license, which is also linked below.\n\n"
		"For direct links to all tools and sources for this application, consult the Program Information window.";
	ImGui::TextWrapped(license_content.c_str());

	ImGui::NewLine();
	ImGui::Text("MIT License:");
	ImGui::SameLine();
	ImGui::PushID("##link_mit_license");
	ImGui::TextLinkOpenURL("Click to open", "https://github.com/PurpleMB/MCC/blob/main/License.txt");
	ImGui::PopID();

	ImGui::Text("CC 2.5 License:");
	ImGui::SameLine();
	ImGui::PushID("##link_cc_license");
	ImGui::TextLinkOpenURL("Click to open", "https://creativecommons.org/licenses/by-nc-sa/2.5/");
	ImGui::PopID();

	ImGui::NewLine();
	ImGui::Separator();

	std::string disclaimer_label = "Copyright Notice";
	float disclaimer_label_width = ImGui::CalcTextSize(disclaimer_label.c_str()).x;
	CenterNextElem(disclaimer_label_width);
	ImGui::Text(disclaimer_label.c_str());

	ImGui::NewLine();

	std::string disclaimer_content = "Pokemon as a franchise and all associated characters and names are trademarks of Nintendo. Pokemon is the copyright property of Nintendo, Game Freak, and Creatures Inc.\n\n"
		"All information used by this application has been gathered from PokeAPI and Bulbapedia. PokeAPI is the copyright property of Paul Hallett and PokeAPI contributors.";
	ImGui::TextWrapped(disclaimer_content.c_str());
}

} // namespace purple_mb::monster_calculator