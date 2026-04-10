cmake_minimum_required(VERSION 3.22)
project(NewAudioProject VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JUCE_DIR "" CACHE PATH "Path to JUCE checkout")
if (NOT EXISTS "${JUCE_DIR}/CMakeLists.txt")
  message(FATAL_ERROR "Set JUCE_DIR to your JUCE path, e.g. -DJUCE_DIR=/path/to/JUCE")
endif()

add_subdirectory("${JUCE_DIR}" "${CMAKE_BINARY_DIR}/JUCE")

set(PRODUCT_DISPLAY_NAME "ProjectName")
set(PRODUCT_BUNDLE_ID "com.yourcompany.projectname")

juce_add_plugin(NewAudioProject
  COMPANY_NAME "Your Company"
  IS_SYNTH TRUE
  NEEDS_MIDI_INPUT TRUE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  EDITOR_WANTS_KEYBOARD_FOCUS TRUE
  PLUGIN_MANUFACTURER_CODE YCmp
  PLUGIN_CODE NPrj
  FORMATS VST3 AU AAX Standalone
  PRODUCT_NAME "${PRODUCT_DISPLAY_NAME}"
  BUNDLE_ID "${PRODUCT_BUNDLE_ID}"
  AAX_COPY_DIR "${CMAKE_BINARY_DIR}/AAX-Test"
  COPY_PLUGIN_AFTER_BUILD TRUE
)

juce_generate_juce_header(NewAudioProject)

file(GLOB_RECURSE SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.mm"
)

target_sources(NewAudioProject PRIVATE ${SOURCE_FILES})

target_compile_definitions(NewAudioProject PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0
  JUCE_DISPLAY_SPLASH_SCREEN=0
  JUCE_REPORT_APP_USAGE=0
  JUCE_MODAL_LOOPS_PERMITTED=1
  JUCE_DONT_DECLARE_PROJECTINFO=1
)

target_link_libraries(NewAudioProject PRIVATE
  juce::juce_audio_basics
  juce::juce_audio_devices
  juce::juce_audio_formats
  juce::juce_audio_processors
  juce::juce_audio_utils
  juce::juce_dsp
  juce::juce_core
  juce::juce_data_structures
  juce::juce_events
  juce::juce_graphics
  juce::juce_gui_basics
  juce::juce_gui_extra
)
