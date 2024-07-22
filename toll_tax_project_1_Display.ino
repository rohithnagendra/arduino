/*********************************************************************
  This is an example for our Toll Tax Collection System

  This example is for a 128x64 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  This example uses Servo Motor & Ultrasonic Sensor
*********************************************************************/

#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c  //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// SDA - A4
// SCL - A5

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16
static const unsigned char PROGMEM logo16_glcd_bmp[] = { B00000000, B11000000,
                                                         B00000001, B11000000,
                                                         B00000001, B11000000,
                                                         B00000011, B11100000,
                                                         B11110011, B11100000,
                                                         B11111110, B11111000,
                                                         B01111110, B11111111,
                                                         B00110011, B10011111,
                                                         B00011111, B11111100,
                                                         B00001101, B01110000,
                                                         B00011011, B10100000,
                                                         B00111111, B11100000,
                                                         B00111111, B11110000,
                                                         B01111100, B11110000,
                                                         B01110000, B01110000,
                                                         B00000000, B00110000 };

Servo myservo;
const int trigPin = 3;
const int echoPin = 5;
long tmeduration;
int distance;

void setup() {
  myservo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  delay(250);                        // wait for the OLED to power up
  display.begin(i2c_Address, true);  // Address 0x3C default
                                     // draw a single pixel
  display.drawPixel(10, 10, SH110X_WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();


  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("WELCOME TO TOLL TAX COLLECTION");
 // display.setTextColor(SH110X_BLACK, SH110X_WHITE);  // 'inverted' text
 // display.println(3.141592);
  //display.setTextSize(2);
  //display.setTextColor(SH110X_WHITE);
  //display.print("0x");
  //display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
}

void WriteMyText(String disTxt) {
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println(disTxt);
  display.display();
}

void ClearMyText() {
  //delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {

  //delay(500);
  //ClearMyText();
  //WriteMyText("Toll Gate Closed");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  tmeduration = pulseIn(echoPin, HIGH);
  distance = (0.034 * tmeduration) / 2;

  if (distance <= 18 && distance != 0) {
    ClearMyText();
    WriteMyText("Toll Gate Opened");
    Serial.print("distance:");
    Serial.println(distance);
    myservo.write(90);
    delay(2000);
    ClearMyText();
    WriteMyText("Toll Gate Closed");
    delay(2000);
    ClearMyText();
    WriteMyText("Thank You for Visiting .");

  } else {
    //ClearMyText();
   // WriteMyText("Toll Gate Closed");
    myservo.write(0);
  }
}