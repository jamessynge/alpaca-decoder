# Provides utility methods and classes, such as PrintCharJsonEscaped and StatusOr
# which aren't necessarily specific to Alpaca, but could be useful in any Arduino
# sketch.

cc_library(
    name = "any_string",
    srcs = ["any_string.cc"],
    hdrs = ["any_string.h"],
    deps = [
        ":literal",
        ":platform",
        ":string_view",
    ],
)

cc_library(
    name = "array",
    hdrs = ["array.h"],
    deps = [":platform"],
)

cc_library(
    name = "connection",
    srcs = ["connection.cc"],
    hdrs = ["connection.h"],
    deps = [
        ":platform",
        ":platform_ethernet",
    ],
)

cc_library(
    name = "counting_bitbucket",
    hdrs = ["counting_bitbucket.h"],
    deps = [
        ":platform",
    ],
)

cc_library(
    name = "escaping",
    srcs = ["escaping.cc"],
    hdrs = ["escaping.h"],
    deps = [
        ":logging",
        ":platform",
    ],
)

cc_library(
    name = "json_encoder",
    srcs = ["json_encoder.cc"],
    hdrs = ["json_encoder.h"],
    deps = [
        ":any_string",
        ":counting_bitbucket",
        ":literal",
        ":platform",
    ],
)

cc_library(
    name = "literal",
    srcs = ["literal.cc"],
    hdrs = ["literal.h"],
    deps = [
        ":escaping",
        ":logging",
        ":platform",
    ],
)

cc_library(
    name = "literal_token",
    hdrs = ["literal_token.h"],
    deps = [
        ":literal",
        ":platform",
        ":string_compare",
        ":string_view",
    ],
)

cc_library(
    name = "logging",
    hdrs = ["logging.h"],
    deps = ["//core:logging"],
)

cc_library(
    name = "platform",
    hdrs = ["platform.h"],
    deps = [
        ":arduino",
        ":pgmspace",
        ":print",
        ":stream",
    ],
)

cc_library(
    name = "platform_ethernet",
    hdrs = ["platform_ethernet.h"],
    deps = [
        ":client",
        ":host_sockets",
        ":platform",
    ],
)

cc_library(
    name = "platform_ethernet_cc",
    srcs = ["platform_ethernet.cc"],
    hdrs = ["platform_ethernet.h"],
    deps = [
        ":client",
        ":host_sockets",
        ":platform",
    ],
)

cc_library(
    name = "printable_str_cat",
    srcs = ["printable_str_cat.cc"],
    hdrs = ["printable_str_cat.h"],
    deps = [
        ":any_string",
        ":literal",
        ":platform",
        ":print",
        ":string_view",
    ],
)

cc_library(
    name = "server_connection_base",
    srcs = ["server_connection_base.cc"],
    hdrs = ["server_connection_base.h"],
    deps = [
        ":connection",
        ":host_sockets",
        ":logging",
        ":platform",
        ":platform_ethernet_cc",
    ],
)

cc_library(
    name = "status",
    hdrs = ["status.h"],
    deps = [
        ":platform",
    ],
)

cc_library(
    name = "status_or",
    hdrs = ["status_or.h"],
    deps = [
        ":logging",
        ":platform",
        ":status",
    ],
)

cc_library(
    name = "string_compare",
    srcs = ["string_compare.cc"],
    hdrs = ["string_compare.h"],
    deps = [
        ":literal",
        ":platform",
        ":string_view",
    ],
)

cc_library(
    name = "string_view",
    srcs = [
        "string_view.cc",
    ],
    hdrs = [
        "string_view.h",
    ],
    deps = [
        ":escaping",
        ":logging",
        ":platform",
        "//absl/strings",
    ],
)

cc_library(
    name = "tiny_string",
    hdrs = ["tiny_string.h"],
    deps = [
        ":logging",
        ":platform",
    ],
)