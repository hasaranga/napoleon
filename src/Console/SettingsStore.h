
// (c) 2024 R.Hasaranga

#pragma once

#include <EEPROM.h>

class SettingsStore
{
	static const int BACKLIGHT_ADDR = 0;
	static const int SOKOBAN_LEVEL_ADDR = 1;
	static const int WATERSORT_LEVEL_ADDR = 2;
public:
	static const uint8_t DEFAULT_BACKLIGHT_LEVEL = 100;
	static const int MIN_BACKLIGHT = 20;
	static const int MAX_BACKLIGHT = 255;

	static void init()
	{
		EEPROM.begin(512);
	}

	static uint8_t readBacklightLevel()
	{
		uint8_t val = EEPROM.read(BACKLIGHT_ADDR);

		if (val < MIN_BACKLIGHT)
			val = DEFAULT_BACKLIGHT_LEVEL;
		else if(val > MAX_BACKLIGHT)
			val = DEFAULT_BACKLIGHT_LEVEL;

		return val;
	}

	static void setBacklightLevel(uint8_t level)
	{
		EEPROM.write(BACKLIGHT_ADDR, level);
	}

	static void setSokobanLevel(uint8_t level)
	{
		EEPROM.write(SOKOBAN_LEVEL_ADDR, level);
	}

	static uint8_t readSokobanLevel()
	{
		return EEPROM.read(SOKOBAN_LEVEL_ADDR);
	}

	static void setWaterSortLevel(uint8_t level)
	{
		EEPROM.write(WATERSORT_LEVEL_ADDR, level);
	}

	static uint8_t readWaterSortLevel()
	{
		return EEPROM.read(WATERSORT_LEVEL_ADDR);
	}

	static void commit()
	{
		EEPROM.commit();
	}
};