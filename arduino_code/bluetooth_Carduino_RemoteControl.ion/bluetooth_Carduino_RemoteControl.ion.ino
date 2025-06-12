/* Create a bluetooth server

    Author: dibigiti
    Creation date: 12/6/2025
    Last modified: 
   
    The server will have one service - CarduinoRemoteControl
    With 2 Characteristics:
       1. Left_Engine
       2. Right_Engine

       Which may have only two values:
       1. 0
       2. 1

       When the value is 0 the engine should be off, and when it's 1 it should be on...

       Let's have some fun!
   */
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID                      "4ab7946e-088c-4c5e-9646-51ffe3baf81d"
#define CHARACTERISTICS_RIGHT_ENGINE_UUID "7e8823de-7c10-4d9b-aa07-15b3c423155b"
#define CHARACTERISTICS_LEFT_ENGINE_UUID  "358180b1-abe1-4dbc-8ed1-b712f15e5a18"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("XIAO_ESP32S3");

  // Create The Bluetooth server
  BLEServer *pServer = BLEDevice::createServer();
  
  // Create The Carduino service
  BLEService *pRemoteControlService = pServer->createService(SERVICE_UUID);
  
  // Add the Right_Engine and Left_Engine Characteristics
  BLECharacteristic *pCharacterRightEngine = pRemoteControlService->createCharacteristic(
    CHARACTERISTICS_RIGHT_ENGINE_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );
  BLECharacteristic *pCharacterLeftEngine = pRemoteControlService->createCharacteristic(
    CHARACTERISTICS_RIGHT_ENGINE_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );
  int initial_value = 0;
  // Set the Characteristics's values
  pCharacterRightEngine->setValue(initial_value);
  pCharacterLeftEngine->setValue(initial_value);

  // Create an advertising request
  pRemoteControlService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Try your phone");

  // TODO: Add callbacks when the value in characteristics changes.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
}
