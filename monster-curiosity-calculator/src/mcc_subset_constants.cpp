#pragma once

#include "mcc_subset_structs.h"
#include "mcc_subset_constants.h"

namespace monster_calculator {

// ColumnInfo constants
extern const ColumnInfo kResNumColInfo = ColumnInfo("Result #", "", false, false, ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_PreferSortDescending, NumberColumnId, 0);
extern const ColumnInfo kNameColInfo = ColumnInfo("Name", "pretty_name", false, false, ImGuiTableColumnFlags_WidthFixed, NameColumnId, 90.0f);
extern const ColumnInfo kDexNumColInfo = ColumnInfo("Dex #", "dex_number", true, false, ImGuiTableColumnFlags_WidthFixed, DexColumnId, 0);
extern const ColumnInfo kColorColInfo = ColumnInfo("Color", "color", true, true, ImGuiTableColumnFlags_WidthFixed, ColorColumnId, 0);
extern const ColumnInfo kShapeColInfo = ColumnInfo("Shape", "shape", true, true, ImGuiTableColumnFlags_WidthFixed, ShapeColumnId, 0);
extern const ColumnInfo kHeightColInfo = ColumnInfo("Height (m)", "height", true, false, ImGuiTableColumnFlags_WidthFixed, HeightColumnId, 0);
extern const ColumnInfo kWeightColInfo = ColumnInfo("Weight (kg)", "weight", true, false, ImGuiTableColumnFlags_WidthFixed, WeightColumnId, 0);
extern const ColumnInfo kPrimTypeColInfo = ColumnInfo("Primary Type", "primary_type", true, true, ImGuiTableColumnFlags_WidthFixed, PrimaryTypeColumnId, 0);
extern const ColumnInfo kSecTypeColInfo = ColumnInfo("Secondary Type", "secondary_type", true, true, ImGuiTableColumnFlags_WidthFixed, SecondaryTypeColumnId, 0);

extern const ColumnInfo kGenerationColInfo = ColumnInfo("Generation", "generation", true, true, ImGuiTableColumnFlags_WidthFixed, GenerationColumnId, 0);
extern const ColumnInfo kFormSwitchColInfo = ColumnInfo("Form Switchable", "form_switchable", true, true, ImGuiTableColumnFlags_WidthFixed, FormSwitchColumnId, 0);
extern const ColumnInfo kGrowthRateColInfo = ColumnInfo("Growth Rate", "growth_rate", true, true, ImGuiTableColumnFlags_WidthFixed, GrowthRateColumnId, 0);
extern const ColumnInfo kGenderRateColInfo = ColumnInfo("Gender Rate", "gender_rate", true, true, ImGuiTableColumnFlags_WidthFixed, GenderRateColumnId, 0);
extern const ColumnInfo kBaseExpColInfo = ColumnInfo("Base Experience", "base_experience", true, false, ImGuiTableColumnFlags_WidthFixed, BaseExpColumnId, 0);
extern const ColumnInfo kBaseHappyColInfo = ColumnInfo("Base Happiness", "base_happiness", true, false, ImGuiTableColumnFlags_WidthFixed, BaseHappyColumnId, 0);
extern const ColumnInfo kCatchRateColInfo = ColumnInfo("Catch Rate", "catch_rate", true, false, ImGuiTableColumnFlags_WidthFixed, CatchRateColumnId, 0);
extern const ColumnInfo kDimorphicColInfo = ColumnInfo("Dimorphic", "dimorphic", true, true, ImGuiTableColumnFlags_WidthFixed, DimorphicColumnId, 0);
extern const ColumnInfo kPrimEggColInfo = ColumnInfo("Primary Egg Group", "primary_egg_group", true, true, ImGuiTableColumnFlags_WidthFixed, PrimEggColumnId, 0);
extern const ColumnInfo kSecEggColInfo = ColumnInfo("Secondary Egg Group", "secondary_egg_group", true, true, ImGuiTableColumnFlags_WidthFixed, SecEggColumnId, 0);
extern const ColumnInfo kIsDefaultColInfo = ColumnInfo("Base Form", "is_default", true, true, ImGuiTableColumnFlags_WidthFixed, IsDefaultColumnId, 0);
extern const ColumnInfo kIsBabyColInfo = ColumnInfo("Baby", "is_baby", true, true, ImGuiTableColumnFlags_WidthFixed, IsBabyColumnId, 0);
extern const ColumnInfo kIsLegendColInfo = ColumnInfo("Legendary", "is_legendary", true, true, ImGuiTableColumnFlags_WidthFixed, IsLegendColumnId, 0);
extern const ColumnInfo kIsMythColInfo = ColumnInfo("Mythical", "is_mythical", true, true, ImGuiTableColumnFlags_WidthFixed, IsMythColumnId, 0);
extern const ColumnInfo kAbilOneColInfo = ColumnInfo("Ability 1", "ability_1", true, false, ImGuiTableColumnFlags_WidthFixed, AbilOneColumnId, 0);
extern const ColumnInfo kAbilTwoColInfo = ColumnInfo("Ability 2", "ability_2", true, false, ImGuiTableColumnFlags_WidthFixed, AbilTwoColumnId, 0);
extern const ColumnInfo kAbilHiddenColInfo = ColumnInfo("Hidden Ability", "hidden_ability", true, false, ImGuiTableColumnFlags_WidthFixed, AbilHiddenColumnId, 0);
extern const ColumnInfo kHealthColInfo = ColumnInfo("Health", "hp", true, false, ImGuiTableColumnFlags_WidthFixed, HealthColumnId, 0);
extern const ColumnInfo kAttackColInfo = ColumnInfo("Attack", "attack", true, false, ImGuiTableColumnFlags_WidthFixed, AttackColumnId, 0);
extern const ColumnInfo kDefenseColInfo = ColumnInfo("Defense", "defense", true, false, ImGuiTableColumnFlags_WidthFixed, DefenseColumnId, 0);
extern const ColumnInfo kSpeAtkColInfo = ColumnInfo("Special Attack", "special_attack", true, false, ImGuiTableColumnFlags_WidthFixed, SpeAtkColumnId, 0);
extern const ColumnInfo kSpeDefColInfo = ColumnInfo("Special Defense", "special_defense", true, false, ImGuiTableColumnFlags_WidthFixed, SpeDefColumnId, 0);
extern const ColumnInfo kSpeedColInfo = ColumnInfo("Speed", "speed", true, false, ImGuiTableColumnFlags_WidthFixed, SpeedColumnId, 0);
extern const ColumnInfo kStatTotalColInfo = ColumnInfo("Stat Total", "stat_total", true, false, ImGuiTableColumnFlags_WidthFixed, StatTotalColumnId, 0);

} // namespace monster_calculator