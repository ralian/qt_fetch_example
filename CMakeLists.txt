cmake_minimum_required(VERSION 3.23)
project(qt_fetch_example VERSION 0.1)

include(FetchContent)
FetchContent_Declare(
  Qt6
  GIT_REPOSITORY https://github.com/qt/qtbase.git
  GIT_TAG        v6.10.1
  SYSTEM EXCLUDE_FROM_ALL OVERRIDE_FIND_PACKAGE
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(X11 REQUIRED GLOBAL COMPONENTS)
  set(QT_FEATURE_xcb ON)
  set(Qt6_MOC_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/libexec/moc)
  set(Qt6_PLATFORM_PLUGIN Qt6::QXcbIntegrationPlugin)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(Qt6_MOC_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/bin/moc)
  set(Qt6_PLATFORM_PLUGIN Qt6::QCocoaIntegrationPlugin)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(Qt6_MOC_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/bin/moc.exe)
  set(Qt6_PLATFORM_PLUGIN Qt6::QWindowsIntegrationPlugin)
endif()

find_package(Qt6 REQUIRED COMPONENTS Gui)

add_subdirectory(example_1)
