// Language: C++

// Include necessary libraries for ESP8266 WiFi and SoftwareSerial for GPS communication
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"

// Define pin numbers for the relay and LED connected to the Arduino
#define RELAY_PIN 1  // Pin for controlling the relay switch (engine)
#define LED_PIN 2 // Pin for controlling an LED (indicator)

// Define pin numbers for the GPS module
#define GPS_RX_PIN 4  // RX pin for GPS module
#define GPS_TX_PIN 5  // TX pin for GPS module

// Create a SoftwareSerial object for GPS communication
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

// Wi-Fi connection details (SSID and password of your Wi-Fi network)
const char* ssid = "your_SSID";         // Wi-Fi SSID (name)
const char* password = "your_PASSWORD"; // Wi-Fi password

// Create a WiFiServer object that will listen on port 80 (HTTP requests)
WiFiServer server(80);

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Initialize serial communication for the GPS module
    gpsSerial.begin(9600);

    // Set the relay and LED pins as outputs
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    // Initially turn off the relay and LED
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, LOW);

    // Start connecting to the specified Wi-Fi network
    WiFi.begin(ssid, password);

    // Wait for Wi-Fi to connect (retry every 1 second)
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    // Once connected, print IP address and start the server
    Serial.println("Connected to WiFi");
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());

    // Start the HTTP server
    server.begin();
}

void loop() {
    // Check if a client (Android app) has connected
    WiFiClient client = server.available();

    if (client) {
        // Read the incoming HTTP request from the client
        String request = client.readStringUntil('\r');
        client.flush();

        // Handle different requests based on the URL path

        // If the request contains "/startEngine", turn on the relay (start engine)
        if (request.indexOf("/startEngine") != -1) {
            digitalWrite(RELAY_PIN, HIGH);  // Activate relay
        }

        // If the request contains "/stopEngine", turn off the relay (stop engine)
        if (request.indexOf("/stopEngine") != -1) {
            digitalWrite(RELAY_PIN, LOW);   // Deactivate relay
        }

        // If the request contains "/toggleLED", toggle the LED state (on/off)
        if (request.indexOf("/toggleLED") != -1) {
            digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
        }

        // If the request contains "/getGPS", send the GPS coordinates to the client
        if (request.indexOf("/getGPS") != -1) {
            String gpsData = getGPSData();  // Get GPS data from the GPS module
            client.print(gpsData);          // Send the GPS data back to the client
        }

        // Flush the client to ensure all data is sent
        client.flush();
    }
}

// Function to read GPS data from the GPS module
String getGPSData() {
    String gpsData = "";
    while (gpsSerial.available() > 0) {
        gpsData += char(gpsSerial.read());  // Read characters from GPS serial and build string
    }
    return gpsData;  // Return the GPS coordinates as a string
}
