# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/live_spectrogram_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/live_spectrogram_autogen.dir/ParseCache.txt"
  "live_spectrogram_autogen"
  )
endif()
