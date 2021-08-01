#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET  4
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float polynomial(float x)
{
  const float a = -1;
  const float b = -4;
  const float c = 5;

  return /*a * x*x + b * x + c*/ /*a * x*x + c*/ a * x -c;
}

void plot()
{
  const float lower_bound = -15;
  const float upper_bound = +15;
  const uint8_t segments = 30;
  const float dx = (upper_bound - lower_bound) / segments;


  const float min_y = -64;
  const float max_y = 64;

  for (float x = lower_bound; x < upper_bound - dx; x += dx)
  {
    const float x1 = map(x,      lower_bound, upper_bound, 0, SCREEN_WIDTH);
    const float x2 = map(x + dx, lower_bound, upper_bound, 0, SCREEN_WIDTH);


    const float y1 = map(polynomial(x),      min_y, max_y, SCREEN_HEIGHT, 0);
    const float y2 = map(polynomial(x + dx), min_y, max_y, SCREEN_HEIGHT, 0);

    const float y_axis_position = map(0, lower_bound, upper_bound, 0, SCREEN_WIDTH);
    const float x_axis_position = map(0, min_y, max_y, SCREEN_HEIGHT, 0);

    
    oled.drawLine(0, x_axis_position, SCREEN_WIDTH, x_axis_position, WHITE);//x axis
    oled.drawLine(y_axis_position, 0, y_axis_position, SCREEN_HEIGHT, WHITE);//y axis
    
    oled.drawLine(x1, y1 , x2 , y2 , WHITE);//graph draw command

    Serial.print("x1=");
    Serial.print(x1);
    Serial.println(" ");
    Serial.print("x2=");
    Serial.print(x2);
    Serial.println(" ");
    Serial.print("y1=");
    Serial.print(y1);
    Serial.println(" ");
    Serial.print("y2=");
    Serial.print(y2);
    Serial.println(" ");

    oled.display();
    
  }
}

void setup()
{
  Serial.begin(9600);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  
  oled.display();
  delay(2000);

  oled.clearDisplay();
  plot();

}


void loop() {}
