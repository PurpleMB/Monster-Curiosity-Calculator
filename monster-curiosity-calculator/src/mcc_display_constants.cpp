#pragma once

#include "mcc_display_structs.h"

#include "mcc_display_constants.h"

namespace monster_calculator {

// DisplayColor constants
const float kColorIntensity = 0.6f;
// Reds
extern const DisplayColor kRedColor = DisplayColor(
	"Red",
	ImVec4(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Blues
extern const DisplayColor kBlueColor = DisplayColor(
	"Blue",
	ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);

// Greens
extern const DisplayColor kGreenColor = DisplayColor(
	"Green",
	ImVec4(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Yellows
extern const DisplayColor kYellowColor = DisplayColor(
	"Yellow",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Oranges
extern const DisplayColor kOrangeColor = DisplayColor(
	"Orange",
	ImVec4(255.0f / 255.0f, 165.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Purples
extern const DisplayColor kPurpleColor = DisplayColor(
	"Purple",
	ImVec4(128.0f / 255.0f, 0.0f / 255.0f, 128.0f / 255.0f, kColorIntensity)
);

// Pinks
extern const DisplayColor kPinkColor = DisplayColor(
	"Pink",
	ImVec4(255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f, kColorIntensity)
);

// Whites
extern const DisplayColor kWhiteColor = DisplayColor(
	"White",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);

// Blacks
extern const DisplayColor kBlackColor = DisplayColor(
	"Black",
	ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Browns
extern const DisplayColor kBrownColor = DisplayColor(
	"Brown",
	ImVec4(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, kColorIntensity)
);

} //  namespace monster_calculator