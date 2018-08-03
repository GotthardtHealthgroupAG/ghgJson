find_package(Qt5Test)

add_executable(QJsonDocumentTest
  QJsonDocumentTest.cpp
)
target_include_directories(QJsonDocumentTest PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib/ttmath-0.9.3
  ${PROJECT_BINARY_DIR}
)
target_link_libraries(QJsonDocumentTest
  Qt5::Test
  ghgJson
)
