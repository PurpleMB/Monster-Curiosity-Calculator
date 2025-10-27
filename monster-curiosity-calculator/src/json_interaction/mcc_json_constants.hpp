#pragma once
#include <string>
#include <unordered_map>

namespace purple_mb::monster_calculator::constants {

const std::string kMonsterJsonDataPath = "./resources/jsons/mccdata.json";	// path to json data RELATIVE TO exe location

// this map has keys that represent the data name in the JSON file, with values
// that represent the expected name of that data in the SQLite database
const std::unordered_map<std::string, std::string> kMonsterJsonNameMap = {
	// JSON name, Database name
	{"unique_id", "id"},
	{"name", "name"},
	{"pretty_name", "pretty_name"},
	{"dex_number", "dex_number"},
	{"primary_type", "primary_type"},
	{"secondary_type", "secondary_type"},
	{"generation", "generation"},
	{"form_switchable", "form_switchable"},
	{"color", "color"},
	{"shape", "shape"},
	{"growth_rate", "growth_rate"},
	{"base_experience", "base_experience"},
	{"base_happiness", "base_happiness"},
	{"catch_rate", "catch_rate"},
	{"hatch_counter", "hatch_counter"},
	{"gender_rate", "gender_rate"},
	{"dimorphic", "dimorphic"},
	{"primary_egg_group", "primary_egg_group"},
	{"secondary_egg_group", "secondary_egg_group"},
	{"is_default", "is_default"},
	{"is_baby", "is_baby"},
	{"is_legendary", "is_legendary"},
	{"is_mythical", "is_mythical"},
	{"height(m)", "height"},
	{"weight(kg)", "weight"},
	{"first_ability", "ability_1"},
	{"second_ability", "ability_2"},
	{"hidden_ability", "ability_hidden"},
	{"pretty_first_ability", "pretty_ability_1"},
	{"pretty_second_ability", "pretty_ability_2"},
	{"pretty_hidden_ability", "pretty_ability_hidden"},
	{"hp", "hp"},
	{"attack", "attack"},
	{"defense", "defense"},
	{"special-attack", "special_attack"},
	{"special-defense", "special_defense"},
	{"speed", "speed"},
	{"base_stat_total", "stat_total"},
	{"monster_url", "monster_url"},
	{"species_url", "species_url"},
	{"form_url", "form_url"}
};

} // namespace purple_mb::monster_calculator::constants