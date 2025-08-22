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
extern const DisplayColor kVermillionColor = DisplayColor(
	"Vermillion",
	ImVec4(227.0f / 255.0f, 66.0f / 255.0f, 52.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kRubyRedColor = DisplayColor(
	"Ruby Red",
	ImVec4(224.0f / 255.0f, 17.0f / 255.0f, 95.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kCheriColor = DisplayColor(
	"Cheri",
	ImVec4(210.0f / 255.0f, 4.0f / 255.0f, 45.0f / 255.0f, kColorIntensity)
);

// Blues
extern const DisplayColor kBlueColor = DisplayColor(
	"Blue",
	ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPeriwinkleColor = DisplayColor(
	"Periwinkle",
	ImVec4(204.0f / 255.0f, 204.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kIndigoColor = DisplayColor(
	"Indigo",
	ImVec4(63.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kRawstColor = DisplayColor(
	"Rawst",
	ImVec4(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, kColorIntensity)
);


// Greens
extern const DisplayColor kGreenColor = DisplayColor(
	"Green",
	ImVec4(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kCeladonColor = DisplayColor(
	"Celadon",
	ImVec4(175.0f / 255.0f, 225.0f / 255.0f, 175.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kViridianColor = DisplayColor(
	"Viridian",
	ImVec4(64.0f / 255.0f, 130.0f / 255.0f, 109.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kLumColor = DisplayColor(
	"Lum",
	ImVec4(11.0f / 255.0f, 218.0f / 255.0f, 81.0f / 255.0f, kColorIntensity)
);

// Yellows
extern const DisplayColor kYellowColor = DisplayColor(
	"Yellow",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kSaffronColor = DisplayColor(
	"Saffron",
	ImVec4(244.0f / 255.0f, 196.0f / 255.0f, 48.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kGoldenrodColor = DisplayColor(
	"Goldenrod",
	ImVec4(218.0f / 255.0f, 165.0f / 255.0f, 32.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kAspearColor = DisplayColor(
	"Aspear",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 143.0f / 255.0f, kColorIntensity)
);

// Oranges
extern const DisplayColor kOrangeColor = DisplayColor(
	"Orange",
	ImVec4(255.0f / 255.0f, 165.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPersimmonColor = DisplayColor(
	"Persimmon",
	ImVec4(236.0f / 255.0f, 88.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kTangerineColor = DisplayColor(
	"Tangerine",
	ImVec4(240.0f / 255.0f, 128.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);

// Purples
extern const DisplayColor kPurpleColor = DisplayColor(
	"Purple",
	ImVec4(128.0f / 255.0f, 0.0f / 255.0f, 128.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kMauveColor = DisplayColor(
	"Mauve",
	ImVec4(224.0f / 255.0f, 176.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kOrchidColor = DisplayColor(
	"Orchid",
	ImVec4(218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kChestoColor = DisplayColor(
	"Chesto",
	ImVec4(112.0f / 255.0f, 41.0f / 255.0f, 99.0f / 255.0f, kColorIntensity)
);

// Pinks
extern const DisplayColor kPinkColor = DisplayColor(
	"Pink",
	ImVec4(255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kRaspberryColor = DisplayColor(
	"Raspberry",
	ImVec4(227.0f / 255.0f, 11.0f / 255.0f, 92.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kFuschiaColor = DisplayColor(
	"Fuschia",
	ImVec4(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPechaColor = DisplayColor(
	"Pecha",
	ImVec4(248.0f / 255.0f, 152.0f / 255.0f, 128.0f / 255.0f, kColorIntensity)
);

// Whites
extern const DisplayColor kWhiteColor = DisplayColor(
	"White",
	ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kSeashellColor = DisplayColor(
	"Seashell",
	ImVec4(255.0f / 255.0f, 245.0f / 255.0f, 238.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kLinenColor = DisplayColor(
	"Linen",
	ImVec4(233.0f / 255.0f, 220.0f / 255.0f, 240.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kPearlColor = DisplayColor(
	"Pearl",
	ImVec4(226.0f / 255.0f, 223.0f / 255.0f, 210.0f / 255.0f, kColorIntensity)
);

// Grays
extern const DisplayColor kGrayColor = DisplayColor(
	"Gray",
	ImVec4(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, kColorIntensity)
);

// Blacks
extern const DisplayColor kBlackColor = DisplayColor(
	"Black",
	ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kCharcoalColor = DisplayColor(
	"Charcoal",
	ImVec4(54.0f / 255.0f, 69.0f / 255.0f, 79.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kMidnightColor = DisplayColor(
	"Midnight",
	ImVec4(25.0f / 255.0f, 25.0f / 255.0f, 112.0f / 255.0f, kColorIntensity)
);

// Browns
extern const DisplayColor kBrownColor = DisplayColor(
	"Brown",
	ImVec4(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kMahoganyColor = DisplayColor(
	"Mahogany",
	ImVec4(192.0f / 255.0f, 64.0f / 255.0f, 0.0f / 255.0f, kColorIntensity)
);
extern const DisplayColor kBrassColor = DisplayColor(
	"Brass",
	ImVec4(225.0f / 255.0f, 193.0f / 255.0f, 110.0f / 255.0f, kColorIntensity)
);

} // namespace monster_calculator