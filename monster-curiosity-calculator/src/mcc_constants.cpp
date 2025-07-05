#pragma once
#include "mcc_constants.h"

namespace monster_calculator {

const std::string kMainTableScheme = (
	"CREATE TABLE IF NOT EXISTS monsters("
	"id INTEGER PRIMARY KEY,"
	"name TEXT NOT NULL,"
	"dex_number INTEGER NOT NULL,"
	"generation TEXT NOT NULL,"
	"form_switchable INT NOT NULL,"
	"color TEXT NOT NULL,"
	"shape TEXT NOT NULL,"
	"growth_rate TEXT NOT NULL,"
	"base_experience INT NOT NULL,"
	"base_happiness INT NOT NULL,"
	"catch_rate INT NOT NULL,"
	"hatch_counter INT NOT NULL,"
	"gender_rate INT NOT NULL,"
	"dimorphic INT NOT NULL, "
	"primary_egg_group TEXT NOT NULL,"
	"secondary_egg_group TEXT NOT NULL,"
	"is_default INT NOT NULL,"
	"is_baby INT NOT NULL,"
	"is_legendary INT NOT NULL,"
	"is_mythical INT NOT NULL,"
	"height DOUBLE NOT NULL,"
	"weight DOUBLE NOT NULL,"
	"primary_type TEXT NOT NULL,"
	"secondary_type TEXT NOT NULL,"
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

const std::vector<std::pair<std::string, std::string>> kRegionsList = {
	{"Kanto", "BETWEEN 1 AND 151"},
	{"Johto", "BETWEEN 152 AND 251"},
	{"Hoenn", "BETWEEN 252 AND 386"},
	{"Sinnoh", "BETWEEN 387 AND 493"},
	{"Unova", "BETWEEN 494 AND 649"},
	{"Kalos", "BETWEEN 650 AND 721"},
	{"Alola", "BETWEEN 722 AND 809"},
	{"Galar", "BETWEEN 810 AND 905"},
	{"Paldea", "BETWEEN 906 AND 1025"},
	{"Any", "BETWEEN 0 AND 2500"},
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

const std::string kRegionDisplayName = "Home Region";
const std::string kRegionQueryFormat = "dex_number {0}";
const ParameterType kRegionParam(kRegionDisplayName, kRegionQueryFormat, Enumerated, kRegionsList);

const std::string kHealthDisplayName = "Health";
const std::string kHealthQueryFormat = "hp BETWEEN {0}";
const ParameterType kHealthParam(kHealthDisplayName, kHealthQueryFormat, Numerical, {{"0", "255"}});

} // namespace monster_calculator