#pragma once
#include <string>
#include <vector>

#include "mcc_structs.h"

namespace monster_calculator {

extern const std::string kMainTableScheme;

extern const std::vector<std::pair<std::string, std::string>> kTypesList;
extern const std::vector<std::pair<std::string, std::string>> kRegionsList;

extern const ParameterType kPrimaryTypeParam;
extern const ParameterType kSecondaryTypeParam;
extern const ParameterType kEitherTypeParam;
extern const ParameterType kRegionParam;
					  
extern const ParameterType kHealthParam;

} // namespace monster_calculator
