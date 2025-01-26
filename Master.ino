//MASTER CODE

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_ADDR 0x3C       // I2C address for the OLED
#define SLAVE_ADDR 9         // I2C address of the slave (DHT11)

// Create the OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin();                // Initialize I2C
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); 
  // Initialize OLED
  display.clearDisplay();      // Clear the display
  display.setTextSize(2);      // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0, 0);     // Set cursor position
  display.println("Temperature:");
  display.display();            // Show initial text
}
void loop() {
  float temperature;
  float humidity;
  
  // Request temperature and humidity from the slave
  Wire.requestFrom(SLAVE_ADDR, sizeof(float) * 2); 
  // Request 8 bytes (2 floats)
  if (Wire.available() == sizeof(float) * 2) {
    Wire.readBytes((char*)&temperature, sizeof(float)); 
    // Read temperature
    Wire.readBytes((char*)&humidity, sizeof(float));    
    // Read humidity
  }
  // Display the temperature
  display.clearDisplay();          // Clear the display
  display.setCursor(0, 0);         // Set cursor position
  display.print("Temp:     ");
  display.print(temperature);       // Print temperature
  display.println(" C");
  display.print("Humidity: ");
  display.print(humidity);          // Print humidity
  display.println(" %");
  display.display();                // Show data on OLED
  delay(2000); // Update every 2 seconds
}
 