//
//    FILE: I2C_PWM_generator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-11-25
// PURPOSE: Arduino UNO as 6 channel PWM co-processor.
//     URL: https://github.com/RobTillaart/PCA9553/issues/9
//

#include <Wire.h>

//  adjust if needed
#define I2C_BASE_ADDRESS    0x30
#define I2C_ADDRESS_PIN     4
#define I2C_BASE_CLOCK      100000


int PWMpins[6] = {3, 5, 6, 9, 10, 11};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);  //  for debugging

  //  POWER ON START
  for (int i = 0; i < 6; i++)
  {
    analogWrite(PWMpins[i], 0);
  }

  //  I2C ADDRESS
  uint8_t I2Caddress = 0x00;
  //  get address bit
  pinMode(I2C_ADDRESS_PIN, INPUT);
  if (digitalRead(I2C_ADDRESS_PIN) == HIGH) I2Caddress += 0x01;

  I2Caddress += I2C_BASE_ADDRESS;  //  0x30..0x31

  //  START AS SLAVE
  Wire.begin(I2Caddress);
  Wire.setClock(I2C_BASE_CLOCK);

  //  WAIT FOR COMMANDS
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop()
{
}


void receiveEvent(int count)
{
  int port = Wire.read();
  int value = Wire.read();

  Serial.print(count);
  if (port < 6)
  {
    analogWrite(PWMpins[port], value);
    //  Serial.println("S");  //  success
  }
  else
  {
    //  Serial.println("F");  //  fail
  }
}

//  optional.
void requestEvent()
{
  Wire.write(0);
}


//  -- END OF FILE --
