//SLAVE CODE

#include <Wire.h>
#include <DHT.h>
#define DHTPIN 2   // Pin where the DHT sensor is connected
#define DHTTYPE DHT11  // Define the type of DHT sensor (DHT11)
#define SLAVE_ADDR 9  // Define the slave I2C address

DHT dht(DHTPIN, DHTTYPE);    // Create a DHT object

float temperature;  // Variable to store temperature
float humidity;    // Variable to store humidity

void setup() {
  Wire.begin(SLAVE_ADDR);  // Initialize I2C as a slave
  Wire.onRequest(requestEvent); 
  // Register the request event
  Wire.onReceive(receiveEvent); 
  // Register the receive event
  dht.begin();              // Start the DHT sensor
}

void loop() {
  // Regularly update the readings
  dht.begin();
  temperature = dht.readTemperature(); 
  // Read temperature in Celsius
  humidity = dht.readHumidity();       
  // Read humidity in percentage
  delay(2000); // Read every 2 seconds
}

// Function to handle requests from the master
void requestEvent() {
  temperature = dht.readTemperature(); // Read temperature in 
                                        //Celsius
  humidity = dht.readHumidity(); // Read humidity in percentage
  // Send temperature and humidity to the master
  Wire.write((byte*)&temperature, sizeof(temperature));
   // Send temperature
  Wire.write((byte*)&humidity, sizeof(humidity)); // Send humidity
}

// Function to handle data received from the master
void receiveEvent(int numBytes) {
  while (Wire.available()) {
    char c = Wire.read(); // Read the incoming byte
    // You can process received data here (e.g., commands)
  }
}

