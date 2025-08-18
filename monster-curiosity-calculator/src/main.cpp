#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"

#include "mcc_gui_windows.h"
#include "mcc_structs.h"

#include "mcc_parameter_structs.h"
#include "mcc_parameter_constants.h"

#include "mcc_display_structs.h"
#include "mcc_display_constants.h"

namespace monster_calculator {

// Extends App-provided boilerplate to handle drawing of 
// windows and GUI elements for MCC.
class MCCApp : public App {
public:
	MCCApp() = default;
	~MCCApp() = default;

	virtual void StartUp() final {
		std::vector<DisplayColor> param_group_colors = {
			kRedColor,
			kBlueColor,
			kGreenColor,
			kYellowColor,
			kOrangeColor,
			kPurpleColor,
			kPinkColor
		};
		ParameterSet param_set = ParameterSet(
			6,
			false,
			param_group_colors
		);
		output_environment.subset_parameters = param_set;

		CreateSubtable(output_environment);
		SortSubtableEntries(output_environment);
	}

	// Put any logic for the GUI that needs to be drawn every frame in here
	virtual void Update() final {
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window_) {
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::ShowDemoWindow(&show_demo_window_);
		}


		ImVec2 window_size = {550, 0};
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

			monster_calculator::DrawSetParameterWindow(window_params, output_environment, parameter_types);

			window_pos.y += kWindowMargin + window_params.window_size.y;
		}

		// value definition window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Output Value Selection";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;

			monster_calculator::DrawValueParameterWindow(window_params, output_environment);

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

			monster_calculator::DrawSetDisplayWindow(window_params, output_environment, subset_column_statuses);

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

	std::vector<std::shared_ptr<ParameterType>> parameter_types = {
		std::make_shared<EnumeratedParameterType>(kPrimaryTypeParam),
		std::make_shared<EnumeratedParameterType>(kSecondaryTypeParam),
		std::make_shared<EnumeratedParameterType>(kEitherTypeParam),
		std::make_shared<EnumeratedParameterType>(kDimorphicParam),
		std::make_shared<EnumeratedParameterType>(kIsDefaultParam),
		std::make_shared<EnumeratedParameterType>(kCanSwitchParam),
		std::make_shared<EnumeratedParameterType>(kIsBabyParam),
		std::make_shared<EnumeratedParameterType>(kIsLegendParam),
		std::make_shared<EnumeratedParameterType>(kIsMythicParam),
		std::make_shared<EnumeratedParameterType>(kColorParam),
		std::make_shared<EnumeratedParameterType>(kShapeParam),
		std::make_shared<EnumeratedParameterType>(kPrimaryEggParam),
		std::make_shared<EnumeratedParameterType>(kSecondaryEggParam),
		std::make_shared<EnumeratedParameterType>(kGenerationParam),
		std::make_shared<EnumeratedParameterType>(kGrowthRateParam),
		std::make_shared<SliderEnumeratedParameterType>(kGenderRateParam),
		std::make_shared<OpenParameterType>(kNameParam),
		std::make_shared<OpenParameterType>(kAbilityParam),
		std::make_shared<OpenParameterType>(kHiddenAbilityParam),
		std::make_shared<OpenParameterType>(kAnyAbilityParam),
		std::make_shared<IntegerParameterType>(kDexNumParam),
		std::make_shared<IntegerParameterType>(kBaseExpParam),
		std::make_shared<IntegerParameterType>(kBaseHappyParam),
		std::make_shared<IntegerParameterType>(kCatchRateParam),
		std::make_shared<IntegerParameterType>(kHatchCountParam),
		std::make_shared<IntegerParameterType>(kHealthParam),
		std::make_shared<IntegerParameterType>(kAttackParam),
		std::make_shared<IntegerParameterType>(kDefenseParam),
		std::make_shared<IntegerParameterType>(kSpeAtkParam),
		std::make_shared<IntegerParameterType>(kSpeDefParam),
		std::make_shared<IntegerParameterType>(kSpeedParam),
		std::make_shared<IntegerParameterType>(kStatTotalParam),
		std::make_shared<DecimalParameterType>(kWeightParam),
		std::make_shared<DecimalParameterType>(kHeightParam)
	};

	std::vector<ColumnStatus> subset_column_statuses = {
		ColumnStatus(ColumnInfo("Result #", "", false, ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_PreferSortDescending, NumberColumnId, 0), true),
		ColumnStatus(ColumnInfo("Name", "pretty_name", false, ImGuiTableColumnFlags_WidthFixed, NameColumnId, 90.0f), true),
		ColumnStatus(ColumnInfo("Dex #", "dex_number", true, ImGuiTableColumnFlags_WidthFixed, DexColumnId, 0), true),
		ColumnStatus(ColumnInfo("Color", "color", true, ImGuiTableColumnFlags_WidthFixed, ColorColumnId, 0), false),
		ColumnStatus(ColumnInfo("Shape", "shape", true, ImGuiTableColumnFlags_WidthFixed, ShapeColumnId, 0), false), 
		ColumnStatus(ColumnInfo("Height (m)", "height", true, ImGuiTableColumnFlags_WidthFixed, HeightColumnId, 0), false),
		ColumnStatus(ColumnInfo("Weight (kg)", "weight", true, ImGuiTableColumnFlags_WidthFixed, WeightColumnId, 0), false),
		ColumnStatus(ColumnInfo("Primary Type", "primary_type", true, ImGuiTableColumnFlags_WidthFixed, PrimaryTypeColumnId, 0), false),
		ColumnStatus(ColumnInfo("Secondary Type", "secondary_type", true, ImGuiTableColumnFlags_WidthFixed, SecondaryTypeColumnId, 0), false)
	};

	OutputEnvironment output_environment;
};

} // namespace monster_calculator

// Main code
int main(int, char**) {
	monster_calculator::MCCApp app;
	app.Run();

	return 0;
}
 