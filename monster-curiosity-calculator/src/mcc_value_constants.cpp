#pragma once
#include <vector>

#include "mcc_value_structs.h"
#include "mcc_value_constants.h"

namespace monster_calculator {

// value calculation arguments
const ValueOperationArgument kGenerationArg = ValueOperationArgument("Generation", "generation", kOrchidColor);
const ValueOperationArgument kFormSwitchArg = ValueOperationArgument("Form Switchable", "form_switchable", kLinenColor);
const ValueOperationArgument kColorArg = ValueOperationArgument("Color", "color", kPeriwinkleColor);
const ValueOperationArgument kShapeArg = ValueOperationArgument("Shape", "shape", kGoldenrodColor);
const ValueOperationArgument kGrowthRateArg = ValueOperationArgument("Growth Rate", "growth_rate", kRubyRedColor);
const ValueOperationArgument kGenderRateArg = ValueOperationArgument("Gender Rate", "gender_rate", kViridianColor);
const ValueOperationArgument kDimorphicArg = ValueOperationArgument("Dimorphic", "dimorphic", kSeashellColor);
const ValueOperationArgument kPrimEggGroupArg = ValueOperationArgument("Primary Egg Group", "primary_egg_group", kBrownColor);
const ValueOperationArgument kSecEggGroupArg = ValueOperationArgument("Secondary Egg Group", "secondary_egg_group", kVermillionColor);
const ValueOperationArgument kIsBaseArg = ValueOperationArgument("Is Base Form", "is_default", kRedColor);
const ValueOperationArgument kIsBabyArg = ValueOperationArgument("Is Baby", "is_baby", kRedColor);
const ValueOperationArgument kIsLegendArg = ValueOperationArgument("Is Legendary", "is_legendary", kRedColor);
const ValueOperationArgument kIsMythArg = ValueOperationArgument("Is Mythical", "is_mythical", kRedColor);
const ValueOperationArgument kPrimTypeArg = ValueOperationArgument("Primary Type", "primary_type", kRedColor);
const ValueOperationArgument kSecTypeArg = ValueOperationArgument("Secondary Type", "secondary_type", kRedColor);
const ValueOperationArgument kAbilOneArg = ValueOperationArgument("First Normal Ability", "ability_1", kRedColor);
const ValueOperationArgument kAbilTwoArg = ValueOperationArgument("Second Normal Ability", "ability_2", kRedColor);
const ValueOperationArgument kAbilHiddenArg = ValueOperationArgument("Hidden Ability", "hidden_ability", kRedColor);


const ValueOperationArgument kHealthArg =       ValueOperationArgument("Health", "hp", kRedColor);
const ValueOperationArgument kAttackArg =       ValueOperationArgument("Attack", "attack", kGreenColor);
const ValueOperationArgument kDefenseArg =      ValueOperationArgument("Defense", "defense", kBlueColor);
const ValueOperationArgument kSpeAtkArg =       ValueOperationArgument("Special Attack", "special_attack", kOrangeColor);
const ValueOperationArgument kSpeDefArg =       ValueOperationArgument("Special Defense", "special_defense", kPurpleColor);
const ValueOperationArgument kSpeedArg =        ValueOperationArgument("Speed", "speed", kPinkColor);
const ValueOperationArgument kStatTotalArg =    ValueOperationArgument("Stat Total", "stat_total", kGrayColor);
const ValueOperationArgument kBaseExpArg =      ValueOperationArgument("Base Experience", "base_experience", kLinenColor);
const ValueOperationArgument kBaseHappyArg =    ValueOperationArgument("Base Happiness", "base_happiness", kRaspberryColor);
const ValueOperationArgument kCatchRateArg =    ValueOperationArgument("Catch Rate", "catch_rate", kBrassColor);
const ValueOperationArgument kHatchCountArg =   ValueOperationArgument("Hatch Cycles", "hatch_counter", kCeladonColor);
const ValueOperationArgument kHeightArg =       ValueOperationArgument("Height", "height", kSaffronColor);
const ValueOperationArgument kWeightArg =       ValueOperationArgument("Weight", "weight", kFuschiaColor);

// argument groups for use by ValueOperations
extern const std::vector<ValueOperationArgument> kNumericalCalcArguments = {
    kHealthArg,
    kAttackArg,
    kDefenseArg,
    kSpeAtkArg,
    kSpeDefArg,
    kSpeedArg,
    kStatTotalArg,
    kBaseExpArg,
    kBaseHappyArg,
    kCatchRateArg,
    kHatchCountArg,
    kHeightArg,
    kWeightArg
};

extern const std::vector<ValueOperationArgument> kCountableCalcArguments = {
    kGenerationArg,
    kFormSwitchArg,
    kColorArg,
    kShapeArg,
    kGrowthRateArg,
    kGenderRateArg,
    kDimorphicArg,
    kPrimEggGroupArg,
    kSecEggGroupArg,
    kIsBaseArg,
    kIsBabyArg,
    kIsLegendArg,
    kIsMythArg,
    kPrimTypeArg,
    kSecTypeArg,
    kAbilOneArg,
    kAbilTwoArg,
    kAbilHiddenArg,
    kHealthArg,
    kAttackArg,
    kDefenseArg,
    kSpeAtkArg,
    kSpeDefArg,
    kSpeedArg,
    kStatTotalArg,
    kBaseExpArg,
    kBaseHappyArg,
    kCatchRateArg,
    kHatchCountArg,
    kHeightArg,
    kWeightArg
};

const std::string kAvgCalcDisplayName = "Average";
const std::string kAvgCalcSelectFormat = "avg({0})";
const std::string kAvgCalcGroupFormat = "";
const std::string kAvgCalcOrderFormat = "";
const std::string kAvgCalcAliasFormat = "avg_{0}";
extern const ValueOperation kAvgCalcOperation = ValueOperation(
    kAvgCalcDisplayName,
    kAvgCalcSelectFormat,
    kAvgCalcGroupFormat,
    kAvgCalcOrderFormat,
    kAvgCalcAliasFormat,
    kRedColor,
    kNumericalCalcArguments
);

const std::string kMinCalcDisplayName = "Minimum";
const std::string kMinCalcSelectFormat = "min({0})";
const std::string kMinCalcGroupFormat = "";
const std::string kMinCalcOrderFormat = "";
const std::string kMinCalcAliasFormat = "min_{0}";
extern const ValueOperation kMinCalcOperation = ValueOperation(
    kMinCalcDisplayName,
    kMinCalcSelectFormat,
    kMinCalcGroupFormat,
    kMinCalcOrderFormat,
    kMinCalcAliasFormat,
    kGreenColor,
    kNumericalCalcArguments
);

const std::string kMaxCalcDisplayName = "Maximum";
const std::string kMaxCalcSelectFormat = "max({0})";
const std::string kMaxCalcGroupFormat = "";
const std::string kMaxCalcOrderFormat = "";
const std::string kMaxCalcAliasFormat = "max_{0}";
extern const ValueOperation kMaxCalcOperation = ValueOperation(
    kMaxCalcDisplayName,
    kMaxCalcSelectFormat,
    kMaxCalcGroupFormat,
    kMaxCalcOrderFormat,
    kMaxCalcAliasFormat,
    kBlueColor,
    kNumericalCalcArguments
);

const std::string kSumCalcDisplayName = "Sum";
const std::string kSumCalcSelectFormat = "sum({0})";
const std::string kSumCalcGroupFormat = "";
const std::string kSumCalcOrderFormat = "";
const std::string kSumCalcAliasFormat = "sum_{0}";
extern const ValueOperation kSumCalcOperation = ValueOperation(
    kSumCalcDisplayName,
    kSumCalcSelectFormat,
    kSumCalcGroupFormat,
    kSumCalcOrderFormat,
    kSumCalcAliasFormat,
    kYellowColor,
    kNumericalCalcArguments
);

const std::string kModeCalcDisplayName = "Mode";
const std::string kModeCalcSelectFormat = "{0}";
const std::string kModeCalcGroupFormat = "{0}";
const std::string kModeCalcOrderFormat = "COUNT({0}) DESC";
const std::string kModeCalcAliasFormat = "mode_{0}";
extern const ValueOperation kModeCalcOperation = ValueOperation(
    kModeCalcDisplayName,
    kModeCalcSelectFormat,
    kModeCalcGroupFormat,
    kModeCalcOrderFormat,
    kModeCalcAliasFormat,
    kPurpleColor,
    kCountableCalcArguments
);

} // namespace monster_calculator