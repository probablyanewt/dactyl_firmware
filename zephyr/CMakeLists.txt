cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
include_directories(/usr/include)
project(dactyl_firmware)
# add_definitions( -DPACTF_SUPPRESS )

FILE(GLOB app_sources ../src/keyboard.c*)
target_sources(app PRIVATE ${app_sources})
