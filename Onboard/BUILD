load("@rules_cc//cc:defs.bzl", "cc_test", "cc_binary", "cc_library")

cc_library(
    name = "onboard",
    srcs = [
            "controller.cc",
            "controls_module.cc",
            "guidance_module.cc",
            "telemetry_logging_module.cc",
            ],
    hdrs = [
            "controller.h",
            "controls_module.h",
            "guidance_module.h",
            "telemetry_logging_module.h",
            "sensor_module.h",
            ],
    deps = [
            "//ControlsToolbox:generic_ode_model",
            "//Utilities:math",
            "@ConcurrentModuleFramework//src:modules",
            ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "controller_test",
    size = "small",
    srcs = ["controller_test.cc",],
    deps = ["@com_google_googletest//:gtest_main",
            "//ControlsToolbox:generic_ode_model",
            "//Onboard:onboard",
            ],
)
