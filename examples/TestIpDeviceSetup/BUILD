# Sketch for testing that we can initialize the IpDevice (i.e. WIZnet W5500).

cc_binary(
    name = "TestIpDeviceSetup",
    srcs = ["TestIpDeviceSetup.ino.cc"],
    deps = [
        "//extras/host/arduino",
        "//extras/host/arduino:arduino_main",
        "//extras/host/ethernet3",
        "//src:TinyAlpacaServer",
    ],
)
