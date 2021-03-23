#include "extras/host/ethernet3/dhcp_class.h"
#ifdef ARDUINO
#include <Arduino.h>
#include <Ethernet3.h>
#include <utils/ip_device.h>
#else
#include "extras/host/ethernet3/ethernet3.h"
#include "utils/addresses.h"
#include "utils/ip_device.h"
#endif

DhcpClass dhcp;
alpaca::IpDevice ip_device;

void announceFailure(const char* message) {
  while (true) {
    Serial.println(message);
    delay(1000);
  }
}

void announceAddresses() {
  Serial.println();
  alpaca::MacAddress mac;
  Ethernet.macAddress(mac.mac);
  Serial.print("MAC: ");
  Serial.println(mac);
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println();
}

void setup() {
  // Setup serial, wait for it to be ready so that our logging messages can be
  // read.
  Serial.begin(9600);
  // Wait for serial port to connect, or at least some minimum amount of time
  // (TBD), else the initial output gets lost.
  while (!Serial) {
  }

  //////////////////////////////////////////////////////////////////////////////
  // Initialize networking.
  Ethernet.setDhcp(&dhcp);
  alpaca::Mega2560Eth::setup_w5500();
  // Provide an "Organizationally Unique Identifier" which will be used as the
  // first 3 bytes of the MAC addresses generated; this means that all boards
  // running this sketch will share the first 3 bytes of their MAC addresses,
  // which may help with locating them.
  alpaca::OuiPrefix oui_prefix(0x53, 0x57, 0x76);
  if (!ip_device.setup(&oui_prefix)) {
    announceFailure("Unable to initialize networking!");
  }

  announceAddresses();

  for (int sock_num = 0; sock_num < Ethernet._maxSockNum; ++sock_num) {
    Serial.print("Socket ");
    Serial.print(sock_num);
    Serial.print(" status: ");
    EthernetClient client(sock_num);
    auto status = client.status();
    switch (status) {
      case SnSR::CLOSED:
        Serial.println("CLOSED");
        break;
      case SnSR::INIT:
        Serial.println("INIT");
        break;
      case SnSR::LISTEN:
        Serial.println("LISTEN");
        break;
      case SnSR::SYNSENT:
        Serial.println("SYNSENT");
        break;
      case SnSR::SYNRECV:
        Serial.println("SYNRECV");
        break;
      case SnSR::ESTABLISHED:
        Serial.println("ESTABLISHED");
        break;
      case SnSR::FIN_WAIT:
        Serial.println("FIN_WAIT");
        break;
      case SnSR::CLOSING:
        Serial.println("CLOSING");
        break;
      case SnSR::TIME_WAIT:
        Serial.println("TIME_WAIT");
        break;
      case SnSR::CLOSE_WAIT:
        Serial.println("CLOSE_WAIT");
        break;
      case SnSR::LAST_ACK:
        Serial.println("LAST_ACK");
        break;
      case SnSR::UDP:
        Serial.println("UDP");
        break;
      case SnSR::IPRAW:
        Serial.println("IPRAW");
        break;
      case SnSR::MACRAW:
        Serial.println("MACRAW");
        break;
      case SnSR::PPPOE:
        Serial.println("PPPOE");
        break;
      default:
        Serial.println(status);
    }
  }
}

void loop() {
  auto dhcp_check = ip_device.maintain_dhcp_lease();
  switch (dhcp_check) {
    case DHCP_CHECK_NONE:
      break;
    case DHCP_CHECK_RENEW_FAIL:
      Serial.println("DHCP_CHECK_RENEW_FAIL: Unable to renew the DHCP lease.");
      delay(1000);
      return;
    case DHCP_CHECK_RENEW_OK:
      Serial.println("DHCP_CHECK_RENEW_OK");
      return;
    case DHCP_CHECK_REBIND_FAIL:
      Serial.println("DHCP_CHECK_REBIND_FAIL: Unable to renew the DHCP lease.");
      delay(1000);
      return;
    case DHCP_CHECK_REBIND_OK:
      Serial.println("DHCP_CHECK_REBIND_OK");
      announceAddresses();
      return;
    default:
      Serial.print("Unexpected result from maintain_dhcp_lease: ");
      Serial.println(dhcp_check);
  }
}
