// This Arduino Sketch demonstrates how to use Tiny Alpaca Server to respond to
// ASCOM Alpaca requests.
//
// TODO(jamessynge): Add more details about how this demo works.
//
// * On first execution alpaca::IpDevice will generate a random MAC address and
//   a default link-local IP address, and store those in EEPROM for later use.
//
// And on each run:
//
// * Uses DHCP to get an IP address, and falls back to using the IP address
//   stored in EEPROM if necessary.
//
// * If assigned an address via DHCP, keeps the DHCP lease alive over time.
//
// * Handles Alpaca Discovery Protocol messages.
//
// * Provides an HTTP server at the specified port (80 in this demo) that
//   decodes ASCOM Alpaca (HTTP) management and device API requests; the server
//   detects malformed and unsupported requests, for which it returns errors.
//
// * Handles /management/* requests using statically provided information about
//   the server and the devices.
//
// * Handles /setup requests with a simple fixed HTML response.
//   TODO(jamessynge): Improve on this.
//
// * Delegates to registered handlers for valid requests of the form:
//
//       /api/v1/{device_type}/{device_number}/{method}
//       /setup/v1/{device_type}
//
// * Provides methods for handlers for sending OK and error responses, including
//   measuring the size of the JSON body without having to allocate memory for
//   it.
//
// Author: james.synge@gmail.com

#include <Arduino.h>
#include <TinyAlpacaServer.h>

#include "dht22_handler.h"

using ::alpaca::DeviceInterface;

// Define some literals, which get stored in PROGMEM (in the case of AVR chips).
// TODO(jamessynge): Add support for storing much of this in EEPROM or on an
// SD Card.
TAS_DEFINE_LITERAL(ServerName,
                   "Our Spiffy Weather Box, based on Tiny Alpaca Server");
TAS_DEFINE_LITERAL(Manufacturer, "Friends of AAVSO & ATMoB");
TAS_DEFINE_LITERAL(ManufacturerVersion,
                   "9099c8af5796a80137ce334713a67a718fd0cd3f");
TAS_DEFINE_LITERAL(DeviceLocation, "Mittleman Observatory, Westford, MA");

// For responding to /management/v1/description.
// Note that this is using C++ 20's designated initializers, which shouldn't be
// available for Arduino, which claims to use C++ 11, but it works.
constexpr alpaca::ServerDescription kServerDescription{
    .server_name = ServerName(),
    .manufacturer = Manufacturer(),
    .manufacturer_version = ManufacturerVersion(),
    .location = DeviceLocation(),
};

static Dht22Handler dht_handler;  // NOLINT

static DeviceInterface* kDevices[] = {&dht_handler};

static constexpr uint16_t kHttpPort = 80;
static DhcpClass dhcp;
static alpaca::IpDevice ip_device;
static alpaca::TinyAlpacaServer tiny_alpaca_server(  // NOLINT
    kHttpPort, kServerDescription, kDevices);

void announceAddresses() {
  Serial.println();
  alpaca::IpDevice::PrintNetworkAddresses();
  Serial.println();
}

void announceFailure(const char* message) {
  while (true) {
    Serial.println(message);
    delay(1000);
  }
}

void setup() {
  // Setup serial, wait for it to be ready so that our logging messages can be
  // read. Note that the baud rate is meaningful on boards that do true serial,
  // while those microcontrollers with builtin USB likely don't rate limit
  // because there isn't a need.
  Serial.begin(57600);

  // Wait for serial port to connect, or at least some minimum amount of time
  // (TBD), else the initial output gets lost. Note that this isn't true for all
  // Arduino-like boards: some reset when the Serial Monitor connects, so we
  // almost always get the initial output.
  while (!Serial) {
  }

  //////////////////////////////////////////////////////////////////////////////
  // Initialize networking.
  Ethernet.setDhcp(&dhcp);
  alpaca::Mega2560Eth::SetupW5500();

  // Provide an "Organizationally Unique Identifier" which will be used as the
  // first 3 bytes of the MAC addresses generated; this means that all boards
  // running this sketch will share the first 3 bytes of their MAC addresses,
  // which may help with locating them.
  alpaca::OuiPrefix oui_prefix(0x53, 0x75, 0x76);
  if (!ip_device.InitializeNetworking(&oui_prefix)) {
    announceFailure("Unable to initialize networking!");
  }
  announceAddresses();
  tiny_alpaca_server.Initialize();
}

// For now only supporting one request at a time. Unless there are multiple
// clients, and some clients are slow to write requests or read responses,
// this shouldn't be a problem.
// static AlpacaRequest request;

void loop() {
  auto dhcp_check = ip_device.MaintainDhcpLease();
  switch (dhcp_check) {
    case DHCP_CHECK_NONE:
    case DHCP_CHECK_RENEW_OK:
      break;
    case DHCP_CHECK_RENEW_FAIL:
      Serial.println("DHCP_CHECK_RENEW_FAIL: Unable to renew the DHCP lease.");
      delay(1000);
      return;
    case DHCP_CHECK_REBIND_FAIL:
      Serial.println("DHCP_CHECK_REBIND_FAIL: Unable to get a new DHCP lease.");
      delay(1000);
      return;
    case DHCP_CHECK_REBIND_OK:
      announceAddresses();
      break;
    default:
      Serial.print("Unexpected result from MaintainDhcpLease: ");
      Serial.println(dhcp_check);
  }
  tiny_alpaca_server.PerformIO();
}
