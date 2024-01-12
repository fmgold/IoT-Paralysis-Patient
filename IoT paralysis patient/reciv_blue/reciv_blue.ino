#include <SPI.h> // Not actualy used but needed to compile
//#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library >
#include <LiquidCrystal.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

int buzz = 5;

byte readCard[4];
String MasterTag = "C9893F94";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";



char inputByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzz, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM WARMING.....");
  lcd.setCursor(0, 1);
  lcd.print("initialize driver");
  delay(5000);
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);;
  lcd.clear();
}

void loop() {
  if (Serial.available()) // if the HC05 is sending something…
  {
    inputByte = Serial.read();
    Serial.println(inputByte);
  }
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
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    lcd.clear();
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
    lcd.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == MasterTag) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.print("Authorized access");
    delay(3000);
    lcd.clear();
  }

  else   {
    Serial.println(" Access denied");
    lcd.print(" Access denied");
    delay(3000);
    lcd.clear();
  }

}


//98D3:31:FA0292
