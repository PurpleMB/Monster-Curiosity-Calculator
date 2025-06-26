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

const std::vector<std::pair<std::string, std::string>> kTypesList = {
	{"Any", "!= '-'"},
	{"None", "= '-'"},
	{"Normal", "= 'normal'"},
	{"Fire", "= 'fire'"},
	{"Fighting", "= 'fighting'"},
	{"Water", "= 'water'"},
	{"Flying", "= 'flying'"},
	{"Grass", "= 'grass'"},
	{"Poison", "= 'poison'"},
	{"Electric", " = 'electric'"},
	{"Ground", "= 'ground'"},
	{"Psychic", "= 'psychic'"},
	{"Rock", "= 'rock'"},
	{"Ice", "= 'ice'"},
	{"Bug", "= 'bug'"},
	{"Dragon", "= 'dragon'"},
	{"Ghost", "= 'ghost'"},
	{"Dark", "= 'dark'"},
	{"Steel", "= 'steel'"},
	{"Fairy", "= 'fairy'"}
};

const std::string kPrimaryDisplayName = "Primary Type";
const std::string kPrimaryQueryFormat = "primary_type {0}";
const ParameterType kPrimaryTypeParam(kPrimaryDisplayName, kPrimaryQueryFormat, Enumerated, kTypesList);

const std::string kSecondaryDisplayName = "Secondary Type";
const std::string kSecondaryQueryFormat = "secondary_type {0}";
const ParameterType kSecondaryTypeParam(kSecondaryDisplayName, kSecondaryQueryFormat, Enumerated, kTypesList);

const std::string kEitherDisplayName = "Either Type";
const std::string kEitherQueryFormat = "primary_type {0} OR secondary_type {0}";
const ParameterType kEitherTypeParam(kEitherDisplayName, kEitherQueryFormat, Enumerated, kTypesList);

const std::string kHealthDisplayName = "Health";
const std::string kHealthQueryFormat = "health {0} {1}";
const ParameterType kHealthParam(kHealthDisplayName, kEitherQueryFormat, Numerical, {{"0", "255"}});

} // namespace monster_calculator