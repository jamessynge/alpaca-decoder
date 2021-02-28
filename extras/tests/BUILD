# Contains tests of code that is in the src directory, to be executed on host.
# We don't put the tests there because otherwise the Arduino IDE tries to treat
# them as code to be compiled for the target microcontroller.

cc_test(
    name = "config_test",
    srcs = ["config_test.cc"],
    deps = [
        ":config",
        ":platform",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "counting_bitbucket_test",
    srcs = ["counting_bitbucket_test.cc"],
    deps = [
        ":counting_bitbucket",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "json_encoder_test",
    srcs = ["json_encoder_test.cc"],
    deps = [
        ":counting_bitbucket",
        ":json_encoder",
        ":test_utils",
        "//absl/strings",
        "//core:logging",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "literal_test",
    srcs = ["literal_test.cc"],
    deps = [
        ":literal",
        ":test_utils",
        "//absl/strings",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "literal_token_test",
    srcs = ["literal_token_test.cc"],
    deps = [
        ":literal_token",
        ":platform",
        ":string_view",
        ":test_utils",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "literals_test",
    srcs = ["literals_test.cc"],
    deps = [
        ":literals",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "pgmspace_test",
    srcs = ["pgmspace_test.cc"],
    deps = [
        ":pgmspace",
        "//absl/strings",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "print_test",
    srcs = ["print_test.cc"],
    deps = [
        ":print",
        ":test_utils",
        "//googletest:gunit_main",
    ],
)

cc_library(
    name = "request_decoder_listener_mock",
    hdrs = ["request_decoder_listener_mock.h"],
    deps = [
        ":request_decoder_listener",
        "//googletest:gunit_headers",
    ],
)

cc_test(
    name = "request_decoder_test",
    timeout = "short",
    srcs = ["request_decoder_test.cc"],
    deps = [
        ":alpaca_request",
        ":decoder_constants",
        ":request_decoder",
        ":request_decoder_listener",
        ":request_decoder_listener_mock",
        ":string_view",
        "//absl/flags:flag",
        "//absl/strings",
        "//core:logging",
        "//googletest:gunit_main",
    ],
)

cc_test(
    name = "string_view_test",
    srcs = ["string_view_test.cc"],
    deps = [
        ":config",
        ":string_view",
        "//core:logging",
        "//googletest:gunit_main",
    ],
)

cc_library(
    name = "test_utils",
    hdrs = ["test_utils.h"],
    deps = [":print"],
)