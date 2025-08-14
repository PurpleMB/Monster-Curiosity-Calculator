#pragma once
#include <string>
#include <vector>

#include "imgui.h"	// for access to ImGui color type

#include "mcc_display_constants.h"

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// enum parameter values
extern const std::vector<ParameterValue> kTypeValuesList = {
    ParameterValue("Any",		"!= '-'",		kWhiteColor),
    ParameterValue("None",		"= '-'",		kCharcoalColor),
    ParameterValue("Normal",	"= 'normal'",	kLinenColor),
    ParameterValue("Fire",		"= 'fire'",		kVermillionColor),
    ParameterValue("Fighting",	"= 'fighting'", kMahoganyColor),
    ParameterValue("Water",		"= 'water'",	kBlueColor),
    ParameterValue("Flying",	"= 'flying'",	kPeriwinkleColor),
    ParameterValue("Grass",		"= 'grass'",	kViridianColor),
    ParameterValue("Poison",	"= 'poison'",	kPurpleColor),
    ParameterValue("Electric",	"= 'electric'", kSaffronColor),
    ParameterValue("Ground",	"= 'ground'",	kBrassColor),
    ParameterValue("Psychic",	"= 'psychic'",	kFuschiaColor),
    ParameterValue("Rock",		"= 'rock'",		kBrownColor),
    ParameterValue("Ice",		"= 'ice'",		kSeashellColor),
    ParameterValue("Bug",		"= 'bug'",		kGreenColor),
    ParameterValue("Dragon",	"= 'dragon'",	kRubyRedColor),
    ParameterValue("Ghost",		"= 'ghost'",	kRaspberryColor),
    ParameterValue("Dark",		"= 'dark'",		kMidnightColor),
    ParameterValue("Steel",		"= 'steel'",	kPearlColor),
    ParameterValue("Fairy",		"= 'fairy'",    kPinkColor)
};

extern const std::vector<ParameterValue> kBinaryValuesList = {
    ParameterValue("True",		"= 1",			kBlueColor),
    ParameterValue("False",		"= 0",			kRedColor)
};

extern const std::vector<ParameterValue> kColorValuesList = {
    ParameterValue("Red",		"= 'red'",		kRedColor),
    ParameterValue("Blue",		"= 'blue'",		kBlueColor),
    ParameterValue("Yellow",	"= 'yellow'",	kYellowColor),
    ParameterValue("Green",		"= 'green'",	kGreenColor),
    ParameterValue("Black",		"= 'black'",	kBlackColor),
    ParameterValue("Brown",		"= 'brown'",	kBrownColor),
    ParameterValue("Purple",	"= 'purple'",	kPurpleColor),
    ParameterValue("Gray",		"= 'gray'",		kGrayColor),
    ParameterValue("White",		"= 'white'",	kWhiteColor),
    ParameterValue("Pink",		"= 'pink'",		kPinkColor)
};

extern const std::vector<ParameterValue> kShapeValuesList = {
    ParameterValue("Ball",		"= 'ball'",		    kVermillionColor),
    ParameterValue("Squiggle",	"= 'squiggle'",	    kOrchidColor),
    ParameterValue("Fish",		"= 'fish'",		    kBlueColor),
    ParameterValue("Arms",		"= 'arms'",		    kBrassColor),
    ParameterValue("Blob",		"= 'blob'",		    kCeladonColor),
    ParameterValue("Upright",	"= 'upright'",	    kLinenColor),
    ParameterValue("Legs",		"= 'legs'",		    kGoldenrodColor),
    ParameterValue("Quadruped",	"= 'quadruped'",    kMahoganyColor),
    ParameterValue("Wings",		"= 'wings'",	    kPeriwinkleColor),
    ParameterValue("Tentacles",	"= 'tentacles'",    kIndigoColor),
    ParameterValue("Heads",		"= 'heads'",	    kFuschiaColor),
    ParameterValue("Humanoid",	"= 'humanoid'",	    kPinkColor),
    ParameterValue("Insect",	"= 'bug-wings'",    kGreenColor),
    ParameterValue("Armor",		"= 'armor'",		kPurpleColor)
};

extern const std::vector<ParameterValue> kEggGroupValuesList = {
    ParameterValue("Mineral",		"= 'mineral'",		    kBrassColor),
    ParameterValue("Amorphous",		"= 'indeterminate'",	kRaspberryColor),
    ParameterValue("Grass",		    "= 'plant'",		    kViridianColor),
    ParameterValue("Water 3",		"= 'water3'",		    kBlueColor),
    ParameterValue("Water 2",		"= 'water2'",		    kMidnightColor),
    ParameterValue("Water 1",		"= 'water1'",		    kIndigoColor),
    ParameterValue("Bug",		    "= 'bug'",		        kGreenColor),
    ParameterValue("Dragon",		"= 'dragon'",		    kRubyRedColor),
    ParameterValue("Flying",		"= 'flying'",		    kPeriwinkleColor),
    ParameterValue("Field",		    "= 'ground'",		    kCeladonColor),
    ParameterValue("Human-like",	"= 'humanshape'",		kLinenColor),
    ParameterValue("Fairy",		    "= 'fairy'",		    kPinkColor),
    ParameterValue("Monster",		"= 'monster'",		    kTangerineColor),
    ParameterValue("Ditto",		    "= 'ditto'",		    kFuschiaColor),
    ParameterValue("Undiscovered",	"= 'no-eggs'",		    kGrayColor),
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
    kTypeValuesList
);

const std::string kIsDefaultDisplayName = "Is Base Form";
const std::string kIsDefaultDatabaseFormat = "is_default {0}";
const std::string kIsDefaultDisplayFormat = "Base Form: {0}";
extern const EnumeratedParameterType kIsDefaultParam = EnumeratedParameterType(
    kIsDefaultDisplayName,
    kIsDefaultDisplayFormat,
    kIsDefaultDatabaseFormat,
    kOrangeColor,
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
    kEggGroupValuesList
);

// open parameter values
extern const std::vector<ParameterOperation> kNameOperations = {
    ParameterOperation("Equals",		"= '{0}'",		    kGreenColor,
        {
            "Name"
        }
    ),
    
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
    ImGuiDataType_String,
    kNameOperations
);

// numerical parameter operations and values
const std::vector<std::string> kRangeOperands = {"Lower bound", "Upper bound"};
extern const std::vector<ParameterOperation> kStandardNumericalOperations = {
    ParameterOperation("Range",			"BETWEEN {0} AND {1}",	kPurpleColor, kRangeOperands ),
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
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kDexNumMin,
    kDexNumMax
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
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kCatchRateMin,
    kCatchRateMax
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
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
);

const std::string kAttackDisplayName = "Attack";
const std::string kAttackDatabaseFormat = "attack {0}";
const std::string kAttackDisplayFormat = "Attack: {0}";
extern const IntegerParameterType kAttackParam = IntegerParameterType(
    kAttackDisplayName,
    kAttackDisplayFormat,
    kAttackDatabaseFormat,
    kBlueColor,
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
);

const std::string kDefenseDisplayName = "Defense";
const std::string kDefenseDatabaseFormat = "defense {0}";
const std::string kDefenseDisplayFormat = "Defense: {0}";
extern const IntegerParameterType kDefenseParam = IntegerParameterType(
    kDefenseDisplayName,
    kDefenseDisplayFormat,
    kDefenseDatabaseFormat,
    kGreenColor,
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
);

const std::string kSpeAtkDisplayName = "Special Attack";
const std::string kSpeAtkDatabaseFormat = "special_attack {0}";
const std::string kSpeAtkDisplayFormat = "Special Attack: {0}";
extern const IntegerParameterType kSpeAtkParam = IntegerParameterType(
    kSpeAtkDisplayName,
    kSpeAtkDisplayFormat,
    kSpeAtkDatabaseFormat,
    kPurpleColor,
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
);

const std::string kSpeDefDisplayName = "Special Defense";
const std::string kSpeDefDatabaseFormat = "special_defense {0}";
const std::string kSpeDefDisplayFormat = "Special Defense: {0}";
extern const IntegerParameterType kSpeDefParam = IntegerParameterType(
    kSpeDefDisplayName,
    kSpeDefDisplayFormat,
    kSpeDefDatabaseFormat,
    kPinkColor,
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
);

const std::string kSpeedDisplayName = "Speed";
const std::string kSpeedDatabaseFormat = "speed {0}";
const std::string kSpeedDisplayFormat = "Speed: {0}";
extern const IntegerParameterType kSpeedParam = IntegerParameterType(
    kSpeedDisplayName,
    kSpeedDisplayFormat,
    kSpeedDatabaseFormat,
    kYellowColor,
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
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
    ImGuiDataType_U32,
    kStandardNumericalOperations,
    kStatTotalMin,
    kStatTotalMax
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
    ImGuiDataType_Double,
    kStandardNumericalOperations,
    kWeightMin,
    kWeightMax
);

} //namespace monster_calculator