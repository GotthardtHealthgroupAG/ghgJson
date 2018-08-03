cmake_minimum_required(VERSION 3.9)
project(ghgJson)
set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Enable/Disable unit tests for the qjson library." on)

set(CMAKE_AUTOMOC ON)

include(GenerateExportHeader)
find_package(Qt5Core)

add_library(ghgJson SHARED
  include/ghgJson/QDecimal.h
  src/qjson.cpp src/qjson_p.h
  src/qjsonarray.cpp include/ghgJson/qjsonarray.h
  src/qjsondocument.cpp include/ghgJson/qjsondocument.h
  src/qjsonobject.cpp include/ghgJson/qjsonobject.h
  src/qjsonparser.cpp src/qjsonparser_p.h
  src/qjsonvalue.cpp include/ghgJson/qjsonvalue.h
  src/qjsonwriter.cpp src/qjsonwriter_p.h
)

generate_export_header(ghgJson EXPORT_FILE_NAME)

target_include_directories(ghgJson PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib/ttmath-0.9.3
  ${PROJECT_BINARY_DIR}
)

target_link_libraries(ghgJson
  Qt5::Core
)

if (${BUILD_TESTS})
  add_subdirectory(tests)
endif()
