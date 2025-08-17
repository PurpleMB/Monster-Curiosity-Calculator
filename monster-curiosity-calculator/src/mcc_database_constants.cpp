#pragma once
#include <string>

#include "mcc_database_constants.h"

namespace monster_calculator {

extern const std::string kMainTableSchema = (
	"CREATE TABLE IF NOT EXISTS monsters("
	"id INTEGER PRIMARY KEY,"
	"name TEXT NOT NULL,"
	"pretty_name TEXT NOT NULL,"
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
	"stat_total INTEGER NOT NULL,"
	"poke_url TEXT NOT NULL,"
	"species_url TEXT NOT NULL,"
	"form_url TEXT NOT NULL"
	");"
	);

} // namespace monster_calculator