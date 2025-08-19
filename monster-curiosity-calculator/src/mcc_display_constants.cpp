#pragma once

#include "mcc_display_structs.h"
#include "mcc_structs.h"

#include "mcc_display_constants.h"

namespace monster_calculator {

// DisplayColor constants
const float kColorIntensity = 0.6f;
// Reds
extern const DisplayColor kRedColor = DisplayColor(
	"Red",
	ImVec4(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kVermillionColor = DisplayColor(
	"Vermillion",
	ImVec4(227.0f / 255.0f, 66.0f / 255.0f, 52.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kRubyRedColor = DisplayColor(
	"Ruby Red",
	ImVec4(224.0f / 255.0f, 17.0f / 255.0f, 95.0f / 255.0f, kColorIntensity)
);

// Blues
extern const DisplayColor kBlueColor = DisplayColor(
	"Blue",
	ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPeriwinkleColor = DisplayColor(
	"Periwinkle",
	ImVec4(204.0f / 255.0f, 204.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kIndigoColor = DisplayColor(
	"Indigo",
	ImVec4(63.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);


// Greens
extern const DisplayColor kGreenColor = DisplayColor(
	"Green",
	ImVec4(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kCeladonColor = DisplayColor(
	"Celadon",
	ImVec4(175.0f / 255.0f, 225.0f / 255.0f, 175.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kViridianColor = DisplayColor(
	"Viridian",
	ImVec4(64.0f / 255.0f, 130.0f / 255.0f, 109.0f / 255.0f, kColorIntensity)
);

// Yellows
extern const DisplayColor kYellowColor = DisplayColor(
	"Yellow",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kSaffronColor = DisplayColor(
	"Saffron",
	ImVec4(244.0f / 255.0f, 196.0f / 255.0f, 48.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kGoldenrodColor = DisplayColor(
	"Goldenrod",
	ImVec4(218.0f / 255.0f, 165.0f / 255.0f, 32.0f / 255.0f, kColorIntensity)
);

// Oranges
extern const DisplayColor kOrangeColor = DisplayColor(
	"Orange",
	ImVec4(255.0f / 255.0f, 165.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPersimmonColor = DisplayColor(
	"Persimmon",
	ImVec4(236.0f / 255.0f, 88.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kTangerineColor = DisplayColor(
	"Tangerine",
	ImVec4(240.0f / 255.0f, 128.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Purples
extern const DisplayColor kPurpleColor = DisplayColor(
	"Purple",
	ImVec4(128.0f / 255.0f, 0.0f / 255.0f, 128.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kMauveColor = DisplayColor(
	"Mauve",
	ImVec4(224.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kOrchidColor = DisplayColor(
	"Orchid",
	ImVec4(218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f, kColorIntensity)
);

// Pinks
extern const DisplayColor kPinkColor = DisplayColor(
	"Pink",
	ImVec4(255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kRaspberryColor = DisplayColor(
	"Raspberry",
	ImVec4(227.0f / 255.0f, 11.0f / 255.0f, 92.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kFuschiaColor = DisplayColor(
	"Fuschia",
	ImVec4(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);

// Whites
extern const DisplayColor kWhiteColor = DisplayColor(
	"White",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kSeashellColor = DisplayColor(
	"Seashell",
	ImVec4(255.0f / 255.0f, 245.0f / 255.0f, 238.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kLinenColor = DisplayColor(
	"Linen",
	ImVec4(233.0f / 255.0f, 220.0f / 255.0f, 240.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPearlColor = DisplayColor(
	"Pearl",
	ImVec4(226.0f / 255.0f, 223.0f / 255.0f, 210.0f / 255.0f, kColorIntensity)
);

// Grays
extern const DisplayColor kGrayColor = DisplayColor(
	"Gray",
	ImVec4(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, kColorIntensity)
);

// Blacks
extern const DisplayColor kBlackColor = DisplayColor(
	"Black",
	ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kCharcoalColor = DisplayColor(
	"Charcoal",
	ImVec4(54.0f / 255.0f, 69.0f / 255.0f, 79.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kMidnightColor = DisplayColor(
	"Midnight",
	ImVec4(25.0f / 255.0f, 25.0f / 255.0f, 112.0f / 255.0f, kColorIntensity)
);

// Browns
extern const DisplayColor kBrownColor = DisplayColor(
	"Brown",
	ImVec4(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kMahoganyColor = DisplayColor(
	"Mahogany",
	ImVec4(192.0f / 255.0f, 64.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kBrassColor = DisplayColor(
	"Brass",
	ImVec4(225.0f / 255.0f, 193.0f / 255.0f, 110.0f / 255.0f, kColorIntensity)
);

// ColumnInfo constants
extern const ColumnInfo kResNumColInfo = ColumnInfo("Result #", "", false, ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_PreferSortDescending, NumberColumnId, 0);
extern const ColumnInfo kNameColInfo = ColumnInfo("Name", "pretty_name", false, ImGuiTableColumnFlags_WidthFixed, NameColumnId, 90.0f);
extern const ColumnInfo kDexNumColInfo = ColumnInfo("Dex #", "dex_number", true, ImGuiTableColumnFlags_WidthFixed, DexColumnId, 0);
extern const ColumnInfo kColorColInfo = ColumnInfo("Color", "color", true, ImGuiTableColumnFlags_WidthFixed, ColorColumnId, 0);
extern const ColumnInfo kShapeColInfo = ColumnInfo("Shape", "shape", true, ImGuiTableColumnFlags_WidthFixed, ShapeColumnId, 0);
extern const ColumnInfo kHeightColInfo = ColumnInfo("Height (m)", "height", true, ImGuiTableColumnFlags_WidthFixed, HeightColumnId, 0);
extern const ColumnInfo kWeightColInfo = ColumnInfo("Weight (kg)", "weight", true, ImGuiTableColumnFlags_WidthFixed, WeightColumnId, 0);
extern const ColumnInfo kPrimTypeColInfo = ColumnInfo("Primary Type", "primary_type", true, ImGuiTableColumnFlags_WidthFixed, PrimaryTypeColumnId, 0);
extern const ColumnInfo kSecTypeColInfo = ColumnInfo("Secondary Type", "secondary_type", true, ImGuiTableColumnFlags_WidthFixed, SecondaryTypeColumnId, 0);

extern const ColumnInfo kGenerationColInfo = ColumnInfo("Generation", "generation", true, ImGuiTableColumnFlags_WidthFixed, GenerationColumnId, 0);
extern const ColumnInfo kFormSwitchColInfo = ColumnInfo("Form Switchable", "form_switchable", true, ImGuiTableColumnFlags_WidthFixed, FormSwitchColumnId, 0);
extern const ColumnInfo kGrowthRateColInfo = ColumnInfo("Growth Rate", "growth_rate", true, ImGuiTableColumnFlags_WidthFixed, GrowthRateColumnId, 0);
extern const ColumnInfo kBaseExpColInfo = ColumnInfo("Base Experience", "base_experience", true, ImGuiTableColumnFlags_WidthFixed, BaseExpColumnId, 0);
extern const ColumnInfo kBaseHappyColInfo = ColumnInfo("Base Happiness", "base_happiness", true, ImGuiTableColumnFlags_WidthFixed, BaseHappyColumnId, 0);
extern const ColumnInfo kCatchRateColInfo = ColumnInfo("Catch Rate", "catch_rate", true, ImGuiTableColumnFlags_WidthFixed, CatchRateColumnId, 0);
extern const ColumnInfo kDimorphicColInfo = ColumnInfo("Dimorphic", "dimorphic", true, ImGuiTableColumnFlags_WidthFixed, DimorphicColumnId, 0);
extern const ColumnInfo kPrimEggColInfo = ColumnInfo("Primary Egg Group", "primary_egg_group", true, ImGuiTableColumnFlags_WidthFixed, PrimEggColumnId, 0);
extern const ColumnInfo kSecEggColInfo = ColumnInfo("Secondary Egg Group", "secondary_egg_group", true, ImGuiTableColumnFlags_WidthFixed, SecEggColumnId, 0);
extern const ColumnInfo kIsDefaultColInfo = ColumnInfo("Base Form", "is_default", true, ImGuiTableColumnFlags_WidthFixed, IsDefaultColumnId, 0);
extern const ColumnInfo kIsBabyColInfo = ColumnInfo("Baby", "is_baby", true, ImGuiTableColumnFlags_WidthFixed, IsBabyColumnId, 0);
extern const ColumnInfo kIsLegendColInfo = ColumnInfo("Legendary", "is_legendary", true, ImGuiTableColumnFlags_WidthFixed, IsLegendColumnId, 0);
extern const ColumnInfo kIsMythColInfo = ColumnInfo("Mythical", "is_mythical", true, ImGuiTableColumnFlags_WidthFixed, IsMythColumnId, 0);
extern const ColumnInfo kAbilOneColInfo = ColumnInfo("Ability 1", "ability_1", true, ImGuiTableColumnFlags_WidthFixed, AbilOneColumnId, 0);
extern const ColumnInfo kAbilTwoColInfo = ColumnInfo("Ability 2", "ability_2", true, ImGuiTableColumnFlags_WidthFixed, AbilTwoColumnId, 0);
extern const ColumnInfo kAbilHiddenColInfo = ColumnInfo("Hidden Ability", "hidden_ability", true, ImGuiTableColumnFlags_WidthFixed, AbilHiddenColumnId, 0);
extern const ColumnInfo kHealthColInfo = ColumnInfo("Health", "hp", true, ImGuiTableColumnFlags_WidthFixed, HealthColumnId, 0);
extern const ColumnInfo kAttackColInfo = ColumnInfo("Attack", "attack", true, ImGuiTableColumnFlags_WidthFixed, AttackColumnId, 0);
extern const ColumnInfo kDefenseColInfo = ColumnInfo("Defense", "defense", true, ImGuiTableColumnFlags_WidthFixed, DefenseColumnId, 0);
extern const ColumnInfo kSpeAtkColInfo = ColumnInfo("Special Attack", "special_attack", true, ImGuiTableColumnFlags_WidthFixed, SpeAtkColumnId, 0);
extern const ColumnInfo kSpeDefColInfo = ColumnInfo("Special Defense", "special_defense", true, ImGuiTableColumnFlags_WidthFixed, SpeDefColumnId, 0);
extern const ColumnInfo kSpeedColInfo = ColumnInfo("Speed", "speed", true, ImGuiTableColumnFlags_WidthFixed, SpeedColumnId, 0);
extern const ColumnInfo kStatTotalColInfo = ColumnInfo("Stat Total", "stat_total", true, ImGuiTableColumnFlags_WidthFixed, StatTotalColumnId, 0);

} //  namespace monster_calculator