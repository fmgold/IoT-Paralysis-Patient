#include <SPI.h> // Not actually used but needed to compile
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
int button = 7;
int buttonState = 0;
void setup()
{
  Serial.begin(9600);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop()
{

  buttonState = digitalRead(button);
  //mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  int X = mpu6050.getAngleX();
  //int Y = mpu6050.getAngleY();
  //int Z = mpu6050.getAngleZ();

  //Serial.print("angleX : ");
  //Serial.println(X);
  //  Serial.print("\tangleY : ");
  //  Serial.print(Y);
  //  Serial.print("\tangleZ : ");
  //  Serial.println(Z);

  if (X >= 15) {
    //    //Serial.println(1);
    //    Serial.write("1");
    Serial.print("a");
    //    Serial.println(X);
    delay(5000);
    X = 0;
  }
  if (buttonState == HIGH) {
    Serial.print("a");

    delay(5000);
    X = 0;
  }

  delay(1000);
}
