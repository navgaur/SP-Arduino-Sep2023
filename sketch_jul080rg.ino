#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <Arduino.h>
#include <Mhz19.h>
#include <SoftwareSerial.h>
#include <Adafruit_BMP085.h>

SoftwareSerial softwareSerial(A0, A1);
Adafruit_BMP085 bmp;

File myFile;
LiquidCrystal lcd(8, 9, 5, 4, 3, 7);
const int chipSelect = 10;

#include <dht11.h>
#define DHT11PIN 2
dht11 DHT11;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Starting");
  lcd.clear();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  lcd.print("BMP Error !");
  while (1) {}
  }
 
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    lcd.setCursor(0, 1);
    lcd.print("SD CARD Error !");    
    return;
  }
  Serial.println("initialization done.");
  myFile = SD.open("test.csv", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to test.csv...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.csv");
  }

  // re-open the file for reading:
  myFile = SD.open("test.csv");
  if (myFile) {
    Serial.println("test.csv:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.csv");
  }
    softwareSerial.begin(9600);

  lcd.setCursor(0,1);
  lcd.print("Ready...");
  delay(2000);
  Serial.println("Ready...");
}

void loop(){
  Serial.println();
  lcd.begin(16, 2);
  myFile = SD.open("test.csv", FILE_WRITE);
  
  int chk=DHT11.read(DHT11PIN);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity(%)");
    lcd.setCursor(0,1);
    lcd.print((float)DHT11.humidity,2);
    delay(5000);
    myFile.print("Humidity(%)=");
    myFile.print((float)DHT11.humidity,2);
    myFile.print('\t');
    lcd.clear();
    myFile.print("Temperature(*C)=");
    lcd.setCursor(0,0);
    lcd.print("Temperature(*C)=");
    lcd.setCursor(0,1);
    lcd.print((float)DHT11.temperature,2);
    delay(5000);
    myFile.print((float)DHT11.temperature,2);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Pressure(Pa)");
    lcd.setCursor(0,1);
    lcd.print(bmp.readPressure());
    delay(5000);
    myFile.print("Pressure(Pa)=");
    myFile.print(bmp.readPressure());
    myFile.print('\t');
    lcd.clear();
    myFile.print("Temperature(*C)=");
    lcd.setCursor(0,0);
    lcd.print("Temperature(*C)=");
    lcd.setCursor(0,1);
    lcd.print(bmp.readTemperature());
    delay(5000);
    myFile.print(bmp.readTemperature());
    lcd.clear();


    Serial.print("Humidity(%)=");
    Serial.print((float)DHT11.humidity,2);
    Serial.print('\t');
    Serial.print("Temperature(*C)=");
    Serial.print((float)DHT11.temperature,2);
    Serial.print('\t');
    Serial.print("Temperature(*C)=");
    Serial.print(bmp.readTemperature());
    Serial.print('\t');
    Serial.print("Pressure(Pa)=");
    Serial.print(bmp.readPressure());
    Serial.println('\t');
    delay(10000);    
    myFile.close();
}
