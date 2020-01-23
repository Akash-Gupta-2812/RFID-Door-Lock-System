#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>
 
#define SS_PIN 5
#define RST_PIN 9
#define RELAY 2 //connect the relay to number 2 pin
#define BUZZER 3 // connect the buzzer to 3 pin
#define ACCESS_DELAY 500
#define DENIED_DELAY 500
 
  // wifi and fire base credentials
  
#define FIREBASE_HOST "https://ledstats-dbe93.firebaseio.com/"
#define FIREBASE_AUTH "NL87b8HMseuNUCAsnP8Jui4sXAPRxw9lowHlIejU"
#define WIFI_SSID "GHAR"
#define WIFI_PASSWORD "misti_2812" 


  //defining date and time 
int timezone = 7 * 3600;
int dst = 0;
String CDate;
String CTime;
//String User;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader for scanning ...");
  Serial.println();
  //connection to wifi
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(500);
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

   configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
   Serial.println("\nWaiting for Internet time");

   while (!time(nullptr)){
    Serial.println("*");
    delay(1000);
    }
    Serial.println("\nTime Response.......OK ");
    
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "8B 6B 86 22") // CARD1
  { 
    Serial.println("Authorized access");
    Serial.println();
    ////delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);
    CDate = p_tm->tm_mday + '/' + (p_tm->tm_mon+1) + '/' + (p_tm->tm_year + 1900);
    CTime = p_tm->tm_hour + ':' + p_tm->tm_min + ':' + p_tm->tm_sec;
    String User = "AKASH GUPTA";
    Firebase.setString("Name",User);
    Firebase.setString("Date",CDate);
    Firebase.setString("Time",CTime);
    if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());  
    return;
  }
    
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}
   }
  else if (content.substring(1) == "19 A4 9B 6E") // KEY_RING
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}
   
  }
  else if (content.substring(1) == "DB 4C 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  
 else if (content.substring(1) == "8B 51 F2 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "AB 51 FF 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "EB 8B 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "3B 87 EB 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "FB B0 EC 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "0B C8 FB 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "9B 40 F8 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "5B 5B F4 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "8B 68 FF 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "2B DE EE 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "7B B6 F7 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "1B C9 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "CB 80 F2 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "DB 57 01 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "FB C2 F9 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "7B C6 0E 99") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "2B 05 ED 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  else if (content.substring(1) == "0B 89 EB 66") // enter your own card number after copying it from serial monitor
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);}   
  }
  
 else   {
    Serial.println(" Access denied");
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
  }
}
