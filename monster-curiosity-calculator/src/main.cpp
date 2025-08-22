#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"

#include "mcc_gui_windows.h"

#include "mcc_parameter_structs.h"
#include "mcc_parameter_constants.h"
#include "mcc_subset_structs.h"
#include "mcc_subset_constants.h"

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
		output_environment.ConvertSubsetEntries(param_type_converter);
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

			monster_calculator::DrawSetParameterWindow(window_params, output_environment, parameter_types, param_type_converter);

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

	std::shared_ptr<EnumeratedParameterType> prim_type_ptr = std::make_shared<EnumeratedParameterType>(kPrimaryTypeParam);
	std::shared_ptr<EnumeratedParameterType> sec_type_ptr = std::make_shared<EnumeratedParameterType>(kSecondaryTypeParam);
	std::shared_ptr<EnumeratedParameterType> either_type_ptr = std::make_shared<EnumeratedParameterType>(kEitherTypeParam);
	std::shared_ptr<EnumeratedParameterType> dimorphic_ptr = std::make_shared<EnumeratedParameterType>(kDimorphicParam);
	std::shared_ptr<EnumeratedParameterType> is_default_ptr = std::make_shared<EnumeratedParameterType>(kIsDefaultParam);
	std::shared_ptr<EnumeratedParameterType> can_switch_ptr = std::make_shared<EnumeratedParameterType>(kCanSwitchParam);
	std::shared_ptr<EnumeratedParameterType> is_baby_ptr = std::make_shared<EnumeratedParameterType>(kIsBabyParam);
	std::shared_ptr<EnumeratedParameterType> is_legend_ptr = std::make_shared<EnumeratedParameterType>(kIsLegendParam);
	std::shared_ptr<EnumeratedParameterType> is_mythic_ptr = std::make_shared<EnumeratedParameterType>(kIsMythicParam);
	std::shared_ptr<EnumeratedParameterType> color_ptr = std::make_shared<EnumeratedParameterType>(kColorParam);
	std::shared_ptr<EnumeratedParameterType> shape_ptr = std::make_shared<EnumeratedParameterType>(kShapeParam);
	std::shared_ptr<EnumeratedParameterType> prim_egg_ptr = std::make_shared<EnumeratedParameterType>(kPrimaryEggParam);
	std::shared_ptr<EnumeratedParameterType> sec_egg_ptr = std::make_shared<EnumeratedParameterType>(kSecondaryEggParam);
	std::shared_ptr<EnumeratedParameterType> generation_ptr = std::make_shared<EnumeratedParameterType>(kGenerationParam);
	std::shared_ptr<EnumeratedParameterType> growth_rate_ptr = std::make_shared<EnumeratedParameterType>(kGrowthRateParam);
	std::shared_ptr<SliderEnumeratedParameterType> gender_rate_ptr = std::make_shared<SliderEnumeratedParameterType>(kGenderRateParam);
	std::shared_ptr<OpenParameterType> name_ptr = std::make_shared<OpenParameterType>(kNameParam);
	std::shared_ptr<OpenParameterType> ability_ptr = std::make_shared<OpenParameterType>(kAbilityParam);
	std::shared_ptr<OpenParameterType> hidden_ability_ptr = std::make_shared<OpenParameterType>(kHiddenAbilityParam);
	std::shared_ptr<OpenParameterType> any_ability_ptr = std::make_shared<OpenParameterType>(kAnyAbilityParam);
	std::shared_ptr<IntegerParameterType> dex_num_ptr = std::make_shared<IntegerParameterType>(kDexNumParam);
	std::shared_ptr<IntegerParameterType> base_exp_ptr = std::make_shared<IntegerParameterType>(kBaseExpParam);
	std::shared_ptr<IntegerParameterType> base_happy_ptr = std::make_shared<IntegerParameterType>(kBaseHappyParam);
	std::shared_ptr<IntegerParameterType> catch_rate_ptr = std::make_shared<IntegerParameterType>(kCatchRateParam);
	std::shared_ptr<IntegerParameterType> hatch_count_ptr = std::make_shared<IntegerParameterType>(kHatchCountParam);
	std::shared_ptr<IntegerParameterType> health_ptr = std::make_shared<IntegerParameterType>(kHealthParam);
	std::shared_ptr<IntegerParameterType> attack_ptr = std::make_shared<IntegerParameterType>(kAttackParam);
	std::shared_ptr<IntegerParameterType> defense_ptr = std::make_shared<IntegerParameterType>(kDefenseParam);
	std::shared_ptr<IntegerParameterType> special_attack_ptr = std::make_shared<IntegerParameterType>(kSpeAtkParam);
	std::shared_ptr<IntegerParameterType> special_defense_ptr = std::make_shared<IntegerParameterType>(kSpeDefParam);
	std::shared_ptr<IntegerParameterType> speed_ptr = std::make_shared<IntegerParameterType>(kSpeedParam);
	std::shared_ptr<IntegerParameterType> stat_total_ptr = std::make_shared<IntegerParameterType>(kStatTotalParam);
	std::shared_ptr<DecimalParameterType> height_ptr = std::make_shared<DecimalParameterType>(kHeightParam);
	std::shared_ptr<DecimalParameterType> weight_ptr = std::make_shared<DecimalParameterType>(kWeightParam);

	std::vector<std::shared_ptr<ParameterType>> parameter_types = {
		prim_type_ptr,
		sec_type_ptr,
		either_type_ptr,
		dimorphic_ptr,
		is_default_ptr,
		can_switch_ptr,
		is_baby_ptr,
		is_legend_ptr,
		is_mythic_ptr,
		color_ptr,
		shape_ptr,
		prim_egg_ptr,
		sec_egg_ptr,
		generation_ptr,
		growth_rate_ptr,
		gender_rate_ptr,
		name_ptr,
		ability_ptr,
		hidden_ability_ptr,
		any_ability_ptr,
		dex_num_ptr,
		base_exp_ptr,
		base_happy_ptr,
		catch_rate_ptr,
		hatch_count_ptr,
		health_ptr,
		attack_ptr,
		defense_ptr,
		special_attack_ptr,
		special_defense_ptr,
		speed_ptr,
		stat_total_ptr,
		height_ptr,
		weight_ptr
	};

	ParameterTypeConverter param_type_converter = ParameterTypeConverter({
		{"primary_type", prim_type_ptr},
		{"secondary_type", sec_type_ptr},
		{"dimorphic", dimorphic_ptr},
		{"is_default", is_default_ptr},
		{"form_switchable", can_switch_ptr},
		{"is_baby", is_baby_ptr},
		{"is_legendary", is_legend_ptr},
		{"is_mythical", is_mythic_ptr},
		{"color", color_ptr},
		{"shape", shape_ptr},
		{"primary_egg_group", prim_egg_ptr},
		{"secondary_egg_group", sec_egg_ptr},
		{"generation", generation_ptr},
		{"growth_rate", growth_rate_ptr},
		{"gender_rate", gender_rate_ptr},
		{"pretty_name", name_ptr},
		{"ability_1", ability_ptr},
		{"hidden_ability", hidden_ability_ptr},
		{"dex_number", dex_num_ptr},
		{"base_experience", base_exp_ptr},
		{"base_happiness", base_happy_ptr},
		{"catch_rate", catch_rate_ptr},
		{"hatch_counter", hatch_count_ptr},
		{"hp", health_ptr},
		{"attack", attack_ptr},
		{"defense", defense_ptr},
		{"special_attack", special_attack_ptr},
		{"special_defense", special_defense_ptr},
		{"speed", speed_ptr},
		{"stat_total", stat_total_ptr},
		{"height", height_ptr},
		{"weight", weight_ptr}
	});

	std::vector<ColumnStatus> subset_column_statuses = {
		ColumnStatus(kResNumColInfo, true),
		ColumnStatus(kNameColInfo, true),
		ColumnStatus(kDexNumColInfo, true),
		ColumnStatus(kColorColInfo, false),
		ColumnStatus(kShapeColInfo, false), 
		ColumnStatus(kHeightColInfo, false),
		ColumnStatus(kWeightColInfo, false),
		ColumnStatus(kPrimTypeColInfo, false),
		ColumnStatus(kSecTypeColInfo, false),
		ColumnStatus(kGenerationColInfo, false),
		ColumnStatus(kFormSwitchColInfo, false),
		ColumnStatus(kGrowthRateColInfo, false),
		ColumnStatus(kGenderRateColInfo, false),
		ColumnStatus(kBaseExpColInfo, false),
		ColumnStatus(kBaseHappyColInfo, false),
		ColumnStatus(kCatchRateColInfo, false),
		ColumnStatus(kDimorphicColInfo, false),
		ColumnStatus(kPrimEggColInfo, false),
		ColumnStatus(kSecEggColInfo, false),
		ColumnStatus(kIsDefaultColInfo, false),
		ColumnStatus(kIsBabyColInfo, false),
		ColumnStatus(kIsLegendColInfo, false),
		ColumnStatus(kIsMythColInfo, false),
		ColumnStatus(kAbilOneColInfo, false),
		ColumnStatus(kAbilTwoColInfo, false),
		ColumnStatus(kAbilHiddenColInfo, false),
		ColumnStatus(kHealthColInfo, false),
		ColumnStatus(kAttackColInfo, false),
		ColumnStatus(kDefenseColInfo, false),
		ColumnStatus(kSpeAtkColInfo, false),
		ColumnStatus(kSpeDefColInfo, false),
		ColumnStatus(kSpeedColInfo, false),
		ColumnStatus(kStatTotalColInfo, false)
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
 