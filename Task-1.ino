#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // Width of OLED display in pixels
#define SCREEN_HEIGHT 64     // Height of OLED display in pixels

#define LED_PIN 8            // Pin connected to LED
#define LDR_PIN A0           // Analog pin connected to LDR

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT); // Create display object

int reading; // Variable to store LDR reading

void setup() {
  // Initialize pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud

  // Initialize OLED display with I2C addr 0x3C, check for successful allocation
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed")); // Print error if display not found
    for(;;); // Infinite loop to stop code execution if display fails to initialize
  }
}

void loop() {
  // Read LDR value
  reading = analogRead(LDR_PIN);

  // Output reading to serial monitor
  Serial.print("Reading: ");
  Serial.println(reading);

  // Turn LED on if reading exceeds threshold, otherwise turn off
  if (reading > 700) {
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }

  // Display reading on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Reading:");
  display.setCursor(40, 30);
  display.setTextSize(3);
  display.println(reading);
  display.display();

  // Short delay between reads/updates
  delay(200);
}
