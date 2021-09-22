load("@rules_cc//cc:defs.bzl", "cc_test")

cc_library(
    name = "generic_ode_model",
    srcs = [
            "generic_ode_model.cc",
            ],
    hdrs = [
            "generic_ode_model.h",
            ],
    visibility = ["//visibility:public"],
)

test_suite(
    name = "control_toolbox_tests",
    tests = [
           ],
)

cc_test(
    name = "generic_ode_model_test",
    size = "small",
    srcs = ["generic_ode_model_test.cc",],
    deps = ["@com_google_googletest//:gtest_main",
            "//:generic_ode_model"],
)

