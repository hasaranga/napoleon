
// (c) 2024 R.Hasaranga

#pragma once

#include <Adafruit_GFX_Buffer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "SettingsStore.h"

class WSHat
{
public:

	static const uint8_t KEY_1 = 21;
	static const uint8_t KEY_2 = 20;
	static const uint8_t KEY_3 = 16;
	static const uint8_t UP_KEY = 6;
	static const uint8_t DOWN_KEY = 19;
	static const uint8_t LEFT_KEY = 15;
	static const uint8_t RIGHT_KEY = 26;
	static const uint8_t CENTER_KEY = 13;

	WSHat();

	void init();
	void setBackLight(uint8_t level);
	bool isKeyPressed(uint8_t key);
	Adafruit_GFX_Buffer<Adafruit_ST7789>* getDisplay();
};
