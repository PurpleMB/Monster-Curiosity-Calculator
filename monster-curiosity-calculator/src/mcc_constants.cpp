#pragma once
#include "mcc_constants.h"

namespace monster_calculator {

const std::string kMainTableScheme = (
	"CREATE TABLE IF NOT EXISTS monsters("
	"id INTEGER PRIMARY KEY,"
	"name TEXT NOT NULL,"
	"dex_number INTEGER NOT NULL,"
	"primary_type TEXT NOT NULL,"
	"secondary_type TEXT NOT NULL,"
	"height DOUBLE NOT NULL,"
	"weight DOUBLE NOT NULL,"
	"ability_1 TEXT NOT NULL,"
	"ability_2 TEXT NOT NULL,"
	"hidden_ability TEXT NOT NULL,"
	"hp INTEGER NOT NULL,"
	"attack INTEGER NOT NULL,"
	"defense INTEGER NOT NULL,"
	"special_attack INTEGER NOT NULL,"
	"special_defense INTEGER NOT NULL,"
	"speed INTEGER NOT NULL,"
	"stat_total INTEGER NOT NULL"
	");"
);

const std::vector<std::string> kTypesList = {
	"Any", // equivalent to "type = *"
	"None", // equivalent to "type = -"
	"Normal",
	"Fire",
	"Fighting",
	"Water",
	"Flying",
	"Grass",
	"Poison",
	"Electric",
	"Ground",
	"Psychic",
	"Rock",
	"Ice",
	"Bug",
	"Dragon",
	"Ghost",
	"Dark",
	"Steel",
	"Fairy"
};

const std::string kPrimaryDisplayName = "Primary Type";
const std::string kPrimaryQueryName = "primary_type";
const ParameterType kPrimaryTypeParam(kPrimaryDisplayName, kPrimaryQueryName, Enumerated, kTypesList);

const std::string kSecondaryDisplayName = "Secondary Type";
const std::string kSecondaryQueryName = "secondary_type";
const ParameterType kSecondaryTypeParam(kSecondaryDisplayName, kSecondaryQueryName, Enumerated, kTypesList);

// TODO: this needs to be restructured. currently identical to checking secondary = value
const std::string kEitherDisplayName = "Either Type";
const std::string kEitherQueryName = "primary_type OR secondary_type";
const ParameterType kEitherTypeParam(kEitherDisplayName, kEitherQueryName, Enumerated, kTypesList);

const std::string kHealthDisplayName = "Health";
const std::string kHealthQueryName = "health";
const ParameterType kHealthParam(kHealthDisplayName, kEitherQueryName, Numerical, {"0", "255"});

} // namespace monster_calculator