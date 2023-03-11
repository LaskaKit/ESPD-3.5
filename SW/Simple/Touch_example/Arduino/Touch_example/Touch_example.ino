/* Touch_example 
 * 
 * Email:podpora@laskakit.cz
 * Web:laskarduino.cz
 */

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <Arduino.h>
/*
 * Chip used in board is FT5436
 * Library used: https://github.com/DustinWatts/FT6236
 * Just changed CHIPID and VENDID
 * Library is included in the project so it does not need to be downloaded
 */
#include "FT6236.h"

// TFT SPI
#define TFT_LED 33			// TFT backlight pin
#define TFT_LED_PWM 100 	// dutyCycle 0-255 last minimum was 15

#define SD_CS_PIN 4

FT6236 ts = FT6236(480, 320);
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library with default width and height

void displayInit()
{
	tft.init();
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);
}

void setup(void)
{
    Serial.begin(115200);
    if (!ts.begin(40)) //40 in this case represents the sensitivity. Try higer or lower for better response. 
    {
        Serial.println("Unable to start the capacitive touchscreen.");
    }
	ts.setRotation(1);
	ledcSetup(1, 5000, 8);		 // ledChannel, freq, resolution
	ledcAttachPin(TFT_LED, 1); // ledPin, ledChannel
	ledcWrite(1, TFT_LED_PWM); // dutyCycle 0-255
    displayInit();
    tft.fillScreen(TFT_BLACK);
	tft.setTextSize(1);
	tft.setTextFont(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextDatum(TL_DATUM);
	tft.drawString("X: ", 3, 0);
	tft.drawString("Y: ", 3, 16);
}

void loop(void)
{

    if (ts.touched())
    {
        // Retrieve a point
        TS_Point p = ts.getPoint();
		tft.setTextColor(TFT_WHITE, TFT_BLACK);
		tft.setTextDatum(TL_DATUM);
		tft.setTextPadding(tft.textWidth("X: 999", 2));
		tft.drawString("X: " + String(p.x), 3, 0);
		tft.setTextPadding(tft.textWidth("Y: 999", 2));
		tft.drawString("Y: " + String(p.y), 3, 16);
    }
    //Debouncing. To avoid returning the same touch multiple times you can play with this delay.
    delay(50);
}