#pragma once
#include <string>
#include <vector>

#include "imgui.h"	// for access to ImGui color type

#include "mcc_display_constants.h"
#include "mcc_display_structs.h"

#include "mcc_parameter_structs.h"
#include "mcc_parameter_constants.h"

namespace monster_calculator {

// enum parameter values
extern const std::vector<ParameterValue> kTypeValuesList = {
    ParameterValue("Normal",	"normal",	    kLinenColor,        0),
    ParameterValue("Fire",		"fire",		    kVermillionColor,   1),
    ParameterValue("Fighting",	"fighting",     kMahoganyColor,     2),
    ParameterValue("Water",		"water",	    kBlueColor,         3),
    ParameterValue("Flying",	"flying",	    kPeriwinkleColor,   4),
    ParameterValue("Grass",		"grass",	    kViridianColor,     5),
    ParameterValue("Poison",	"poison",	    kPurpleColor,       6),
    ParameterValue("Electric",	"electric",     kSaffronColor,      7),
    ParameterValue("Ground",	"ground",	    kBrassColor,        8),
    ParameterValue("Psychic",	"psychic",	    kFuschiaColor,      9),
    ParameterValue("Rock",		"rock",		    kBrownColor,        10),
    ParameterValue("Ice",		"ice",		    kSeashellColor,     11),
    ParameterValue("Bug",		"bug",		    kGreenColor,        12),
    ParameterValue("Dragon",	"dragon",	    kRubyRedColor,      13),
    ParameterValue("Ghost",		"ghost",	    kRaspberryColor,    14),
    ParameterValue("Dark",		"dark",		    kMidnightColor,     15),
    ParameterValue("Steel",		"steel",	    kPearlColor,        16),
    ParameterValue("Fairy",		"fairy",        kPinkColor,         17),
    ParameterValue("None",		"-",		    kCharcoalColor,     18)
};

extern const std::vector<ParameterValue> kBinaryValuesList = {
    ParameterValue("True",		"1",			kBlueColor,     0),
    ParameterValue("False",		"0",			kRedColor,      1)
};

extern const std::vector<ParameterValue> kColorValuesList = {
    ParameterValue("Red",		"red",		    kRedColor,      0),
    ParameterValue("Blue",		"blue",		    kBlueColor,     1),
    ParameterValue("Yellow",	"yellow",	    kYellowColor,   2),
    ParameterValue("Green",		"green",	    kGreenColor,    3),
    ParameterValue("Black",		"black",	    kBlackColor,    4),
    ParameterValue("Brown",		"brown",	    kBrownColor,    5),
    ParameterValue("Purple",	"purple",	    kPurpleColor,   6),
    ParameterValue("Gray",		"gray",		    kGrayColor,     7),
    ParameterValue("White",		"white",	    kWhiteColor,    8),
    ParameterValue("Pink",		"pink",		    kPinkColor,     9)
};

extern const std::vector<ParameterValue> kShapeValuesList = {
    ParameterValue("Ball",		"ball",		    kVermillionColor,   0),
    ParameterValue("Squiggle",	"squiggle",	    kOrchidColor,       1),
    ParameterValue("Fish",		"fish",		    kBlueColor,         2),
    ParameterValue("Arms",		"arms",		    kBrassColor,        3),
    ParameterValue("Blob",		"blob",		    kCeladonColor,      4),
    ParameterValue("Upright",	"upright",	    kLinenColor,        5),
    ParameterValue("Legs",		"legs",		    kGoldenrodColor,    6),
    ParameterValue("Quadruped",	"quadruped",    kMahoganyColor,     7),
    ParameterValue("Wings",		"wings",	    kPeriwinkleColor,   8),
    ParameterValue("Tentacles",	"tentacles",    kIndigoColor,       9),
    ParameterValue("Heads",		"heads",	    kFuschiaColor,      10),
    ParameterValue("Humanoid",	"humanoid",	    kPinkColor,         11),
    ParameterValue("Insect",	"bug-wings",    kGreenColor,        12),
    ParameterValue("Armor",		"armor",		kPurpleColor,       13)
};

extern const std::vector<ParameterValue> kEggGroupValuesList = {
    ParameterValue("Mineral",		"mineral",		    kBrassColor,        0),
    ParameterValue("Amorphous",		"indeterminate",	kRaspberryColor,    1),
    ParameterValue("Grass",		    "plant",		    kViridianColor,     2),
    ParameterValue("Water 3",		"water3",		    kBlueColor,         3),
    ParameterValue("Water 2",		"water2",		    kMidnightColor,     4),
    ParameterValue("Water 1",		"water1",		    kIndigoColor,       5),
    ParameterValue("Bug",		    "bug",		        kGreenColor,        6),
    ParameterValue("Dragon",		"dragon",		    kRubyRedColor,      7),
    ParameterValue("Flying",		"flying",		    kPeriwinkleColor,   8),
    ParameterValue("Field",		    "ground",		    kCeladonColor,      9),
    ParameterValue("Human-like",	"humanshape",		kLinenColor,        10),
    ParameterValue("Fairy",		    "fairy",		    kPinkColor,         11),
    ParameterValue("Monster",		"monster",		    kTangerineColor,    12),
    ParameterValue("Ditto",		    "ditto",		    kFuschiaColor,      13),
    ParameterValue("Undiscovered",	"no-eggs",		    kGrayColor,         14),
    ParameterValue("None",	        "-",		        kBlackColor,        15)
};

extern const std::vector<ParameterValue> kGenerationValuesList = {
    ParameterValue("Gen. I",      "generation-i",        kRedColor,           0),
    ParameterValue("Gen. II",     "generation-ii",       kSeashellColor,      1),
    ParameterValue("Gen. III",    "generation-iii",      kRubyRedColor,       2),
    ParameterValue("Gen. IV",     "generation-iv",       kPinkColor,          3),
    ParameterValue("Gen. V",      "generation-v",        kGrayColor,          4),
    ParameterValue("Gen. VI",     "generation-vi",       kVermillionColor,    5),
    ParameterValue("Gen. VII",    "generation-vii",      kPurpleColor,        6),
    ParameterValue("Gen. VIII",   "generation-viii",     kBrassColor,         7),
    ParameterValue("Gen. IX",     "generation-ix",       kIndigoColor,        8)
};

extern const std::vector<ParameterValue> kGrowthRateValuesList = {
    ParameterValue("Fluctuating",   "fast-then-very-slow",      kRedColor,        0),
    ParameterValue("Slow",          "slow",                     kGreenColor,      1),
    ParameterValue("Medium Slow",   "medium-slow",              kBlueColor,       2),
    ParameterValue("Medium Fast",   "medium",                   kPurpleColor,     3),
    ParameterValue("Fast",          "fast",                     kOrangeColor,     4),
    ParameterValue("Erratic",       "slow-then-very-fast",      kPinkColor,       5)
};

extern const std::vector<ParameterOperation> kTextEnumOperations = {
    ParameterOperation("Equals",		"= '{0}'",		    kGreenColor,
        {
            "Required value"
        }
    ),
    ParameterOperation("Not Equals" ,  "!= '{0}'",      kRedColor,
        {
            "Forbidden value"
        }
    )
};

extern const std::vector<ParameterOperation> kValueEnumOperations = {
    ParameterOperation("Equals",		"= {0}",		    kGreenColor,
        {
            "Required value"
        }
    ),
    ParameterOperation("Not Equals" ,  "!= {0}",      kRedColor,
        {
            "Forbidden value"
        }
    )
};

// enumerated parameters
const std::string kPrimaryDisplayName = "Primary Type";
const std::string kPrimaryDatabaseFormat = "primary_type {0}";
const std::string kPrimaryDisplayFormat = "Primary Type: {0}";
extern const EnumeratedParameterType kPrimaryTypeParam = EnumeratedParameterType(
    kPrimaryDisplayName,
    kPrimaryDisplayFormat,
    kPrimaryDatabaseFormat,
    kRedColor,
    kTextEnumOperations,
    kTypeValuesList
);

const std::string kSecondaryDisplayName = "Secondary Type";
const std::string kSecondaryDatabaseFormat = "secondary_type {0}";
const std::string kSecondaryDisplayFormat = "Secondary Type: {0}";
extern const EnumeratedParameterType kSecondaryTypeParam = EnumeratedParameterType(
    kSecondaryDisplayName,
    kSecondaryDisplayFormat,
    kSecondaryDatabaseFormat,
    kBlueColor,
    kTextEnumOperations,
    kTypeValuesList
);

const std::string kEitherTypeDisplayName = "Either Type";
const std::string kEitherTypeDatabaseFormat = "primary_type {0} OR secondary_type {0}";
const std::string kEitherTypeDisplayFormat = "Either Type: {0}";
extern const EnumeratedParameterType kEitherTypeParam = EnumeratedParameterType(
    kEitherTypeDisplayName,
    kEitherTypeDisplayFormat,
    kEitherTypeDatabaseFormat,
    kPurpleColor,
    kTextEnumOperations,
    kTypeValuesList
);

const std::string kDimorphicDisplayName = "Is Dimorphic";
const std::string kDimorphicDatabaseFormat = "dimorphic {0}";
const std::string kDimorphicDisplayFormat = "Dimorphic: {0}";
extern const EnumeratedParameterType kDimorphicParam = EnumeratedParameterType(
    kDimorphicDisplayName,
    kDimorphicDisplayFormat,
    kDimorphicDatabaseFormat,
    kMahoganyColor,
    kValueEnumOperations,
    kBinaryValuesList
);

const std::string kIsDefaultDisplayName = "Is Base Form";
const std::string kIsDefaultDatabaseFormat = "is_default {0}";
const std::string kIsDefaultDisplayFormat = "Base Form: {0}";
extern const EnumeratedParameterType kIsDefaultParam = EnumeratedParameterType(
    kIsDefaultDisplayName,
    kIsDefaultDisplayFormat,
    kIsDefaultDatabaseFormat,
    kOrangeColor,
    kValueEnumOperations,
    kBinaryValuesList
);

const std::string kCanSwitchDisplayName = "Form Switchable";
const std::string kCanSwitchDatabaseFormat = "form_switchable {0}";
const std::string kCanSwitchDisplayFormat = "Can Switch Form: {0}";
extern const EnumeratedParameterType kCanSwitchParam = EnumeratedParameterType(
    kCanSwitchDisplayName,
    kCanSwitchDisplayFormat,
    kCanSwitchDatabaseFormat,
    kVermillionColor,
    kValueEnumOperations,
    kBinaryValuesList
);

const std::string kBabyDisplayName = "Is A Baby";
const std::string kBabyDatabaseFormat = "is_baby {0}";
const std::string kBabyDisplayFormat = "Baby: {0}";
extern const EnumeratedParameterType kIsBabyParam = EnumeratedParameterType(
    kBabyDisplayName,
    kBabyDisplayFormat,
    kBabyDatabaseFormat,
    kPinkColor,
    kValueEnumOperations,
    kBinaryValuesList
);

const std::string kLegendDisplayName = "Is Legendary";
const std::string kLegendDatabaseFormat = "is_legendary {0}";
const std::string kLegendDisplayFormat = "Legendary: {0}";
extern const EnumeratedParameterType kIsLegendParam = EnumeratedParameterType(
    kLegendDisplayName,
    kLegendDisplayFormat,
    kLegendDatabaseFormat,
    kIndigoColor,
    kValueEnumOperations,
    kBinaryValuesList
);

const std::string kMythicDisplayName = "Is Mythical";
const std::string kMythicDatabaseFormat = "is_mythical {0}";
const std::string kMythicDisplayFormat = "Mythical: {0}";
extern const EnumeratedParameterType kIsMythicParam = EnumeratedParameterType(
    kMythicDisplayName,
    kMythicDisplayFormat,
    kMythicDatabaseFormat,
    kOrchidColor,
    kValueEnumOperations,
    kBinaryValuesList
);

const std::string kColorDisplayName = "Color";
const std::string kColorDatabaseFormat = "color {0}";
const std::string kColorDisplayFormat = "Color: {0}";
extern const EnumeratedParameterType kColorParam = EnumeratedParameterType(
    kColorDisplayName,
    kColorDisplayFormat,
    kColorDatabaseFormat,
    kCeladonColor,
    kTextEnumOperations,
    kColorValuesList
);

const std::string kShapeDisplayName = "Shape";
const std::string kShapeDatabaseFormat = "shape {0}";
const std::string kShapeDisplayFormat = "Shape: {0}";
extern const EnumeratedParameterType kShapeParam = EnumeratedParameterType(
    kShapeDisplayName,
    kShapeDisplayFormat,
    kShapeDatabaseFormat,
    kYellowColor,
    kTextEnumOperations,
    kShapeValuesList
);

const std::string kPrimaryEggDisplayName = "Primary Egg Group";
const std::string kPrimaryEggDatabaseFormat = "primary_egg_group {0}";
const std::string kPrimaryEggDisplayFormat = "Primary Egg Group: {0}";
extern const EnumeratedParameterType kPrimaryEggParam = EnumeratedParameterType(
    kPrimaryEggDisplayName,
    kPrimaryEggDisplayFormat,
    kPrimaryEggDatabaseFormat,
    kPeriwinkleColor,
    kTextEnumOperations,
    kEggGroupValuesList
);

const std::string kSecondaryEggDisplayName = "Secondary Egg Group";
const std::string kSecondaryEggDatabaseFormat = "secondary_egg_group {0}";
const std::string kSecondaryEggDisplayFormat = "Secondary Egg Group: {0}";
extern const EnumeratedParameterType kSecondaryEggParam = EnumeratedParameterType(
    kSecondaryEggDisplayName,
    kSecondaryEggDisplayFormat,
    kSecondaryEggDatabaseFormat,
    kLinenColor,
    kTextEnumOperations,
    kEggGroupValuesList
);

const std::string kGenerationDisplayName = "Generation";
const std::string kGenerationDatabaseFormat = "generation {0}";
const std::string kGenerationDisplayFormat = "Generation: {0}";
extern const EnumeratedParameterType kGenerationParam = EnumeratedParameterType(
    kGenerationDisplayName,
    kGenerationDisplayFormat,
    kGenerationDatabaseFormat,
    kSeashellColor,
    kTextEnumOperations,
    kGenerationValuesList
);

const std::string kGrowthRateDisplayName = "Growth Rate";
const std::string kGrowthRateDatabaseFormat = "growth_rate {0}";
const std::string kGrowthRateDisplayFormat = "Growth Rate: {0}";
extern const EnumeratedParameterType kGrowthRateParam = EnumeratedParameterType(
    kGrowthRateDisplayName,
    kGrowthRateDisplayFormat,
    kGrowthRateDatabaseFormat,
    kBrownColor,
    kTextEnumOperations,
    kGrowthRateValuesList
);

// enumerated slider parameter values and operations
extern const std::vector<ParameterValue> kGenderRateValuesList = {
    ParameterValue("Gender Unknown",	    "-1",	kPearlColor,        0),
    ParameterValue("100%% Male",	        "0",	kPeriwinkleColor,   1),
    ParameterValue("87.5%% Male",	        "1",	kPeriwinkleColor,   2),
    ParameterValue("75%% Male ",	        "2",	kPeriwinkleColor,   3),
    ParameterValue("62.5%% Male Male",	    "3",	kPeriwinkleColor,   4),
    ParameterValue("50%% Male & Female",	"4",	kOrchidColor,       5),
    ParameterValue("62.5%% Female",	        "5",	kPinkColor,         6),
    ParameterValue("75%% Female",	        "6",	kPinkColor,         7),
    ParameterValue("87.5%% Female",	        "7",	kPinkColor,         8),
    ParameterValue("100%% Female",	        "8",	kPinkColor,         9)
};

extern const std::vector<ParameterOperation> kSliderEnumOperations = {
    ParameterOperation("Equals",        "= {0}",        kGreenColor,
        {
            "Target value"
        }
    )
};

// enumerated slider parameters
const std::string kGenderRateDisplayName = "Gender Rate";
const std::string kGenderRateDatabaseFormat = "gender_rate {0}";
const std::string kGenderRateDisplayFormat = "Gender Rate: {0}";
extern const SliderEnumeratedParameterType kGenderRateParam = SliderEnumeratedParameterType(
    kGenderRateDisplayName,
    kGenderRateDisplayFormat,
    kGenderRateDatabaseFormat,
    kSaffronColor,
    kSliderEnumOperations,
    kGenderRateValuesList
);

// open parameter values & operations
extern const std::vector<ParameterOperation> kNameOperations = {
    ParameterOperation("Equals",		"= '{0}'",		    kGreenColor,
        {
            "Name"
        }
    ),
    ParameterOperation("Starts With" ,  "LIKE '{0}%'",      kRedColor,
        {
            "Name Prefix"
        }
    ),
    ParameterOperation("Ends With" ,    "LIKE '%{0}'",      kBlueColor,
        {
            "Name Suffix"
        }
    ),
    ParameterOperation("Contains" ,     "LIKE '%{0}%'",     kPurpleColor,
        {
            "Name Component"
        }
    )
};

// open parameter values & operations
extern const std::vector<ParameterOperation> kAbilityOperations = {
    ParameterOperation("Equals",		"= '{0}'",		    kGreenColor,
        {
            "Ability"
        }
    ),
    ParameterOperation("Starts With" ,  "LIKE '{0}%'",      kRedColor,
        {
            "Ability Prefix"
        }
    ),
    ParameterOperation("Ends With" ,    "LIKE '%{0}'",      kBlueColor,
        {
            "Ability Suffix"
        }
    ),
    ParameterOperation("Contains" ,     "LIKE '%{0}%'",     kPurpleColor,
        {
            "Ability Component"
        }
    )
};

extern const std::vector<DisplayColor> kOpenParamColors = {
    kRedColor, kRubyRedColor,
    kBlueColor, kIndigoColor,
    kGreenColor, kCeladonColor,
    kYellowColor, kSaffronColor,
    kOrangeColor, kTangerineColor,
    kPurpleColor, kOrchidColor,
    kPinkColor, kRaspberryColor,
    kWhiteColor, kSeashellColor,
    kBrassColor
};

// open parameters
const std::string kNameDisplayName = "Name";
const std::string kNameDatabaseFormat = "name {0}";
const std::string kNameDisplayFormat = "Name: {0}";
extern const OpenParameterType kNameParam = OpenParameterType(
    kNameDisplayName,
    kNameDisplayFormat,
    kNameDatabaseFormat,
    kMauveColor,
    kNameOperations,
    kOpenParamColors
);

const std::string kNormalAbilitiesDisplayName = "Normal Abilities";
const std::string kNormalAbilitiesDatabaseFormat = "ability_1 {0} OR ability_2 {0}";
const std::string kNormalAbilitiesDisplayFormat = "Normal Abilities: {0}";
extern const OpenParameterType kNormalAbilitiesParam = OpenParameterType(
    kNormalAbilitiesDisplayName,
    kNormalAbilitiesDisplayFormat,
    kNormalAbilitiesDatabaseFormat,
    kSaffronColor,
    kAbilityOperations,
    kOpenParamColors
);

const std::string kNormalAbilityOneDisplayName = "First Normal Ability";
const std::string kNormalAbilityOneDatabaseFormat = "ability_1 {0}";
const std::string kNormalAbilityOneDisplayFormat = "First Normal Ability: {0}";
extern const OpenParameterType kNormalAbilityOneParam = OpenParameterType(
    kNormalAbilityOneDisplayName,
    kNormalAbilityOneDisplayFormat,
    kNormalAbilityOneDatabaseFormat,
    kRawstColor,
    kAbilityOperations,
    kOpenParamColors
);

const std::string kNormalAbilityTwoDisplayName = "Second Normal Ability";
const std::string kNormalAbilityTwoDatabaseFormat = "ability_2 {0}";
const std::string kNormalAbilityTwoDisplayFormat = "Second Normal Ability: {0}";
extern const OpenParameterType kNormalAbilityTwoParam = OpenParameterType(
    kNormalAbilityTwoDisplayName,
    kNormalAbilityTwoDisplayFormat,
    kNormalAbilityTwoDatabaseFormat,
    kPechaColor,
    kAbilityOperations,
    kOpenParamColors
);

const std::string kHiddenAbilityDisplayName = "Hidden Ability";
const std::string kHiddenAbilityDatabaseFormat = "hidden_ability {0}";
const std::string kHiddenAbilityDisplayFormat = "Hidden Ability: {0}";
extern const OpenParameterType kHiddenAbilityParam = OpenParameterType(
    kHiddenAbilityDisplayName,
    kHiddenAbilityDisplayFormat,
    kHiddenAbilityDatabaseFormat,
    kRubyRedColor,
    kAbilityOperations,
    kOpenParamColors
);

const std::string kAnyAbilityDisplayName = "Any Ability";
const std::string kAnyAbilityDatabaseFormat = "ability_1 {0} OR ability_2 {0} OR hidden_ability {0}";
const std::string kAnyAbilityDisplayFormat = "Any Ability: {0}";
extern const OpenParameterType kAnyAbilityParam = OpenParameterType(
    kAnyAbilityDisplayName,
    kAnyAbilityDisplayFormat,
    kAnyAbilityDatabaseFormat,
    kTangerineColor,
    kAbilityOperations,
    kOpenParamColors
);

// numerical parameter operations and values
const std::vector<std::string> kRangeOperands = {"Lower bound", "Upper bound"};
extern const std::vector<ParameterOperation> kStandardNumericalOperations = {
    ParameterOperation("Range",			"BETWEEN {0} AND {1}",	kPurpleColor, kRangeOperands),
    ParameterOperation("Equal",			"= {0}",		kGreenColor,
        {
            "Target value"
        }
    ),
    ParameterOperation("Less Than",		"< {0}",		kRedColor,
        {
            "Maximum value"
        }
    ),
    ParameterOperation("Greater Than",	"> {0}",		kBlueColor,
        {
            "Minimum value"
        }
    )
};

extern const std::vector<DisplayColor> kStandardStatColors = {
    kRedColor, kOrangeColor, kYellowColor, kGreenColor, kBlueColor, kPurpleColor
};
extern const std::vector<float> kLinearThresholds = {
    0.0f, 0.16f, 0.33f, 0.5f, 0.67f, 0.83f
};
extern const std::vector<float> kStandardStatThresholds = {
    0.0f, 0.15f, 0.3f, 0.5f, 0.7f, 0.9f
};

// slightly adjusted thresholds for weight and height due to uneven distribution of values
extern const std::vector<float> kWeightThresholds = {
    0.0f, 0.05f, 0.1f, 0.2f, 0.35f, 0.5f
};
extern const std::vector<float> kHeightThresholds = {
    0.0f, 0.1f, 0.2, 0.35f, 0.5f, 0.7f
};

// Integer parameters
const int kDexNumMin = 1;
const int kDexNumMax = 1025;

const std::string kDexNumDisplayName = "Dex Number";
const std::string kDexNumDatabaseFormat = "dex_number {0}";
const std::string kDexNumDisplayFormat = "Dex #: {0}";
extern const IntegerParameterType kDexNumParam = IntegerParameterType(
    kDexNumDisplayName,
    kDexNumDisplayFormat,
    kDexNumDatabaseFormat,
    kIndigoColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kDexNumMin,
    kDexNumMax,
    kLinearThresholds
);

const int kBaseExpMin = 1;
const int kBaseExpMax = 1024;

const std::string kBaseExpDisplayName = "Base Experience";
const std::string kBaseExpDatabaseFormat = "base_experience {0}";
const std::string kBaseExpDisplayFormat = "Base Experience: {0}";
extern const IntegerParameterType kBaseExpParam = IntegerParameterType(
    kBaseExpDisplayName,
    kBaseExpDisplayFormat,
    kBaseExpDatabaseFormat,
    kVermillionColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kBaseExpMin,
    kBaseExpMax,
    kStandardStatThresholds
);

const int kBaseHappyMin = 0;
const int kBaseHappyMax = 255;

const std::string kBaseHappyDisplayName = "Base Happiness";
const std::string kBaseHappyDatabaseFormat = "base_happiness {0}";
const std::string kBaseHappyDisplayFormat = "Base Happiness: {0}";
extern const IntegerParameterType kBaseHappyParam = IntegerParameterType(
    kBaseHappyDisplayName,
    kBaseHappyDisplayFormat,
    kBaseHappyDatabaseFormat,
    kSeashellColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kBaseHappyMin,
    kBaseHappyMax,
    kLinearThresholds
);

const int kCatchRateMin = 0;
const int kCatchRateMax = 255;


const std::string kCatchRateDisplayName = "Catch Rate";
const std::string kCatchRateDatabaseFormat = "catch_rate {0}";
const std::string kCatchRateDisplayFormat = "Catch Rate: {0}";
extern const IntegerParameterType kCatchRateParam = IntegerParameterType(
    kCatchRateDisplayName,
    kCatchRateDisplayFormat,
    kCatchRateDatabaseFormat,
    kMahoganyColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kCatchRateMin,
    kCatchRateMax,
    kLinearThresholds
);

const int kHatchCountMin = 1;
const int kHatchCountMax = 255;


const std::string kHatchCountDisplayName = "Hatch Cycles";
const std::string kHatchCountDatabaseFormat = "hatch_counter {0}";
const std::string kHatchCountDisplayFormat = "Hatch Cycles: {0}";
extern const IntegerParameterType kHatchCountParam = IntegerParameterType(
    kHatchCountDisplayName,
    kHatchCountDisplayFormat,
    kHatchCountDatabaseFormat,
    kPeriwinkleColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kHatchCountMin,
    kHatchCountMax,
    kLinearThresholds
);


const int kSingleStatMin = 0;
const int kSingleStatMax = 255;

const std::string kHealthDisplayName = "Health";
const std::string kHealthDatabaseFormat = "hp {0}";
const std::string kHealthDisplayFormat = "Health: {0}";
extern const IntegerParameterType kHealthParam = IntegerParameterType(
    kHealthDisplayName,
    kHealthDisplayFormat,
    kHealthDatabaseFormat,
    kRedColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kSingleStatMin,
    kSingleStatMax,
    kStandardStatThresholds
);

const std::string kAttackDisplayName = "Attack";
const std::string kAttackDatabaseFormat = "attack {0}";
const std::string kAttackDisplayFormat = "Attack: {0}";
extern const IntegerParameterType kAttackParam = IntegerParameterType(
    kAttackDisplayName,
    kAttackDisplayFormat,
    kAttackDatabaseFormat,
    kBlueColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kSingleStatMin,
    kSingleStatMax,
    kStandardStatThresholds
);

const std::string kDefenseDisplayName = "Defense";
const std::string kDefenseDatabaseFormat = "defense {0}";
const std::string kDefenseDisplayFormat = "Defense: {0}";
extern const IntegerParameterType kDefenseParam = IntegerParameterType(
    kDefenseDisplayName,
    kDefenseDisplayFormat,
    kDefenseDatabaseFormat,
    kGreenColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kSingleStatMin,
    kSingleStatMax,
    kStandardStatThresholds
);

const std::string kSpeAtkDisplayName = "Special Attack";
const std::string kSpeAtkDatabaseFormat = "special_attack {0}";
const std::string kSpeAtkDisplayFormat = "Special Attack: {0}";
extern const IntegerParameterType kSpeAtkParam = IntegerParameterType(
    kSpeAtkDisplayName,
    kSpeAtkDisplayFormat,
    kSpeAtkDatabaseFormat,
    kPurpleColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kSingleStatMin,
    kSingleStatMax,
    kStandardStatThresholds
);

const std::string kSpeDefDisplayName = "Special Defense";
const std::string kSpeDefDatabaseFormat = "special_defense {0}";
const std::string kSpeDefDisplayFormat = "Special Defense: {0}";
extern const IntegerParameterType kSpeDefParam = IntegerParameterType(
    kSpeDefDisplayName,
    kSpeDefDisplayFormat,
    kSpeDefDatabaseFormat,
    kPinkColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kSingleStatMin,
    kSingleStatMax,
    kStandardStatThresholds
);

const std::string kSpeedDisplayName = "Speed";
const std::string kSpeedDatabaseFormat = "speed {0}";
const std::string kSpeedDisplayFormat = "Speed: {0}";
extern const IntegerParameterType kSpeedParam = IntegerParameterType(
    kSpeedDisplayName,
    kSpeedDisplayFormat,
    kSpeedDatabaseFormat,
    kYellowColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kSingleStatMin,
    kSingleStatMax,
    kStandardStatThresholds
);

const int kStatTotalMin = 0;
const int kStatTotalMax = 1530;

const std::string kBaseStatTotalDisplayName = "Base Stat Total";
const std::string kBaseStatTotalDatabaseFormat = "stat_total {0}";
const std::string kBaseStatTotalDisplayFormat = "Base Stat Total: {0}";
extern const IntegerParameterType kStatTotalParam = IntegerParameterType(
    kBaseStatTotalDisplayName,
    kBaseStatTotalDisplayFormat,
    kBaseStatTotalDatabaseFormat,
    kFuschiaColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kStatTotalMin,
    kStatTotalMax,
    kStandardStatThresholds
);

// decimal parameters
const double kWeightMin = 0.0;
const double kWeightMax = 2000.0;
const std::string kWeightDisplayName = "Weight (kg)";
const std::string kWeightDatabaseFormat = "weight {0}";
const std::string kWeightDisplayFormat = "Weight: {0}";
extern const DecimalParameterType kWeightParam = DecimalParameterType(
    kWeightDisplayName,
    kWeightDisplayFormat,
    kWeightDatabaseFormat,
    kRaspberryColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kWeightMin,
    kWeightMax,
    kWeightThresholds
);

const double kHeightMin = 0.0;
const double kHeightMax = 2000.0;
const std::string kHeightDisplayName = "Height(m)";
const std::string kHeightDatabaseFormat = "height {0}";
const std::string kHeightDisplayFormat = "Height: {0}";
extern const DecimalParameterType kHeightParam = DecimalParameterType(
    kHeightDisplayName,
    kHeightDisplayFormat,
    kHeightDatabaseFormat,
    kGoldenrodColor,
    kStandardNumericalOperations,
    kStandardStatColors,
    kHeightMin,
    kHeightMax,
    kHeightThresholds
);

} //namespace monster_calculator