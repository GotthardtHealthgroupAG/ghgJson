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
add_test(NAME QJsonDocumentTest COMMAND QJsonDocumentTest)


add_executable(QJsonObjectTest
  QJsonObjectTest.cpp
)
target_include_directories(QJsonObjectTest PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib/ttmath-0.9.3
  ${PROJECT_BINARY_DIR}
)
target_link_libraries(QJsonObjectTest
  Qt5::Test
  ghgJson
)
add_test(NAME QJsonObjectTest COMMAND QJsonObjectTest)
