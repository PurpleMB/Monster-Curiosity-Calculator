#pragma once
#include <string>
#include <vector>

#include "mcc_structs.h"

namespace monster_calculator {

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
extern const ParameterType kPrimaryTypeParam(kPrimaryDisplayName, kPrimaryQueryName, kTypesList);


const std::string kSecondaryDisplayName = "Secondary Type";
const std::string kSecondaryQueryName = "secondary_type";
extern const ParameterType kSecondaryTypeParam(kSecondaryDisplayName, kSecondaryQueryName, kTypesList);

// TODO: this needs to be restructured. currently identical to checking secondary = value
const std::string kEitherDisplayName = "Either Type";
const std::string kEitherQueryName = "primary_type OR secondary_type";
extern const ParameterType kEitherTypeParam(kEitherDisplayName, kEitherQueryName, kTypesList);

} // namespace monster_calculator
