#include <Arduino.h>

#define SIGRD   RSIG    // Signature Row from Store Program Memory Control and Status Register
#define EIFR    GIFR    // External/General Interrupt Flag Register
#define WDTCSR  WDTCR   // WDT Control Register

extern void serialEventRun(void) __attribute__((weak));

#define SDA_PORT PORTB
#define SDA_PIN 3
#define SCL_PORT PORTB
#define SCL_PIN 4
#include <SoftWire.h>
SoftWire sWire = SoftWire();

#include <TinyBME280.h>

#define MY_SPLASH_SCREEN_DISABLED
#define MY_DISABLE_RAM_ROUTING_TABLE_FEATURE
#define MY_DISABLED_SERIAL
#define MY_PASSIVE_NODE
#define MY_DISABLE_REMOTE_RESET

#define MY_RADIO_RF24
#define MY_RF24_CE_PIN      NOT_A_PIN
#define MY_RF24_CS_PIN      NOT_A_PIN

#define MY_NODE_ID 99
#define MY_RF24_CHANNEL 0x70

#include <MySensors.h>

#define TEMP_CHILD 0
#define BARO_CHILD 1
#define HUM_CHILD 2

MyMessage tempMsg(TEMP_CHILD, V_TEMP);
MyMessage pressureMsg(BARO_CHILD, V_PRESSURE);
MyMessage humMsg(HUM_CHILD, V_HUM);

void setup() {
  sWire.begin();
  sleep(1000);
  BME280setup(sWire);
}

void presentation() {
  sendSketchInfo("TinyBME", "0.3");
  present(TEMP_CHILD, S_TEMP);
  present(BARO_CHILD, S_BARO);
  present(HUM_CHILD, S_HUM);
}

uint32_t v;

void loop() {
  
  v = BME280temperature(sWire);
  send(tempMsg.set(v));
  sleep(100);
  
  v = BME280pressure(sWire);
  send(pressureMsg.set(v));
  sleep(100);
  
  v = BME280humidity(sWire);
  send(humMsg.set(v));
  
  sleep(30000);
}
