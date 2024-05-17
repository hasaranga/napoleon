
// (c) 2024 R.Hasaranga

#pragma once

// it is not essential to make a border with greybrick.
// you can have yellow boxes in a level at the beginning.
// there is no way to put the player on a pointbox at the beginning.

// sokoban_greybrick
#define SK_GB 0

// sokoban_emptybox
#define SK_EB 1

// sokoban_pointbox
#define SK_PB 2

// sokoban_yellowbox
#define SK_YB 3

// sokoban_redbox
#define SK_RB 4

// sokoban_player
#define SK_PL 5

#define SKOBAN_LEVEL_COUNT 30

const uint8_t sokoban_level_1[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_RB, SK_EB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_PL, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_2[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_PB, SK_PB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PL, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_3[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_EB, SK_GB, SK_PL, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_PB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_RB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_GB, SK_PB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_4[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_PB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_PB, SK_GB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_RB, SK_GB, SK_PL, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_5[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_PL, SK_RB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_PB, SK_EB, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_PB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_6[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PL, SK_GB, SK_GB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_GB, SK_PB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_RB, SK_PB, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_GB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_7[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_EB, SK_PL, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_EB, SK_GB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PB, SK_EB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_8[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_PB, SK_PL, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_PB, SK_RB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_9[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_PB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_RB, SK_PB, SK_PL, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_10[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PL, SK_RB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PB, SK_EB, SK_GB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_PB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_11[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_PB, SK_PL, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_PB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_12[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_EB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PL, SK_PB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_PB, SK_RB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_13[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_PB, SK_RB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PL, SK_EB, SK_PB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_14[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_PL, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_PB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_PB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_PB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_15[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_EB, SK_RB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_PB, SK_RB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_EB, SK_PL, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_RB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_16[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_RB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_PB, SK_PL, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_17[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_PB, SK_PB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_GB, SK_RB, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_PL, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_18[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_RB, SK_EB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PL, SK_PB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_19[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_EB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_PB, SK_EB, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_PB, SK_PB, SK_RB, SK_PL, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_20[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_RB, SK_EB, SK_PB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_PL, SK_EB, SK_RB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_PB, SK_PB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t sokoban_level_21[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_PL, SK_EB, SK_EB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_PB, SK_PB, SK_PB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Lines to squares
const uint8_t sokoban_level_22[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_PB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_PL, SK_RB, SK_EB, SK_YB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_YB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_PB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Two Lines
const uint8_t sokoban_level_23[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_PB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PL, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_PB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Vertical to horizontal
const uint8_t sokoban_level_24[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_PB, SK_PB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PL, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_PB, SK_PB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - closing the gap
const uint8_t sokoban_level_25[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_RB, SK_RB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_PB, SK_PB, SK_PB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_PB, SK_PB, SK_PB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_PL, SK_RB, SK_RB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Vertical to horizontal 3
const uint8_t sokoban_level_26[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_YB, SK_PB, SK_YB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PL, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_YB, SK_PB, SK_YB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Infusion
const uint8_t sokoban_level_27[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_GB, SK_EB, SK_GB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_RB, SK_GB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_RB, SK_RB, SK_PL, SK_RB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_PB, SK_PB, SK_PB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Vertical to horizontal 4
const uint8_t sokoban_level_28[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_YB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PL, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_YB, SK_PB, SK_RB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Infusion2
const uint8_t sokoban_level_29[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_GB, SK_EB, SK_GB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_EB, SK_GB, SK_EB, SK_GB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PL, SK_RB, SK_RB, SK_GB, SK_GB,
	SK_GB, SK_PB, SK_PB, SK_PB, SK_PB, SK_PB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

// Sokofun - Mic's style
const uint8_t sokoban_level_30[] PROGMEM = {
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_PB, SK_PB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_EB, SK_YB, SK_PB, SK_PL, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_YB, SK_EB, SK_GB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_RB, SK_PB, SK_RB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_GB, SK_GB, SK_EB, SK_RB, SK_EB, SK_GB,
	SK_GB, SK_EB, SK_EB, SK_EB, SK_EB, SK_GB, SK_GB, SK_GB,
	SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB, SK_GB
};

const uint8_t* sokoban_levels[] = { sokoban_level_1, sokoban_level_2,
sokoban_level_3, sokoban_level_4, sokoban_level_5, sokoban_level_6, 
sokoban_level_7, sokoban_level_8, sokoban_level_9, sokoban_level_10, 
sokoban_level_11, sokoban_level_12, sokoban_level_13, sokoban_level_14,
sokoban_level_15, sokoban_level_16, sokoban_level_17, sokoban_level_18, 
sokoban_level_19, sokoban_level_20, sokoban_level_21, sokoban_level_22,
sokoban_level_23, sokoban_level_24, sokoban_level_25, sokoban_level_26,
sokoban_level_27, sokoban_level_28, sokoban_level_29, sokoban_level_30 };