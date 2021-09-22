load("@rules_cc//cc:defs.bzl", "cc_test", "cc_binary", "cc_library")


cc_binary(
    name = "main",
    srcs = [
            "main.cc",
            ],
    deps = [
            "@ConcurrentModuleFramework//src:modules",
            "//Simulation:simulation",
            "//Onboard:onboard",
            ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "quadcopter_test",
    srcs = ["quadcopter_test.cc",],
    deps = ["@com_google_googletest//:gtest_main",
            "//Onboard:onboard",
            "//Simulation:simulation",
            "@ConcurrentModuleFramework//src:modules",
            ],
)