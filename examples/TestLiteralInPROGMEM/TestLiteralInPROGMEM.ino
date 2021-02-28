#ifdef ARDUINO
#include <Arduino.h>
#include <TinyAlpacaServer.h>
#else
#include "TinyAlpacaServer.h"
#endif

using alpaca::Literal;

constexpr char buffer1[] PROGMEM = "abc";

constexpr Literal literal1(buffer1);

void setup() {
  // Setup serial, wait for it to be ready so that our logging messages can be
  // read.
  Serial.begin(9600);
  // Wait for serial port to connect, or at least some minimum amount of time
  // (TBD), else the initial output gets lost.
  while (!Serial) {
  }
}

void loop() {
  delay(1000);

  Serial.print("literal1: ");
  literal1.printTo(Serial);
  Serial.println();
  Serial.println();

  Serial.print("literal2: ");
  literal2.printTo(Serial);
  Serial.println();
  Serial.println();

  Serial.print("JSON literal1: ");
  literal1.printJsonEscapedTo(Serial);
  Serial.println();
  Serial.println();

  Serial.print("JSON literal2: ");
  literal2.printJsonEscapedTo(Serial);
  Serial.println();
  Serial.println();
}
