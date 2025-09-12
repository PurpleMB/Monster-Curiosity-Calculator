#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "mcc_app_dx11.h"

#include "mcc_window_management.h"
#include "mcc_gui_windows.h"
#include "mcc_menu_elements.h"

#include "mcc_parameter_structs.h"
#include "mcc_parameter_constants.h"
#include "mcc_value_structs.h"
#include "mcc_value_constants.h"
#include "mcc_subset_structs.h"
#include "mcc_subset_constants.h"
#include "mcc_database_constants.h"

#include "mcc_database_querying.h"

namespace monster_calculator {

// Extends App-provided boilerplate to handle drawing of 
// windows and GUI elements for MCC.
class MCCApp : public App {
public:
	MCCApp() = default;
	~MCCApp() = default;

	virtual void StartUp() final {
		// load images into textures
		{
			// load palceholder texture
			ID3D11ShaderResourceView* test_texture = nullptr;
			int ph_image_width = 0;
			int ph_image_height = 0;
			bool ph_ret = LoadTextureFromFile("./data/images/placeholder.png", &test_texture, &ph_image_width, &ph_image_height);
			IM_ASSERT(ph_ret);
			output_environment.AddTextureToMap("placeholder", test_texture);

			// load body 01
			ID3D11ShaderResourceView* body_01_texture = nullptr;
			int body_01_width = 0;
			int body_01_height = 0;
			bool body_01_ret = LoadTextureFromFile("./data/images/bodies/01_Ball.png", &body_01_texture, &body_01_width, &body_01_height);
			IM_ASSERT(body_01_ret);
			output_environment.AddTextureToMap("ball", body_01_texture);

			// load body 02
			ID3D11ShaderResourceView* body_02_texture = nullptr;
			int body_02_width = 0;
			int body_02_height = 0;
			bool body_02_ret = LoadTextureFromFile("./data/images/bodies/02_Squiggle.png", &body_02_texture, &body_02_width, &body_02_height);
			IM_ASSERT(body_02_ret);
			output_environment.AddTextureToMap("squiggle", body_02_texture);

			// load body 03
			ID3D11ShaderResourceView* body_03_texture = nullptr;
			int body_03_width = 0;
			int body_03_height = 0;
			bool body_03_ret = LoadTextureFromFile("./data/images/bodies/03_Fish.png", &body_03_texture, &body_03_width, &body_03_height);
			IM_ASSERT(body_03_ret);
			output_environment.AddTextureToMap("fish", body_03_texture);

			// load body 04
			ID3D11ShaderResourceView* body_04_texture = nullptr;
			int body_04_width = 0;
			int body_04_height = 0;
			bool body_04_ret = LoadTextureFromFile("./data/images/bodies/04_Arms.png", &body_04_texture, &body_04_width, &body_04_height);
			IM_ASSERT(body_04_ret);
			output_environment.AddTextureToMap("arms", body_04_texture);

			// load body 05
			ID3D11ShaderResourceView* body_05_texture = nullptr;
			int body_05_width = 0;
			int body_05_height = 0;
			bool body_05_ret = LoadTextureFromFile("./data/images/bodies/05_Blob.png", &body_05_texture, &body_05_width, &body_05_height);
			IM_ASSERT(body_05_ret);
			output_environment.AddTextureToMap("blob", body_05_texture);

			// load body 06
			ID3D11ShaderResourceView* body_06_texture = nullptr;
			int body_06_width = 0;
			int body_06_height = 0;
			bool body_06_ret = LoadTextureFromFile("./data/images/bodies/06_Upright.png", &body_06_texture, &body_06_width, &body_06_height);
			IM_ASSERT(body_06_ret);
			output_environment.AddTextureToMap("upright", body_06_texture);

			// load body 07
			ID3D11ShaderResourceView* body_07_texture = nullptr;
			int body_07_width = 0;
			int body_07_height = 0;
			bool body_07_ret = LoadTextureFromFile("./data/images/bodies/07_Legs.png", &body_07_texture, &body_07_width, &body_07_height);
			IM_ASSERT(body_07_ret);
			output_environment.AddTextureToMap("legs", body_07_texture);

			// load body 08
			ID3D11ShaderResourceView* body_08_texture = nullptr;
			int body_08_width = 0;
			int body_08_height = 0;
			bool body_08_ret = LoadTextureFromFile("./data/images/bodies/08_Quadruped.png", &body_08_texture, &body_08_width, &body_08_height);
			IM_ASSERT(body_08_ret);
			output_environment.AddTextureToMap("quadruped", body_08_texture);

			// load body 09
			ID3D11ShaderResourceView* body_09_texture = nullptr;
			int body_09_width = 0;
			int body_09_height = 0;
			bool body_09_ret = LoadTextureFromFile("./data/images/bodies/09_Wings.png", &body_09_texture, &body_09_width, &body_09_height);
			IM_ASSERT(body_09_ret);
			output_environment.AddTextureToMap("wings", body_09_texture);

			// load body 10
			ID3D11ShaderResourceView* body_10_texture = nullptr;
			int body_10_width = 0;
			int body_10_height = 0;
			bool body_10_ret = LoadTextureFromFile("./data/images/bodies/10_Tentacles.png", &body_10_texture, &body_10_width, &body_10_height);
			IM_ASSERT(body_10_ret);
			output_environment.AddTextureToMap("tentacles", body_10_texture);

			// load body 11
			ID3D11ShaderResourceView* body_11_texture = nullptr;
			int body_11_width = 0;
			int body_11_height = 0;
			bool body_11_ret = LoadTextureFromFile("./data/images/bodies/11_Heads.png", &body_11_texture, &body_11_width, &body_11_height);
			IM_ASSERT(body_11_ret);
			output_environment.AddTextureToMap("heads", body_11_texture);

			// load body 12
			ID3D11ShaderResourceView* body_12_texture = nullptr;
			int body_12_width = 0;
			int body_12_height = 0;
			bool body_12_ret = LoadTextureFromFile("./data/images/bodies/12_Humanoid.png", &body_12_texture, &body_12_width, &body_12_height);
			IM_ASSERT(body_12_ret);
			output_environment.AddTextureToMap("humanoid", body_12_texture);

			// load body 13
			ID3D11ShaderResourceView* body_13_texture = nullptr;
			int body_13_width = 0;
			int body_13_height = 0;
			bool body_13_ret = LoadTextureFromFile("./data/images/bodies/13_Insect.png", &body_13_texture, &body_13_width, &body_13_height);
			IM_ASSERT(body_13_ret);
			output_environment.AddTextureToMap("bug-wings", body_13_texture);

			// load body 14
			ID3D11ShaderResourceView* body_14_texture = nullptr;
			int body_14_width = 0;
			int body_14_height = 0;
			bool body_14_ret = LoadTextureFromFile("./data/images/bodies/14_Armor.png", &body_14_texture, &body_14_width, &body_14_height);
			IM_ASSERT(body_14_ret);
			output_environment.AddTextureToMap("armor", body_14_texture);
		}

		// create parameter groups
		std::vector<std::string> param_group_names = {
			"Cheri",
			"Chesto",
			"Pecha",
			"Rawst",
			"Aspear",
			"Lum"
		};
		std::vector<DisplayColor> param_group_colors = {
			kCheriColor,
			kChestoColor,
			kPechaColor,
			kRawstColor,
			kAspearColor,
			kLumColor
		};
		ParameterSet param_set = ParameterSet(
			6,
			false,
			param_group_names,
			param_group_colors
		);
		output_environment.subset_parameters = param_set;
		
		OpenDatabaseConnection(output_environment);
		GenerateTableSubset(output_environment, kMainTableName, kSubTableName);
		RetrieveTableEntries(output_environment, kSubTableName);
		output_environment.ConvertSubsetEntries(param_type_converter);
	}

	// Put any logic for the GUI that needs to be drawn every frame in here
	virtual void Update() final {
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window_) {
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::ShowDemoWindow(&show_demo_window_);
		}

		// menu window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Menu";
			float menu_width = ImGui::GetMainViewport()->WorkSize.x;
			window_params.window_size = ImVec2(menu_width, 0);
			window_params.window_position = ImVec2(0, 0);
			window_params.imgui_window_settings = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration;
			monster_calculator::BeginStyledWindow(window_params);

			monster_calculator::DrawMenuBarWindow(output_environment);

			monster_calculator::EndStyledWindow(window_params);
		}

		// possible menu sub-windows
		{
			ImVec2 subwindow_size = {300, 300};
			if (output_environment.show_settings) {
				monster_calculator::WindowParameters window_params;
				window_params.name = "Settings";
				window_params.window_size = subwindow_size;
				window_params.window_position = ImGui::GetCursorPos();
				window_params.imgui_window_settings = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
				monster_calculator::BeginDynamicWindow(window_params, &output_environment.show_settings);

				monster_calculator::DrawSettingsWindow(output_environment);

				monster_calculator::EndDynamicWindow(window_params);
			}
			if (output_environment.show_database_rebuild) {
				monster_calculator::WindowParameters window_params;
				window_params.name = "Program Log";
				window_params.window_size = subwindow_size;
				window_params.window_position = ImGui::GetCursorPos();
				window_params.imgui_window_settings = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
				monster_calculator::BeginDynamicWindow(window_params, &output_environment.show_database_rebuild);

				monster_calculator::DrawDatabaseRebuildWindow(output_environment);

				monster_calculator::EndDynamicWindow(window_params);
			}
			if (output_environment.show_program_log) {
				monster_calculator::WindowParameters window_params;
				window_params.name = "Program Log";
				window_params.window_size = subwindow_size;
				window_params.window_position = ImGui::GetCursorPos();
				window_params.imgui_window_settings = ImGuiWindowFlags_None;
				monster_calculator::BeginDynamicWindow(window_params, &output_environment.show_program_log);

				monster_calculator::DrawProgramLogWindow(output_environment);

				monster_calculator::EndDynamicWindow(window_params);
			}
			if (output_environment.show_user_guide) {

			}
			if (output_environment.show_program_info) {
				monster_calculator::WindowParameters window_params;
				window_params.name = "Program Info";
				window_params.window_size = {450, 0};
				window_params.window_position = ImGui::GetCursorPos();
				window_params.imgui_window_settings = ImGuiWindowFlags_NoResize;
				monster_calculator::BeginDynamicWindow(window_params, &output_environment.show_program_info);

				monster_calculator::DrawProgramInfoWindow(output_environment);

				monster_calculator::EndDynamicWindow(window_params);
			}
		}


		ImVec2 window_size = {550, 0};
		ImVec2 window_pos = {kWindowMargin, kWindowMargin + 50};

		// set restriction window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Dataset Refinement";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;
			monster_calculator::BeginStyledWindow(window_params);

			monster_calculator::DrawSetParameterWindow(output_environment, parameter_types, param_type_converter);

			monster_calculator::EndStyledWindow(window_params);
			window_pos.y += kWindowMargin + window_params.window_size.y;
		}

		// value definition window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Output Value Selection";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;
			monster_calculator::BeginStyledWindow(window_params);

			monster_calculator::DrawValueParameterWindow(output_environment, value_calc_types, param_type_converter);

			monster_calculator::EndStyledWindow(window_params);
			window_pos.x += kWindowMargin + window_params.window_size.x;
			window_pos.y = kWindowMargin + 50;
		}

		// set display window
		{
			monster_calculator::WindowParameters window_params;
			window_params.name = "Subset Display";
			window_params.window_size = window_size;
			window_params.window_position = window_pos;
			window_params.imgui_window_settings = kDefaultImGuiWindowSettings;
			monster_calculator::BeginStyledWindow(window_params);

			monster_calculator::DrawSetDisplayWindow(output_environment, subset_column_statuses);

			monster_calculator::EndStyledWindow(window_params);
			window_pos.y += kWindowMargin + window_params.window_size.y;
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
	std::shared_ptr<EnumeratedParameterType> either_egg_ptr = std::make_shared<EnumeratedParameterType>(kEitherEggParam);
	std::shared_ptr<EnumeratedParameterType> generation_ptr = std::make_shared<EnumeratedParameterType>(kGenerationParam);
	std::shared_ptr<EnumeratedParameterType> growth_rate_ptr = std::make_shared<EnumeratedParameterType>(kGrowthRateParam);
	std::shared_ptr<EnumeratedParameterType> gender_rate_ptr = std::make_shared<EnumeratedParameterType>(kGenderRateParam);
	std::shared_ptr<OpenParameterType> name_ptr = std::make_shared<OpenParameterType>(kNameParam);
	std::shared_ptr<OpenParameterType> normal_abilities_ptr = std::make_shared<OpenParameterType>(kNormalAbilitiesParam);
	std::shared_ptr<OpenParameterType> normal_ability_one_ptr = std::make_shared<OpenParameterType>(kNormalAbilityOneParam);
	std::shared_ptr<OpenParameterType> normal_ability_two_ptr = std::make_shared<OpenParameterType>(kNormalAbilityTwoParam);
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
		either_egg_ptr,
		generation_ptr,
		growth_rate_ptr,
		gender_rate_ptr,
		name_ptr,
		normal_abilities_ptr,
		normal_ability_one_ptr,
		normal_ability_two_ptr,
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
		{"pretty_ability_1", normal_ability_one_ptr},
		{"pretty_ability_2", normal_ability_two_ptr},
		{"pretty_hidden_ability", hidden_ability_ptr},
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

	std::shared_ptr<ValueOperation> avg_value_ptr = std::make_shared<ValueOperation>(kAvgCalcOperation);
	std::shared_ptr<ValueOperation> min_value_ptr = std::make_shared<ValueOperation>(kMinCalcOperation);
	std::shared_ptr<ValueOperation> max_value_ptr = std::make_shared<ValueOperation>(kMaxCalcOperation);
	std::shared_ptr<ValueOperation> sum_value_ptr = std::make_shared<ValueOperation>(kSumCalcOperation);
	std::shared_ptr<ValueOperation> median_value_ptr = std::make_shared<ValueOperation>(kMedianCalcOperation);
	std::shared_ptr<ValueOperation> mode_value_ptr = std::make_shared<ValueOperation>(kModeCalcOperation);
	std::shared_ptr<ValueOperation> random_value_ptr = std::make_shared<ValueOperation>(kRandomEntryCalcOperation);

	std::vector<std::shared_ptr<ValueOperation>> value_calc_types = {
		avg_value_ptr,
		min_value_ptr,
		max_value_ptr,
		sum_value_ptr,
		median_value_ptr,
		mode_value_ptr,
		random_value_ptr
	};
	
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
 