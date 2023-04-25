#include <TinyGPS++.h> // Include the TinyGPS++ library
#include <SoftwareSerial.h>
TinyGPSPlus GPS; // Create a TinyGPSPlus object

//#define GPS_BAUD 9600 // GPS module baud rate. GP3906 defaults to 9600.
//#define gpsPort ssGPS 

SoftwareSerial SIM900(7, 8); //TX/RX inia Untuk Koneksi Modul SIM900
char vbyte;
String txtMsg;
int SW = 9; //Key untuk menyalakan SIM900

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SIM900.begin(9600);
keySIM900();
SIM900.println("AT+CNMI=1,2,0,0,0");
  delay(1000);
  SIM900.println("AT+CSCS=\"GSM\"");
  delay(1000);
  SIM900.print("AT+CMGF=1\r");
  delay(1000);
  Serial.println("Ready");
  sistemready();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(GPS.location.lat(), 6);
  Serial.println(GPS.location.lng(), 6);
  //Serial.print("Alt: "); Serial.println(GPS.altitude.feet());
  //Serial.print("Course: "); Serial.println(GPS.course.deg());
  //Serial.print("Speed: "); Serial.println(GPS.speed.mph());
  //Serial.print("Date: "); printDate();
  //Serial.print("Time: "); printTime();
  //Serial.print("Sats: "); Serial.println(GPS.satellites.value());
  //Serial.println();
  String dataprint="http://www.google.com/maps/place/"; 
  
  smartDelay(500);
  SIM900.listen();
  if (SIM900.available()) {
  char inByte = SIM900.read();
  //Serial.write(inByte); 
  if (inByte == 'Q') {
  SIM900.listen();
  delay(1000);
  SIM900.println("AT + CMGS = \"+628988541995\"");
  delay(1000);
  SIM900.print("Dimana Lokasi Motor Saya ?\n Klik Alamat Dibawah:\n");
  SIM900.print(dataprint); 
  SIM900.print(GPS.location.lat(), 6);
  SIM900.print(",");
  SIM900.println(GPS.location.lng(), 6);
  SIM900.print('\n');
  SIM900.print("Telususri Motor Anda Sekarang!!!");
  SIM900.println((char)26);   
}
}
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (Serial.available())
      GPS.encode(Serial.read()); // Send it to the encode function
    // tinyGPS.encode(char) continues to "load" the tinGPS object with new
    // data coming in from the GPS module. As full NMEA strings begin to come in
    // the GPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}

void keySIM900(){
  pinMode(SW, OUTPUT); 
 //1 digitalWrite(SW, HIGH);
  Serial.println("Hidupkan power");
  digitalWrite(SW, LOW);
  delay(1000);
  digitalWrite(SW, HIGH);
  delay(3000);
  digitalWrite(SW, LOW);
  delay(1000);
}

void sistemready()
{
  SIM900.listen();
  SIM900.println("AT + CMGS = \"+628988541995\"");
  delay(1000);
  //SIM900.print("System Ready OM");        // message to send
  SIM900.print("Alat Berjalan dengan Baik, Sekarang Motor Anda Berada di ?\nKlik Alamat Dibawah:\n");
  SIM900.print("http://www.google.com/maps/place/"); 
  SIM900.print(GPS.location.lat(), 6);
  SIM900.print(",");
  SIM900.println(GPS.location.lng(), 6);
  SIM900.print('\n');
  SIM900.print("Sistem Sudah Siap Pantau!!!");
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  
}

