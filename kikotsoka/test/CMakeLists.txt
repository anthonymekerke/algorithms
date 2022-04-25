INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/src
  ${OPENXUM_WS_CPP_BINARY_DIR}/src)

LINK_DIRECTORIES()

ADD_EXECUTABLE(kikotsoka-cpp-test tests.cpp)

TARGET_LINK_LIBRARIES(kikotsoka-cpp-test kikotsoka)