
// (c) 2024 R.Hasaranga

#include "WSHat.h"

#define TFT_MOSI 11
#define TFT_SCLK 10
#define TFT_CS 8
#define TFT_RST 27
#define TFT_DC 25
#define TFT_BL 24

Adafruit_GFX_Buffer<Adafruit_ST7789> tftDisplay = Adafruit_GFX_Buffer<Adafruit_ST7789>(240,
	240, Adafruit_ST7789(&SPI1, TFT_CS, TFT_DC, TFT_RST));

WSHat::WSHat() {}

void WSHat::init()
{
	gpio_set_function(TFT_MOSI, GPIO_FUNC_SPI);
	gpio_set_function(TFT_SCLK, GPIO_FUNC_SPI);

	pinMode(TFT_BL, OUTPUT); // backlight
	analogWrite(TFT_BL, SettingsStore::readBacklightLevel()); // set brightness 0 - 255

	tftDisplay.init(240, 240);
	tftDisplay.setSPISpeed(70 * 1000 * 1000); // 70MHz
	tftDisplay.setRotation(3);

	tftDisplay.fillScreen(ST77XX_BLACK);
	tftDisplay.display();

	pinMode(WSHat::KEY_1, INPUT_PULLUP);
	pinMode(WSHat::KEY_2, INPUT_PULLUP);
	pinMode(WSHat::KEY_3, INPUT_PULLUP);
	pinMode(WSHat::UP_KEY, INPUT_PULLUP);
	pinMode(WSHat::DOWN_KEY, INPUT_PULLUP);
	pinMode(WSHat::LEFT_KEY, INPUT_PULLUP);
	pinMode(WSHat::RIGHT_KEY, INPUT_PULLUP);
	pinMode(WSHat::CENTER_KEY, INPUT_PULLUP);
}

void WSHat::setBackLight(uint8_t level)
{
	analogWrite(TFT_BL, level);
}

bool WSHat::isKeyPressed(uint8_t key)
{
	return (digitalRead(key) == LOW);
}

Adafruit_GFX_Buffer<Adafruit_ST7789>* WSHat::getDisplay()
{
	return &tftDisplay;
}