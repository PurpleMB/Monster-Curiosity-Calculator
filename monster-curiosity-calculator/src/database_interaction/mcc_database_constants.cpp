#pragma once
#include <string>
#include <vector>

#include "mcc_database_structs.h"

#include "mcc_database_constants.h"

namespace purple_mb::monster_calculator {

extern const std::string kDatabaseFilePath = "./resources/databases/mccdata.db";
extern const std::string kMainTableName = "Monsters";
extern const std::string kSubTableName = "Submonsters";

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

} // namespace purple_mb::monster_calculator