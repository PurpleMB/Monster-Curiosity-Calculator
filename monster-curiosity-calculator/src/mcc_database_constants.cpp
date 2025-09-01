#pragma once
#include <string>
#include <vector>

#include "mcc_database_structs.h"

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
	"pretty_ability_1 TEXT NOT NULL,"
	"pretty_ability_2 TEXT NOT NULL,"
	"pretty_hidden_ability TEXT NOT NULL,"
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

extern const std::string kMainTableSchemaPruned = (
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
	"pretty_ability_1 TEXT NOT NULL,"
	"pretty_ability_2 TEXT NOT NULL,"
	"pretty_hidden_ability TEXT NOT NULL,"
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
	);

extern const std::vector<std::string> kMainTableColumnNameList = {
	"id",
	"name",
	"pretty_name",
	"dex_number",
	"generation",
	"form_switchable",
	"color",
	"shape",	
	"growth_rate",
	"base_experience",
	"base_happiness",
	"catch_rate",
	"hatch_counter",
	"gender_rate",
	"dimorphic",
	"primary_egg_group",
	"secondary_egg_group",
	"is_default",
	"is_baby",
	"is_legendary",
	"is_mythical",
	"height",
	"weight",
	"primary_type",
	"secondary_type",
	"ability_1",
	"ability_2",
	"hidden_ability",
	"pretty_ability_1",
	"pretty_ability_2",
	"pretty_hidden_ability",
	"hp",
	"attack",
	"defense",
	"special_attack",
	"special_defense",
	"speed",
	"stat_total",
	"poke_url",
	"species_url",
	"form_url"
};

extern const TableSchemaList kMainTableSchemaList = TableSchemaList({
	TableColumnSchema("id", "INTEGER", "PRIMARY KEY"),
	TableColumnSchema("name", "TEXT", "NOT NULL"),
	TableColumnSchema("pretty_name", "TEXT", "NOT NULL"),
	TableColumnSchema("dex_number", "INTEGER", "NOT NULL"),
	TableColumnSchema("generation", "TEXT", "NOT NULL"),
	TableColumnSchema("form_switchable", "INT", "NOT NULL"),
	TableColumnSchema("color", "TEXT", "NOT NULL"),
	TableColumnSchema("shape", "TEXT", "NOT NULL"),
	TableColumnSchema("growth_rate", "TEXT", "NOT NULL"),
	TableColumnSchema("base_experience", "INT", "NOT NULL"),
	TableColumnSchema("base_happiness", "INT", "NOT NULL"),
	TableColumnSchema("catch_rate", "INT", "NOT NULL"),
	TableColumnSchema("hatch_counter", "INT", "NOT NULL"),
	TableColumnSchema("gender_rate", "INT", "NOT NULL"),
	TableColumnSchema("dimorphic", "INT", "NOT NULL"),
	TableColumnSchema("primary_egg_group", "TEXT", "NOT NULL"),
	TableColumnSchema("secondary_egg_group", "TEXT", "NOT NULL"),
	TableColumnSchema("is_default", "INT", "NOT NULL"),
	TableColumnSchema("is_baby", "INT", "NOT NULL"),
	TableColumnSchema("is_legendary", "INT", "NOT NULL"),
	TableColumnSchema("is_mythical", "INT", "NOT NULL"),
	TableColumnSchema("height", "DOUBLE", "NOT NULL"),
	TableColumnSchema("weight", "DOUBLE", "NOT NULL"),
	TableColumnSchema("primary_type", "TEXT", "NOT NULL"),
	TableColumnSchema("secondary_type", "TEXT", "NOT NULL"),
	TableColumnSchema("ability_1", "TEXT", "NOT NULL"),
	TableColumnSchema("ability_2", "TEXT", "NOT NULL"),
	TableColumnSchema("hidden_ability", "TEXT", "NOT NULL"),
	TableColumnSchema("pretty_ability_1", "TEXT", "NOT NULL"),
	TableColumnSchema("pretty_ability_2", "TEXT", "NOT NULL"),
	TableColumnSchema("pretty_hidden_ability", "TEXT", "NOT NULL"),
	TableColumnSchema("hp", "INTEGER", "NOT NULL"),
	TableColumnSchema("attack", "INTEGER", "NOT NULL"),
	TableColumnSchema("defense", "INTEGER", "NOT NULL"),
	TableColumnSchema("special_attack", "INTEGER", "NOT NULL"),
	TableColumnSchema("special_defense", "INTEGER", "NOT NULL"),
	TableColumnSchema("speed", "INTEGER", "NOT NULL"),
	TableColumnSchema("stat_total", "INTEGER", "NOT NULL"),
	TableColumnSchema("poke_url", "TEXT", "NOT NULL"),
	TableColumnSchema("species_url", "TEXT", "NOT NULL"),
	TableColumnSchema("form_url", "TEXT", "NOT NULL")
});

} // namespace monster_calculator