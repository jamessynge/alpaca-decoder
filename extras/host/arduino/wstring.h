#ifndef TINY_ALPACA_SERVER_EXTRAS_HOST_ARDUINO_WSTRING_H_
#define TINY_ALPACA_SERVER_EXTRAS_HOST_ARDUINO_WSTRING_H_

// This provides just enough of WString.h (from Arduino) for my needs when
// testing on host.

#include "extras/host/arduino/pgmspace.h"

// There is no actually definition of class __FlashStringHelper, it is just used
// to provide a distinct type for a pointer to a char array stored in flash.
class __FlashStringHelper;
#define F(string_literal) \
  (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

#endif  // TINY_ALPACA_SERVER_EXTRAS_HOST_ARDUINO_WSTRING_H_
