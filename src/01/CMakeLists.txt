set(CURRENT ${CMAKE_CURRENT_SOURCE_DIR})

message(${CURRENT})

add_executable(hello ${CURRENT}/hello.cpp)
target_link_libraries(hello pthread) 