#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "FT3168.h"

//Display driver CO5300
// Define QSPI bus pins (adjust for your board)
#define QSPI_CS    9
#define QSPI_SCK   10
#define QSPI_D0    11
#define QSPI_D1    12
#define QSPI_D2    13
#define QSPI_D3    14
//AMOLED Reset – GPIO 21

// Initialize QSPI Bus
Arduino_DataBus *bus = new Arduino_ESP32QSPI(QSPI_CS, QSPI_SCK,QSPI_D0, QSPI_D1, QSPI_D2, QSPI_D3);

// Initialize Display
Arduino_GFX *gfx = new Arduino_CO5300(bus, 21 /* RST */, 0 /* rotation */, 280 /* width */, 456 /* height */,21,0,0,0);
//Arduino_CO5300::     Arduino_CO5300(Arduino_DataBus *bus, int8_t rst, uint8_t r, int16_t w, int16_t h, uint8_t col_offset1, uint8_t row_offset1, uint8_t col_offset2, uint8_t row_offset2)

uint32_t screenWidth = 280;
uint32_t screenHeight = 456;

// TOUCH
//#define TP_SDA 47
//#define TP_SCL 48
//#define TP_INT 46

void touchfunct()
{
  uint16_t tp_x,tp_y;
  uint8_t win = getTouch(&tp_x,&tp_y);
  if(win)
  {
    //Serial.printf("Touch X:%d Y:%d\n",tp_x,tp_y);
    gfx->setCursor(10, 130);
    gfx->setTextColor(WHITE,DARKCYAN);
    gfx->print("Touch X: ");
    gfx->print(tp_x);
    gfx->print("   ");
    gfx->setCursor(10, 170);
    gfx->print("Touch Y: ");
    gfx->print(tp_y);
    gfx->print("   ");
  }

}


void setup() {
  Serial.begin(115200);

  Touch_Init();
  
  gfx->begin();  // Init Display
  gfx->setRotation(0);
  gfx->fillScreen(DARKCYAN);

  gfx->setTextSize(2); //Default text will not show with size of 1

  gfx->setCursor(0, 10);
  gfx->setTextColor(RED);
  gfx->print("Hello World - RED");

  gfx->setCursor(0, 40);
  gfx->setTextColor(GREEN);
  gfx->print("Hello World - GREEN");

  gfx->setCursor(0, 70);
  gfx->setTextColor(BLUE);
  gfx->print("Hello World - BLUE");
}

void loop() {
  
  touchfunct();
  
}