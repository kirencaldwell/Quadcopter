load("@rules_cc//cc:defs.bzl", "cc_test", "cc_binary", "cc_library")

cc_library(
    name = "simulation",
    srcs = [
            "quadcopter_model.cc",
            "gyroscope_model.cc",
            "simulation_module.cc",
            "sensor_module.cc",
            "gyroscope_module.cc",
            "accelerometer_module.cc",
            ],
    hdrs = [
            "quadcopter_model.h",
            "gyroscope_model.h",
            "simulation_module.h",
            "sensor_module.h",
            "gyroscope_module.h",
            "accelerometer_module.h",
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
        name = "dynamics_test",
        size = "small",
        srcs = ["quadcopter_model_test.cc",],
        deps = ["@com_google_googletest//:gtest_main",
                "//Onboard:onboard",
                "//Simulation:simulation",
                ],
)

