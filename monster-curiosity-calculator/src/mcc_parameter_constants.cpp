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

// enumerated parameters
const std::string kPrimaryDisplayName = "Primary Type";
const std::string kPrimaryDatabaseFormat = "primary_type {0}";
const std::string kPrimaryDisplayFormat = "Primary Type: {0}";
extern const EnumeratedParameterType kPrimaryTypeParam = EnumeratedParameterType(
	kPrimaryDisplayName,
	kPrimaryDisplayFormat,
	kPrimaryDatabaseFormat,
	kTypeValuesList
);

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations = {
	ParameterValue("Range",		"BETWEEN",	ImVec4(0, 0, 0, 0)),
	ParameterValue("Equal",		"=",		ImVec4(0, 0, 0, 0))
};

const int kByteMin = 0;
const int kByteMax = 255;

// numerical parameters
const std::string kHealthDisplayName = "Health";
const std::string kHealthDatabaseFormat = "hp {0}";
const std::string kHealthDisplayFormat = "Health {0}";
extern const NumericalParameterType kHealthParam = NumericalParameterType(
	kHealthDisplayName,
	kHealthDisplayFormat,
	kHealthDatabaseFormat,
	kStandardNumericalOperations,
	kByteMin,
	kByteMax
);

} //namespace monster_calculator