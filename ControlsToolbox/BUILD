load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "generic_model",
    srcs = [
            "generic_model.cc",
            "model_parameter.cc",
            ],
    hdrs = [
            "generic_model.h",
            "model_parameter.h",
            ],
    deps = [
            "//Utilities:math",
            "named_vector",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
        name = "named_vector",
        srcs = [
                "named_vector.cc",
        ],
        hdrs = [
                "named_vector.h",
        ],
        visibility = ["//visibility:public"],
)
cc_test(
        name = "named_vector_test",
        size = "small",
        srcs = ["named_vector_test.cc",],
        deps = ["@com_google_googletest//:gtest_main",
                "//ControlsToolbox:named_vector"],
)

test_suite(
    name = "control_toolbox_tests",
    tests = [
            "named_vector_test",
            "generic_model_test",
            "model_parameter_test",
           ],
)

cc_test(
    name = "model_parameter_test",
    size = "small",
    srcs = ["model_parameter_test.cc",],
    deps = ["@com_google_googletest//:gtest_main",
            "//ControlsToolbox:generic_model"],
)
cc_test(
    name = "generic_model_test",
    size = "small",
    srcs = ["generic_model_test.cc",],
    deps = ["@com_google_googletest//:gtest_main",
            "//ControlsToolbox:generic_model"],
)

