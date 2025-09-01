#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

#include <json/json.h>
#include <json/value.h>

#include "mcc_json_processing.h"

namespace monster_calculator {

std::vector<std::unordered_map<std::string, std::string>> CompileMonsterJsonData(std::string file_path) {
	const char* json_path = file_path.c_str();
	std::ifstream monster_json_stream(json_path, std::ifstream::binary);
	Json::Value monster_values;
	monster_json_stream >> monster_values;
	int monster_count = monster_values.size();
	std::cout << "JSON COUNT" << monster_count << std::endl;

	std::vector<std::unordered_map<std::string, std::string>> json_entries_list = {};

	for(int i = 0; i < monster_count; i++) {
		Json::Value monster_entry = monster_values[i];
		json_entries_list.push_back(UnpackMonsterJsonEntry(monster_entry));
	}

	std::cout << "MAP SIZE" << json_entries_list.size() << std::endl;
	return json_entries_list;
}

std::unordered_map<std::string, std::string> UnpackMonsterJsonEntry(Json::Value entry) {
	std::unordered_map<std::string, std::string> entry_data_map = {};

	std::string unique_id = entry["unique_id"].asString();
	entry_data_map["id"] = unique_id;
	std::string mon_name = entry["name"].asString();
	entry_data_map["name"] = mon_name;
	std::string pretty_name = entry["pretty_name"].asString();
	entry_data_map["pretty_name"] = pretty_name;
	std::string dex_num = entry["dex_number"].asString();
	entry_data_map["dex_number"] = dex_num;

	std::string generation = entry["generation"].asString();
	entry_data_map["generation"] = generation;
	std::string switchable = entry["form_switchable"].asString();
	entry_data_map["form_switchable"] = switchable;
	std::string color = entry["color"].asString();
	entry_data_map["color"] = color;
	std::string shape = entry["shape"].asString();
	entry_data_map["shape"] = shape;

	std::string prim_type = entry["types"]["primary"].asString();
	entry_data_map["primary_type"] = prim_type;
	std::string sec_type = entry["types"]["secondary"].asString();
	entry_data_map["secondary_type"] = sec_type;

	std::string growth_rate = entry["growth_rate"].asString();
	entry_data_map["growth_rate"] = growth_rate;
	std::string base_experience = entry["base_experience"].asString();
	entry_data_map["base_experience"] = base_experience;
	std::string base_happiness = entry["base_happiness"].asString();
	entry_data_map["base_happiness"] = base_happiness;
	std::string catch_rate = entry["catch_rate"].asString();
	entry_data_map["catch_rate"] = catch_rate;

	std::string hatch_count = entry["hatch_counter"].asString();
	entry_data_map["hatch_counter"] = hatch_count;
	std::string gender_rate = entry["gender_rate"].asString();
	entry_data_map["gender_rate"] = gender_rate;
	std::string dimorphic = entry["dimorphic"].asString();
	entry_data_map["dimorphic"] = dimorphic;

	std::string prim_egg = entry["egg_groups"]["primary"].asString();
	entry_data_map["primary_egg_group"] = prim_egg;
	std::string sec_egg = entry["egg_groups"]["secondary"].asString();
	entry_data_map["secondary_egg_group"] = sec_egg;

	std::string is_default = entry["is_default"].asString();
	entry_data_map["is_default"] = is_default;
	std::string is_baby = entry["is_baby"].asString();
	entry_data_map["is_baby"] = is_baby;
	std::string is_legendary = entry["is_legendary"].asString();
	entry_data_map["is_legendary"] = is_legendary;
	std::string is_mythical = entry["is_mythical"].asString();
	entry_data_map["is_mythical"] = is_mythical;

	std::string height = entry["height(m)"].asString();
	entry_data_map["height"] = height;
	std::string weight = entry["weight(kg)"].asString();
	entry_data_map["weight"] = weight;

	std::string abil1 = entry["abilities"]["first"].asString();
	entry_data_map["ability_1"] = abil1;
	std::string abil2 = entry["abilities"]["second"].asString();
	entry_data_map["ability_2"] = abil2;
	std::string abil_hidden = entry["abilities"]["hidden"].asString();
	entry_data_map["hidden_ability"] = abil_hidden;

	std::string pretty_abil1 = entry["pretty_abilities"]["first"].asString();
	entry_data_map["pretty_ability_1"] = pretty_abil1;
	std::string pretty_abil2 = entry["pretty_abilities"]["second"].asString();
	entry_data_map["pretty_ability_2"] = pretty_abil2;
	std::string pretty_abil_hidden = entry["pretty_abilities"]["hidden"].asString();
	entry_data_map["pretty_hidden_ability"] = pretty_abil_hidden;

	std::string health = entry["stats"]["hp"].asString();
	entry_data_map["hp"] = health;
	std::string attack = entry["stats"]["attack"].asString();
	entry_data_map["attack"] = attack;
	std::string defense = entry["stats"]["defense"].asString();
	entry_data_map["defense"] = defense;
	std::string spe_atk = entry["stats"]["special-attack"].asString();
	entry_data_map["special_attack"] = spe_atk;
	std::string spe_def = entry["stats"]["special-defense"].asString();
	entry_data_map["special_defense"] = spe_def;
	std::string speed = entry["stats"]["speed"].asString();
	entry_data_map["speed"] = speed;
	std::string stat_total = entry["stats"]["total"].asString();
	entry_data_map["stat_total"] = stat_total;

	std::string poke_url = entry["poke_url"].asString();
	entry_data_map["poke_url"] = poke_url;
	std::string species_url = entry["species_url"].asString();
	entry_data_map["species_url"] = species_url;
	std::string form_url = entry["form_url"].asString();
	entry_data_map["form_url"] = form_url;

	return entry_data_map;
}

} // namespace monster_calculator