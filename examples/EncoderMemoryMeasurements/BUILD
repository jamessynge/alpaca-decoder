# With Arduino Builder, can be used to measure the amount of memory
# required when various objects/code is referenced by the sketch.

cc_binary(
    name = "encoder_memory_measurements",
    srcs = ["EncoderMemoryMeasurements.ino.cc"],
    deps = [
        "//extras/host/arduino",
        "//extras/host/arduino:arduino_main",
        "//src:TinyAlpacaServer",
    ],
)
