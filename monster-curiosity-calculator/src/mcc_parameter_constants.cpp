#pragma once
#include <string>

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// enum parameter values
extern const std::vector<ParameterValue> kTypeValuesList = {
    ParameterValue("Any",		"!= '-'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("None",		"= '-'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Normal",	"= 'normal'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Fire",		"= 'fire'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Fighting",	"= 'fighting'", ImVec4(0, 0, 0, 0)),
    ParameterValue("Water",		"= 'water'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Flying",	"= 'flying'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Grass",		"= 'grass'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Poison",	"= 'poison'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Electric",	"= 'electric'", ImVec4(0, 0, 0, 0)),
    ParameterValue("Ground",	"= 'ground'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Psychic",	"= 'psychic'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Rock",		"= 'rock'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Ice",		"= 'ice'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Bug",		"= 'bug'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Dragon",	"= 'dragon'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Ghost",		"= 'ghost'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Dark",		"= 'dark'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Steel",		"= 'steel'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Fairy",		"= 'fairy'",	ImVec4(0, 0, 0, 0))
};

extern const std::vector<ParameterValue> kBinaryValuesList = {
    ParameterValue("True",		"= 1",			ImVec4(0, 0, 0, 0)),
    ParameterValue("False",		"= 0",			ImVec4(0, 0, 0, 0))
};

extern const std::vector<ParameterValue> kColorValuesList = {
    ParameterValue("Red",		"= 'red'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Blue",		"= 'blue'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Yellow",	"= 'yellow'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Green",		"= 'green'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Black",		"= 'black'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Brown",		"= 'brown'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Purple",	"= 'purple'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Gray",		"= 'gray'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("White",		"= 'white'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Pink",		"= 'pink'",		ImVec4(0, 0, 0, 0))
};

extern const std::vector<ParameterValue> kShapeValuesList = {
    ParameterValue("Ball",		"= 'ball'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Squiggle",	"= 'squiggle'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Fish",		"= 'fish'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Arms",		"= 'arms'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Blob",		"= 'blob'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Upright",	"= 'upright'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Legs",		"= 'legs'",		ImVec4(0, 0, 0, 0)),
    ParameterValue("Quadruped",	"= 'quadruped'",ImVec4(0, 0, 0, 0)),
    ParameterValue("Wings",		"= 'wings'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Tentacles",	"= 'tentacles'",ImVec4(0, 0, 0, 0)),
    ParameterValue("Heads",		"= 'heads'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Humanoid",	"= 'humanoid'",	ImVec4(0, 0, 0, 0)),
    ParameterValue("Insect",	"= 'bug-wings'",ImVec4(0, 0, 0, 0)),
    ParameterValue("Armor",		"= 'armor'",		ImVec4(0, 0, 0, 0))
};

// enumerated parameters
const std::string kPrimaryDisplayName = "Primary Type";
const std::string kPrimaryDatabaseFormat = "primary_type {0}";
const std::string kPrimaryDisplayFormat = "Primary Type: {0}";
const ImVec4 kPrimaryParamColor = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
extern const EnumeratedParameterType kPrimaryTypeParam = EnumeratedParameterType(
    kPrimaryDisplayName,
    kPrimaryDisplayFormat,
    kPrimaryDatabaseFormat,
    kPrimaryParamColor,
    kTypeValuesList
);

const std::string kBabyDisplayName = "Is A Baby";
const std::string kBabyDatabaseFormat = "is_baby {0}";
const std::string kBabyDisplayFormat = "Baby: {0}";
const ImVec4 kBabyParamColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
extern const EnumeratedParameterType kIsBabyParam = EnumeratedParameterType(
    kBabyDisplayName,
    kBabyDisplayFormat,
    kBabyDatabaseFormat,
    kBabyParamColor,
    kBinaryValuesList
);

const std::string kColorDisplayName = "Color";
const std::string kColorDatabaseFormat = "color {0}";
const std::string kColorDisplayFormat = "Color: {0}";
const ImVec4 kColorParamColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
extern const EnumeratedParameterType kColorParam = EnumeratedParameterType(
    kColorDisplayName,
    kColorDisplayFormat,
    kColorDatabaseFormat,
    kColorParamColor,
    kColorValuesList
);

const std::string kShapeDisplayName = "Shape";
const std::string kShapeDatabaseFormat = "shape {0}";
const std::string kShapeDisplayFormat = "Shape: {0}";
const ImVec4 kShapeParamColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
extern const EnumeratedParameterType kShapeParam = EnumeratedParameterType(
    kShapeDisplayName,
    kShapeDisplayFormat,
    kShapeDatabaseFormat,
    kShapeParamColor,
    kShapeValuesList
);

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations = {
    ParameterValue("Range",			"BETWEEN",	ImVec4(1.0f, 0.0f, 0.0f, 0.6f)),
    ParameterValue("Equal",			"=",		ImVec4(0.0f, 1.0f, 0.0f, 0.6f)),
    ParameterValue("Less Than",		"<",		ImVec4(0.0f, 0.0f, 1.0f, 0.6f)),
    ParameterValue("Greater Than",	">",		ImVec4(1.0f, 1.0f, 0.0f, 0.6f))
};


const

// numerical parameters
const int kDexNumMin = 1;
const int kDexNumMax = 1025;

const std::string kDexNumDisplayName = "Dex Number";
const std::string kDexNumDatabaseFormat = "dex_number {0}";
const std::string kDexNumDisplayFormat = "Dex #: {0}";
const ImVec4 kDexNumParamColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
extern const NumericalParameterType kDexNumParam = NumericalParameterType(
    kDexNumDisplayName,
    kDexNumDisplayFormat,
    kDexNumDatabaseFormat,
    kDexNumParamColor,
    kStandardNumericalOperations,
    kDexNumMin,
    kDexNumMax
);

const int kCatchRateMin = 0;
const int kCatchRateMax = 255;


const std::string kCatchRateDisplayName = "Catch Rate";
const std::string kCatchRateDatabaseFormat = "catch_rate {0}";
const std::string kCatchRateDisplayFormat = "Catch Rate: {0}";
const ImVec4 kCatchRateParamColor = ImVec4(0.5f, 0.5f, 0.0f, 1.0f);
extern const NumericalParameterType kCatchRateParam = NumericalParameterType(
    kCatchRateDisplayName,
    kCatchRateDisplayFormat,
    kCatchRateDatabaseFormat,
    kCatchRateParamColor,
    kStandardNumericalOperations,
    kCatchRateMin,
    kCatchRateMax
);


const int kSingleStatMin = 0;
const int kSingleStatMax = 255;

const std::string kHealthDisplayName = "Health";
const std::string kHealthDatabaseFormat = "hp {0}";
const std::string kHealthDisplayFormat = "Health: {0}";
const ImVec4 kHealthParamColor = ImVec4(0.5f, 0.5f, 0.5f, 0.0f);
extern const NumericalParameterType kHealthParam = NumericalParameterType(
    kHealthDisplayName,
    kHealthDisplayFormat,
    kHealthDatabaseFormat,
    kHealthParamColor,
    kStandardNumericalOperations,
    kSingleStatMin,
    kSingleStatMax
);

const int kStatTotalMin = 0;
const int kStatTotalMax = 1530;

const std::string kBaseStatTotalDisplayName = "Base Stat Total";
const std::string kBaseStatTotalDatabaseFormat = "stat_total {0}";
const std::string kBaseStatTotalDisplayFormat = "Base Stat Total: {0}";
const ImVec4 kStatTotalParamColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
extern const NumericalParameterType kStatTotalParam = NumericalParameterType(
    kBaseStatTotalDisplayName,
    kBaseStatTotalDisplayFormat,
    kBaseStatTotalDatabaseFormat,
    kStatTotalParamColor,
    kStandardNumericalOperations,
    kStatTotalMin,
    kStatTotalMax
);

} //namespace monster_calculator