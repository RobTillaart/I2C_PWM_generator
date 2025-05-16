//
//    FILE: I2C_PWM_generator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-11-25
// PURPOSE: Arduino UNO as 6 channel PWM co-processor.
//     URL: https://github.com/RobTillaart/PCA9553/issues/9
//

#include <avr/wdt.h>
#include <Wire.h>

//  adjust if needed
#define I2C_BASE_ADDRESS    0x30
#define I2C_ADDRESS_PIN     4
#define I2C_BASE_CLOCK      100000


const int PWMpins[6] = {3, 5, 6, 9, 10, 11};
//  power on start values can be adapted to your need.
const uint8_t POSValue[6] = {0, 0, 0, 0, 0, 0 };
//  cache current value, prep for getPWM()
uint8_t currentValue[6];

const int LEDPIN = 13;
uint32_t lastBlink = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);  //  for debugging

  //  WATCHDOG
  wdt_enable(WDTO_2S);

  //  HEARTBEAT PIN
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  //  POWER ON START
  for (int i = 0; i < 6; i++)
  {
    analogWrite(PWMpins[i], POSValue[i]);
    currentValue[i] = POSValue[i];
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
  //  watchdog
  wdt_reset();

  //  heartbeat
  uint32_t now = millis();
  if ((now - lastBlink) >= 1000)
  {
    lastBlink = now;
    digitalWrite(13, !digitalRead(13));
  }
}


void receiveEvent(int count)
{
  int port = Wire.read();
  int value = Wire.read();

  Serial.print(count);
  if (port < 6)
  {
    analogWrite(PWMpins[port], value);
    currentValue[port] = value;
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
