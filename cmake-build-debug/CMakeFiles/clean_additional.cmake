# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/irc-client_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/irc-client_autogen.dir/ParseCache.txt"
  "irc-client_autogen"
  )
endif()
